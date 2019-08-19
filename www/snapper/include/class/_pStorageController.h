//---------------------------------------------------------------------
// <copyright file="_pStorageController.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pStorageController : public ReferenceableMemberProvider
{
public:
    _pStorageController() : ReferenceableMemberProvider("StorageController")    
    {
        create_prop("Oem",  nullptr);
        create_prop("MemberId",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Assembly",  nullptr);
        create_prop("AssetTag",  nullptr);
        create_prop("FirmwareVersion",  nullptr);
        create_prop("Identifiers",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("Location",  nullptr);
        create_prop("Manufacturer",  nullptr);
        create_prop("Model",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("PartNumber",  nullptr);
        create_prop("SKU",  nullptr);
        create_prop("SerialNumber",  nullptr);
        create_prop("SpeedGbps",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("SupportedControllerProtocols",  nullptr);
        create_prop("SupportedDeviceProtocols",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Storage.v1_4_0");
        set_desc("This schema defines a storage controller and its respective properties.  A storage controller represents a storage device (physical or virtual) that produces Volumes.");
    }

    virtual ~_pStorageController()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("Assembly");
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["Enclosures"] = nullptr;
        m_Links_prop_objs["Enclosures@odata.count"] = nullptr;
        m_Links_prop_objs["Enclosures@odata.navigationLink"] = nullptr;
        add_Links_arr_props("Enclosures");
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "StorageControllerActions");
        add_property_class("Assembly", "Navigation Type.Entity", "Assembly");
        add_property_class("AssetTag", "Primitive Type.", "Edm.String");
        add_property_class("FirmwareVersion", "Primitive Type.", "Edm.String");
        add_property_class("Identifiers", "Collection Type.", "Identifier");
        add_property_class("Links", "Complex Type.", "StorageControllerLinks");
        add_property_class("Location", "Complex Type.", "Location");
        add_property_class("Manufacturer", "Primitive Type.", "Edm.String");
        add_property_class("Model", "Primitive Type.", "Edm.String");
        add_property_class("Name", "Primitive Type.", "Edm.String");
        add_property_class("PartNumber", "Primitive Type.", "Edm.String");
        add_property_class("SKU", "Primitive Type.", "Edm.String");
        add_property_class("SerialNumber", "Primitive Type.", "Edm.String");
        add_property_class("SpeedGbps", "Primitive Type.", "Edm.Decimal");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("SupportedControllerProtocols", "Collection Type.", "Protocol");
        add_property_class("SupportedDeviceProtocols", "Collection Type.", "Protocol");
    }

    void prep_prop_attrs()
    {
        auto AssetTag_attr = std::make_shared<prop_attribute>();
        AssetTag_attr->prop_name = "AssetTag";
        AssetTag_attr->read_only = false;
        add_property_attr("AssetTag", AssetTag_attr);

        auto SpeedGbps_attr = std::make_shared<prop_attribute>();
        SpeedGbps_attr->prop_name = "SpeedGbps";
        SpeedGbps_attr->read_only = true;
        add_property_attr("SpeedGbps", SpeedGbps_attr);

        auto PartNumber_attr = std::make_shared<prop_attribute>();
        PartNumber_attr->prop_name = "PartNumber";
        PartNumber_attr->read_only = true;
        add_property_attr("PartNumber", PartNumber_attr);

        auto FirmwareVersion_attr = std::make_shared<prop_attribute>();
        FirmwareVersion_attr->prop_name = "FirmwareVersion";
        FirmwareVersion_attr->read_only = true;
        add_property_attr("FirmwareVersion", FirmwareVersion_attr);

        auto Manufacturer_attr = std::make_shared<prop_attribute>();
        Manufacturer_attr->prop_name = "Manufacturer";
        Manufacturer_attr->read_only = true;
        add_property_attr("Manufacturer", Manufacturer_attr);

        auto Model_attr = std::make_shared<prop_attribute>();
        Model_attr->prop_name = "Model";
        Model_attr->read_only = true;
        add_property_attr("Model", Model_attr);

        auto SupportedDeviceProtocols_attr = std::make_shared<prop_attribute>();
        SupportedDeviceProtocols_attr->prop_name = "SupportedDeviceProtocols";
        SupportedDeviceProtocols_attr->read_only = true;
        SupportedDeviceProtocols_attr->add_enum("PCIe");
        SupportedDeviceProtocols_attr->add_enum("AHCI");
        SupportedDeviceProtocols_attr->add_enum("UHCI");
        SupportedDeviceProtocols_attr->add_enum("SAS");
        SupportedDeviceProtocols_attr->add_enum("SATA");
        SupportedDeviceProtocols_attr->add_enum("USB");
        SupportedDeviceProtocols_attr->add_enum("NVMe");
        SupportedDeviceProtocols_attr->add_enum("FC");
        SupportedDeviceProtocols_attr->add_enum("iSCSI");
        SupportedDeviceProtocols_attr->add_enum("FCoE");
        SupportedDeviceProtocols_attr->add_enum("FCP");
        SupportedDeviceProtocols_attr->add_enum("FICON");
        SupportedDeviceProtocols_attr->add_enum("NVMeOverFabrics");
        SupportedDeviceProtocols_attr->add_enum("SMB");
        SupportedDeviceProtocols_attr->add_enum("NFSv3");
        SupportedDeviceProtocols_attr->add_enum("NFSv4");
        SupportedDeviceProtocols_attr->add_enum("HTTP");
        SupportedDeviceProtocols_attr->add_enum("HTTPS");
        SupportedDeviceProtocols_attr->add_enum("FTP");
        SupportedDeviceProtocols_attr->add_enum("SFTP");
        SupportedDeviceProtocols_attr->add_enum("iWARP");
        SupportedDeviceProtocols_attr->add_enum("RoCE");
        SupportedDeviceProtocols_attr->add_enum("RoCEv2");
        SupportedDeviceProtocols_attr->add_enum("OEM");
        add_property_attr("SupportedDeviceProtocols", SupportedDeviceProtocols_attr);

        auto SupportedControllerProtocols_attr = std::make_shared<prop_attribute>();
        SupportedControllerProtocols_attr->prop_name = "SupportedControllerProtocols";
        SupportedControllerProtocols_attr->read_only = true;
        SupportedControllerProtocols_attr->add_enum("PCIe");
        SupportedControllerProtocols_attr->add_enum("AHCI");
        SupportedControllerProtocols_attr->add_enum("UHCI");
        SupportedControllerProtocols_attr->add_enum("SAS");
        SupportedControllerProtocols_attr->add_enum("SATA");
        SupportedControllerProtocols_attr->add_enum("USB");
        SupportedControllerProtocols_attr->add_enum("NVMe");
        SupportedControllerProtocols_attr->add_enum("FC");
        SupportedControllerProtocols_attr->add_enum("iSCSI");
        SupportedControllerProtocols_attr->add_enum("FCoE");
        SupportedControllerProtocols_attr->add_enum("FCP");
        SupportedControllerProtocols_attr->add_enum("FICON");
        SupportedControllerProtocols_attr->add_enum("NVMeOverFabrics");
        SupportedControllerProtocols_attr->add_enum("SMB");
        SupportedControllerProtocols_attr->add_enum("NFSv3");
        SupportedControllerProtocols_attr->add_enum("NFSv4");
        SupportedControllerProtocols_attr->add_enum("HTTP");
        SupportedControllerProtocols_attr->add_enum("HTTPS");
        SupportedControllerProtocols_attr->add_enum("FTP");
        SupportedControllerProtocols_attr->add_enum("SFTP");
        SupportedControllerProtocols_attr->add_enum("iWARP");
        SupportedControllerProtocols_attr->add_enum("RoCE");
        SupportedControllerProtocols_attr->add_enum("RoCEv2");
        SupportedControllerProtocols_attr->add_enum("OEM");
        add_property_attr("SupportedControllerProtocols", SupportedControllerProtocols_attr);

        auto SKU_attr = std::make_shared<prop_attribute>();
        SKU_attr->prop_name = "SKU";
        SKU_attr->read_only = true;
        add_property_attr("SKU", SKU_attr);

        auto SerialNumber_attr = std::make_shared<prop_attribute>();
        SerialNumber_attr->prop_name = "SerialNumber";
        SerialNumber_attr->read_only = true;
        add_property_attr("SerialNumber", SerialNumber_attr);

        auto Name_attr = std::make_shared<prop_attribute>();
        Name_attr->prop_name = "Name";
        Name_attr->read_only = true;
        add_property_attr("Name", Name_attr);

        auto Assembly_attr = std::make_shared<prop_attribute>();
        Assembly_attr->prop_name = "Assembly";
        Assembly_attr->read_only = true;
        add_property_attr("Assembly", Assembly_attr);

     }

};

}}

