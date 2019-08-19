//---------------------------------------------------------------------
// <copyright file="Voltage.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include <math.h>
#include <sstream>
#include "class/Voltage.h"
#include "class/ClassNames.h"
#include "class/ProviderHelper.h"
#include <www/engine/rf_debug.h>
#include <www/engine/topology.h>
#include "datainf/DataInterfaceMgr.h"

namespace snapper { namespace providers 
{

std::shared_ptr<memid_acckey_map> Voltage::getlist_memid_acckey(std::string containing_path)
{
    std::shared_ptr<memid_acckey_map> list = std::make_shared<memid_acckey_map>();
    bson::BSONObj dataobjs;
    std::string relpath = containing_path.substr(0, containing_path.find(" "));
    DataInterfaceMgr::mockupGetData(relpath, dataobjs);


    std::vector<bson::BSONElement> volts = BE_Array(dataobjs.getField("Voltages"));
    for(int i = 0; i < volts.size(); i++)
    {
        bson::BSONObj v = volts[i].Obj();
        string name = v.getStringField("MemberId");
        (*list)[name] = std::string(name)+"@"+get_name();
    }

    return list;
}

int Voltage::handle_get(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Voltage::handle_post(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Voltage::handle_patch(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Voltage::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Voltage::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

void Voltage::SetRelatedItems(vector<std::string> arr)
{
    bson::BSONArrayBuilder refArr;

    for (int i=0; i<arr.size(); ++i)
    {
        string className = arr[i];
        std::shared_ptr<memid_acckey_map> idlist = getlist_memid_acckey_fromclass(className);
        if (idlist != nullptr)
        {
            for (auto it=idlist->begin();it != idlist->end();++it)
            {
                std::string accessor_key = it->second;
                std::shared_ptr<std::string> uri = snapper::service::ResourceTopology::search_url(accessor_key);
                if (uri != nullptr)
                    refArr.append(BSON(ODATA_ID << uri->c_str()));
            }
        }
    }
    
    setobj("RelatedItem", MAKE_BSON_OBJ("RelatedItem", refArr.arr()));
}

int Voltage::autoexpand_array(bson::BSONArrayBuilder* a, std::string containing_path, std::shared_ptr<bson::BSONObj> q_param )
{

    bson::BSONObj dataobjs;
    std::string relpath = containing_path.substr(0, containing_path.find(" "));// from parent /redfish/v1/Chassis/1/Power
    DataInterfaceMgr::mockupGetData(relpath, dataobjs);

    std::vector<bson::BSONElement> volts = BE_Array(dataobjs.getField("Voltages"));
    for(int i = 0; i < volts.size(); i++)
    {
        bson::BSONObj v = volts[i].Obj();

        setobj("MemberId", MAKE_BSON_OBJ("MemberId", v.getStringField("MemberId")));
        setobj("Name", MAKE_BSON_OBJ("Name", v.getStringField("Name")));
        setobj("SensorNumber", MAKE_BSON_OBJ("SensorNumber", v.getStringField("SensorNumber")));
        setobj("PhysicalContext", MAKE_BSON_OBJ("PhysicalContext", MAKE_ENUM_STRING(PhysicalContext_VoltageRegulator)));

        vector<std::string> classArr = {RF_CHASSIS, RF_SYSTEM};
        SetRelatedItems(classArr);

        SnapperProvider::auto_build_objects_ResGET(containing_path);

        bson::BSONObj o = ::bson::fromjson(serialize_objs());
        a->append(o);  
        reset_obj();
    }

    return RFRC_SUCCESS;
}



REGISTER_PROVIDER(Voltage);
}}

