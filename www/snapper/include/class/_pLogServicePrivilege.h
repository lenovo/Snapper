//---------------------------------------------------------------------
// <copyright file="_pLogServicePrivilege.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "SnapperPrivilege.h" 

namespace snapper { namespace providers 
{

class _pLogServicePrivilege: public SnapperPrivilege
{
public:
    _pLogServicePrivilege(): SnapperPrivilege("LogService")
    {
        add_base_priv("GET", "Login");
        add_base_priv("HEAD", "Login");
        add_base_priv("PATCH", "ConfigureManager");
        add_base_priv("PUT", "ConfigureManager");
        add_base_priv("DELETE", "ConfigureManager");
        add_base_priv("POST", "AbilityClearEventLogs");

    }

    virtual ~_pLogServicePrivilege() 
    {}

};

}}

