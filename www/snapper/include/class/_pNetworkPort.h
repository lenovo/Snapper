//---------------------------------------------------------------------
// <copyright file="_pNetworkPort.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pNetworkPort : public ResourceProvider
{
public:
    _pNetworkPort() : ResourceProvider("NetworkPort")    
    {
        enum FlowControl 
        {
            FlowControl_None,
            FlowControl_TX,
            FlowControl_RX,
            FlowControl_TX_RX,
        };

        enum SupportedEthernetCapabilities 
        {
            SupportedEthernetCapabilities_WakeOnLAN,
            SupportedEthernetCapabilities_EEE,
        };

        enum LinkNetworkTechnology 
        {
            LinkNetworkTechnology_Ethernet,
            LinkNetworkTechnology_InfiniBand,
            LinkNetworkTechnology_FibreChannel,
        };

        enum LinkStatus 
        {
            LinkStatus_Down,
            LinkStatus_Up,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("ActiveLinkTechnology",  nullptr);
        create_prop("AssociatedNetworkAddresses",  nullptr);
        create_prop("EEEEnabled",  nullptr);
        create_prop("FlowControlConfiguration",  nullptr);
        create_prop("FlowControlStatus",  nullptr);
        create_prop("LinkStatus",  nullptr);
        create_prop("NetDevFuncMaxBWAlloc",  nullptr);
        create_prop("NetDevFuncMinBWAlloc",  nullptr);
        create_prop("PhysicalPortNumber",  nullptr);
        create_prop("PortMaximumMTU",  nullptr);
        create_prop("SignalDetected",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("SupportedEthernetCapabilities",  nullptr);
        create_prop("SupportedLinkCapabilities",  nullptr);
        create_prop("WakeOnLANEnabled",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("NetworkPort.v1_1_0");
        set_desc("A Network Port represents a discrete physical port capable of connecting to a network.");
    }

    virtual ~_pNetworkPort()    
    {}

    void prepare_navigation_property()
    {
    }

        
    void prepare_Links()
    {
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("ActiveLinkTechnology", "Enum Type.", "LinkNetworkTechnology");
        add_property_class("AssociatedNetworkAddresses", "Collection Type.", "Edm.String");
        add_property_class("EEEEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("FlowControlConfiguration", "Enum Type.", "FlowControl");
        add_property_class("FlowControlStatus", "Enum Type.", "FlowControl");
        add_property_class("LinkStatus", "Enum Type.", "LinkStatus");
        add_property_class("NetDevFuncMaxBWAlloc", "Collection Type.", "NetDevFuncMaxBWAlloc");
        add_property_class("NetDevFuncMinBWAlloc", "Collection Type.", "NetDevFuncMinBWAlloc");
        add_property_class("PhysicalPortNumber", "Primitive Type.", "Edm.String");
        add_property_class("PortMaximumMTU", "Primitive Type.", "Edm.Int64");
        add_property_class("SignalDetected", "Primitive Type.", "Edm.Boolean");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("SupportedEthernetCapabilities", "Collection Type.", "SupportedEthernetCapabilities");
        add_property_class("SupportedLinkCapabilities", "Collection Type.", "SupportedLinkCapabilities");
        add_property_class("WakeOnLANEnabled", "Primitive Type.", "Edm.Boolean");
    }

    void prep_prop_attrs()
    {
        auto SignalDetected_attr = std::make_shared<prop_attribute>();
        SignalDetected_attr->prop_name = "SignalDetected";
        SignalDetected_attr->read_only = true;
        add_property_attr("SignalDetected", SignalDetected_attr);

        auto FlowControlConfiguration_attr = std::make_shared<prop_attribute>();
        FlowControlConfiguration_attr->prop_name = "FlowControlConfiguration";
        FlowControlConfiguration_attr->read_only = false;
        FlowControlConfiguration_attr->add_enum("None");
        FlowControlConfiguration_attr->add_enum("TX");
        FlowControlConfiguration_attr->add_enum("RX");
        FlowControlConfiguration_attr->add_enum("TX_RX");
        add_property_attr("FlowControlConfiguration", FlowControlConfiguration_attr);

        auto FlowControlStatus_attr = std::make_shared<prop_attribute>();
        FlowControlStatus_attr->prop_name = "FlowControlStatus";
        FlowControlStatus_attr->read_only = true;
        FlowControlStatus_attr->add_enum("None");
        FlowControlStatus_attr->add_enum("TX");
        FlowControlStatus_attr->add_enum("RX");
        FlowControlStatus_attr->add_enum("TX_RX");
        add_property_attr("FlowControlStatus", FlowControlStatus_attr);

        auto PortMaximumMTU_attr = std::make_shared<prop_attribute>();
        PortMaximumMTU_attr->prop_name = "PortMaximumMTU";
        PortMaximumMTU_attr->read_only = true;
        add_property_attr("PortMaximumMTU", PortMaximumMTU_attr);

        auto WakeOnLANEnabled_attr = std::make_shared<prop_attribute>();
        WakeOnLANEnabled_attr->prop_name = "WakeOnLANEnabled";
        WakeOnLANEnabled_attr->read_only = false;
        add_property_attr("WakeOnLANEnabled", WakeOnLANEnabled_attr);

        auto PhysicalPortNumber_attr = std::make_shared<prop_attribute>();
        PhysicalPortNumber_attr->prop_name = "PhysicalPortNumber";
        PhysicalPortNumber_attr->read_only = true;
        add_property_attr("PhysicalPortNumber", PhysicalPortNumber_attr);

        auto LinkStatus_attr = std::make_shared<prop_attribute>();
        LinkStatus_attr->prop_name = "LinkStatus";
        LinkStatus_attr->read_only = true;
        LinkStatus_attr->add_enum("Down");
        LinkStatus_attr->add_enum("Up");
        add_property_attr("LinkStatus", LinkStatus_attr);

        auto ActiveLinkTechnology_attr = std::make_shared<prop_attribute>();
        ActiveLinkTechnology_attr->prop_name = "ActiveLinkTechnology";
        ActiveLinkTechnology_attr->read_only = false;
        ActiveLinkTechnology_attr->add_enum("Ethernet");
        ActiveLinkTechnology_attr->add_enum("InfiniBand");
        ActiveLinkTechnology_attr->add_enum("FibreChannel");
        add_property_attr("ActiveLinkTechnology", ActiveLinkTechnology_attr);

        auto SupportedEthernetCapabilities_attr = std::make_shared<prop_attribute>();
        SupportedEthernetCapabilities_attr->prop_name = "SupportedEthernetCapabilities";
        SupportedEthernetCapabilities_attr->read_only = true;
        SupportedEthernetCapabilities_attr->add_enum("WakeOnLAN");
        SupportedEthernetCapabilities_attr->add_enum("EEE");
        add_property_attr("SupportedEthernetCapabilities", SupportedEthernetCapabilities_attr);

        auto AssociatedNetworkAddresses_attr = std::make_shared<prop_attribute>();
        AssociatedNetworkAddresses_attr->prop_name = "AssociatedNetworkAddresses";
        AssociatedNetworkAddresses_attr->read_only = true;
        add_property_attr("AssociatedNetworkAddresses", AssociatedNetworkAddresses_attr);

        auto EEEEnabled_attr = std::make_shared<prop_attribute>();
        EEEEnabled_attr->prop_name = "EEEEnabled";
        EEEEnabled_attr->read_only = false;
        add_property_attr("EEEEnabled", EEEEnabled_attr);

     }

};

}}

