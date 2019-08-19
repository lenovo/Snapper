//---------------------------------------------------------------------
// <copyright file="_pSessionCollectionPrivilege.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "SnapperPrivilege.h" 

namespace snapper { namespace providers 
{

class _pSessionCollectionPrivilege: public SnapperPrivilege
{
public:
    _pSessionCollectionPrivilege(): SnapperPrivilege("SessionCollection")
    {
        add_base_priv("GET", "Login");
        add_base_priv("HEAD", "Login");
        add_base_priv("PATCH", "ConfigureManager");
        add_base_priv("PUT", "ConfigureManager");
        add_base_priv("DELETE", "ConfigureManager");
        add_base_priv("POST", "UserAccountManagement");
        add_base_priv("POST", "ConfigureUsers");

    }

    virtual ~_pSessionCollectionPrivilege() 
    {}

};

}}

