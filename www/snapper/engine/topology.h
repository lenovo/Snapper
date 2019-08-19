//---------------------------------------------------------------------
// <copyright file="topology.h" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once

#include <algorithm>
#include <string.h>

using namespace std;

namespace snapper { namespace service
{

#define T_EDM_TYPE_PRIMITIVE    "Primitive Type."
#define T_EDM_TYPE_DEFINITION   "Type Definition."
#define T_EDM_TYPE_COLLECTION   "Collection Type."
#define T_EDM_TYPE_COMPLEX      "Complex Type."
#define T_EDM_TYPE_ENUM         "Enum Type."
#define T_EDM_TYPE_ENTITY       "Entity Type."
#define T_EDM_TYPE_NAVIGATION   "Navigation Type."
#define T_EDM_TYPE_NAVIGATION_E   "Navigation Type.Entity"
#define T_EDM_TYPE_NAVIGATION_C   "Navigation Type.Collection"
#define T_EDM_TYPE_OPERATION    "Operation Type."
#define T_EDM_TYPE_UNKNOWN      "Unknown Type."


class ResourceTopology
{
public:
    ResourceTopology(std::string p, std::string seg, std::string c, std::string key = "", int exp = 1): path(p), segname(seg), classname(c), acc_key(key), expanded(exp)
    {
         //std::cout << p << "," << seg << " (" << c << ")" << std::endl;
    }
	std::string path;//parent path of the node
	std::string segname;//property/node_id name
	std::string classname;

    std::string acc_key;
    std::vector< std::shared_ptr<ResourceTopology> > subnodes;
    int expanded; // can auto-expand like navigation property. it's false when the node is primitive, enum, complex or not implemented resource

    static bool topology_created;

public:
    static std::map<std::string, std::string > url_topology;
    static void build_topology();
    static std::shared_ptr<std::string> search_url(std::string acckey);
    static std::shared_ptr<std::string> search_url(std::string acckey, std::string refresh_classname);
    static std::shared_ptr<std::string> search_accessor(std::string url);
    static void update_topology(std::string classname);

    static void topo_resource_gen_recur( std::shared_ptr<ResourceTopology> inst);
    static void traverse_resource_topo_tree( std::shared_ptr<ResourceTopology> root);
    static void update_resource_node( std::shared_ptr<ResourceTopology> node, std::string classname);
    static bool blacklist(std::string classname);
    static bool emptyroot();
};






}}
