//---------------------------------------------------------------------
// <copyright file="Fan.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/_pPhysicalContext.h"
#include "class/Fan.h"
#include "datainf/DataInterfaceMgr.h"
#include <www/engine/topology.h>



using namespace snapper::service;


namespace snapper { namespace providers 
{

std::shared_ptr<memid_acckey_map> Fan::getlist_memid_acckey(std::string containing_path)
{
    std::shared_ptr<memid_acckey_map> list = std::make_shared<memid_acckey_map>();
    bson::BSONObj dataobjs;
    std::string relpath = containing_path.substr(0, containing_path.find(" "));
    DataInterfaceMgr::mockupGetData(relpath, dataobjs);


    std::vector<bson::BSONElement> fans = BE_Array(dataobjs.getField("Fans"));
    for(int i = 0; i < fans.size(); i++)
    {
        bson::BSONObj p = fans[i].Obj();
        string name = p.getStringField("MemberId");
        (*list)[name] = std::string(name)+"@"+get_name();
    }


    return list;
}

int Fan::handle_get(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Fan::handle_post(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Fan::handle_patch(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Fan::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Fan::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Fan::autoexpand_array(bson::BSONArrayBuilder* a, std::string containing_path, std::shared_ptr<bson::BSONObj> q_param)
{
    bson::BSONObj dataobjs;
    std::string relpath = containing_path.substr(0, containing_path.find(" "));// from parent /redfish/v1/Chassis/1/Thermal
    DataInterfaceMgr::mockupGetData(relpath, dataobjs);

    std::vector<bson::BSONElement> fans = BE_Array(dataobjs.getField("Fans"));
    for(int i = 0; i < fans.size(); i++)
    {
        bson::BSONObj f = fans[i].Obj();

        set_status_obj(MAKE_ENUM_STRING(State_Enabled), MAKE_ENUM_STRING(Health_OK), MAKE_ENUM_STRING(Health_OK));

        setobj("MemberId", MAKE_BSON_OBJ("MemberId", f.getStringField("MemberId")));
        setobj("Name", MAKE_BSON_OBJ("Name", f.getStringField("Name")));

        setobj( "Reading",         MAKE_BSON_OBJ("Reading", f.getIntField("Reading")));
        setobj( "MaxReadingRange",         MAKE_BSON_OBJ("MaxReadingRange", (int)100));
        setobj( "MinReadingRange",         MAKE_BSON_OBJ("MinReadingRange", (int)0));
        setobj( "ReadingUnits",         MAKE_BSON_OBJ("ReadingUnits", MAKE_ENUM_STRING(ReadingUnits_Percent)) );
        setobj( "PhysicalContext",         MAKE_BSON_OBJ("PhysicalContext", MAKE_ENUM_STRING(PhysicalContext_SystemBoard)) );

        if(f.hasField("LowerThresholdFatal") && !f.getField("LowerThresholdFatal").isNull())
            setobj( "LowerThresholdFatal",  MAKE_BSON_OBJ("LowerThresholdFatal", f.getIntField("LowerThresholdFatal")));
        if(f.hasField("LowerThresholdCritical") && !f.getField("LowerThresholdCritical").isNull())
            setobj( "LowerThresholdCritical",         MAKE_BSON_OBJ("LowerThresholdCritical", f.getIntField("LowerThresholdCritical")));
        if(f.hasField("LowerThresholdNonCritical") && !f.getField("LowerThresholdNonCritical").isNull())
            setobj( "LowerThresholdNonCritical",         MAKE_BSON_OBJ("LowerThresholdNonCritical", f.getIntField("LowerThresholdNonCritical")) );
        if(f.hasField("UpperThresholdFatal") && !f.getField("UpperThresholdFatal").isNull())
            setobj( "UpperThresholdFatal",         MAKE_BSON_OBJ("UpperThresholdFatal", f.getIntField("UpperThresholdFatal")) );
        if(f.hasField("UpperThresholdCritical") && !f.getField("UpperThresholdCritical").isNull())
            setobj( "UpperThresholdCritical",         MAKE_BSON_OBJ("UpperThresholdCritical", f.getIntField("UpperThresholdCritical")) );
        if(f.hasField("UpperThresholdNonCritical") && !f.getField("UpperThresholdNonCritical").isNull())
            setobj( "UpperThresholdNonCritical",         MAKE_BSON_OBJ("UpperThresholdNonCritical", f.getIntField("UpperThresholdNonCritical")) );

        if(f.hasField("Location") && !f.getField("Location").isNull())
            setobj( "Location",         MAKE_BSON_OBJ("Location", BE_Object(f.getField("Location"))) );

        bson::BSONArrayBuilder RelatedItems;
        std::shared_ptr<std::string> uri;
        uri = ResourceTopology::search_url("1@ComputerSystem");
        if(uri != nullptr)
             RelatedItems.append(BSON(ODATA_ID << uri->c_str()));
        uri = ResourceTopology::search_url("1@Chassis");
        if(uri != nullptr)
             RelatedItems.append(BSON(ODATA_ID << uri->c_str()));             
        setobj("RelatedItem", MAKE_BSON_OBJ("RelatedItem", RelatedItems.arr()));

        SnapperProvider::auto_build_objects_ResGET(containing_path);

        bson::BSONObj o = ::bson::fromjson(serialize_objs());
        a->append(o);  
        reset_obj();
    }
    return RFRC_SUCCESS;
}


REGISTER_PROVIDER(Fan);
}}

