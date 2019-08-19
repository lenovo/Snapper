//---------------------------------------------------------------------
// <copyright file="_pEventRecord.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pEventRecord : public ReferenceableMemberProvider
{
public:
    _pEventRecord() : ReferenceableMemberProvider("EventRecord")    
    {
        create_prop("Oem",  nullptr);
        create_prop("MemberId",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("EventId",  nullptr);
        create_prop("EventTimestamp",  nullptr);
        create_prop("EventType",  nullptr);
        create_prop("Message",  nullptr);
        create_prop("MessageArgs",  nullptr);
        create_prop("MessageId",  nullptr);
        create_prop("OriginOfCondition",  nullptr);
        create_prop("Severity",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Event.v1_2_0");
    }

    virtual ~_pEventRecord()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_refer_props("OriginOfCondition");
    }

        
    void prepare_Links()
    {
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "EventRecordActions");
        add_property_class("Context", "Primitive Type.", "Edm.String");
        add_property_class("EventId", "Primitive Type.", "Edm.String");
        add_property_class("EventTimestamp", "Primitive Type.", "Edm.DateTimeOffset");
        add_property_class("EventType", "Enum Type.", "EventType");
        add_property_class("Message", "Primitive Type.", "Edm.String");
        add_property_class("MessageArgs", "Collection Type.", "Edm.String");
        add_property_class("MessageId", "Primitive Type.", "Edm.String");
        add_property_class("OriginOfCondition", "Navigation Type.Entity", "Item");
        add_property_class("Severity", "Primitive Type.", "Edm.String");
    }

    void prep_prop_attrs()
    {
        auto Context_attr = std::make_shared<prop_attribute>();
        Context_attr->prop_name = "Context";
        Context_attr->read_only = true;
        add_property_attr("Context", Context_attr);

        auto Message_attr = std::make_shared<prop_attribute>();
        Message_attr->prop_name = "Message";
        Message_attr->read_only = true;
        add_property_attr("Message", Message_attr);

        auto MessageArgs_attr = std::make_shared<prop_attribute>();
        MessageArgs_attr->prop_name = "MessageArgs";
        MessageArgs_attr->read_only = true;
        add_property_attr("MessageArgs", MessageArgs_attr);

        auto Severity_attr = std::make_shared<prop_attribute>();
        Severity_attr->prop_name = "Severity";
        Severity_attr->read_only = true;
        add_property_attr("Severity", Severity_attr);

        auto OriginOfCondition_attr = std::make_shared<prop_attribute>();
        OriginOfCondition_attr->prop_name = "OriginOfCondition";
        OriginOfCondition_attr->read_only = true;
        add_property_attr("OriginOfCondition", OriginOfCondition_attr);

        auto MessageId_attr = std::make_shared<prop_attribute>();
        MessageId_attr->prop_name = "MessageId";
        MessageId_attr->read_only = true;
        add_property_attr("MessageId", MessageId_attr);

        auto EventTimestamp_attr = std::make_shared<prop_attribute>();
        EventTimestamp_attr->prop_name = "EventTimestamp";
        EventTimestamp_attr->read_only = true;
        add_property_attr("EventTimestamp", EventTimestamp_attr);

        auto EventId_attr = std::make_shared<prop_attribute>();
        EventId_attr->prop_name = "EventId";
        EventId_attr->read_only = true;
        add_property_attr("EventId", EventId_attr);

        auto EventType_attr = std::make_shared<prop_attribute>();
        EventType_attr->prop_name = "EventType";
        EventType_attr->read_only = true;
        EventType_attr->add_enum("StatusChange");
        EventType_attr->add_enum("ResourceUpdated");
        EventType_attr->add_enum("ResourceAdded");
        EventType_attr->add_enum("ResourceRemoved");
        EventType_attr->add_enum("Alert");
        add_property_attr("EventType", EventType_attr);

     }

};

}}

