//---------------------------------------------------------------------
// <copyright file="_pEvent.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pEvent : public ResourceProvider
{
public:
    _pEvent() : ResourceProvider("Event")    
    {
        enum EventType 
        {
            EventType_StatusChange,
            EventType_ResourceUpdated,
            EventType_ResourceAdded,
            EventType_ResourceRemoved,
            EventType_Alert,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Context",  nullptr);
        create_prop("Events",  nullptr);
        create_prop("Events@odata.count",  nullptr);
        create_prop("Events@odata.navigationLink",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Event.v1_2_1");
        set_desc("The Event schema describes the JSON payload received by an Event Destination (which has subscribed to event notification) when events occurs.  This resource contains data about event(s), including descriptions, severity and MessageId reference to a Message Registry that can be accessed for further information.");
    }

    virtual ~_pEvent()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_arr_props("Events");
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
        add_property_class("Context", "Primitive Type.", "Edm.String");
        add_property_class("Events", "Navigation Type.Collection", "EventRecord");
    }

    void prep_prop_attrs()
    {
        auto Context_attr = std::make_shared<prop_attribute>();
        Context_attr->prop_name = "Context";
        Context_attr->read_only = true;
        add_property_attr("Context", Context_attr);

     }

};

}}

