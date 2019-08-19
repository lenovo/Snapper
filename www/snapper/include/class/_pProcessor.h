//---------------------------------------------------------------------
// <copyright file="_pProcessor.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pProcessor : public ResourceProvider
{
public:
    _pProcessor() : ResourceProvider("Processor")    
    {
        enum ProcessorType 
        {
            ProcessorType_CPU,
            ProcessorType_GPU,
            ProcessorType_FPGA,
            ProcessorType_DSP,
            ProcessorType_Accelerator,
            ProcessorType_Core,
            ProcessorType_Thread,
            ProcessorType_OEM,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Assembly",  nullptr);
        create_prop("InstructionSet",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("Location",  nullptr);
        create_prop("Manufacturer",  nullptr);
        create_prop("MaxSpeedMHz",  nullptr);
        create_prop("Model",  nullptr);
        create_prop("ProcessorArchitecture",  nullptr);
        create_prop("ProcessorId",  nullptr);
        create_prop("ProcessorType",  nullptr);
        create_prop("Socket",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("SubProcessors",  nullptr);
        create_prop("TotalCores",  nullptr);
        create_prop("TotalThreads",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Processor.v1_3_0");
        set_desc("This is the schema definition for the Processor resource.  It represents the properties of a processor attached to a System.");
    }

    virtual ~_pProcessor()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("Assembly");
        add_navigation_contained_props("SubProcessors");
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["Chassis"] = nullptr;
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("Assembly", "Navigation Type.Entity", "Assembly");
        add_property_class("InstructionSet", "Type Definition.", "Edm.String");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("Location", "Complex Type.", "Location");
        add_property_class("Manufacturer", "Primitive Type.", "Edm.String");
        add_property_class("MaxSpeedMHz", "Primitive Type.", "Edm.Int64");
        add_property_class("Model", "Primitive Type.", "Edm.String");
        add_property_class("ProcessorArchitecture", "Type Definition.", "Edm.String");
        add_property_class("ProcessorId", "Complex Type.", "ProcessorId");
        add_property_class("ProcessorType", "Enum Type.", "ProcessorType");
        add_property_class("Socket", "Primitive Type.", "Edm.String");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("SubProcessors", "Navigation Type.Entity", "ProcessorCollection");
        add_property_class("TotalCores", "Primitive Type.", "Edm.Int64");
        add_property_class("TotalThreads", "Primitive Type.", "Edm.Int64");
    }

    void prep_prop_attrs()
    {
        auto TotalThreads_attr = std::make_shared<prop_attribute>();
        TotalThreads_attr->prop_name = "TotalThreads";
        TotalThreads_attr->read_only = true;
        add_property_attr("TotalThreads", TotalThreads_attr);

        auto Socket_attr = std::make_shared<prop_attribute>();
        Socket_attr->prop_name = "Socket";
        Socket_attr->read_only = true;
        add_property_attr("Socket", Socket_attr);

        auto ProcessorType_attr = std::make_shared<prop_attribute>();
        ProcessorType_attr->prop_name = "ProcessorType";
        ProcessorType_attr->read_only = true;
        ProcessorType_attr->add_enum("CPU");
        ProcessorType_attr->add_enum("GPU");
        ProcessorType_attr->add_enum("FPGA");
        ProcessorType_attr->add_enum("DSP");
        ProcessorType_attr->add_enum("Accelerator");
        ProcessorType_attr->add_enum("Core");
        ProcessorType_attr->add_enum("Thread");
        ProcessorType_attr->add_enum("OEM");
        add_property_attr("ProcessorType", ProcessorType_attr);

        auto ProcessorArchitecture_attr = std::make_shared<prop_attribute>();
        ProcessorArchitecture_attr->prop_name = "ProcessorArchitecture";
        ProcessorArchitecture_attr->read_only = true;
        add_property_attr("ProcessorArchitecture", ProcessorArchitecture_attr);

        auto Manufacturer_attr = std::make_shared<prop_attribute>();
        Manufacturer_attr->prop_name = "Manufacturer";
        Manufacturer_attr->read_only = true;
        add_property_attr("Manufacturer", Manufacturer_attr);

        auto InstructionSet_attr = std::make_shared<prop_attribute>();
        InstructionSet_attr->prop_name = "InstructionSet";
        InstructionSet_attr->read_only = true;
        add_property_attr("InstructionSet", InstructionSet_attr);

        auto Model_attr = std::make_shared<prop_attribute>();
        Model_attr->prop_name = "Model";
        Model_attr->read_only = true;
        add_property_attr("Model", Model_attr);

        auto TotalCores_attr = std::make_shared<prop_attribute>();
        TotalCores_attr->prop_name = "TotalCores";
        TotalCores_attr->read_only = true;
        add_property_attr("TotalCores", TotalCores_attr);

        auto MaxSpeedMHz_attr = std::make_shared<prop_attribute>();
        MaxSpeedMHz_attr->prop_name = "MaxSpeedMHz";
        MaxSpeedMHz_attr->read_only = true;
        add_property_attr("MaxSpeedMHz", MaxSpeedMHz_attr);

        auto Assembly_attr = std::make_shared<prop_attribute>();
        Assembly_attr->prop_name = "Assembly";
        Assembly_attr->read_only = true;
        add_property_attr("Assembly", Assembly_attr);

        auto SubProcessors_attr = std::make_shared<prop_attribute>();
        SubProcessors_attr->prop_name = "SubProcessors";
        SubProcessors_attr->read_only = true;
        add_property_attr("SubProcessors", SubProcessors_attr);

     }

};

}}

