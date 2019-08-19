//---------------------------------------------------------------------
// <copyright file="PowerSupply.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/PowerSupply.h"
#include "class/ClassNames.h"
#include <www/engine/rf_debug.h>
#include <www/engine/topology.h>
#include "datainf/DataInterfaceMgr.h"
#include "class/ProviderHelper.h"

namespace snapper { namespace providers 
{

std::shared_ptr<memid_acckey_map> PowerSupply::getlist_memid_acckey(std::string containing_path)
{
    std::shared_ptr<memid_acckey_map> list = std::make_shared<memid_acckey_map>();
    bson::BSONObj dataobjs;
    std::string relpath = containing_path.substr(0, containing_path.find(" "));
    DataInterfaceMgr::mockupGetData(relpath, dataobjs);


    std::vector<bson::BSONElement> psus = BE_Array(dataobjs.getField("PowerSupplies"));
    for(int i = 0; i < psus.size(); i++)
    {
        bson::BSONObj p = psus[i].Obj();
        string name = p.getStringField("MemberId");
        (*list)[name] = std::string(name)+"@"+get_name();
    }

    return list;
}

void PowerSupply::SetRelatedItems(std::string className, std::string propName)
{
    std::shared_ptr<std::string> uri;
    std::string accessor_key = "";
    std::shared_ptr<memid_acckey_map> idlist = getlist_memid_acckey_fromclass(className);
    bson::BSONArrayBuilder refArr;
    
    if (idlist != nullptr)
    {
        for (auto it=idlist->begin();it != idlist->end();++it)
        {
            accessor_key = it->second;
            uri = snapper::service::ResourceTopology::search_url(accessor_key);
            if (uri != nullptr)
                refArr.append(BSON(ODATA_ID << uri->c_str()));
        }
    }

    setobj(propName, MAKE_BSON_OBJ(propName, refArr.arr()));
}

int PowerSupply::handle_get(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int PowerSupply::handle_post(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int PowerSupply::handle_patch(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int PowerSupply::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int PowerSupply::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int PowerSupply::autoexpand_array(bson::BSONArrayBuilder* a, std::string containing_path, std::shared_ptr<bson::BSONObj> q_param)
{
    bson::BSONObj dataobjs;
    std::string relpath = containing_path.substr(0, containing_path.find(" "));// from parent /redfish/v1/Chassis/1/Power
    DataInterfaceMgr::mockupGetData(relpath, dataobjs);

    std::vector<bson::BSONElement> psus = BE_Array(dataobjs.getField("PowerSupplies"));
    for(int i = 0; i < psus.size(); i++)
    {
        bson::BSONObj p = psus[i].Obj();

        setobj("MemberId", MAKE_BSON_OBJ("MemberId", p.getStringField("MemberId")));
        setobj("Name", MAKE_BSON_OBJ("Name", p.getStringField("Name")));
        setobj("FirmwareVersion", MAKE_BSON_OBJ("FirmwareVersion", p.getStringField("FirmwareVersion")));
        setobj("SerialNumber", MAKE_BSON_OBJ("SerialNumber", p.getStringField("SerialNumber")));
        setobj("PartNumber", MAKE_BSON_OBJ("PartNumber", p.getStringField("PartNumber")));
        setobj("Manufacturer", MAKE_BSON_OBJ("Manufacturer", p.getStringField("Manufacturer")));
        setobj("PowerSupplyType", MAKE_BSON_OBJ("PowerSupplyType", p.getStringField("PowerSupplyType")));
        setobj("LineInputVoltageType", MAKE_BSON_OBJ("LineInputVoltageType", p.getStringField("LineInputVoltageType")));
        setobj("LineInputVoltage", MAKE_BSON_OBJ("LineInputVoltage", p.getIntField("LineInputVoltage")));
        setobj("PowerCapacityWatts", MAKE_BSON_OBJ("PowerCapacityWatts", p.getIntField("PowerCapacityWatts")));

        bson::BSONArrayBuilder ar;
        auto aList = BE_Array(p.getField("InputRanges"));
        for(int m = 0; m < aList.size(); m++)
			ar.append(aList[m]);
        bson::BSONArray arr_obj = ar.arr();
        setobj( "InputRanges",         MAKE_BSON_OBJ("InputRanges",  arr_obj) );

        SetRelatedItems(RF_CHASSIS, "RelatedItem");

        set_status_obj(MAKE_ENUM_STRING(State_Enabled), MAKE_ENUM_STRING(Health_OK), MAKE_ENUM_STRING(Health_OK));

        SnapperProvider::auto_build_objects_ResGET(containing_path);

        bson::BSONObj o = ::bson::fromjson(serialize_objs());
        a->append(o);  
        reset_obj();
    }
    return RFRC_SUCCESS;
}

REGISTER_PROVIDER(PowerSupply);
}}

