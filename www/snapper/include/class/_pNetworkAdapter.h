//---------------------------------------------------------------------
// <copyright file="_pNetworkAdapter.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pNetworkAdapter : public ResourceProvider
{
public:
    _pNetworkAdapter() : ResourceProvider("NetworkAdapter")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Assembly",  nullptr);
        create_prop("Controllers",  nullptr);
        create_prop("Manufacturer",  nullptr);
        create_prop("Model",  nullptr);
        create_prop("NetworkDeviceFunctions",  nullptr);
        create_prop("NetworkPorts",  nullptr);
        create_prop("PartNumber",  nullptr);
        create_prop("SKU",  nullptr);
        create_prop("SerialNumber",  nullptr);
        create_prop("Status",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("NetworkAdapter.v1_1_0");
        set_desc("A NetworkAdapter represents the physical network adapter capable of connecting to a computer network.  Examples include but are not limited to Ethernet, Fibre Channel, and converged network adapters.");
    }

    virtual ~_pNetworkAdapter()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("NetworkPorts");
        add_navigation_contained_props("NetworkDeviceFunctions");
        add_navigation_contained_props("Assembly");
    }

        
    void prepare_Links()
    {
    }

    void prepare_OemLenovo()
    {
    }

    virtual void set_actions_obj()
    {
         create_prop( "Actions",   std::make_shared<bson::BSONObj>(BSON("Actions" << BSON(
                "#NetworkAdapter.ResetSettingsToDefault"
                << BSON("target" << (get_base_odata_id() + "/Actions/NetworkAdapter.ResetSettingsToDefault")
                << "title" << "ResetSettingsToDefault")
                )
                )) );
     }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("Assembly", "Navigation Type.Entity", "Assembly");
        add_property_class("Controllers", "Collection Type.", "Controllers");
        add_property_class("Manufacturer", "Primitive Type.", "Edm.String");
        add_property_class("Model", "Primitive Type.", "Edm.String");
        add_property_class("NetworkDeviceFunctions", "Navigation Type.Entity", "NetworkDeviceFunctionCollection");
        add_property_class("NetworkPorts", "Navigation Type.Entity", "NetworkPortCollection");
        add_property_class("PartNumber", "Primitive Type.", "Edm.String");
        add_property_class("SKU", "Primitive Type.", "Edm.String");
        add_property_class("SerialNumber", "Primitive Type.", "Edm.String");
        add_property_class("Status", "Complex Type.", "Status");
    }

    void prep_prop_attrs()
    {
        auto PartNumber_attr = std::make_shared<prop_attribute>();
        PartNumber_attr->prop_name = "PartNumber";
        PartNumber_attr->read_only = true;
        add_property_attr("PartNumber", PartNumber_attr);

        auto SerialNumber_attr = std::make_shared<prop_attribute>();
        SerialNumber_attr->prop_name = "SerialNumber";
        SerialNumber_attr->read_only = true;
        add_property_attr("SerialNumber", SerialNumber_attr);

        auto SKU_attr = std::make_shared<prop_attribute>();
        SKU_attr->prop_name = "SKU";
        SKU_attr->read_only = true;
        add_property_attr("SKU", SKU_attr);

        auto Model_attr = std::make_shared<prop_attribute>();
        Model_attr->prop_name = "Model";
        Model_attr->read_only = true;
        add_property_attr("Model", Model_attr);

        auto Manufacturer_attr = std::make_shared<prop_attribute>();
        Manufacturer_attr->prop_name = "Manufacturer";
        Manufacturer_attr->read_only = true;
        add_property_attr("Manufacturer", Manufacturer_attr);

        auto NetworkPorts_attr = std::make_shared<prop_attribute>();
        NetworkPorts_attr->prop_name = "NetworkPorts";
        NetworkPorts_attr->read_only = true;
        add_property_attr("NetworkPorts", NetworkPorts_attr);

        auto NetworkDeviceFunctions_attr = std::make_shared<prop_attribute>();
        NetworkDeviceFunctions_attr->prop_name = "NetworkDeviceFunctions";
        NetworkDeviceFunctions_attr->read_only = true;
        add_property_attr("NetworkDeviceFunctions", NetworkDeviceFunctions_attr);

        auto Assembly_attr = std::make_shared<prop_attribute>();
        Assembly_attr->prop_name = "Assembly";
        Assembly_attr->read_only = true;
        add_property_attr("Assembly", Assembly_attr);

     }

};

}}

