//---------------------------------------------------------------------
// <copyright file="PowerControl.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/StorageController.h"
#include "class/ClassNames.h"
#include <www/engine/rf_debug.h>
#include <www/engine/topology.h>



namespace snapper { namespace providers 
{
    



std::shared_ptr<memid_acckey_map> StorageController::getlist_memid_acckey(std::string containing_path)
{
    std::shared_ptr<memid_acckey_map> list = std::make_shared<memid_acckey_map>();
    bson::BSONObj dataobjs;
    std::string relpath = containing_path.substr(0, containing_path.find(" "));
    DataInterfaceMgr::mockupGetData(relpath, dataobjs);


    std::vector<bson::BSONElement> pctls = BE_Array(dataobjs.getField("StorageControllers"));
    for(int i = 0; i < pctls.size(); i++)
    {
        bson::BSONObj p = pctls[i].Obj();
        string name = p.getStringField("MemberId");
        (*list)[name] = std::string(name)+"@"+get_name();
    }

    return list;

}


int StorageController::autoexpand_array(bson::BSONArrayBuilder* a, std::string containing_path, std::shared_ptr<bson::BSONObj> q_param )
{
    bson::BSONObj dataobjs;
    std::string relpath = containing_path.substr(0, containing_path.find(" "));// from parent /redfish/v1/Chassis/1/Power
    DataInterfaceMgr::mockupGetData(relpath, dataobjs);
std::cout << "auto expand Scontroller  ..... " << containing_path << std::endl;
    std::vector<bson::BSONElement> scs = BE_Array(dataobjs.getField("StorageControllers"));
    for(int i = 0; i < scs.size(); i++)
    {
        bson::BSONObj p = scs[i].Obj();

        setobj("MemberId", MAKE_BSON_OBJ("MemberId", p.getStringField("MemberId")));
        setobj("Name", MAKE_BSON_OBJ("Name", p.getStringField("Name")));
        setobj("Manufacturer", MAKE_BSON_OBJ("Manufacturer",  p.getStringField("Manufacturer")));
        setobj("Model", MAKE_BSON_OBJ("Model",  p.getStringField("Model")));
        setobj("PartNumber", MAKE_BSON_OBJ("PartNumber",  p.getStringField("PartNumber")));
        setobj("SerialNumber", MAKE_BSON_OBJ("SerialNumber",  p.getStringField("SerialNumber")));
	    setobj("FirmwareVersion", MAKE_BSON_OBJ("FirmwareVersion",  p.getStringField("FirmwareVersion")));

        bson::BSONElement e = p.getField("Identifiers");
        if(e.eoo() != true) 
        {
            bson::BSONObjBuilder t;
            t.append(e);
            if(strlen(e.fieldName()))
               setobj(e.fieldName(), std::make_shared<bson::BSONObj>(t.obj()) );
        }

        set_status_obj(MAKE_ENUM_STRING(State_Enabled), MAKE_ENUM_STRING(Health_OK), MAKE_ENUM_STRING(Health_OK));

        SnapperProvider::auto_build_objects_ResGET(containing_path);

        bson::BSONObj o = ::bson::fromjson(serialize_objs());
        a->append(o);  
        reset_obj();
    }
    return RFRC_SUCCESS;
}
int StorageController::handle_get(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}


int StorageController::handle_post(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int StorageController::handle_patch(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int StorageController::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int StorageController::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}


REGISTER_PROVIDER(StorageController);
}}

