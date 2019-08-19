//---------------------------------------------------------------------
// <copyright file="_pIPAddresses.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

        enum IPv6AddressOrigin 
        {
            IPv6AddressOrigin_Static,
            IPv6AddressOrigin_DHCPv6,
            IPv6AddressOrigin_LinkLocal,
            IPv6AddressOrigin_SLAAC,
        };

        enum AddressState 
        {
            AddressState_Preferred,
            AddressState_Deprecated,
            AddressState_Tentative,
            AddressState_Failed,
        };

        enum IPv4AddressOrigin 
        {
            IPv4AddressOrigin_Static,
            IPv4AddressOrigin_DHCP,
            IPv4AddressOrigin_BOOTP,
            IPv4AddressOrigin_IPv4LinkLocal,
        };

