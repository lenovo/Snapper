//---------------------------------------------------------------------
// <copyright file="ManagerCollection.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/ManagerCollection.h"

namespace snapper { namespace providers 
{

int ManagerCollection::handle_get(shared_ptr<::snapper::service::request_context> request)
{
    //inovke at the BEGINNING for resource GET
    SnapperProvider::prepare_ResGet(request);


    //////////////////////////////////////////////////////
    // handle navigation property query under the resource
    const char* prop_in = is_navprop_query(request);
    if(prop_in)
    {
        return access_member_prop(prop_in, "Manager");
    }


    //////////////////////////////////////////////////////
    // GET resource query
    string oid_in = request->get_raw_path();

    // invoke at the END for resource GET
    SnapperProvider::auto_build_objects_ResGET(oid_in);

    return RFRC_SUCCESS;

}

int ManagerCollection::handle_post(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}



REGISTER_PROVIDER(ManagerCollection);
}}

