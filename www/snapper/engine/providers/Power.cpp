//---------------------------------------------------------------------
// <copyright file="Power.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/Power.h"
#include <www/engine/rf_debug.h>
#include <www/engine/request_context.h>

namespace snapper { namespace providers 
{
    
//const string PowerDesc("Power Consumption and Power Limiting");

std::shared_ptr<memid_acckey_map> Power::getlist_memid_acckey(std::string containing_path)
{
    return nullptr;
}


int Power::handle_get(shared_ptr<::snapper::service::request_context> request)
{
    //inovke at the BEGINNING for resource GET
    SnapperProvider::prepare_ResGet(request);

    //////////////////////////////////////////////////////
    // handle navigation property query under the resource
    const char* prop_in = is_navprop_query(request);
    if(prop_in)//navigation prop access
    {
        return RFRC_METHOD_NOT_ALLOWED;
    }

    //////////////////////////////////////////////////////
    // GET resource query
    string oid_in = request->get_raw_path();
    //set_desc(PowerDesc);    
        
    // set referenceable member array
    set_prop_autoexpand_arr("Voltage", "Voltages");    
    set_prop_autoexpand_arr("PowerSupply", "PowerSupplies");    
    set_prop_autoexpand_arr("PowerControl", "PowerControl");    
    set_prop_autoexpand_arr("Redundancy", "Redundancy");    

    // invoke at the END for resource GET
    SnapperProvider::auto_build_objects_ResGET(oid_in);

    return RFRC_SUCCESS;
}


int Power::handle_post(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Power::handle_patch(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Power::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Power::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

REGISTER_PROVIDER(Power);
}}

