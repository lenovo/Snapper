//---------------------------------------------------------------------
// <copyright file="_pSessionService.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pSessionService : public ResourceProvider
{
public:
    _pSessionService() : ResourceProvider("SessionService")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("ServiceEnabled",  nullptr);
        create_prop("SessionTimeout",  nullptr);
        create_prop("Sessions",  nullptr);
        create_prop("Status",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("SessionService.v1_1_3");
        set_desc("This is the schema definition for the Session Service.  It represents the properties for the service itself and has links to the actual list of sessions.");
    }

    virtual ~_pSessionService()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("Sessions");
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
        add_property_class("ServiceEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("SessionTimeout", "Primitive Type.", "Edm.Int64");
        add_property_class("Sessions", "Navigation Type.Entity", "SessionCollection");
        add_property_class("Status", "Complex Type.", "Status");
    }

    void prep_prop_attrs()
    {
        auto Sessions_attr = std::make_shared<prop_attribute>();
        Sessions_attr->prop_name = "Sessions";
        Sessions_attr->read_only = true;
        add_property_attr("Sessions", Sessions_attr);

        auto ServiceEnabled_attr = std::make_shared<prop_attribute>();
        ServiceEnabled_attr->prop_name = "ServiceEnabled";
        ServiceEnabled_attr->read_only = false;
        add_property_attr("ServiceEnabled", ServiceEnabled_attr);

        auto SessionTimeout_attr = std::make_shared<prop_attribute>();
        SessionTimeout_attr->prop_name = "SessionTimeout";
        SessionTimeout_attr->read_only = false;
        add_property_attr("SessionTimeout", SessionTimeout_attr);

     }

};

}}

