//---------------------------------------------------------------------
// <copyright file="ServiceRoot.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/ServiceRoot.h"


namespace snapper { namespace providers 
{

int ServiceRoot::handle_get(shared_ptr<::snapper::service::request_context> request)
{
    return false;
}

int ServiceRoot::handle_get(const string uri_path)
{
    if (uri_path.compare("/redfish/v1") == 0)
    {
        bson::BSONObj dataobjs;
        DataInterfaceMgr::mockupGetData(uri_path, dataobjs);
        //std::cout << dataobjs.jsonString(bson::Strict,1) << std::endl;

        // setup values for building common objs
        set_base_odata_id(root_uri); 
        set_id_key(root_uri + "/ServiceRoot"); // id is "ServiceRoot"
    
        string version = get_namespace();
        version = version.substr(version.find(".v") + 2);
        size_t pos = version.find("_");
        while(pos != string::npos)
        {
            version.replace(pos, 1, ".");
            pos = version.find("_");
        }
        setobj("RedfishVersion",         MAKE_BSON_OBJ("RedfishVersion", version));
    
        setobj("UUID", MAKE_BSON_OBJ("UUID", dataobjs.getStringField("UUID")));
        setobj( "Tasks",    MAKE_BSON_OBJ("Tasks", BE_Object(dataobjs.getField("Tasks")) ));
        setobj( "EventService",    MAKE_BSON_OBJ("EventService", BE_Object(dataobjs.getField("EventService")) ));
        setobj( "UpdateService",    MAKE_BSON_OBJ("UpdateService", BE_Object(dataobjs.getField("UpdateService")) ));
        setobj( "SessionService",    MAKE_BSON_OBJ("SessionService", BE_Object(dataobjs.getField("SessionService")) ));
        setobj( "AccountService",    MAKE_BSON_OBJ("AccountService", BE_Object(dataobjs.getField("AccountService")) ));        

        setLinksobj("Sessions", MAKE_BSON_OBJ("Sessions", BSON(ODATA_ID << (root_uri + "/SessionService/Sessions")) ));
    
        // invoke at the END for resource GET
        SnapperProvider::auto_build_objects_ResGET(root_uri);       
    
    }
    else if (uri_path.compare("/redfish/v1/odata") == 0)
    {        
        setobj("value", std::make_shared<bson::BSONObj>BSON("value" 
                    << BSON_ARRAY(BSON("url" << "/redfish/v1/"
                                    << "name" << "Service"
                                    << "kind" << "Singleton")
                             << BSON("url" << "/redfish/v1/managers"
                                    << "name" << "managers"
                                    << "kind" << "Singleton")
                             << BSON("url" << "/redfish/v1/JsonSchemas"
                                    << "name" << "JsonSchemas"
                                    << "kind" << "Singleton")
                             << BSON("url" << "/redfish/v1/EventService"
                                    << "name" << "EventService"
                                    << "kind" << "Singleton")
                             << BSON("url" << "/redfish/v1/Chassis"
                                    << "name" << "Chassis"
                                    << "kind" << "Singleton")
                             << BSON("url" << "/redfish/v1/Tasks"
                                    << "name" << "Tasks"
                                    << "kind" << "Singleton")
                             << BSON("url" << "/redfish/v1/SessionService"
                                    << "name" << "SessionService"
                                    << "kind" << "Singleton")
                             << BSON("url" << "/redfish/v1/AccountService"
                                    << "name" << "AccountService"
                                    << "kind" << "Singleton")
                             << BSON("url" << "/redfish/v1/Systems"
                                    << "name" << "Systems"
                                    << "kind" << "Singleton")
                             << BSON("url" << "/redfish/v1/Registries"
                                    << "name" << "Registries"
                                    << "kind" << "Singleton")
                             << BSON("url" << "/redfish/v1/UpdateService"
                                    << "name" << "UpdateService"
                                    << "kind" << "Singleton"))));
                             //<< BSON("url" << "/redfish/v1/Fabrics"
                             //       << "name" << "Fabrics"
                             //       << "kind" << "Singleton")
                             //<< BSON("url" << "/redfish/v1/Fabrics"
                             //       << "name" << "Fabrics"
                             //       << "kind" << "Singleton")
                             //<< BSON("url" << "/redfish/v1/StorageServices"
                             //       << "name" << "StorageServices"
                             //       << "kind" << "Singleton")
                             //<< BSON("url" << "/redfish/v1/StorageSystems"
                             //       << "name" << "StorageSystems"
                             //       << "kind" << "Singleton")
                             //<< BSON("url" << "/redfish/v1/CompositionService"
                             //       << "name" << "CompositionService"
                             //       << "kind" << "Singleton"))));
        setobj(ODATA_CONTEXT, MAKE_BSON_OBJ(ODATA_CONTEXT, "redfish/v1/$metadata"));
        
    }
    else
    {
        override_http_code(HTTP_BAD_REQUEST);
        return RFRC_FAILURE;
    }

    return RFRC_SUCCESS;
}


int ServiceRoot::handle_post(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int ServiceRoot::handle_patch(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int ServiceRoot::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int ServiceRoot::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}


REGISTER_PROVIDER(ServiceRoot);

}}

