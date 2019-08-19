//---------------------------------------------------------------------
// <copyright file="_pEventDestination.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pEventDestination : public ResourceProvider
{
public:
    _pEventDestination() : ResourceProvider("EventDestination")    
    {
        enum EventDestinationProtocol 
        {
            EventDestinationProtocol_Redfish,
        };

        enum SubscriptionType 
        {
            SubscriptionType_RedfishEvent,
            SubscriptionType_SSE,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Context",  nullptr);
        create_prop("Destination",  nullptr);
        create_prop("EventTypes",  nullptr);
        create_prop("HttpHeaders",  nullptr);
        create_prop("MessageIds",  nullptr);
        create_prop("OriginResources",  nullptr);
        create_prop("OriginResources@odata.count",  nullptr);
        create_prop("OriginResources@odata.navigationLink",  nullptr);
        create_prop("Protocol",  nullptr);
        create_prop("SubscriptionType",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("EventDestination.v1_3_0");
        set_desc("An Event Destination desribes the target of an event subscription, including the types of events subscribed and context to provide to the target in the Event payload.");
    }

    virtual ~_pEventDestination()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_arr_props("OriginResources");
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
        add_property_class("Destination", "Primitive Type.", "Edm.String");
        add_property_class("EventTypes", "Collection Type.", "EventType");
        add_property_class("HttpHeaders", "Collection Type.", "HttpHeaderProperty");
        add_property_class("MessageIds", "Collection Type.", "Edm.String");
        add_property_class("OriginResources", "Navigation Type.Collection", "ItemOrCollection");
        add_property_class("Protocol", "Enum Type.", "EventDestinationProtocol");
        add_property_class("SubscriptionType", "Enum Type.", "SubscriptionType");
    }

    void prep_prop_attrs()
    {
        auto Context_attr = std::make_shared<prop_attribute>();
        Context_attr->prop_name = "Context";
        Context_attr->read_only = false;
        add_property_attr("Context", Context_attr);

        auto Protocol_attr = std::make_shared<prop_attribute>();
        Protocol_attr->prop_name = "Protocol";
        Protocol_attr->read_only = true;
        Protocol_attr->add_enum("Redfish");
        Protocol_attr->required_on_create = true;
        add_property_attr("Protocol", Protocol_attr);

        auto EventTypes_attr = std::make_shared<prop_attribute>();
        EventTypes_attr->prop_name = "EventTypes";
        EventTypes_attr->read_only = true;
        EventTypes_attr->add_enum("StatusChange");
        EventTypes_attr->add_enum("ResourceUpdated");
        EventTypes_attr->add_enum("ResourceAdded");
        EventTypes_attr->add_enum("ResourceRemoved");
        EventTypes_attr->add_enum("Alert");
        EventTypes_attr->required_on_create = true;
        add_property_attr("EventTypes", EventTypes_attr);

        auto Destination_attr = std::make_shared<prop_attribute>();
        Destination_attr->prop_name = "Destination";
        Destination_attr->read_only = true;
        Destination_attr->required_on_create = true;
        add_property_attr("Destination", Destination_attr);

        auto MessageIds_attr = std::make_shared<prop_attribute>();
        MessageIds_attr->prop_name = "MessageIds";
        MessageIds_attr->read_only = true;
        add_property_attr("MessageIds", MessageIds_attr);

        auto OriginResources_attr = std::make_shared<prop_attribute>();
        OriginResources_attr->prop_name = "OriginResources";
        OriginResources_attr->read_only = true;
        add_property_attr("OriginResources", OriginResources_attr);

        auto SubscriptionType_attr = std::make_shared<prop_attribute>();
        SubscriptionType_attr->prop_name = "SubscriptionType";
        SubscriptionType_attr->read_only = true;
        SubscriptionType_attr->add_enum("RedfishEvent");
        SubscriptionType_attr->add_enum("SSE");
        add_property_attr("SubscriptionType", SubscriptionType_attr);

     }

};

}}

