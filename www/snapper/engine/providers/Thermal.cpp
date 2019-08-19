//---------------------------------------------------------------------
// <copyright file="Thermal.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/Thermal.h"

namespace snapper { namespace providers 
{

std::shared_ptr<memid_acckey_map> Thermal::getlist_memid_acckey(std::string containing_path)
{
    return nullptr;
}

int Thermal::handle_get(shared_ptr<::snapper::service::request_context> request)
{
    SnapperProvider::prepare_ResGet(request);

    string oid_in = request->get_raw_path();
    set_prop_autoexpand_arr("Fan", "Fans"); 
    set_prop_autoexpand_arr("Temperature", "Temperatures"); 


    set_status_obj(MAKE_ENUM_STRING(State_Enabled),
                       MAKE_ENUM_STRING(Health_OK),
                       MAKE_ENUM_STRING(Health_OK)); //TODO to check rollup health of fan/temp/redundancy 

    SnapperProvider::auto_build_objects_ResGET(oid_in);	
    return RFRC_SUCCESS;
}

int Thermal::handle_post(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Thermal::handle_patch(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Thermal::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int Thermal::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}


REGISTER_PROVIDER(Thermal);
}}

