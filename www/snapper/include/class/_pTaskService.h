//---------------------------------------------------------------------
// <copyright file="_pTaskService.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pTaskService : public ResourceProvider
{
public:
    _pTaskService() : ResourceProvider("TaskService")    
    {
        enum OverWritePolicy 
        {
            OverWritePolicy_Manual,
            OverWritePolicy_Oldest,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("CompletedTaskOverWritePolicy",  nullptr);
        create_prop("DateTime",  nullptr);
        create_prop("LifeCycleEventOnTaskStateChange",  nullptr);
        create_prop("ServiceEnabled",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("Tasks",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("TaskService.v1_1_1");
        set_desc("This is the schema definition for the Task Service.  It represents the properties for the service itself and has links to the actual list of tasks.");
    }

    virtual ~_pTaskService()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("Tasks");
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
        add_property_class("CompletedTaskOverWritePolicy", "Enum Type.", "OverWritePolicy");
        add_property_class("DateTime", "Primitive Type.", "Edm.DateTimeOffset");
        add_property_class("LifeCycleEventOnTaskStateChange", "Primitive Type.", "Edm.Boolean");
        add_property_class("ServiceEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("Tasks", "Navigation Type.Entity", "TaskCollection");
    }

    void prep_prop_attrs()
    {
        auto Tasks_attr = std::make_shared<prop_attribute>();
        Tasks_attr->prop_name = "Tasks";
        Tasks_attr->read_only = true;
        add_property_attr("Tasks", Tasks_attr);

        auto ServiceEnabled_attr = std::make_shared<prop_attribute>();
        ServiceEnabled_attr->prop_name = "ServiceEnabled";
        ServiceEnabled_attr->read_only = false;
        add_property_attr("ServiceEnabled", ServiceEnabled_attr);

        auto LifeCycleEventOnTaskStateChange_attr = std::make_shared<prop_attribute>();
        LifeCycleEventOnTaskStateChange_attr->prop_name = "LifeCycleEventOnTaskStateChange";
        LifeCycleEventOnTaskStateChange_attr->read_only = true;
        add_property_attr("LifeCycleEventOnTaskStateChange", LifeCycleEventOnTaskStateChange_attr);

        auto DateTime_attr = std::make_shared<prop_attribute>();
        DateTime_attr->prop_name = "DateTime";
        DateTime_attr->read_only = true;
        add_property_attr("DateTime", DateTime_attr);

        auto CompletedTaskOverWritePolicy_attr = std::make_shared<prop_attribute>();
        CompletedTaskOverWritePolicy_attr->prop_name = "CompletedTaskOverWritePolicy";
        CompletedTaskOverWritePolicy_attr->read_only = true;
        CompletedTaskOverWritePolicy_attr->add_enum("Manual");
        CompletedTaskOverWritePolicy_attr->add_enum("Oldest");
        add_property_attr("CompletedTaskOverWritePolicy", CompletedTaskOverWritePolicy_attr);

     }

};

}}

