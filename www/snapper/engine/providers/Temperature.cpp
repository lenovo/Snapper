//---------------------------------------------------------------------
// <copyright file="Temperature.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/Temperature.h"
#include "class/_pPhysicalContext.h"
#include "datainf/DataInterfaceMgr.h"
#include <www/engine/topology.h>


#define UNIT_MODIFIER  0.1f

using namespace snapper::service;


namespace snapper { namespace providers 
{

std::shared_ptr<memid_acckey_map> Temperature::getlist_memid_acckey(std::string containing_path)
{
    std::shared_ptr<memid_acckey_map> list = std::make_shared<memid_acckey_map>();
    bson::BSONObj dataobjs;
    std::string relpath = containing_path.substr(0, containing_path.find(" "));
    DataInterfaceMgr::mockupGetData(relpath, dataobjs);


    std::vector<bson::BSONElement> temps = BE_Array(dataobjs.getField("Temperatures"));
    for(int i = 0; i < temps.size(); i++)
    {
        bson::BSONObj t = temps[i].Obj();
        string name = t.getStringField("MemberId");
        (*list)[name] = std::string(name)+"@"+get_name();
    }

    return list;
}

int Temperature::handle_get(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Temperature::handle_post(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Temperature::handle_patch(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Temperature::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Temperature::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Temperature::autoexpand_array(bson::BSONArrayBuilder* a, std::string containing_path, std::shared_ptr<bson::BSONObj> q_param)
{
    bson::BSONObj dataobjs;
    std::string relpath = containing_path.substr(0, containing_path.find(" "));// from parent /redfish/v1/Chassis/1/Thermal
    DataInterfaceMgr::mockupGetData(relpath, dataobjs);

    std::vector<bson::BSONElement> temps = BE_Array(dataobjs.getField("Temperatures"));
    for(int i = 0; i < temps.size(); i++)
    {
        bson::BSONObj t = temps[i].Obj();

        set_status_obj(MAKE_ENUM_STRING(State_Enabled), MAKE_ENUM_STRING(Health_OK), MAKE_ENUM_STRING(Health_OK));

        setobj("MemberId", MAKE_BSON_OBJ("MemberId", t.getStringField("MemberId")));
        setobj("Name", MAKE_BSON_OBJ("Name", t.getStringField("Name")));

        setobj("SensorNumber",         MAKE_BSON_OBJ("SensorNumber", t.getIntField("SensorNumber")));
	    setobj("ReadingCelsius",         MAKE_BSON_OBJ("ReadingCelsius", t.getIntField("ReadingCelsius") ));


        if(t.hasField("LowerThresholdFatal") && !t.getField("LowerThresholdFatal").isNull())
            setobj( "LowerThresholdFatal",  MAKE_BSON_OBJ("LowerThresholdFatal", t.getIntField("LowerThresholdFatal")));
        if(t.hasField("LowerThresholdCritical") && !t.getField("LowerThresholdCritical").isNull())
            setobj( "LowerThresholdCritical",         MAKE_BSON_OBJ("LowerThresholdCritical", t.getIntField("LowerThresholdCritical")));
        if(t.hasField("LowerThresholdNonCritical") && !t.getField("LowerThresholdNonCritical").isNull())
            setobj( "LowerThresholdNonCritical",         MAKE_BSON_OBJ("LowerThresholdNonCritical", t.getIntField("LowerThresholdNonCritical")) );
        if(t.hasField("UpperThresholdFatal") && !t.getField("UpperThresholdFatal").isNull())
            setobj( "UpperThresholdFatal",         MAKE_BSON_OBJ("UpperThresholdFatal", t.getIntField("UpperThresholdFatal")) );
        if(t.hasField("UpperThresholdCritical") && !t.getField("UpperThresholdCritical").isNull())
            setobj( "UpperThresholdCritical",         MAKE_BSON_OBJ("UpperThresholdCritical", t.getIntField("UpperThresholdCritical")) );
        if(t.hasField("UpperThresholdNonCritical") && !t.getField("UpperThresholdNonCritical").isNull())
            setobj( "UpperThresholdNonCritical",         MAKE_BSON_OBJ("UpperThresholdNonCritical", t.getIntField("UpperThresholdNonCritical")) );


        setobj("MaxReadingRangeTemp", MAKE_BSON_OBJ("MaxReadingRangeTemp", t.getIntField("MaxReadingRangeTemp")  ));
        setobj("MinReadingRangeTemp", MAKE_BSON_OBJ("MinReadingRangeTemp", t.getIntField("MinReadingRangeTemp")  ));
        setobj("PhysicalContext", MAKE_BSON_OBJ("PhysicalContext", t.getStringField("PhysicalContext")  ));

        bson::BSONArrayBuilder RelatedItems;
        std::shared_ptr<std::string> uri;
        uri = ResourceTopology::search_url("1@ComputerSystem");
        if(uri != nullptr)
             RelatedItems.append(BSON(ODATA_ID << uri->c_str()));
        uri = ResourceTopology::search_url("1@Chassis");
        if(uri != nullptr)
             RelatedItems.append(BSON(ODATA_ID << uri->c_str()));

        std::string EntityID = t.getStringField("PhysicalContext");
        std::string source = t.getStringField("Name");
        size_t pos =  source.find(" ");
        if(pos != string::npos)
            source.replace(pos, 1, "_");
        if(EntityID.compare("CPU") == 0)  // CPU related
        {
            int cpuindex = 0;
            sscanf(source.c_str(),"%*[^0-9]%i",&cpuindex);
            uri = ResourceTopology::search_url(to_string(cpuindex)+"@Processor");
            if(uri != nullptr)
                RelatedItems.append(BSON(ODATA_ID << uri->c_str()));                
        }
        setobj("RelatedItem", MAKE_BSON_OBJ("RelatedItem", RelatedItems.arr()));

        SnapperProvider::auto_build_objects_ResGET(containing_path);

        bson::BSONObj o = ::bson::fromjson(serialize_objs());
        a->append(o);  
        reset_obj();
    }
    return RFRC_SUCCESS;
}



REGISTER_PROVIDER(Temperature);
}}

