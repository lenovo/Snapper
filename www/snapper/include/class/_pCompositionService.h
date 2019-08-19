//---------------------------------------------------------------------
// <copyright file="_pCompositionService.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pCompositionService : public ResourceProvider
{
public:
    _pCompositionService() : ResourceProvider("CompositionService")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("ResourceBlocks",  nullptr);
        create_prop("ResourceZones",  nullptr);
        create_prop("ServiceEnabled",  nullptr);
        create_prop("Status",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("CompositionService.v1_0_1");
        set_desc("The CompositionService schema defines a Composition Service which represents the properties for the service and links to the resources available for composition.");
    }

    virtual ~_pCompositionService()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("ResourceZones");
        add_navigation_contained_props("ResourceBlocks");
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
        add_property_class("ResourceBlocks", "Navigation Type.Entity", "ResourceBlockCollection");
        add_property_class("ResourceZones", "Navigation Type.Entity", "ZoneCollection");
        add_property_class("ServiceEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("Status", "Complex Type.", "Status");
    }

    void prep_prop_attrs()
    {
        auto ResourceZones_attr = std::make_shared<prop_attribute>();
        ResourceZones_attr->prop_name = "ResourceZones";
        ResourceZones_attr->read_only = true;
        add_property_attr("ResourceZones", ResourceZones_attr);

        auto ResourceBlocks_attr = std::make_shared<prop_attribute>();
        ResourceBlocks_attr->prop_name = "ResourceBlocks";
        ResourceBlocks_attr->read_only = true;
        add_property_attr("ResourceBlocks", ResourceBlocks_attr);

        auto ServiceEnabled_attr = std::make_shared<prop_attribute>();
        ServiceEnabled_attr->prop_name = "ServiceEnabled";
        ServiceEnabled_attr->read_only = false;
        add_property_attr("ServiceEnabled", ServiceEnabled_attr);

     }

};

}}

