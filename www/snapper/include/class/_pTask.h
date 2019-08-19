//---------------------------------------------------------------------
// <copyright file="_pTask.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pTask : public ResourceProvider
{
public:
    _pTask() : ResourceProvider("Task")    
    {
        enum TaskState 
        {
            TaskState_New,
            TaskState_Starting,
            TaskState_Running,
            TaskState_Suspended,
            TaskState_Interrupted,
            TaskState_Pending,
            TaskState_Stopping,
            TaskState_Completed,
            TaskState_Exception,
            TaskState_Service,
            TaskState_Cancelling,
            TaskState_Cancelled,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("EndTime",  nullptr);
        create_prop("Messages",  nullptr);
        create_prop("StartTime",  nullptr);
        create_prop("TaskMonitor",  nullptr);
        create_prop("TaskState",  nullptr);
        create_prop("TaskStatus",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Task.v1_2_0");
        set_desc("This resource contains information about a specific Task scheduled by or being executed by a Redfish service's Task Service.");
    }

    virtual ~_pTask()    
    {}

    void prepare_navigation_property()
    {
    }

        
    void prepare_Links()
    {
    }

    void prepare_OemLenovo()
    {
        create_OemLenovo_prop("@odata.type", std::make_shared<bson::BSONObj>(BSON("@odata.type" << "#LenovoTask.v1_0_0.Lenovo")));
        create_OemLenovo_prop("FFDCForDownloading", nullptr);
        
        add_property_class("Oem/Lenovo/FFDCForDownloading", "Complex Type.", "FFDCDump");
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("EndTime", "Primitive Type.", "Edm.DateTimeOffset");
        add_property_class("Messages", "Collection Type.", "Message");
        add_property_class("StartTime", "Primitive Type.", "Edm.DateTimeOffset");
        add_property_class("TaskMonitor", "Primitive Type.", "Edm.String");
        add_property_class("TaskState", "Enum Type.", "TaskState");
        add_property_class("TaskStatus", "Enum Type.", "Health");
    }

    void prep_prop_attrs()
    {
        auto EndTime_attr = std::make_shared<prop_attribute>();
        EndTime_attr->prop_name = "EndTime";
        EndTime_attr->read_only = true;
        add_property_attr("EndTime", EndTime_attr);

        auto TaskStatus_attr = std::make_shared<prop_attribute>();
        TaskStatus_attr->prop_name = "TaskStatus";
        TaskStatus_attr->read_only = true;
        TaskStatus_attr->add_enum("OK");
        TaskStatus_attr->add_enum("Warning");
        TaskStatus_attr->add_enum("Critical");
        add_property_attr("TaskStatus", TaskStatus_attr);

        auto StartTime_attr = std::make_shared<prop_attribute>();
        StartTime_attr->prop_name = "StartTime";
        StartTime_attr->read_only = true;
        add_property_attr("StartTime", StartTime_attr);

        auto TaskState_attr = std::make_shared<prop_attribute>();
        TaskState_attr->prop_name = "TaskState";
        TaskState_attr->read_only = true;
        TaskState_attr->add_enum("New");
        TaskState_attr->add_enum("Starting");
        TaskState_attr->add_enum("Running");
        TaskState_attr->add_enum("Suspended");
        TaskState_attr->add_enum("Interrupted");
        TaskState_attr->add_enum("Pending");
        TaskState_attr->add_enum("Stopping");
        TaskState_attr->add_enum("Completed");
        TaskState_attr->add_enum("Killed");
        TaskState_attr->add_enum("Exception");
        TaskState_attr->add_enum("Service");
        TaskState_attr->add_enum("Cancelling");
        TaskState_attr->add_enum("Cancelled");
        add_property_attr("TaskState", TaskState_attr);

        auto TaskMonitor_attr = std::make_shared<prop_attribute>();
        TaskMonitor_attr->prop_name = "TaskMonitor";
        TaskMonitor_attr->read_only = true;
        add_property_attr("TaskMonitor", TaskMonitor_attr);

     }

};

}}

