//---------------------------------------------------------------------
// <copyright file="_pManagerAccountPrivilege.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "SnapperPrivilege.h" 

namespace snapper { namespace providers 
{

class _pManagerAccountPrivilege: public SnapperPrivilege
{
public:
    _pManagerAccountPrivilege(): SnapperPrivilege("ManagerAccount")
    {
        add_base_priv("GET", "Login");
        add_base_priv("HEAD", "Login");
        add_base_priv("PATCH", "ConfigureUsers");
        add_base_priv("PATCH", "UserAccountManagement");
        add_base_priv("POST", "ConfigureUsers");
        add_base_priv("PUT", "ConfigureUsers");
        add_base_priv("DELETE", "ConfigureUsers");
        add_base_priv("DELETE", "UserAccountManagement");

    }

    virtual ~_pManagerAccountPrivilege() 
    {}

};

}}

