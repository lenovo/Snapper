//---------------------------------------------------------------------
// <copyright file="ComputerSystem.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/ComputerSystem.h"
#include <www/engine/rf_debug.h>
#include <www/engine/topology.h>
#include "datainf/DataInterfaceMgr.h"
#include "class/ClassCommon.h"
#include <unistd.h>


using namespace snapper::service;

namespace snapper { namespace providers 
{

std::shared_ptr<memid_acckey_map> ComputerSystem::getlist_memid_acckey(std::string containing_path)
{
    std::shared_ptr<memid_acckey_map> list = std::make_shared<memid_acckey_map>();
    std::vector<string> m;
    int rc = DataInterfaceMgr::mockupMemberList(containing_path, m);

    for(int i = 0; i < m.size(); i++)
    {
        (*list)[m[i]] = std::string(m[i])+"@"+"ComputerSystem";
    }
    return list;
}

void ComputerSystem::build_all_objs(const string oid, bson::BSONObj & dataobjs)
{
    std::shared_ptr<std::string> uri;
    std::string accessor_key = "";
    std::shared_ptr< memid_acckey_map > idlist = nullptr;
    bson::BSONArrayBuilder pcidevs;
    bson::BSONArrayBuilder pcifuns;

    // pcie function/device
    idlist = getlist_memid_acckey_fromclass("PCIeFunction");
    if (idlist != nullptr) {
        for (auto it=idlist->begin();it != idlist->end();++it) {
            accessor_key = it->second;
            uri = ResourceTopology::search_url(accessor_key);
            if(uri != nullptr)
                pcifuns.append(BSON(ODATA_ID << uri->c_str()));
        }
    }
    else
        RF_PRINT_DBG("Get no list from PCIeFunction\n");
    setobj("PCIeFunctions", MAKE_BSON_OBJ("PCIeFunctions", pcifuns.arr()));


    idlist = getlist_memid_acckey_fromclass("PCIeDevice");
    if (idlist != nullptr) {
        for (auto it=idlist->begin();it != idlist->end();++it) {
            accessor_key = it->second;
            uri = ResourceTopology::search_url(accessor_key);
            if(uri != nullptr)
                pcidevs.append(BSON(ODATA_ID << uri->c_str()));
        }
    }
    else
        RF_PRINT_DBG("Get no list from PCIeDevice\n");
    setobj("PCIeDevices", MAKE_BSON_OBJ("PCIeDevices", pcidevs.arr()));        

    setobj("SystemType",         MAKE_BSON_OBJ("SystemType", "Physical"));

    //Links
    set_Links_arr_prop("Chassis", "Chassis");

    set_Links_arr_prop("Manager", "ManagedBy");

    set_Links_arr_prop("PowerSupply", "PoweredBy");

    set_Links_arr_prop("Fan", "CooledBy");

    set_Links_arr_prop("Endpoint", "Endpoints");

    set_Links_arr_prop("ResourceBlock", "ResourceBlocks");


    // data objects
    setobj( "SKU",         MAKE_BSON_OBJ("SKU", dataobjs.getStringField("SKU")) );
    setobj( "SerialNumber",         MAKE_BSON_OBJ("SerialNumber", dataobjs.getStringField("SerialNumber")) );
    setobj( "Model",         MAKE_BSON_OBJ("Model", dataobjs.getStringField("Model")) );
    setobj( "UUID",         MAKE_BSON_OBJ("UUID", dataobjs.getStringField("UUID")) );
    setobj( "Manufacturer",         MAKE_BSON_OBJ("Manufacturer", "Lenovo"));
    setobj( "HostName",         MAKE_BSON_OBJ("HostName", dataobjs.getStringField("HostName")) );
    setobj( "BiosVersion",         MAKE_BSON_OBJ("BiosVersion", dataobjs.getStringField("BiosVersion")) );
    setobj( "SystemType",         MAKE_BSON_OBJ("SystemType", MAKE_ENUM_STRING(SystemType_Physical)) );
    setobj( "PowerState",         MAKE_BSON_OBJ("PowerState", dataobjs.getStringField("PowerState")) );
    setobj( "IndicatorLED",         MAKE_BSON_OBJ("IndicatorLED", dataobjs.getStringField("IndicatorLED")) );
    setobj( "PartNumber",         MAKE_BSON_OBJ("PartNumber", dataobjs.getStringField("PartNumber")) );
    setobj( "AssetTag",         MAKE_BSON_OBJ("AssetTag", dataobjs.getStringField("AssetTag")) );
    setobj("HostWatchdogTimer",     MAKE_BSON_OBJ("HostWatchdogTimer", 
                                  BSON("FunctionEnabled" << false 
                                    << "WarningAction" << MAKE_ENUM_STRING(WatchdogWarningActions_None)
                                    << "TimeoutAction" << MAKE_ENUM_STRING(WatchdogTimeoutActions_PowerCycle)
                                    << "Status" << BSON( 
                                                      "State" << MAKE_ENUM_STRING(State_Enabled) 
                                                   << "Health" << MAKE_ENUM_STRING(Health_OK) 
                                                   << "HealthRollup" << MAKE_ENUM_STRING(Health_OK))
                                    )  )
           );
    setobj( "SimpleStorage",         MAKE_BSON_NULL_OBJ("SimpleStorage") );

    //complex
    setobj( "MemorySummary",    MAKE_BSON_OBJ("MemorySummary", BE_Object(dataobjs.getField("MemorySummary")) ));
    setobj( "ProcessorSummary",    MAKE_BSON_OBJ("ProcessorSummary", BE_Object(dataobjs.getField("ProcessorSummary")) ));
    setobj( "Boot",    MAKE_BSON_OBJ("Boot", BE_Object(dataobjs.getField("Boot")) ));
    setOemLenovoobj( "FrontPanelUSB",    MAKE_BSON_OBJ("FrontPanelUSB", BE_Object(dataobjs.getField("FrontPanelUSB")) ));

    set_status_obj(MAKE_ENUM_STRING(State_Enabled),
                       MAKE_ENUM_STRING(Health_OK),
                       MAKE_ENUM_STRING(Health_OK));
}

int ComputerSystem::handle_get(shared_ptr<::snapper::service::request_context> request)
{    
    //inovke at the BEGINNING for resource GET
    SnapperProvider::prepare_ResGet(request);


    //////////////////////////////////////////////////////
    // handle navigation property query under the resource
    const char* prop_in = is_navprop_query(request);
    if(prop_in)
        return navigation_property_query(request);

    bson::BSONObj dataobjs;
    DataInterfaceMgr::mockupGetData(request->get_raw_path(), dataobjs);
    //std::cout << dataobjs.jsonString(bson::Strict) << std::endl;

    //////////////////////////////////////////////////////
    // GET resource query
    string oid_in = request->get_raw_path();
    build_all_objs(oid_in, dataobjs);

    // invoke at the END for resource GET
    SnapperProvider::auto_build_objects_ResGET(oid_in);
    return RFRC_SUCCESS;
}

int ComputerSystem::navigation_property_query(shared_ptr<::snapper::service::request_context> request)
{
    std::string member_id;
    string oid_in = request->get_raw_path();
    const char* prop_in = is_navprop_query(request);
    std::shared_ptr< memid_acckey_map > idlist = nullptr;
    bson::BSONArrayBuilder arr_builder;
    bson::BSONObjBuilder obj_builder;

    string base_uri = oid_in.substr(0, oid_in.find_last_of("/"));
    bson::BSONObj dataobjs;
    DataInterfaceMgr::mockupGetData(base_uri, dataobjs);
    std::cout << "base uri ----- : " << base_uri << std::endl;


    switch (HASH_STRING(prop_in))
    {
        case "PCIeDevices"_HASH:
        {
            if ((idlist = getlist_memid_acckey_fromclass("PCIeDevice")) != nullptr) {
                for (auto it=idlist->begin();it != idlist->end();++it) {
                    member_id = "/" + it->first;
                    arr_builder << BSON(ODATA_ID << build_str(oid_in, member_id));
                }
            }
            else
                RF_PRINT_DBG("Get no list from PCIeFunction in ComputerSystem\n");

            obj_builder.append("value", arr_builder.arr());
            create_prop("value", std::make_shared<bson::BSONObj>(obj_builder.obj()) );
            break;
        }

        case "PCIeFunctions"_HASH:
        {
            if ((idlist = getlist_memid_acckey_fromclass("PCIeFunction")) != nullptr) {
                for (auto it=idlist->begin();it != idlist->end();++it) {
                    member_id = "/" + it->first;
                    arr_builder << BSON(ODATA_ID << build_str(oid_in, member_id));
                }
            }
            else
                RF_PRINT_DBG("Get no list from PCIeFunction in ComputerSystem\n");

            obj_builder.append("value", arr_builder.arr());
            create_prop("value", std::make_shared<bson::BSONObj>(obj_builder.obj()) );
            break;
        }
        default:
        {
            return RFRC_INVALID_PARAMS; //shouldn't come here
        }
    }

    return RFRC_SUCCESS;
}

int ComputerSystem::handle_post(shared_ptr<::snapper::service::request_context> request)
{

    return RFRC_METHOD_NOT_ALLOWED;
}

int ComputerSystem::handle_patch(shared_ptr<::snapper::service::request_context> request)
{  
    return RFRC_METHOD_NOT_ALLOWED;
}

int ComputerSystem::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int ComputerSystem::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}







REGISTER_PROVIDER(ComputerSystem)

}}

