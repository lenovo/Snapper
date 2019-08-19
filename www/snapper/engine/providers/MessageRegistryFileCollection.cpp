//---------------------------------------------------------------------
// <copyright file="MessageRegistryFileCollection.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/MessageRegistryFileCollection.h"
#include <www/engine/topology.h>
#include <www/engine/rf_debug.h>

namespace snapper { namespace providers 
{

int MessageRegistryFileCollection::handle_get(shared_ptr<::snapper::service::request_context> request)
{ 
    //inovke at the BEGINNING for resource GET
    SnapperProvider::prepare_ResGet(request);


    //////////////////////////////////////////////////////
    // handle navigation property query under the resource
    const char* prop_in = is_navprop_query(request);
    if(prop_in)
    {
        return access_member_prop(prop_in, "MessageRegistryFile");
    }

    //////////////////////////////////////////////////////
    // GET resource query
    string oid_in = request->get_raw_path();

    // invoke at the END for resource GET
    SnapperProvider::auto_build_objects_ResGET(oid_in);

    return RFRC_SUCCESS;
}

int MessageRegistryFileCollection::handle_post(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}


int MessageRegistryFileCollection::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int MessageRegistryFileCollection::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}


REGISTER_PROVIDER(MessageRegistryFileCollection)

}}

