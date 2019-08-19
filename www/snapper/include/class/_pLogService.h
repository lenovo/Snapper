//---------------------------------------------------------------------
// <copyright file="_pLogService.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pLogService : public ResourceProvider
{
public:
    _pLogService() : ResourceProvider("LogService")    
    {
        enum OverWritePolicy 
        {
            OverWritePolicy_Unknown,
            OverWritePolicy_WrapsWhenFull,
            OverWritePolicy_NeverOverWrites,
        };

        enum LogEntryTypes 
        {
            LogEntryTypes_Event,
            LogEntryTypes_SEL,
            LogEntryTypes_Multiple,
            LogEntryTypes_OEM,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("DateTime",  nullptr);
        create_prop("DateTimeLocalOffset",  nullptr);
        create_prop("Entries",  nullptr);
        create_prop("LogEntryType",  nullptr);
        create_prop("MaxNumberOfRecords",  nullptr);
        create_prop("OverWritePolicy",  nullptr);
        create_prop("ServiceEnabled",  nullptr);
        create_prop("Status",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("LogService.v1_1_0");
        set_desc("This resource represents the log service for the resource or service to which it is associated.");
    }

    virtual ~_pLogService()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("Entries");
    }

        
    void prepare_Links()
    {
    }

    void prepare_OemLenovo()
    {
        create_OemLenovo_prop("@odata.type", std::make_shared<bson::BSONObj>(BSON("@odata.type" << "#LenovoLogService.v1_0_0.Lenovo")));
        create_OemLenovo_prop("AuditFristSeqNum", nullptr);
        create_OemLenovo_prop("AuditLastSeqNum", nullptr);
        create_OemLenovo_prop("DesiredCategories", nullptr);
        create_OemLenovo_prop("PlatformFirstSeqNum", nullptr);
        create_OemLenovo_prop("PlatformLastSeqNum", nullptr);
        create_OemLenovo_prop("SupportedCategories", nullptr);
        create_OemLenovo_prop("VMMoveCategory", nullptr);
        
        add_property_class("Oem/Lenovo/AuditFristSeqNum", "Primitive Type.", "Edm.Int64");
        add_property_class("Oem/Lenovo/AuditLastSeqNum", "Primitive Type.", "Edm.Int64");
        add_property_class("Oem/Lenovo/DesiredCategories", "Primitive Type.", "Edm.Int64");
        add_property_class("Oem/Lenovo/PlatformFirstSeqNum", "Primitive Type.", "Edm.Int64");
        add_property_class("Oem/Lenovo/PlatformLastSeqNum", "Primitive Type.", "Edm.Int64");
        add_property_class("Oem/Lenovo/SupportedCategories", "Primitive Type.", "Edm.Int64");
        add_property_class("Oem/Lenovo/VMMoveCategory", "Collection Type.", "VMMoveCategoryItem");
    }

    virtual void set_actions_obj()
    {
         create_prop( "Actions",   std::make_shared<bson::BSONObj>(BSON("Actions" << BSON(
                "#LogService.ClearLog"
                << BSON("target" << (get_base_odata_id() + "/Actions/LogService.ClearLog")
                << "title" << "ClearLog")
                )
                )) );
     }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("DateTime", "Primitive Type.", "Edm.DateTimeOffset");
        add_property_class("DateTimeLocalOffset", "Primitive Type.", "Edm.String");
        add_property_class("Entries", "Navigation Type.Entity", "LogEntryCollection");
        add_property_class("LogEntryType", "Enum Type.", "LogEntryTypes");
        add_property_class("MaxNumberOfRecords", "Primitive Type.", "Edm.Int64");
        add_property_class("OverWritePolicy", "Enum Type.", "OverWritePolicy");
        add_property_class("ServiceEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("Status", "Complex Type.", "Status");
    }

    void prep_prop_attrs()
    {
        auto Entries_attr = std::make_shared<prop_attribute>();
        Entries_attr->prop_name = "Entries";
        Entries_attr->read_only = true;
        add_property_attr("Entries", Entries_attr);

        auto DateTime_attr = std::make_shared<prop_attribute>();
        DateTime_attr->prop_name = "DateTime";
        DateTime_attr->read_only = false;
        add_property_attr("DateTime", DateTime_attr);

        auto DateTimeLocalOffset_attr = std::make_shared<prop_attribute>();
        DateTimeLocalOffset_attr->prop_name = "DateTimeLocalOffset";
        DateTimeLocalOffset_attr->read_only = false;
        add_property_attr("DateTimeLocalOffset", DateTimeLocalOffset_attr);

        auto OverWritePolicy_attr = std::make_shared<prop_attribute>();
        OverWritePolicy_attr->prop_name = "OverWritePolicy";
        OverWritePolicy_attr->read_only = true;
        OverWritePolicy_attr->add_enum("Unknown");
        OverWritePolicy_attr->add_enum("WrapsWhenFull");
        OverWritePolicy_attr->add_enum("NeverOverWrites");
        add_property_attr("OverWritePolicy", OverWritePolicy_attr);

        auto MaxNumberOfRecords_attr = std::make_shared<prop_attribute>();
        MaxNumberOfRecords_attr->prop_name = "MaxNumberOfRecords";
        MaxNumberOfRecords_attr->read_only = true;
        add_property_attr("MaxNumberOfRecords", MaxNumberOfRecords_attr);

        auto ServiceEnabled_attr = std::make_shared<prop_attribute>();
        ServiceEnabled_attr->prop_name = "ServiceEnabled";
        ServiceEnabled_attr->read_only = false;
        add_property_attr("ServiceEnabled", ServiceEnabled_attr);

        auto LogEntryType_attr = std::make_shared<prop_attribute>();
        LogEntryType_attr->prop_name = "LogEntryType";
        LogEntryType_attr->read_only = true;
        LogEntryType_attr->add_enum("Event");
        LogEntryType_attr->add_enum("SEL");
        LogEntryType_attr->add_enum("Multiple");
        LogEntryType_attr->add_enum("OEM");
        add_property_attr("LogEntryType", LogEntryType_attr);

     }

};

}}

