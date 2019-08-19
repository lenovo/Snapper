//---------------------------------------------------------------------
// <copyright file="_pLogEntry.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pLogEntry : public ResourceProvider
{
public:
    _pLogEntry() : ResourceProvider("LogEntry")    
    {
        enum LEDState 
        {
            LEDState_Lit,
            LEDState_Blinking,
            LEDState_Off,
            LEDState_ControlPattern,
        };

        enum Serviceable 
        {
            Serviceable_NotServiceable,
            Serviceable_ServiceableByLenovo,
            Serviceable_ServiceableByCustomer,
        };

        enum Source 
        {
            Source_Unknown,
            Source_Other,
            Source_Audit,
            Source_Cooling,
            Source_Power,
            Source_Disks,
            Source_Memory,
            Source_Processors,
            Source_System,
            Source_Test,
        };

        enum LogEntryType 
        {
            LogEntryType_Event,
            LogEntryType_SEL,
            LogEntryType_Oem,
        };

        enum EventSeverity 
        {
            EventSeverity_OK,
            EventSeverity_Warning,
            EventSeverity_Critical,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Created",  nullptr);
        create_prop("EntryCode",  nullptr);
        create_prop("EntryType",  nullptr);
        create_prop("EventId",  nullptr);
        create_prop("EventTimestamp",  nullptr);
        create_prop("EventType",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("Message",  nullptr);
        create_prop("MessageArgs",  nullptr);
        create_prop("MessageId",  nullptr);
        create_prop("OemLogEntryCode",  nullptr);
        create_prop("OemRecordFormat",  nullptr);
        create_prop("OemSensorType",  nullptr);
        create_prop("SensorNumber",  nullptr);
        create_prop("SensorType",  nullptr);
        create_prop("Severity",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("LogEntry.v1_3_0");
        set_desc("This resource defines the record format for a log.  It is designed to be used for SEL logs (from IPMI) as well as Event Logs and OEM-specific log formats.  The EntryType field indicates the type of log and the resource includes several additional properties dependent on the EntryType.");
    }

    virtual ~_pLogEntry()    
    {}

    void prepare_navigation_property()
    {
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["OriginOfCondition"] = nullptr;
    }

    void prepare_OemLenovo()
    {
        create_OemLenovo_prop("@odata.type", std::make_shared<bson::BSONObj>(BSON("@odata.type" << "#LenovoLogEntry.v1_0_0.Lenovo")));
        create_OemLenovo_prop("AffectedIndicatorLEDs", nullptr);
        create_OemLenovo_prop("AlertingManagedElement", nullptr);
        create_OemLenovo_prop("AuxiliaryData", nullptr);
        create_OemLenovo_prop("CommonEventID", nullptr);
        create_OemLenovo_prop("EventFlag", nullptr);
        create_OemLenovo_prop("EventID", nullptr);
        create_OemLenovo_prop("EventSequenceNumber", nullptr);
        create_OemLenovo_prop("EventType", nullptr);
        create_OemLenovo_prop("FailingFRU", nullptr);
        create_OemLenovo_prop("Hidden", nullptr);
        create_OemLenovo_prop("IsLocalEvent", nullptr);
        create_OemLenovo_prop("LenovoMessageID", nullptr);
        create_OemLenovo_prop("RawDebugLogURL", nullptr);
        create_OemLenovo_prop("RelatedEventID", nullptr);
        create_OemLenovo_prop("ReportingChain", nullptr);
        create_OemLenovo_prop("Serviceable", nullptr);
        create_OemLenovo_prop("Source", nullptr);
        create_OemLenovo_prop("TSLVersion", nullptr);
        
        add_property_class("Oem/Lenovo/AffectedIndicatorLEDs", "Collection Type.", "AffectedIndicatorLED");
        add_property_class("Oem/Lenovo/AlertingManagedElement", "Primitive Type.", "Edm.String");
        add_property_class("Oem/Lenovo/AuxiliaryData", "Primitive Type.", "Edm.String");
        add_property_class("Oem/Lenovo/CommonEventID", "Primitive Type.", "Edm.String");
        add_property_class("Oem/Lenovo/EventFlag", "Primitive Type.", "Edm.Int64");
        add_property_class("Oem/Lenovo/EventID", "Primitive Type.", "Edm.String");
        add_property_class("Oem/Lenovo/EventSequenceNumber", "Primitive Type.", "Edm.Int64");
        add_property_class("Oem/Lenovo/EventType", "Primitive Type.", "Edm.Int64");
        add_property_class("Oem/Lenovo/FailingFRU", "Collection Type.", "FailingFRUItem");
        add_property_class("Oem/Lenovo/Hidden", "Primitive Type.", "Edm.Boolean");
        add_property_class("Oem/Lenovo/IsLocalEvent", "Primitive Type.", "Edm.Boolean");
        add_property_class("Oem/Lenovo/LenovoMessageID", "Primitive Type.", "Edm.String");
        add_property_class("Oem/Lenovo/RawDebugLogURL", "Primitive Type.", "Edm.String");
        add_property_class("Oem/Lenovo/RelatedEventID", "Primitive Type.", "Edm.String");
        add_property_class("Oem/Lenovo/ReportingChain", "Primitive Type.", "Edm.String");
        add_property_class("Oem/Lenovo/Serviceable", "Enum Type.", "Serviceable");
        add_property_class("Oem/Lenovo/Source", "Enum Type.", "Source");
        add_property_class("Oem/Lenovo/TSLVersion", "Primitive Type.", "Edm.String");
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("Created", "Primitive Type.", "Edm.DateTimeOffset");
        add_property_class("EntryCode", "Type Definition.", "Edm.String");
        add_property_class("EntryType", "Enum Type.", "LogEntryType");
        add_property_class("EventId", "Primitive Type.", "Edm.String");
        add_property_class("EventTimestamp", "Primitive Type.", "Edm.DateTimeOffset");
        add_property_class("EventType", "Enum Type.", "EventType");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("Message", "Primitive Type.", "Edm.String");
        add_property_class("MessageArgs", "Collection Type.", "Edm.String");
        add_property_class("MessageId", "Primitive Type.", "Edm.String");
        add_property_class("OemLogEntryCode", "Primitive Type.", "Edm.String");
        add_property_class("OemRecordFormat", "Primitive Type.", "Edm.String");
        add_property_class("OemSensorType", "Primitive Type.", "Edm.String");
        add_property_class("SensorNumber", "Primitive Type.", "Edm.Int64");
        add_property_class("SensorType", "Type Definition.", "Edm.String");
        add_property_class("Severity", "Enum Type.", "EventSeverity");
    }

    void prep_prop_attrs()
    {
        auto Severity_attr = std::make_shared<prop_attribute>();
        Severity_attr->prop_name = "Severity";
        Severity_attr->read_only = true;
        Severity_attr->add_enum("OK");
        Severity_attr->add_enum("Warning");
        Severity_attr->add_enum("Critical");
        add_property_attr("Severity", Severity_attr);

        auto Created_attr = std::make_shared<prop_attribute>();
        Created_attr->prop_name = "Created";
        Created_attr->read_only = true;
        add_property_attr("Created", Created_attr);

        auto EntryType_attr = std::make_shared<prop_attribute>();
        EntryType_attr->prop_name = "EntryType";
        EntryType_attr->read_only = true;
        EntryType_attr->add_enum("Event");
        EntryType_attr->add_enum("SEL");
        EntryType_attr->add_enum("Oem");
        EntryType_attr->required_on_create = true;
        add_property_attr("EntryType", EntryType_attr);

        auto OemRecordFormat_attr = std::make_shared<prop_attribute>();
        OemRecordFormat_attr->prop_name = "OemRecordFormat";
        OemRecordFormat_attr->read_only = true;
        add_property_attr("OemRecordFormat", OemRecordFormat_attr);

        auto MessageArgs_attr = std::make_shared<prop_attribute>();
        MessageArgs_attr->prop_name = "MessageArgs";
        MessageArgs_attr->read_only = true;
        add_property_attr("MessageArgs", MessageArgs_attr);

        auto SensorType_attr = std::make_shared<prop_attribute>();
        SensorType_attr->prop_name = "SensorType";
        SensorType_attr->read_only = true;
        add_property_attr("SensorType", SensorType_attr);

        auto MessageId_attr = std::make_shared<prop_attribute>();
        MessageId_attr->prop_name = "MessageId";
        MessageId_attr->read_only = true;
        add_property_attr("MessageId", MessageId_attr);

        auto EntryCode_attr = std::make_shared<prop_attribute>();
        EntryCode_attr->prop_name = "EntryCode";
        EntryCode_attr->read_only = true;
        add_property_attr("EntryCode", EntryCode_attr);

        auto SensorNumber_attr = std::make_shared<prop_attribute>();
        SensorNumber_attr->prop_name = "SensorNumber";
        SensorNumber_attr->read_only = true;
        add_property_attr("SensorNumber", SensorNumber_attr);

        auto Message_attr = std::make_shared<prop_attribute>();
        Message_attr->prop_name = "Message";
        Message_attr->read_only = true;
        add_property_attr("Message", Message_attr);

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

        auto OemSensorType_attr = std::make_shared<prop_attribute>();
        OemSensorType_attr->prop_name = "OemSensorType";
        OemSensorType_attr->read_only = true;
        add_property_attr("OemSensorType", OemSensorType_attr);

        auto OemLogEntryCode_attr = std::make_shared<prop_attribute>();
        OemLogEntryCode_attr->prop_name = "OemLogEntryCode";
        OemLogEntryCode_attr->read_only = true;
        add_property_attr("OemLogEntryCode", OemLogEntryCode_attr);

     }

};

}}

