//---------------------------------------------------------------------
// <copyright file="Storage.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/Storage.h"
#include <www/engine/rf_debug.h>
#include <www/engine/topology.h>

using namespace snapper::service;


namespace snapper { namespace providers 
{


std::shared_ptr<memid_acckey_map> Storage::getlist_memid_acckey(std::string containing_path)
{
    std::shared_ptr<memid_acckey_map> list = std::make_shared<memid_acckey_map>();
    std::vector<string> m;
    int rc = DataInterfaceMgr::mockupMemberList(containing_path, m);

    for(int i = 0; i < m.size(); i++)
    {
        (*list)[m[i]] = std::string(m[i])+"@"+"Storage";
    }
    return list;

}



int Storage::handle_get(shared_ptr<::snapper::service::request_context> request)
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

    enum_property_values(dataobjs);

    set_prop_autoexpand_arr("StorageController", "StorageControllers"); //let StorageController work for Storage 
	
    set_status_obj(MAKE_ENUM_STRING(State_Enabled),
                       MAKE_ENUM_STRING(Health_OK),
                       MAKE_ENUM_STRING(Health_OK)); //build object for Staus    

    // invoke at the END for resource GET
    SnapperProvider::auto_build_objects_ResGET(oid_in);
    return RFRC_SUCCESS;
}

int Storage::navigation_property_query(shared_ptr<::snapper::service::request_context> request)
{
    std::string member_id;
    string oid_in = request->get_raw_path();
    const char* prop_in = is_navprop_query(request);
    std::shared_ptr< memid_acckey_map > idlist = nullptr;
    bson::BSONArrayBuilder arr_builder;
    bson::BSONObjBuilder obj_builder;

    switch (HASH_STRING(prop_in))
    {
        case "Drives"_HASH:
        {
            cout<<"navigation_property_query enterred, oid_in="<<oid_in<<endl;
            if ((idlist = getlist_memid_acckey_fromclass("Drive",oid_in)) != nullptr) {
                for (auto it=idlist->begin();it != idlist->end();++it) {
                    member_id = "/" + it->first;
                    arr_builder << BSON(ODATA_ID << build_str(oid_in, member_id));
                }
            }
            else
                RF_PRINT_DBG("Get no list from Drive under Storage\n");

            obj_builder.append("value", arr_builder.arr());
            create_prop("value", std::make_shared<bson::BSONObj>(obj_builder.obj()) );
            break;
        }
       
        default:
        {
            return RFRC_INVALID_PARAMS; //shouldn't come here
        }
    }

    return RFRC_SUCCESS;
}



int Storage::handle_post(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Storage::handle_patch(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Storage::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Storage::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}
int Storage::autoexpand_array(bson::BSONArrayBuilder* a, std::string containing_path, std::shared_ptr<bson::BSONObj> q_param)
{
    cout<<"Storage containing_path: "<<containing_path<<endl; 
    return 0;
}


REGISTER_PROVIDER(Storage);
}}

