//---------------------------------------------------------------------
// <copyright file="_pNetworkDeviceFunction.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pNetworkDeviceFunction : public ResourceProvider
{
public:
    _pNetworkDeviceFunction() : ResourceProvider("NetworkDeviceFunction")    
    {
        enum BootMode 
        {
            BootMode_Disabled,
            BootMode_PXE,
            BootMode_iSCSI,
            BootMode_FibreChannel,
            BootMode_FibreChannelOverEthernet,
        };

        enum WWNSource 
        {
            WWNSource_ConfiguredLocally,
            WWNSource_ProvidedByFabric,
        };

        enum AuthenticationMethod 
        {
            AuthenticationMethod_None,
            AuthenticationMethod_CHAP,
            AuthenticationMethod_MutualCHAP,
        };

        enum IPAddressType 
        {
            IPAddressType_IPv4,
            IPAddressType_IPv6,
        };

        enum NetworkDeviceTechnology 
        {
            NetworkDeviceTechnology_Disabled,
            NetworkDeviceTechnology_Ethernet,
            NetworkDeviceTechnology_FibreChannel,
            NetworkDeviceTechnology_iSCSI,
            NetworkDeviceTechnology_FibreChannelOverEthernet,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("AssignablePhysicalPorts",  nullptr);
        create_prop("AssignablePhysicalPorts@odata.count",  nullptr);
        create_prop("AssignablePhysicalPorts@odata.navigationLink",  nullptr);
        create_prop("BootMode",  nullptr);
        create_prop("DeviceEnabled",  nullptr);
        create_prop("Ethernet",  nullptr);
        create_prop("FibreChannel",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("MaxVirtualFunctions",  nullptr);
        create_prop("NetDevFuncCapabilities",  nullptr);
        create_prop("NetDevFuncType",  nullptr);
        create_prop("PhysicalPortAssignment",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("VirtualFunctionsEnabled",  nullptr);
        create_prop("iSCSIBoot",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("NetworkDeviceFunction.v1_2_1");
        set_desc("A Network Device Function represents a logical interface exposed by the network adapter.");
    }

    virtual ~_pNetworkDeviceFunction()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_arr_props("AssignablePhysicalPorts");
        add_navigation_refer_props("PhysicalPortAssignment");
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["Endpoints"] = nullptr;
        m_Links_prop_objs["Endpoints@odata.count"] = nullptr;
        m_Links_prop_objs["Endpoints@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["PCIeFunction"] = nullptr;
        add_Links_arr_props("Endpoints");
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("AssignablePhysicalPorts", "Navigation Type.Collection", "NetworkPort");
        add_property_class("BootMode", "Enum Type.", "BootMode");
        add_property_class("DeviceEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("Ethernet", "Complex Type.", "Ethernet");
        add_property_class("FibreChannel", "Complex Type.", "FibreChannel");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("MaxVirtualFunctions", "Primitive Type.", "Edm.Int64");
        add_property_class("NetDevFuncCapabilities", "Collection Type.", "NetworkDeviceTechnology");
        add_property_class("NetDevFuncType", "Enum Type.", "NetworkDeviceTechnology");
        add_property_class("PhysicalPortAssignment", "Navigation Type.Entity", "NetworkPort");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("VirtualFunctionsEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("iSCSIBoot", "Complex Type.", "iSCSIBoot");
    }

    void prep_prop_attrs()
    {
        auto MaxVirtualFunctions_attr = std::make_shared<prop_attribute>();
        MaxVirtualFunctions_attr->prop_name = "MaxVirtualFunctions";
        MaxVirtualFunctions_attr->read_only = true;
        add_property_attr("MaxVirtualFunctions", MaxVirtualFunctions_attr);

        auto VirtualFunctionsEnabled_attr = std::make_shared<prop_attribute>();
        VirtualFunctionsEnabled_attr->prop_name = "VirtualFunctionsEnabled";
        VirtualFunctionsEnabled_attr->read_only = true;
        add_property_attr("VirtualFunctionsEnabled", VirtualFunctionsEnabled_attr);

        auto DeviceEnabled_attr = std::make_shared<prop_attribute>();
        DeviceEnabled_attr->prop_name = "DeviceEnabled";
        DeviceEnabled_attr->read_only = false;
        add_property_attr("DeviceEnabled", DeviceEnabled_attr);

        auto NetDevFuncCapabilities_attr = std::make_shared<prop_attribute>();
        NetDevFuncCapabilities_attr->prop_name = "NetDevFuncCapabilities";
        NetDevFuncCapabilities_attr->read_only = true;
        NetDevFuncCapabilities_attr->add_enum("Disabled");
        NetDevFuncCapabilities_attr->add_enum("Ethernet");
        NetDevFuncCapabilities_attr->add_enum("FibreChannel");
        NetDevFuncCapabilities_attr->add_enum("iSCSI");
        NetDevFuncCapabilities_attr->add_enum("FibreChannelOverEthernet");
        add_property_attr("NetDevFuncCapabilities", NetDevFuncCapabilities_attr);

        auto BootMode_attr = std::make_shared<prop_attribute>();
        BootMode_attr->prop_name = "BootMode";
        BootMode_attr->read_only = false;
        BootMode_attr->add_enum("Disabled");
        BootMode_attr->add_enum("PXE");
        BootMode_attr->add_enum("iSCSI");
        BootMode_attr->add_enum("FibreChannel");
        BootMode_attr->add_enum("FibreChannelOverEthernet");
        add_property_attr("BootMode", BootMode_attr);

        auto NetDevFuncType_attr = std::make_shared<prop_attribute>();
        NetDevFuncType_attr->prop_name = "NetDevFuncType";
        NetDevFuncType_attr->read_only = false;
        NetDevFuncType_attr->add_enum("Disabled");
        NetDevFuncType_attr->add_enum("Ethernet");
        NetDevFuncType_attr->add_enum("FibreChannel");
        NetDevFuncType_attr->add_enum("iSCSI");
        NetDevFuncType_attr->add_enum("FibreChannelOverEthernet");
        add_property_attr("NetDevFuncType", NetDevFuncType_attr);

        auto AssignablePhysicalPorts_attr = std::make_shared<prop_attribute>();
        AssignablePhysicalPorts_attr->prop_name = "AssignablePhysicalPorts";
        AssignablePhysicalPorts_attr->read_only = true;
        add_property_attr("AssignablePhysicalPorts", AssignablePhysicalPorts_attr);

        auto PhysicalPortAssignment_attr = std::make_shared<prop_attribute>();
        PhysicalPortAssignment_attr->prop_name = "PhysicalPortAssignment";
        PhysicalPortAssignment_attr->read_only = true;
        add_property_attr("PhysicalPortAssignment", PhysicalPortAssignment_attr);

     }

};

}}

