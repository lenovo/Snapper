//---------------------------------------------------------------------
// <copyright file="_pComputerSystemPrivilege.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "SnapperPrivilege.h" 

namespace snapper { namespace providers 
{

class _pComputerSystemPrivilege: public SnapperPrivilege
{
public:
    _pComputerSystemPrivilege(): SnapperPrivilege("ComputerSystem")
    {
        add_base_priv("GET", "Login");
        add_base_priv("HEAD", "Login");
        add_base_priv("PATCH", "ConfigureComponents");
        add_base_priv("POST", "ConfigureComponents");
        add_base_priv("PUT", "ConfigureComponents");
        add_base_priv("DELETE", "ConfigureComponents");

        add_prop_priv("IndicatorLED", "PATCH", "ConfigureBasic");
        add_prop_priv("IndicatorLED", "PATCH", "ConfigureAdvanced");

        add_prop_priv("AssetTag", "PATCH", "ConfigureNetworkingAndSecurity");
        add_prop_priv("AssetTag", "PATCH", "ConfigureAdvanced");

        add_prop_priv("HostName", "PATCH", "ConfigureNetworkingAndSecurity");
        add_prop_priv("HostName", "PATCH", "ConfigureAdvanced");

        add_prop_priv("Boot", "PATCH", "ConfigureAdvanced");

        add_prop_priv("HostWatchdogTimer", "PATCH", "RemoteServerPowerRestartAccess");

    }

    virtual ~_pComputerSystemPrivilege() 
    {}

};

}}

