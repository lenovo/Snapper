//---------------------------------------------------------------------
// <copyright file="_pManagerNetworkProtocol.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pManagerNetworkProtocol : public ResourceProvider
{
public:
    _pManagerNetworkProtocol() : ResourceProvider("ManagerNetworkProtocol")    
    {
        enum NotifyIPv6Scope 
        {
            NotifyIPv6Scope_Link,
            NotifyIPv6Scope_Site,
            NotifyIPv6Scope_Organization,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("DHCP",  nullptr);
        create_prop("FQDN",  nullptr);
        create_prop("HTTP",  nullptr);
        create_prop("HTTPS",  nullptr);
        create_prop("HostName",  nullptr);
        create_prop("IPMI",  nullptr);
        create_prop("KVMIP",  nullptr);
        create_prop("NTP",  nullptr);
        create_prop("SNMP",  nullptr);
        create_prop("SSDP",  nullptr);
        create_prop("SSH",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("Telnet",  nullptr);
        create_prop("VirtualMedia",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("ManagerNetworkProtocol.v1_2_0");
        set_desc("This resource is used to obtain or modify the network services managed by a given manager.");
    }

    virtual ~_pManagerNetworkProtocol()    
    {}

    void prepare_navigation_property()
    {
    }

        
    void prepare_Links()
    {
    }

    void prepare_OemLenovo()
    {
        create_OemLenovo_prop("@odata.type", std::make_shared<bson::BSONObj>(BSON("@odata.type" << "#LenovoManagerNetworkProtocol.v1_0_0.Lenovo")));
        create_OemLenovo_prop("LDAPClient", nullptr);
        
        add_property_class("Oem/Lenovo/LDAPClient", "Navigation Type.Entity", "LenovoLDAPClient");
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("DHCP", "Complex Type.", "Protocol");
        add_property_class("FQDN", "Primitive Type.", "Edm.String");
        add_property_class("HTTP", "Complex Type.", "Protocol");
        add_property_class("HTTPS", "Complex Type.", "Protocol");
        add_property_class("HostName", "Primitive Type.", "Edm.String");
        add_property_class("IPMI", "Complex Type.", "Protocol");
        add_property_class("KVMIP", "Complex Type.", "Protocol");
        add_property_class("NTP", "Complex Type.", "NTPProtocol");
        add_property_class("SNMP", "Complex Type.", "Protocol");
        add_property_class("SSDP", "Complex Type.", "SSDProtocol");
        add_property_class("SSH", "Complex Type.", "Protocol");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("Telnet", "Complex Type.", "Protocol");
        add_property_class("VirtualMedia", "Complex Type.", "Protocol");
    }

    void prep_prop_attrs()
    {
        auto HostName_attr = std::make_shared<prop_attribute>();
        HostName_attr->prop_name = "HostName";
        HostName_attr->read_only = true;
        add_property_attr("HostName", HostName_attr);

        auto FQDN_attr = std::make_shared<prop_attribute>();
        FQDN_attr->prop_name = "FQDN";
        FQDN_attr->read_only = true;
        add_property_attr("FQDN", FQDN_attr);

     }

};

}}

