//---------------------------------------------------------------------
// <copyright file="NetworkPortCollection.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/NetworkPortCollection.h"
#include <www/engine/topology.h>
#include <www/engine/rf_debug.h>
#include "class/ClassNames.h"

namespace snapper { namespace providers 
{

int NetworkPortCollection::handle_get(shared_ptr<::snapper::service::request_context> request)
{ 
    //inovke at the BEGINNING for resource GET
    SnapperProvider::prepare_ResGet(request);


    //////////////////////////////////////////////////////
    // handle navigation property query under the resource
    const char* prop_in = is_navprop_query(request);
    if(prop_in)
    {
        auto idlist = getlist_memid_acckey_fromclass(RF_NETWORKPORTCOL);
        std::string containing_path;
        if (idlist == nullptr)
        {
            RF_PRINT_DBG("%s::%s()- Cannot find self acckey.\n", RF_NETWORKPORTCOL, __FUNCTION__);
            return access_member_prop(prop_in, "NetworkPort");
        }
        else
        {
            containing_path = idlist->begin()->first + " " + idlist->begin()->second;
            return access_member_prop(prop_in, "NetworkPort", containing_path);
        }
    }


    //////////////////////////////////////////////////////
    // GET resource query
    string oid_in = request->get_raw_path();

    // invoke at the END for resource GET
    SnapperProvider::auto_build_objects_ResGET(oid_in);

    return RFRC_SUCCESS;
}

int NetworkPortCollection::handle_post(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}


REGISTER_PROVIDER(NetworkPortCollection);
}}

