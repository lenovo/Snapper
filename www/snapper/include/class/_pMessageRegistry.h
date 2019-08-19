//---------------------------------------------------------------------
// <copyright file="_pMessageRegistry.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pMessageRegistry : public ResourceProvider
{
public:
    _pMessageRegistry() : ResourceProvider("MessageRegistry")    
    {
        enum ParamType 
        {
            ParamType_string,
            ParamType_number,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Language",  nullptr);
        create_prop("Messages",  nullptr);
        create_prop("OwningEntity",  nullptr);
        create_prop("RegistryPrefix",  nullptr);
        create_prop("RegistryVersion",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("MessageRegistry.v1_1_1");
        set_desc("This is the schema definition for all Message Registries.  It represents the properties for the registries themselves.  The MessageId is formed per the Redfish specification.  It consists of the RegistryPrefix concatenated with the version concatenated with the unique identifier for the message registry entry.");
    }

    virtual ~_pMessageRegistry()    
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
        add_property_class("Language", "Primitive Type.", "Edm.String");
        add_property_class("Messages", "Complex Type.", "MessageProperty");
        add_property_class("OwningEntity", "Primitive Type.", "Edm.String");
        add_property_class("RegistryPrefix", "Primitive Type.", "Edm.String");
        add_property_class("RegistryVersion", "Primitive Type.", "Edm.String");
    }

    void prep_prop_attrs()
    {
        auto OwningEntity_attr = std::make_shared<prop_attribute>();
        OwningEntity_attr->prop_name = "OwningEntity";
        OwningEntity_attr->read_only = true;
        add_property_attr("OwningEntity", OwningEntity_attr);

        auto RegistryVersion_attr = std::make_shared<prop_attribute>();
        RegistryVersion_attr->prop_name = "RegistryVersion";
        RegistryVersion_attr->read_only = true;
        add_property_attr("RegistryVersion", RegistryVersion_attr);

        auto RegistryPrefix_attr = std::make_shared<prop_attribute>();
        RegistryPrefix_attr->prop_name = "RegistryPrefix";
        RegistryPrefix_attr->read_only = true;
        add_property_attr("RegistryPrefix", RegistryPrefix_attr);

        auto Language_attr = std::make_shared<prop_attribute>();
        Language_attr->prop_name = "Language";
        Language_attr->read_only = true;
        add_property_attr("Language", Language_attr);

     }

};

}}

