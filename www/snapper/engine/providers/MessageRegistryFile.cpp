//---------------------------------------------------------------------
// <copyright file="MessageRegistryFile.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/MessageRegistryFile.h"
#include <www/engine/rf_debug.h>
#include <www/engine/topology.h>
#include "class/SnapperRegistry.h"

using namespace snapper::service;

namespace snapper { namespace providers 
{
#ifndef __SIM_X86__
const string FILE_DIR = "/var/www/snapper/schema_json/registries/";
#else
const string FILE_DIR = "../schema_json/registries/";
#endif

std::shared_ptr<memid_acckey_map> MessageRegistryFile::getlist_memid_acckey(std::string containing_path)
{
    std::shared_ptr<memid_acckey_map> list = std::make_shared<memid_acckey_map>();
    
    DIR *dp;
    struct dirent *dirp;
    //get json file list
    if ((dp = opendir(FILE_DIR.c_str())) == NULL) 
    {
        RF_PRINT_ERR("opendir error\n");
        return nullptr;
    }
    vector<::odata::utility::string_t> fileNameList;
    while ((dirp = readdir(dp)) != NULL) 
    {
        ::odata::utility::string_t filename = string(dirp->d_name);

        std::size_t found = filename.find_last_of(".");
        if (found != std::string::npos)
        {
            ::odata::utility::string_t fileBase = filename.substr(0,found);
            ::odata::utility::string_t fileExt  = filename.substr(found);

            if (fileExt.compare(".json") == 0)
            {                
                (*list)[fileBase] = fileBase + get_name();
            }
        }
    }
    closedir(dp);
    return list;
}

int MessageRegistryFile::handle_get(shared_ptr<::snapper::service::request_context> request)
{    
    //inovke at the BEGINNING for resource GET
    SnapperProvider::prepare_ResGet(request);

    string file_name(get_id_key() + ".json");
    ifstream ifs(FILE_DIR + file_name);
    if(!ifs)
    {
        override_http_code(HTTP_BAD_REQUEST);
        return RFRC_FAILURE;    
    }    
    
    bson::BSONArrayBuilder arr;
    bson::BSONObjBuilder b;
    bson::BSONArrayBuilder lan_arr;
    lan_arr << "en";
    b.append("Language", "en");
    b.append("Uri", (schema_uri + "/registries/" + file_name));
    arr.append(b.obj());
    setobj( "Location",         MAKE_BSON_OBJ("Location", arr.arr()) );
            
    setobj( "Languages",         MAKE_BSON_OBJ("Languages", lan_arr.arr()) );
    setobj( "Registry",         MAKE_BSON_OBJ("Registry", get_id_key().c_str()) );
    

    //////////////////////////////////////////////////////
    // GET resource query
    string oid_in = request->get_raw_path();


    // invoke at the END for resource GET
    SnapperProvider::auto_build_objects_ResGET(oid_in);
    return RFRC_SUCCESS;
}


int MessageRegistryFile::handle_post(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}


int MessageRegistryFile::handle_patch(shared_ptr<::snapper::service::request_context> request)
{    
    return RFRC_METHOD_NOT_ALLOWED;
}

int MessageRegistryFile::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int MessageRegistryFile::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

REGISTER_PROVIDER(MessageRegistryFile)

}}

