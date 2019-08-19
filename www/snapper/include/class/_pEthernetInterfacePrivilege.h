//---------------------------------------------------------------------
// <copyright file="_pEthernetInterfacePrivilege.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "SnapperPrivilege.h" 

namespace snapper { namespace providers 
{

class _pEthernetInterfacePrivilege: public SnapperPrivilege
{
public:
    _pEthernetInterfacePrivilege(): SnapperPrivilege("EthernetInterface")
    {
        add_base_priv("GET", "Login");
        add_base_priv("HEAD", "Login");
        add_base_priv("PATCH", "ConfigureComponents");
        add_base_priv("POST", "ConfigureComponents");
        add_base_priv("PUT", "ConfigureComponents");
        add_base_priv("DELETE", "ConfigureComponents");

        add_subordinate_priv("Manager/EthernetInterfaceCollection", "GET", "Login");
        add_subordinate_priv("Manager/EthernetInterfaceCollection", "PATCH", "ConfigureNetworkingAndSecurity");
        add_subordinate_priv("Manager/EthernetInterfaceCollection", "PATCH", "ConfigureAdvanced");

    }

    virtual ~_pEthernetInterfacePrivilege() 
    {}

};

}}

