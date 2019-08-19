//---------------------------------------------------------------------
// <copyright file="_pEventService.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pEventService : public ResourceProvider
{
public:
    _pEventService() : ResourceProvider("EventService")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("DeliveryRetryAttempts",  nullptr);
        create_prop("DeliveryRetryIntervalSeconds",  nullptr);
        create_prop("EventTypesForSubscription",  nullptr);
        create_prop("ServerSentEventUri",  nullptr);
        create_prop("ServiceEnabled",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("Subscriptions",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("EventService.v1_1_0");
        set_desc("The Event Service resource contains properties for managing event subcriptions and generates the events sent to subscribers.  The resource has links to the actual collection of subscriptions (called Event Destinations).");
    }

    virtual ~_pEventService()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("Subscriptions");
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
                "#EventService.SubmitTestEvent"
                << BSON("target" << (get_base_odata_id() + "/Actions/EventService.SubmitTestEvent")
                << "title" << "SubmitTestEvent"
                << "EventType@Redfish.AllowableValues"
                << BSON_ARRAY("StatusChange"
                             << "ResourceUpdated"
                             << "ResourceAdded"
                             << "ResourceRemoved"
                             << "Alert"))
                )
                )) );
     }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("DeliveryRetryAttempts", "Primitive Type.", "Edm.Int64");
        add_property_class("DeliveryRetryIntervalSeconds", "Primitive Type.", "Edm.Int64");
        add_property_class("EventTypesForSubscription", "Collection Type.", "EventType");
        add_property_class("ServerSentEventUri", "Primitive Type.", "Edm.String");
        add_property_class("ServiceEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("Subscriptions", "Navigation Type.Entity", "EventDestinationCollection");
    }

    void prep_prop_attrs()
    {
        auto Subscriptions_attr = std::make_shared<prop_attribute>();
        Subscriptions_attr->prop_name = "Subscriptions";
        Subscriptions_attr->read_only = true;
        add_property_attr("Subscriptions", Subscriptions_attr);

        auto DeliveryRetryIntervalSeconds_attr = std::make_shared<prop_attribute>();
        DeliveryRetryIntervalSeconds_attr->prop_name = "DeliveryRetryIntervalSeconds";
        DeliveryRetryIntervalSeconds_attr->read_only = false;
        add_property_attr("DeliveryRetryIntervalSeconds", DeliveryRetryIntervalSeconds_attr);

        auto DeliveryRetryAttempts_attr = std::make_shared<prop_attribute>();
        DeliveryRetryAttempts_attr->prop_name = "DeliveryRetryAttempts";
        DeliveryRetryAttempts_attr->read_only = false;
        add_property_attr("DeliveryRetryAttempts", DeliveryRetryAttempts_attr);

        auto EventTypesForSubscription_attr = std::make_shared<prop_attribute>();
        EventTypesForSubscription_attr->prop_name = "EventTypesForSubscription";
        EventTypesForSubscription_attr->read_only = true;
        EventTypesForSubscription_attr->add_enum("StatusChange");
        EventTypesForSubscription_attr->add_enum("ResourceUpdated");
        EventTypesForSubscription_attr->add_enum("ResourceAdded");
        EventTypesForSubscription_attr->add_enum("ResourceRemoved");
        EventTypesForSubscription_attr->add_enum("Alert");
        add_property_attr("EventTypesForSubscription", EventTypesForSubscription_attr);

        auto ServiceEnabled_attr = std::make_shared<prop_attribute>();
        ServiceEnabled_attr->prop_name = "ServiceEnabled";
        ServiceEnabled_attr->read_only = false;
        add_property_attr("ServiceEnabled", ServiceEnabled_attr);

        auto ServerSentEventUri_attr = std::make_shared<prop_attribute>();
        ServerSentEventUri_attr->prop_name = "ServerSentEventUri";
        ServerSentEventUri_attr->read_only = true;
        add_property_attr("ServerSentEventUri", ServerSentEventUri_attr);

     }

};

}}

