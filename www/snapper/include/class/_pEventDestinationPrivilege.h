//---------------------------------------------------------------------
// <copyright file="_pEventDestinationPrivilege.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "SnapperPrivilege.h" 

namespace snapper { namespace providers 
{

class _pEventDestinationPrivilege: public SnapperPrivilege
{
public:
    _pEventDestinationPrivilege(): SnapperPrivilege("EventDestination")
    {
        add_base_priv("GET", "Login");
        add_base_priv("HEAD", "Login");
        add_base_priv("PATCH", "ConfigureAdvanced");
        add_base_priv("PATCH", "ConfigureNetworkingAndSecurity");
        add_base_priv("POST", "ConfigureManager");
        add_base_priv("PUT", "ConfigureManager");
        add_base_priv("DELETE", "ConfigureAdvanced");
        add_base_priv("DELETE", "ConfigureNetworkingAndSecurity");

    }

    virtual ~_pEventDestinationPrivilege() 
    {}

};

}}

