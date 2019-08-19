//---------------------------------------------------------------------
// <copyright file="_pNetworkInterface.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pNetworkInterface : public ResourceProvider
{
public:
    _pNetworkInterface() : ResourceProvider("NetworkInterface")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("NetworkDeviceFunctions",  nullptr);
        create_prop("NetworkPorts",  nullptr);
        create_prop("Status",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("NetworkInterface.v1_1_0");
        set_desc("A NetworkInterface contains references linking NetworkAdapter, NetworkPort, and NetworkDeviceFunction resources and represents the functionality available to the containing system.");
    }

    virtual ~_pNetworkInterface()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("NetworkPorts");
        add_navigation_contained_props("NetworkDeviceFunctions");
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["NetworkAdapter"] = nullptr;
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("NetworkDeviceFunctions", "Navigation Type.Entity", "NetworkDeviceFunctionCollection");
        add_property_class("NetworkPorts", "Navigation Type.Entity", "NetworkPortCollection");
        add_property_class("Status", "Complex Type.", "Status");
    }

    void prep_prop_attrs()
    {
        auto NetworkPorts_attr = std::make_shared<prop_attribute>();
        NetworkPorts_attr->prop_name = "NetworkPorts";
        NetworkPorts_attr->read_only = true;
        add_property_attr("NetworkPorts", NetworkPorts_attr);

        auto NetworkDeviceFunctions_attr = std::make_shared<prop_attribute>();
        NetworkDeviceFunctions_attr->prop_name = "NetworkDeviceFunctions";
        NetworkDeviceFunctions_attr->read_only = true;
        add_property_attr("NetworkDeviceFunctions", NetworkDeviceFunctions_attr);

     }

};

}}

