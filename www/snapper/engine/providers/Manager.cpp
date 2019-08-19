//---------------------------------------------------------------------
// <copyright file="Manager.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/Manager.h"
#include "datainf/DataInterfaceMgr.h"
#include <www/engine/topology.h>
#include <www/engine/rf_debug.h>
#include "class/ClassCommon.h"
#include "class/ProviderHelper.h"

using namespace snapper::service;

namespace snapper { namespace providers 
{
static string current_dategmt;
static int current_autodst;
static string current_dstspecial;
std::shared_ptr<memid_acckey_map> Manager::getlist_memid_acckey(std::string containing_path)
{
    std::shared_ptr<memid_acckey_map> list = std::make_shared<memid_acckey_map>();
    std::vector<string> m;
    int rc = DataInterfaceMgr::mockupMemberList(containing_path, m);

    for(int i = 0; i < m.size(); i++)
    {
        (*list)[m[i]] = std::string(m[i])+"@"+"Manager";
    }
    return list;

}


int Manager::handle_get(shared_ptr<::snapper::service::request_context> request)
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

    setobj( "UUID",         MAKE_BSON_OBJ("UUID", dataobjs.getStringField("UUID")) );
    setobj( "ServiceEntryPointUUID",         MAKE_BSON_OBJ("ServiceEntryPointUUID", dataobjs.getStringField("ServiceEntryPointUUID")) );
    setobj( "DateTimeLocalOffset",         MAKE_BSON_OBJ("DateTimeLocalOffset", dataobjs.getStringField("DateTimeLocalOffset")) );
    setobj( "AutoDSTEnabled",         MAKE_BSON_OBJ("AutoDSTEnabled",  false) );
    setobj( "FirmwareVersion",         MAKE_BSON_OBJ("FirmwareVersion", dataobjs.getStringField("FirmwareVersion")) );
    setobj( "PowerState",         MAKE_BSON_OBJ("PowerState", dataobjs.getStringField("PowerState")) );
    setobj( "DateTime",         MAKE_BSON_OBJ("DateTime", dataobjs.getStringField("DateTime")) );
    setobj( "ManagerType",         MAKE_BSON_OBJ("ManagerType", MAKE_ENUM_STRING(ManagerType_BMC)) );
    setobj( "Model",         MAKE_BSON_OBJ("Model", "Lenovo XClarity Controller") );

    setobj("LogServices", MAKE_BSON_LINK_NAV_OBJ("LogServices", "/redfish/v1/Systems/1/LogServices" ));//TODO


    setobj( "GraphicalConsole",         MAKE_BSON_OBJ("GraphicalConsole", BE_Object(dataobjs.getField("GraphicalConsole")) ) );
    setobj( "SerialConsole",         MAKE_BSON_OBJ("SerialConsole", BE_Object(dataobjs.getField("SerialConsole")) ) );
    setobj( "CommandShell",         MAKE_BSON_OBJ("CommandShell", BE_Object(dataobjs.getField("CommandShell")) ) );

    //Links
    set_Links_arr_prop("Chassis", "ManagerForChassis");
    set_Links_arr_prop("ComputerSystem", "ManagerForServers");

    set_status_obj(MAKE_ENUM_STRING(State_Enabled),
                       MAKE_ENUM_STRING(Health_OK),
                       MAKE_ENUM_STRING(Health_OK)); //build object for Staus    

    // invoke at the END for resource GET
    SnapperProvider::auto_build_objects_ResGET(oid_in);
    return RFRC_SUCCESS;
}

int Manager::navigation_property_query(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Manager::handle_post(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Manager::handle_patch(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Manager::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Manager::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}


REGISTER_PROVIDER(Manager);
}}

