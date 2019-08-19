//---------------------------------------------------------------------
// <copyright file="_pServiceRootPrivilege.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "SnapperPrivilege.h" 

namespace snapper { namespace providers 
{

class _pServiceRootPrivilege: public SnapperPrivilege
{
public:
    _pServiceRootPrivilege(): SnapperPrivilege("ServiceRoot")
    {
        add_base_priv("GET", "Login");
        add_base_priv("HEAD", "Login");
        add_base_priv("PATCH", "ConfigureManager");
        add_base_priv("PUT", "ConfigureManager");
        add_base_priv("DELETE", "ConfigureManager");
        add_base_priv("POST", "ConfigureManager");

    }

    virtual ~_pServiceRootPrivilege() 
    {}

};

}}

