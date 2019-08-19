//---------------------------------------------------------------------
// <copyright file="_pEthernetInterface.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pEthernetInterface : public ResourceProvider
{
public:
    _pEthernetInterface() : ResourceProvider("EthernetInterface")    
    {
        enum LinkStatus 
        {
            LinkStatus_LinkUp,
            LinkStatus_NoLink,
            LinkStatus_LinkDown,
        };

        enum DHCPv6OperatingMode 
        {
            DHCPv6OperatingMode_Stateful,
            DHCPv6OperatingMode_Stateless,
            DHCPv6OperatingMode_Disabled,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("AutoNeg",  nullptr);
        create_prop("DHCPv4",  nullptr);
        create_prop("DHCPv6",  nullptr);
        create_prop("FQDN",  nullptr);
        create_prop("FullDuplex",  nullptr);
        create_prop("HostName",  nullptr);
        create_prop("IPv4Addresses",  nullptr);
        create_prop("IPv4StaticAddresses",  nullptr);
        create_prop("IPv6AddressPolicyTable",  nullptr);
        create_prop("IPv6Addresses",  nullptr);
        create_prop("IPv6DefaultGateway",  nullptr);
        create_prop("IPv6StaticAddresses",  nullptr);
        create_prop("IPv6StaticDefaultGateways",  nullptr);
        create_prop("InterfaceEnabled",  nullptr);
        create_prop("LinkStatus",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("MACAddress",  nullptr);
        create_prop("MTUSize",  nullptr);
        create_prop("MaxIPv6StaticAddresses",  nullptr);
        create_prop("NameServers",  nullptr);
        create_prop("PermanentMACAddress",  nullptr);
        create_prop("SpeedMbps",  nullptr);
        create_prop("StatelessAddressAutoConfig",  nullptr);
        create_prop("StaticNameServers",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("UefiDevicePath",  nullptr);
        create_prop("VLAN",  nullptr);
        create_prop("VLANs",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("EthernetInterface.v1_4_0");
        set_desc("The EthernetInterface schema represents a single, logical ethernet interface or network interface controller (NIC).");
    }

    virtual ~_pEthernetInterface()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("VLANs");
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["Chassis"] = nullptr;
        m_Links_prop_objs["Endpoints"] = nullptr;
        m_Links_prop_objs["Endpoints@odata.count"] = nullptr;
        m_Links_prop_objs["Endpoints@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["HostInterface"] = nullptr;
        add_Links_arr_props("Endpoints");
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("AutoNeg", "Primitive Type.", "Edm.Boolean");
        add_property_class("DHCPv4", "Complex Type.", "DHCPv4Configuration");
        add_property_class("DHCPv6", "Complex Type.", "DHCPv6Configuration");
        add_property_class("FQDN", "Primitive Type.", "Edm.String");
        add_property_class("FullDuplex", "Primitive Type.", "Edm.Boolean");
        add_property_class("HostName", "Primitive Type.", "Edm.String");
        add_property_class("IPv4Addresses", "Collection Type.", "IPv4Address");
        add_property_class("IPv4StaticAddresses", "Collection Type.", "IPv4Address");
        add_property_class("IPv6AddressPolicyTable", "Collection Type.", "IPv6AddressPolicyEntry");
        add_property_class("IPv6Addresses", "Collection Type.", "IPv6Address");
        add_property_class("IPv6DefaultGateway", "Primitive Type.", "Edm.String");
        add_property_class("IPv6StaticAddresses", "Collection Type.", "IPv6StaticAddress");
        add_property_class("IPv6StaticDefaultGateways", "Collection Type.", "IPv6StaticAddress");
        add_property_class("InterfaceEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("LinkStatus", "Enum Type.", "LinkStatus");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("MACAddress", "Type Definition.", "Edm.String");
        add_property_class("MTUSize", "Primitive Type.", "Edm.Int64");
        add_property_class("MaxIPv6StaticAddresses", "Primitive Type.", "Edm.Int64");
        add_property_class("NameServers", "Collection Type.", "Edm.String");
        add_property_class("PermanentMACAddress", "Type Definition.", "Edm.String");
        add_property_class("SpeedMbps", "Primitive Type.", "Edm.Int64");
        add_property_class("StatelessAddressAutoConfig", "Complex Type.", "StatelessAddressAutoConfiguration");
        add_property_class("StaticNameServers", "Collection Type.", "Edm.String");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("UefiDevicePath", "Primitive Type.", "Edm.String");
        add_property_class("VLAN", "Complex Type.", "VLAN");
        add_property_class("VLANs", "Navigation Type.Entity", "VLanNetworkInterfaceCollection");
    }

    void prep_prop_attrs()
    {
        auto VLANs_attr = std::make_shared<prop_attribute>();
        VLANs_attr->prop_name = "VLANs";
        VLANs_attr->read_only = true;
        add_property_attr("VLANs", VLANs_attr);

        auto IPv6DefaultGateway_attr = std::make_shared<prop_attribute>();
        IPv6DefaultGateway_attr->prop_name = "IPv6DefaultGateway";
        IPv6DefaultGateway_attr->read_only = true;
        add_property_attr("IPv6DefaultGateway", IPv6DefaultGateway_attr);

        auto MaxIPv6StaticAddresses_attr = std::make_shared<prop_attribute>();
        MaxIPv6StaticAddresses_attr->prop_name = "MaxIPv6StaticAddresses";
        MaxIPv6StaticAddresses_attr->read_only = true;
        add_property_attr("MaxIPv6StaticAddresses", MaxIPv6StaticAddresses_attr);

        auto FQDN_attr = std::make_shared<prop_attribute>();
        FQDN_attr->prop_name = "FQDN";
        FQDN_attr->read_only = false;
        add_property_attr("FQDN", FQDN_attr);

        auto NameServers_attr = std::make_shared<prop_attribute>();
        NameServers_attr->prop_name = "NameServers";
        NameServers_attr->read_only = true;
        add_property_attr("NameServers", NameServers_attr);

        auto UefiDevicePath_attr = std::make_shared<prop_attribute>();
        UefiDevicePath_attr->prop_name = "UefiDevicePath";
        UefiDevicePath_attr->read_only = true;
        add_property_attr("UefiDevicePath", UefiDevicePath_attr);

        auto InterfaceEnabled_attr = std::make_shared<prop_attribute>();
        InterfaceEnabled_attr->prop_name = "InterfaceEnabled";
        InterfaceEnabled_attr->read_only = false;
        add_property_attr("InterfaceEnabled", InterfaceEnabled_attr);

        auto HostName_attr = std::make_shared<prop_attribute>();
        HostName_attr->prop_name = "HostName";
        HostName_attr->read_only = false;
        add_property_attr("HostName", HostName_attr);

        auto PermanentMACAddress_attr = std::make_shared<prop_attribute>();
        PermanentMACAddress_attr->prop_name = "PermanentMACAddress";
        PermanentMACAddress_attr->read_only = true;
        add_property_attr("PermanentMACAddress", PermanentMACAddress_attr);

        auto SpeedMbps_attr = std::make_shared<prop_attribute>();
        SpeedMbps_attr->prop_name = "SpeedMbps";
        SpeedMbps_attr->read_only = false;
        add_property_attr("SpeedMbps", SpeedMbps_attr);

        auto MACAddress_attr = std::make_shared<prop_attribute>();
        MACAddress_attr->prop_name = "MACAddress";
        MACAddress_attr->read_only = false;
        add_property_attr("MACAddress", MACAddress_attr);

        auto MTUSize_attr = std::make_shared<prop_attribute>();
        MTUSize_attr->prop_name = "MTUSize";
        MTUSize_attr->read_only = false;
        add_property_attr("MTUSize", MTUSize_attr);

        auto AutoNeg_attr = std::make_shared<prop_attribute>();
        AutoNeg_attr->prop_name = "AutoNeg";
        AutoNeg_attr->read_only = false;
        add_property_attr("AutoNeg", AutoNeg_attr);

        auto FullDuplex_attr = std::make_shared<prop_attribute>();
        FullDuplex_attr->prop_name = "FullDuplex";
        FullDuplex_attr->read_only = false;
        add_property_attr("FullDuplex", FullDuplex_attr);

        auto LinkStatus_attr = std::make_shared<prop_attribute>();
        LinkStatus_attr->prop_name = "LinkStatus";
        LinkStatus_attr->read_only = true;
        LinkStatus_attr->add_enum("LinkUp");
        LinkStatus_attr->add_enum("NoLink");
        LinkStatus_attr->add_enum("LinkDown");
        add_property_attr("LinkStatus", LinkStatus_attr);

        auto StaticNameServers_attr = std::make_shared<prop_attribute>();
        StaticNameServers_attr->prop_name = "StaticNameServers";
        StaticNameServers_attr->read_only = false;
        add_property_attr("StaticNameServers", StaticNameServers_attr);

     }

};

}}

