//---------------------------------------------------------------------
// <copyright file="_pResourceBlock.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pResourceBlock : public ResourceProvider
{
public:
    _pResourceBlock() : ResourceProvider("ResourceBlock")    
    {
        enum CompositionState 
        {
            CompositionState_Composing,
            CompositionState_ComposedAndAvailable,
            CompositionState_Composed,
            CompositionState_Unused,
            CompositionState_Failed,
        };

        enum ResourceBlockType 
        {
            ResourceBlockType_Compute,
            ResourceBlockType_Processor,
            ResourceBlockType_Memory,
            ResourceBlockType_Network,
            ResourceBlockType_Storage,
            ResourceBlockType_ComputerSystem,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("CompositionStatus",  nullptr);
        create_prop("ComputerSystems",  nullptr);
        create_prop("ComputerSystems@odata.count",  nullptr);
        create_prop("ComputerSystems@odata.navigationLink",  nullptr);
        create_prop("EthernetInterfaces",  nullptr);
        create_prop("EthernetInterfaces@odata.count",  nullptr);
        create_prop("EthernetInterfaces@odata.navigationLink",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("Memory",  nullptr);
        create_prop("Memory@odata.count",  nullptr);
        create_prop("Memory@odata.navigationLink",  nullptr);
        create_prop("NetworkInterfaces",  nullptr);
        create_prop("NetworkInterfaces@odata.count",  nullptr);
        create_prop("NetworkInterfaces@odata.navigationLink",  nullptr);
        create_prop("Processors",  nullptr);
        create_prop("Processors@odata.count",  nullptr);
        create_prop("Processors@odata.navigationLink",  nullptr);
        create_prop("ResourceBlockType",  nullptr);
        create_prop("SimpleStorage",  nullptr);
        create_prop("SimpleStorage@odata.count",  nullptr);
        create_prop("SimpleStorage@odata.navigationLink",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("Storage",  nullptr);
        create_prop("Storage@odata.count",  nullptr);
        create_prop("Storage@odata.navigationLink",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("ResourceBlock.v1_1_0");
        set_desc("This schema defines a Resource Block resource.");
    }

    virtual ~_pResourceBlock()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_arr_props("ComputerSystems");
        add_navigation_arr_props("NetworkInterfaces");
        add_navigation_arr_props("SimpleStorage");
        add_navigation_arr_props("Processors");
        add_navigation_arr_props("Memory");
        add_navigation_arr_props("EthernetInterfaces");
        add_navigation_arr_props("Storage");
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["Chassis"] = nullptr;
        m_Links_prop_objs["Chassis@odata.count"] = nullptr;
        m_Links_prop_objs["Chassis@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["ComputerSystems"] = nullptr;
        m_Links_prop_objs["ComputerSystems@odata.count"] = nullptr;
        m_Links_prop_objs["ComputerSystems@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["Zones"] = nullptr;
        m_Links_prop_objs["Zones@odata.count"] = nullptr;
        m_Links_prop_objs["Zones@odata.navigationLink"] = nullptr;
        add_Links_arr_props("Chassis");
        add_Links_arr_props("ComputerSystems");
        add_Links_arr_props("Zones");
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("CompositionStatus", "Complex Type.", "CompositionStatus");
        add_property_class("ComputerSystems", "Navigation Type.Collection", "ComputerSystem");
        add_property_class("EthernetInterfaces", "Navigation Type.Collection", "EthernetInterface");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("Memory", "Navigation Type.Collection", "Memory");
        add_property_class("NetworkInterfaces", "Navigation Type.Collection", "NetworkInterface");
        add_property_class("Processors", "Navigation Type.Collection", "Processor");
        add_property_class("ResourceBlockType", "Collection Type.", "ResourceBlockType");
        add_property_class("SimpleStorage", "Navigation Type.Collection", "SimpleStorage");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("Storage", "Navigation Type.Collection", "Storage");
    }

    void prep_prop_attrs()
    {
        auto ComputerSystems_attr = std::make_shared<prop_attribute>();
        ComputerSystems_attr->prop_name = "ComputerSystems";
        ComputerSystems_attr->read_only = true;
        add_property_attr("ComputerSystems", ComputerSystems_attr);

        auto NetworkInterfaces_attr = std::make_shared<prop_attribute>();
        NetworkInterfaces_attr->prop_name = "NetworkInterfaces";
        NetworkInterfaces_attr->read_only = true;
        add_property_attr("NetworkInterfaces", NetworkInterfaces_attr);

        auto ResourceBlockType_attr = std::make_shared<prop_attribute>();
        ResourceBlockType_attr->prop_name = "ResourceBlockType";
        ResourceBlockType_attr->read_only = true;
        ResourceBlockType_attr->add_enum("Compute");
        ResourceBlockType_attr->add_enum("Processor");
        ResourceBlockType_attr->add_enum("Memory");
        ResourceBlockType_attr->add_enum("Network");
        ResourceBlockType_attr->add_enum("Storage");
        ResourceBlockType_attr->add_enum("ComputerSystem");
        add_property_attr("ResourceBlockType", ResourceBlockType_attr);

        auto SimpleStorage_attr = std::make_shared<prop_attribute>();
        SimpleStorage_attr->prop_name = "SimpleStorage";
        SimpleStorage_attr->read_only = true;
        add_property_attr("SimpleStorage", SimpleStorage_attr);

        auto Processors_attr = std::make_shared<prop_attribute>();
        Processors_attr->prop_name = "Processors";
        Processors_attr->read_only = true;
        add_property_attr("Processors", Processors_attr);

        auto Memory_attr = std::make_shared<prop_attribute>();
        Memory_attr->prop_name = "Memory";
        Memory_attr->read_only = true;
        add_property_attr("Memory", Memory_attr);

        auto EthernetInterfaces_attr = std::make_shared<prop_attribute>();
        EthernetInterfaces_attr->prop_name = "EthernetInterfaces";
        EthernetInterfaces_attr->read_only = true;
        add_property_attr("EthernetInterfaces", EthernetInterfaces_attr);

        auto Storage_attr = std::make_shared<prop_attribute>();
        Storage_attr->prop_name = "Storage";
        Storage_attr->read_only = true;
        add_property_attr("Storage", Storage_attr);

     }

};

}}

