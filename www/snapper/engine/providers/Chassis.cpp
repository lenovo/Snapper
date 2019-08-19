//---------------------------------------------------------------------
// <copyright file="Chassis.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/Chassis.h"
#include "datainf/DataInterfaceMgr.h"
#include <www/engine/topology.h>
#include <www/engine/rf_debug.h>
#include "class/ClassCommon.h"

using namespace snapper::service;

namespace snapper { namespace providers 
{

std::shared_ptr<memid_acckey_map> Chassis::getlist_memid_acckey(std::string containing_path)
{
    std::shared_ptr<memid_acckey_map> list = std::make_shared<memid_acckey_map>();
    std::vector<string> m;
    int rc = DataInterfaceMgr::mockupMemberList(containing_path, m);

    for(int i = 0; i < m.size(); i++)
    {
        (*list)[m[i]] = std::string(m[i])+"@"+"Chassis";
    }
    return list;

}


int Chassis::handle_get(shared_ptr<::snapper::service::request_context> request)
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

    //Links
    set_Links_arr_prop("ComputerSystem", "ComputerSystems");

    set_Links_arr_prop("Manager", "ManagedBy");//TODO

    set_Links_arr_prop("Manager", "ManagersInChassis");

    set_Links_arr_prop("PowerSupply", "PoweredBy");

    set_Links_arr_prop("Fan", "CooledBy");

    set_Links_arr_prop("PCIeDevice", "PCIeDevices");

    set_Links_arr_prop("Storage", "Storage");

    set_Links_arr_prop("Drive", "Drives");

    set_Links_arr_prop("ResourceBlock", "ResourceBlocks");

    setLinksobj("ContainedBy", MAKE_BSON_LINK_NAV_OBJ("ContainedBy", "/redfish/v1/Chassis/1" ));


    setobj( "ChassisType",         MAKE_BSON_OBJ("ChassisType", MAKE_ENUM_STRING(ChassisType_RackMount)) );
    setobj( "SKU",         MAKE_BSON_OBJ("SKU", dataobjs.getStringField("SKU")) );
    setobj( "SerialNumber",         MAKE_BSON_OBJ("SerialNumber", dataobjs.getStringField("SerialNumber")) );
    setobj( "Model",         MAKE_BSON_OBJ("Model", dataobjs.getStringField("Model")) );
    setobj( "Manufacturer",         MAKE_BSON_OBJ("Manufacturer", "Lenovo"));
    setobj( "HeightMm",         MAKE_BSON_OBJ("HeightMm", dataobjs.getIntField("HeightMm")) );
    setobj( "PowerState",         MAKE_BSON_OBJ("PowerState", dataobjs.getStringField("PowerState")) );
    setobj( "IndicatorLED",         MAKE_BSON_OBJ("IndicatorLED", dataobjs.getStringField("IndicatorLED")) );
    setobj("LogServices", MAKE_BSON_LINK_NAV_OBJ("LogServices", "/redfish/v1/Systems/1/LogServices" ));//TODO
    setobj( "Assembly",         MAKE_BSON_NULL_OBJ("Assembly") );
    setobj( "PartNumber",         MAKE_BSON_OBJ("PartNumber", dataobjs.getStringField("PartNumber")) );
    setobj( "AssetTag",         MAKE_BSON_OBJ("AssetTag", dataobjs.getStringField("AssetTag")) );

    setobj( "Location",    MAKE_BSON_OBJ("Location", BE_Object(dataobjs.getField("Location")) ));

    set_status_obj(MAKE_ENUM_STRING(State_Enabled),
                       MAKE_ENUM_STRING(Health_OK),
                       MAKE_ENUM_STRING(Health_OK));

    // invoke at the END for resource GET
    SnapperProvider::auto_build_objects_ResGET(oid_in);
    return RFRC_SUCCESS;
}

int Chassis::navigation_property_query(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Chassis::handle_post(shared_ptr<::snapper::service::request_context> request)
{

    return RFRC_METHOD_NOT_ALLOWED;
}

int Chassis::handle_patch(shared_ptr<::snapper::service::request_context> request)
{

    return RFRC_METHOD_NOT_ALLOWED;
}

int Chassis::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Chassis::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}




REGISTER_PROVIDER(Chassis);

}}

