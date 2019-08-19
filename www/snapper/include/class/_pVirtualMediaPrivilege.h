//---------------------------------------------------------------------
// <copyright file="_pVirtualMediaPrivilege.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "SnapperPrivilege.h" 

namespace snapper { namespace providers 
{

class _pVirtualMediaPrivilege: public SnapperPrivilege
{
public:
    _pVirtualMediaPrivilege(): SnapperPrivilege("VirtualMedia")
    {
        add_base_priv("GET", "Login");
        add_base_priv("HEAD", "Login");
        add_base_priv("PATCH", "RemoteConsoleAccess");
        add_base_priv("PATCH", "RemoteConsoleAndVirtualMediaAcccess");
        add_base_priv("PUT", "ConfigureManager");
        add_base_priv("DELETE", "ConfigureManager");
        add_base_priv("POST", "ConfigureManager");

    }

    virtual ~_pVirtualMediaPrivilege() 
    {}

};

}}

