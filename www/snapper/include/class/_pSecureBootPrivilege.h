//---------------------------------------------------------------------
// <copyright file="_pSecureBootPrivilege.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "SnapperPrivilege.h" 

namespace snapper { namespace providers 
{

class _pSecureBootPrivilege: public SnapperPrivilege
{
public:
    _pSecureBootPrivilege(): SnapperPrivilege("SecureBoot")
    {
        add_base_priv("GET", "Login");
        add_base_priv("HEAD", "Login");
        add_base_priv("PATCH", "ConfigureAdvanced");
        add_base_priv("PATCH", "ConfigureNetworkingAndSecurity");
        add_base_priv("POST", "ConfigureComponents");
        add_base_priv("PUT", "ConfigureComponents");
        add_base_priv("DELETE", "ConfigureComponents");

    }

    virtual ~_pSecureBootPrivilege() 
    {}

};

}}

