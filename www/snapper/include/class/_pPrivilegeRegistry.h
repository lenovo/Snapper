//---------------------------------------------------------------------
// <copyright file="_pPrivilegeRegistry.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pPrivilegeRegistry : public ResourceProvider
{
public:
    _pPrivilegeRegistry() : ResourceProvider("PrivilegeRegistry")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Mappings",  nullptr);
        create_prop("OEMPrivilegesUsed",  nullptr);
        create_prop("PrivilegesUsed",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("PrivilegeRegistry.v1_1_1");
        set_desc("This is the schema definition for Operation to Privilege mapping.");
    }

    virtual ~_pPrivilegeRegistry()    
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
        add_property_class("Mappings", "Collection Type.", "Mapping");
        add_property_class("OEMPrivilegesUsed", "Collection Type.", "Edm.String");
        add_property_class("PrivilegesUsed", "Collection Type.", "PrivilegeType");
    }

    void prep_prop_attrs()
    {
        auto OEMPrivilegesUsed_attr = std::make_shared<prop_attribute>();
        OEMPrivilegesUsed_attr->prop_name = "OEMPrivilegesUsed";
        OEMPrivilegesUsed_attr->read_only = false;
        add_property_attr("OEMPrivilegesUsed", OEMPrivilegesUsed_attr);

        auto PrivilegesUsed_attr = std::make_shared<prop_attribute>();
        PrivilegesUsed_attr->prop_name = "PrivilegesUsed";
        PrivilegesUsed_attr->read_only = false;
        PrivilegesUsed_attr->add_enum("Login");
        PrivilegesUsed_attr->add_enum("ConfigureManager");
        PrivilegesUsed_attr->add_enum("ConfigureUsers");
        PrivilegesUsed_attr->add_enum("ConfigureSelf");
        PrivilegesUsed_attr->add_enum("ConfigureComponents");
        add_property_attr("PrivilegesUsed", PrivilegesUsed_attr);

     }

};

}}

