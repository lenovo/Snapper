//---------------------------------------------------------------------
// <copyright file="_pPCIeDevice.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pPCIeDevice : public ResourceProvider
{
public:
    _pPCIeDevice() : ResourceProvider("PCIeDevice")    
    {
        enum DeviceType 
        {
            DeviceType_SingleFunction,
            DeviceType_MultiFunction,
            DeviceType_Simulated,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Assembly",  nullptr);
        create_prop("AssetTag",  nullptr);
        create_prop("DeviceType",  nullptr);
        create_prop("FirmwareVersion",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("Manufacturer",  nullptr);
        create_prop("Model",  nullptr);
        create_prop("PartNumber",  nullptr);
        create_prop("SKU",  nullptr);
        create_prop("SerialNumber",  nullptr);
        create_prop("Status",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("PCIeDevice.v1_2_0");
        set_desc("This is the schema definition for the PCIeDevice resource.  It represents the properties of a PCIeDevice attached to a System.");
    }

    virtual ~_pPCIeDevice()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_refer_props("Assembly");
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["Chassis"] = nullptr;
        m_Links_prop_objs["Chassis@odata.count"] = nullptr;
        m_Links_prop_objs["Chassis@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["PCIeFunctions"] = nullptr;
        m_Links_prop_objs["PCIeFunctions@odata.count"] = nullptr;
        m_Links_prop_objs["PCIeFunctions@odata.navigationLink"] = nullptr;
        add_Links_arr_props("Chassis");
        add_Links_arr_props("PCIeFunctions");
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("Assembly", "Navigation Type.Entity", "Assembly");
        add_property_class("AssetTag", "Primitive Type.", "Edm.String");
        add_property_class("DeviceType", "Enum Type.", "DeviceType");
        add_property_class("FirmwareVersion", "Primitive Type.", "Edm.String");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("Manufacturer", "Primitive Type.", "Edm.String");
        add_property_class("Model", "Primitive Type.", "Edm.String");
        add_property_class("PartNumber", "Primitive Type.", "Edm.String");
        add_property_class("SKU", "Primitive Type.", "Edm.String");
        add_property_class("SerialNumber", "Primitive Type.", "Edm.String");
        add_property_class("Status", "Complex Type.", "Status");
    }

    void prep_prop_attrs()
    {
        auto AssetTag_attr = std::make_shared<prop_attribute>();
        AssetTag_attr->prop_name = "AssetTag";
        AssetTag_attr->read_only = false;
        add_property_attr("AssetTag", AssetTag_attr);

        auto PartNumber_attr = std::make_shared<prop_attribute>();
        PartNumber_attr->prop_name = "PartNumber";
        PartNumber_attr->read_only = true;
        add_property_attr("PartNumber", PartNumber_attr);

        auto DeviceType_attr = std::make_shared<prop_attribute>();
        DeviceType_attr->prop_name = "DeviceType";
        DeviceType_attr->read_only = true;
        DeviceType_attr->add_enum("SingleFunction");
        DeviceType_attr->add_enum("MultiFunction");
        DeviceType_attr->add_enum("Simulated");
        add_property_attr("DeviceType", DeviceType_attr);

        auto SerialNumber_attr = std::make_shared<prop_attribute>();
        SerialNumber_attr->prop_name = "SerialNumber";
        SerialNumber_attr->read_only = true;
        add_property_attr("SerialNumber", SerialNumber_attr);

        auto SKU_attr = std::make_shared<prop_attribute>();
        SKU_attr->prop_name = "SKU";
        SKU_attr->read_only = true;
        add_property_attr("SKU", SKU_attr);

        auto Model_attr = std::make_shared<prop_attribute>();
        Model_attr->prop_name = "Model";
        Model_attr->read_only = true;
        add_property_attr("Model", Model_attr);

        auto FirmwareVersion_attr = std::make_shared<prop_attribute>();
        FirmwareVersion_attr->prop_name = "FirmwareVersion";
        FirmwareVersion_attr->read_only = true;
        add_property_attr("FirmwareVersion", FirmwareVersion_attr);

        auto Manufacturer_attr = std::make_shared<prop_attribute>();
        Manufacturer_attr->prop_name = "Manufacturer";
        Manufacturer_attr->read_only = true;
        add_property_attr("Manufacturer", Manufacturer_attr);

        auto Assembly_attr = std::make_shared<prop_attribute>();
        Assembly_attr->prop_name = "Assembly";
        Assembly_attr->read_only = true;
        add_property_attr("Assembly", Assembly_attr);

     }

};

}}

