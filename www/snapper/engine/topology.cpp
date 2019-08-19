//---------------------------------------------------------------------
// <copyright file="topology.cpp" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#include "bson/bson.h"
#include "bson/util/json.h"
#include "class/SnapperProvider.h"
#include "class/ClassCommon.h"

#include "topology.h"
#include "rf_engine_error.h"
#include "rf_debug.h"

#include <time.h>
#include <pthread.h>

#define ODATA_COUNT_CLASS  "ODataCount"
#define MEMBER_COUNT_PROP  "Members@odata.count"

using namespace ::std;
using namespace ::snapper::providers;
namespace snapper { namespace service
{
std::map<std::string, std::string > ResourceTopology::url_topology;
static std::shared_ptr<ResourceTopology> root_node = nullptr;
static pthread_mutex_t topology_lock=PTHREAD_MUTEX_INITIALIZER;
bool ResourceTopology::topology_created = false;

/*
recursion to generate all node
*/
void ResourceTopology::topo_resource_gen_recur( std::shared_ptr<ResourceTopology> inst)
{

    std::shared_ptr<SnapperProvider> cur_p =  ProviderObjectFactory::GetObject(inst->classname);
    if(cur_p == nullptr)
        return;
    std::map<const std::string, std::vector<std::string>> propmap = cur_p->get_property_class();

    std::map<std::string, std::vector<std::string> >::iterator it;
    for(it=propmap.begin();it!=propmap.end();++it)
    {
        std::string propname = it->first;
        std::vector<std::string> classtype = it->second;
        if(classtype.size() != 2) 
            continue;
        std::shared_ptr<SnapperProvider> sub_p = ProviderObjectFactory::GetObject(classtype[1]);

        if(classtype[0].compare(0, strlen(T_EDM_TYPE_NAVIGATION), T_EDM_TYPE_NAVIGATION) == 0 && sub_p != nullptr)
        { // currently we only check navigation property which are resource types
            if(cur_p->get_type() == Provider_Resource)
            {
                if(sub_p->get_type() == Provider_Resource && classtype[0].compare(T_EDM_TYPE_NAVIGATION_C) == 0)//current node Systems/1, child node PCIeFunctions of type Collection(PCIeFunction)
                {
                // Resource contains collection of Resource - Systems/1/PCIeFunctions like "Systems/1/PCIeFunctions/ob_1.00"  like OData.AutoExpandReferences
                    std::string newpath = inst->path + "/" + inst->segname;
                    std::string newacc_key = inst->acc_key + NO_KEY+classtype[1];

                    auto leafnode = std::make_shared<ResourceTopology>(newpath, propname, classtype[1], newacc_key); //use parent acckey
                    inst->subnodes.push_back(leafnode);//add leaf 1/PCIeFunctions

                    std::string containing_path = newpath + "/" + propname + " " + newacc_key;//path and accessor
                    std::shared_ptr<memid_acckey_map> idlist = sub_p->getlist_memid_acckey(containing_path);//PCIeFunction to get memberid and accessor key
                    if(idlist == nullptr)
                        continue;
                    for(auto it=idlist->begin();it != idlist->end();++it)
                    {
                        std::string memberid = it->first;
                        std::string accessor_key = it->second;

                        leafnode = std::make_shared<ResourceTopology>(newpath, (propname+"/"+memberid), classtype[1], accessor_key);
                        inst->subnodes.push_back(leafnode);//add leaf 1/PCIeFunctions/ob_1.00
                        // TODO if there's resource url under the child node to access? should continue recurse?
                    }
                    //std::cout << "resource collection(resource) - " << newpath << " " << propname << std::endl;
                }
                else if(sub_p->get_type() == Provider_Resource && classtype[0].compare(T_EDM_TYPE_NAVIGATION_E) == 0)//current node Systems/1, child node Bios
                {
                // Resource contains Resource  - Systems/1/Bios 
                    std::string newpath = inst->path + "/" + inst->segname;
                    auto node = std::make_shared<ResourceTopology>(newpath, propname, classtype[1], inst->acc_key + NO_KEY+classtype[1]);//use parent acckey

                    //std::cout << "resource resource(entity) - " << newpath << " " << propname << std::endl;
                    inst->subnodes.push_back(node);
                    topo_resource_gen_recur(node);
                }
                else if(sub_p->get_type() == Provider_ResourceCollection && classtype[0].compare(T_EDM_TYPE_NAVIGATION_E) == 0)//current node Chassis/1, child node NetworkAdapters of type NetworkAdapterCollection
                {
                // Resource contains ResourceCollection  - Chassis/1/NetworkAdapters
                    std::string newpath = inst->path + "/" + inst->segname;
                    auto node = std::make_shared<ResourceTopology>(newpath, propname, classtype[1], inst->acc_key + NO_KEY+classtype[1]);//parent acckey

                    //std::cout << "resource resourcecollection(entity) - " << newpath << " " << propname << std::endl;
                    inst->subnodes.push_back(node);
                    topo_resource_gen_recur(node);
                }
                else if(sub_p->get_type() == Provider_ReferenceableMember && classtype[0].compare(T_EDM_TYPE_NAVIGATION_C) == 0)//current node Chassis/1/Power, child node PowerControl of type Collection(PowerControl)
                {
                // Resource contains collection of ReferenceableMember - Chassis/1/Power#/PowerControl/0
                    std::string containing_path = inst->path + "/" + inst->segname + " " + inst->acc_key;//path and accessor
                    std::shared_ptr<memid_acckey_map> idlist = sub_p->getlist_memid_acckey(containing_path);//PowerControl to get memberid and accessor key
                    if(idlist == nullptr)
                        continue;

                    for(auto it=idlist->begin();it != idlist->end();++it)
                    {
                        std::string memberid = it->first;
                        std::string accessor_key = it->second;
                        std::string newpath = inst->path + "/" + inst->segname;

                        auto leafnode = std::make_shared<ResourceTopology>(newpath, ("#/"+propname+"/"+memberid), classtype[1], accessor_key);
                        inst->subnodes.push_back(leafnode);//add leaf Power#/PowerControl/0
                        //std::cout << "resource collection(referencemem) - " << newpath << " " << propname << "/" << memberid << std::endl;
                    }
                }
                else
                {
                    std::string newpath = inst->path + "/" + inst->segname;
                    auto leafnode = std::make_shared<ResourceTopology>(newpath, propname, classtype[1], inst->acc_key + NO_KEY+classtype[1]);//parent acckey
                    inst->subnodes.push_back(leafnode);
                }

            }
            else if(cur_p->get_type() == Provider_ResourceCollection)//current node Systems, child property Members of type Collection(ComputerSystem)
            {
                // ResourceCollection contains Resource  - Systems/1
                std::string containing_path = inst->path + "/" + inst->segname + " " + inst->acc_key;//path and accessor
                std::shared_ptr<memid_acckey_map> idlist = sub_p->getlist_memid_acckey(containing_path);//ComputerSystem to get memberid and accessor key

                // always add subnode of odata count for Members. it would be used by traverse to identify if the resource has sub-resource tree, specifically for ResourceCollection case
                std::string odatapath = inst->path + "/" + inst->segname;
                auto odata_leafnode = std::make_shared<ResourceTopology>(odatapath, MEMBER_COUNT_PROP, ODATA_COUNT_CLASS, inst->acc_key + NO_KEY+ODATA_COUNT_CLASS, 0);//parent acckey. it can't be expanded
                inst->subnodes.push_back(odata_leafnode);

                if(idlist == nullptr)
                    continue;

                for(auto it=idlist->begin();it != idlist->end();++it)
                {
                    std::string memberid = it->first;
                    std::string accessor_key = it->second;
                    std::string newpath = inst->path + "/" + inst->segname;

                    auto node = std::make_shared<ResourceTopology>(newpath, memberid, classtype[1], accessor_key);
                    //std::cout << "ResourceCollection - " << containing_path << " " << newpath << " " << memberid << std::endl;
                    inst->subnodes.push_back(node);
                    topo_resource_gen_recur(node);
                }
            }
            else if(cur_p->get_type() == Provider_ReferenceableMember)
            {
                // ReferenceableMember contains collcection of ReferenceableMember  -  TODO , PowerSupply -> collection of Redundancy
                std::string newpath = inst->path + "/" + inst->segname;
                auto node = std::make_shared<ResourceTopology>(newpath, propname, classtype[1], inst->acc_key + NO_KEY+classtype[1]);//parent acckey

                inst->subnodes.push_back(node);
                topo_resource_gen_recur(node);
            }

        }
        else //non-resource property or the resource is not implemented yet
        {
            std::string newpath = inst->path + "/" + inst->segname;
            auto leafnode = std::make_shared<ResourceTopology>(newpath, propname, classtype[1], inst->acc_key + NO_KEY+classtype[1], 0);//parent acckey. it can't be expanded as it isn't navigation property
            inst->subnodes.push_back(leafnode);
        }

    }

}
bool ResourceTopology::blacklist(std::string classname)
{
    if(classname.compare("JsonSchemaFile") == 0)
        return true;
    return false;
}

/*
recursion to access all subnode,store the result in global table 
which contains the URL and unique magic number to locate the URL
*/
void ResourceTopology::traverse_resource_topo_tree( std::shared_ptr<ResourceTopology> root)
{
    if(ProviderObjectFactory::GetObject(root->classname) == nullptr)// only print implemented resource
        return;

    bool isleaf = true;
    std::string url = root->path + "/" + root->segname;
    for(int i = 0; i < root->subnodes.size(); i++)
    {
        // case 1: Systems/1/LogServices/ has subnodes ActiveLog, StandardLog which also has subnode Entries
        if(root->subnodes[i]->subnodes.size() > 0)
            isleaf = false;

        // case 2: /redfish/v1/Tasks/ has subnodes Tasks when subnode Tasks has no member
        if(root->subnodes[i]->expanded)
            isleaf = false;

        // case 3: /redfish/v1/Systems/1/LogServices/ActiveLog/Entries/ has Members which autoexpand LogEntry
        if(root->subnodes[i]->segname.compare(MEMBER_COUNT_PROP) == 0 )
            isleaf = false;

    }
    //std::cout << "is leaf node " << isleaf << std::endl;

    /* need to follow Redfish.Uri
    if(!isleaf)//show suffix '/' if there's sub-resource tree under the node/url
        url += "/";
    */
    url_topology[url] = root->acc_key;
    if(blacklist(root->classname) == false)
        std::cout << url << "        [" << root->acc_key << "]" << std::endl;//can't use tracebuffer in recursion function

    for(int i = 0; i < root->subnodes.size(); i++)
        traverse_resource_topo_tree(root->subnodes[i]);
}
std::shared_ptr<std::string> ResourceTopology::search_url(std::string acckey)
{
    pthread_mutex_lock( &topology_lock ); 

    std::shared_ptr<std::string> ptr = nullptr;
    for(auto it=url_topology.begin();it != url_topology.end();++it)
    {
        if(it->second == acckey)
        {
            ptr = std::make_shared<std::string>(it->first);
            break;
        }
    }
    if(ptr == nullptr)
        RF_PRINT_WARN("URI for acckey %s not found, topology may be out of date! \n", acckey.c_str() );

    pthread_mutex_unlock( &topology_lock );

    return ptr;
}

/*in case topology cache is not updated as trigger code somehow missing or does not 
work, manually refresh topology by class
*/
std::shared_ptr<std::string> ResourceTopology::search_url(std::string acckey, std::string refresh_classname)
{
    std::shared_ptr<std::string> uri = search_url(acckey);
    if(uri == nullptr && refresh_classname.length())
    {
        RF_PRINT_WARN("refresh class %s, then retry searching URI for acckey %s\n", refresh_classname.c_str(), acckey.c_str() );
        update_topology(refresh_classname);
        uri = search_url(acckey);
    }
    return uri;
}

std::shared_ptr<std::string> ResourceTopology::search_accessor(std::string url)
{
    pthread_mutex_lock( &topology_lock ); 

    std::shared_ptr<std::string> ptr = nullptr;
    string uri_s = url;
    if(uri_s.at(uri_s.size()-1) == '/')
        uri_s.erase(uri_s.size()-1);

    if(url_topology.find(uri_s) != url_topology.end()) //try none suffix '/' first
        ptr = std::make_shared<std::string>(url_topology[uri_s]);
    else // try suffix '/' which contains sub resource tree
    {
        uri_s += "/";
        if(url_topology.find(uri_s) != url_topology.end())
            ptr = std::make_shared<std::string>(url_topology[uri_s]);
    }

    if(ptr == nullptr)
        RF_PRINT_WARN("acckey for URI %s not found, topology may be out of date! \n", url.c_str() );

    pthread_mutex_unlock( &topology_lock );

    return ptr;
}

void ResourceTopology::build_topology()
{
    pthread_mutex_lock( &topology_lock ); 

    root_node = std::make_shared<ResourceTopology>("", "redfish/v1", "ServiceRoot", NO_KEY "ServiceRoot");
    url_topology.clear();//build from clean table

    time_t t1 = time(NULL);
    topo_resource_gen_recur(root_node);
    traverse_resource_topo_tree(root_node);

    time_t t2 = time(NULL);
    RF_PRINT("==== Topology build cost %d secs ===\n", (int)(t2-t1));

    pthread_mutex_unlock( &topology_lock );
}

/*
recursion for subnode refresh
*/
void ResourceTopology::update_resource_node( std::shared_ptr<ResourceTopology> node, std::string classname)
{
    if(node == nullptr || ProviderObjectFactory::GetObject(node->classname) == nullptr)
        return;

    if(classname.compare(node->classname) == 0)
    {
        RF_PRINT("update class node: %s at %s %s\n", classname.c_str(), node->path.c_str(), node->segname.c_str());
        node->subnodes.clear();
        topo_resource_gen_recur(node);
        return;
    }

    for(int i = 0; i < node->subnodes.size(); i++)
        update_resource_node(node->subnodes[i], classname);
}

void ResourceTopology::update_topology(std::string classname)
{
    if(root_node == nullptr)//start with empty
        return;

    pthread_mutex_lock( &topology_lock ); 

    url_topology.clear();//build from clean table

    time_t t1 = time(NULL);
    update_resource_node(root_node, classname);
    traverse_resource_topo_tree(root_node);

    time_t t2 = time(NULL);
    RF_PRINT("==== Topology update cost %d secs ===\n", (int)(t2-t1));

    pthread_mutex_unlock( &topology_lock );
}

bool ResourceTopology::emptyroot()
{
    return (root_node == nullptr);
}


}}
