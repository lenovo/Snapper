//---------------------------------------------------------------------
// <copyright file="PowerControl.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/PowerControl.h"
#include "class/ClassNames.h"
#include "class/ProviderHelper.h"
#include "datainf/DataInterfaceMgr.h"
#include <www/engine/rf_debug.h>
#include <www/engine/topology.h>
#include "protocol.h"

using namespace snapper::service;

namespace snapper { namespace providers 
{
    

std::shared_ptr<memid_acckey_map> PowerControl::getlist_memid_acckey(std::string containing_path)
{
    std::shared_ptr<memid_acckey_map> list = std::make_shared<memid_acckey_map>();
    bson::BSONObj dataobjs;
    std::string relpath = containing_path.substr(0, containing_path.find(" "));
    DataInterfaceMgr::mockupGetData(relpath, dataobjs);


    std::vector<bson::BSONElement> pctls = BE_Array(dataobjs.getField("PowerControl"));
    for(int i = 0; i < pctls.size(); i++)
    {
        bson::BSONObj p = pctls[i].Obj();
        string name = p.getStringField("MemberId");
        (*list)[name] = std::string(name)+"@"+get_name();
    }

    return list;

}

int PowerControl::autoexpand_array(bson::BSONArrayBuilder* a, std::string containing_path, std::shared_ptr<bson::BSONObj> q_param )
{
    bson::BSONObj dataobjs;
    std::string relpath = containing_path.substr(0, containing_path.find(" "));// from parent /redfish/v1/Chassis/1/Power
    DataInterfaceMgr::mockupGetData(relpath, dataobjs);

    std::vector<bson::BSONElement> pctls = BE_Array(dataobjs.getField("PowerControl"));
    for(int i = 0; i < pctls.size(); i++)
    {
        bson::BSONObj p = pctls[i].Obj();

        setobj("MemberId", MAKE_BSON_OBJ("MemberId", p.getStringField("MemberId")));
        setobj("Name", MAKE_BSON_OBJ("Name", p.getStringField("Name")));
        setobj("PowerMetrics", MAKE_BSON_OBJ("PowerMetrics", BE_Object(p.getField("PowerMetrics")) ));
        setobj("PowerLimit", MAKE_BSON_OBJ("PowerLimit", BE_Object(p.getField("PowerLimit")) ));

        if(p.hasField("PowerAllocatedWatts"))
            setobj("PowerAllocatedWatts", MAKE_BSON_OBJ("PowerAllocatedWatts", p.getIntField("PowerAllocatedWatts")) );
        if(p.hasField("PowerAvailableWatts"))
            setobj("PowerAvailableWatts", MAKE_BSON_OBJ("PowerAvailableWatts", p.getIntField("PowerAvailableWatts")) );
        if(p.hasField("PowerCapacityWatts"))
            setobj("PowerCapacityWatts", MAKE_BSON_OBJ("PowerCapacityWatts", p.getIntField("PowerCapacityWatts")) );
        if(p.hasField("PowerConsumedWatts"))
            setobj("PowerConsumedWatts", MAKE_BSON_OBJ("PowerConsumedWatts", p.getIntField("PowerConsumedWatts")) );
        if(p.hasField("PowerRequestedWatts"))
            setobj("PowerRequestedWatts", MAKE_BSON_OBJ("PowerRequestedWatts", p.getIntField("PowerRequestedWatts")) );

        SetRelatedItems(RF_CHASSIS);
        set_status_obj(MAKE_ENUM_STRING(State_Enabled), MAKE_ENUM_STRING(Health_OK), MAKE_ENUM_STRING(Health_OK));

        SnapperProvider::auto_build_objects_ResGET(containing_path);

        bson::BSONObj o = ::bson::fromjson(serialize_objs());
        a->append(o);  
        reset_obj();
    }
    return RFRC_SUCCESS;
}

void PowerControl::SetRelatedItems(string className)
{
    shared_ptr<memid_acckey_map> idlist = getlist_memid_acckey_fromclass(className);
    bson::BSONArrayBuilder refArr;
    
    if (idlist != nullptr)
    {
        for (auto it=idlist->begin();it != idlist->end();++it)
        {
            string accessor_key = it->second;
            auto uri = snapper::service::ResourceTopology::search_url(accessor_key);
            if (uri != nullptr)
                refArr.append(BSON(ODATA_ID << uri->c_str()));
        }
    }

    setobj("RelatedItem", MAKE_BSON_OBJ("RelatedItem", refArr.arr()));
}

int PowerControl::handle_get(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}


int PowerControl::handle_post(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int PowerControl::handle_patch(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}


int PowerControl::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int PowerControl::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

REGISTER_PROVIDER(PowerControl);
}}

