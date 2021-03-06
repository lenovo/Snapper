//---------------------------------------------------------------------
// <copyright file="_pTaskPrivilege.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "SnapperPrivilege.h" 

namespace snapper { namespace providers 
{

class _pTaskPrivilege: public SnapperPrivilege
{
public:
    _pTaskPrivilege(): SnapperPrivilege("Task")
    {
        add_base_priv("GET", "Login");
        add_base_priv("HEAD", "Login");
        add_base_priv("PATCH", "ConfigureManager");
        add_base_priv("PUT", "ConfigureManager");
        add_base_priv("DELETE", "ConfigureManager");
        add_base_priv("DELETE", "ConfigureAdvanced");
        add_base_priv("POST", "ConfigureManager");

    }

    virtual ~_pTaskPrivilege() 
    {}

};

}}

