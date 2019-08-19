//---------------------------------------------------------------------
// <copyright file="_pDrive.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pDrive : public ResourceProvider
{
public:
    _pDrive() : ResourceProvider("Drive")    
    {
        enum StatusIndicator 
        {
            StatusIndicator_OK,
            StatusIndicator_Fail,
            StatusIndicator_Rebuild,
            StatusIndicator_PredictiveFailureAnalysis,
            StatusIndicator_Hotspare,
            StatusIndicator_InACriticalArray,
            StatusIndicator_InAFailedArray,
        };

        enum EncryptionStatus 
        {
            EncryptionStatus_Unlocked,
            EncryptionStatus_Locked,
            EncryptionStatus_Foreign,
            EncryptionStatus_Unencrypted,
        };

        enum EncryptionAbility 
        {
            EncryptionAbility_None,
            EncryptionAbility_SelfEncryptingDrive,
            EncryptionAbility_Other,
        };

        enum HotspareType 
        {
            HotspareType_None,
            HotspareType_Global,
            HotspareType_Chassis,
            HotspareType_Dedicated,
        };

        enum MediaType 
        {
            MediaType_HDD,
            MediaType_SSD,
            MediaType_SMR,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Assembly",  nullptr);
        create_prop("AssetTag",  nullptr);
        create_prop("BlockSizeBytes",  nullptr);
        create_prop("CapableSpeedGbs",  nullptr);
        create_prop("CapacityBytes",  nullptr);
        create_prop("EncryptionAbility",  nullptr);
        create_prop("EncryptionStatus",  nullptr);
        create_prop("FailurePredicted",  nullptr);
        create_prop("HotspareType",  nullptr);
        create_prop("Identifiers",  nullptr);
        create_prop("IndicatorLED",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("Manufacturer",  nullptr);
        create_prop("MediaType",  nullptr);
        create_prop("Model",  nullptr);
        create_prop("NegotiatedSpeedGbs",  nullptr);
        create_prop("Operations",  nullptr);
        create_prop("PartNumber",  nullptr);
        create_prop("PhysicalLocation",  nullptr);
        create_prop("PredictedMediaLifeLeftPercent",  nullptr);
        create_prop("Protocol",  nullptr);
        create_prop("Revision",  nullptr);
        create_prop("RotationSpeedRPM",  nullptr);
        create_prop("SKU",  nullptr);
        create_prop("SerialNumber",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("StatusIndicator",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Drive.v1_4_0");
        set_desc("The Drive schema represents a single physical disk drive for a system, including links to associated Volumes.");
    }

    virtual ~_pDrive()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("Assembly");
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["Chassis"] = nullptr;
        m_Links_prop_objs["Endpoints"] = nullptr;
        m_Links_prop_objs["Endpoints@odata.count"] = nullptr;
        m_Links_prop_objs["Endpoints@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["Volumes"] = nullptr;
        m_Links_prop_objs["Volumes@odata.count"] = nullptr;
        m_Links_prop_objs["Volumes@odata.navigationLink"] = nullptr;
        add_Links_arr_props("Endpoints");
        add_Links_arr_props("Volumes");
    }

    void prepare_OemLenovo()
    {
    }

    virtual void set_actions_obj()
    {
         create_prop( "Actions",   std::make_shared<bson::BSONObj>(BSON("Actions" << BSON(
                "#Drive.SecureErase"
                << BSON("target" << (get_base_odata_id() + "/Actions/Drive.SecureErase")
                << "title" << "SecureErase")
                )
                )) );
     }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("Assembly", "Navigation Type.Entity", "Assembly");
        add_property_class("AssetTag", "Primitive Type.", "Edm.String");
        add_property_class("BlockSizeBytes", "Primitive Type.", "Edm.Int64");
        add_property_class("CapableSpeedGbs", "Primitive Type.", "Edm.Decimal");
        add_property_class("CapacityBytes", "Primitive Type.", "Edm.Int64");
        add_property_class("EncryptionAbility", "Enum Type.", "EncryptionAbility");
        add_property_class("EncryptionStatus", "Enum Type.", "EncryptionStatus");
        add_property_class("FailurePredicted", "Primitive Type.", "Edm.Boolean");
        add_property_class("HotspareType", "Enum Type.", "HotspareType");
        add_property_class("Identifiers", "Collection Type.", "Identifier");
        add_property_class("IndicatorLED", "Enum Type.", "IndicatorLED");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("Location", "Collection Type.", "Location");
        add_property_class("Manufacturer", "Primitive Type.", "Edm.String");
        add_property_class("MediaType", "Enum Type.", "MediaType");
        add_property_class("Model", "Primitive Type.", "Edm.String");
        add_property_class("NegotiatedSpeedGbs", "Primitive Type.", "Edm.Decimal");
        add_property_class("Operations", "Collection Type.", "Operations");
        add_property_class("PartNumber", "Primitive Type.", "Edm.String");
        add_property_class("PhysicalLocation", "Complex Type.", "Location");
        add_property_class("PredictedMediaLifeLeftPercent", "Primitive Type.", "Edm.Decimal");
        add_property_class("Protocol", "Enum Type.", "Protocol");
        add_property_class("Revision", "Primitive Type.", "Edm.String");
        add_property_class("RotationSpeedRPM", "Primitive Type.", "Edm.Decimal");
        add_property_class("SKU", "Primitive Type.", "Edm.String");
        add_property_class("SerialNumber", "Primitive Type.", "Edm.String");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("StatusIndicator", "Enum Type.", "StatusIndicator");
    }

    void prep_prop_attrs()
    {
        auto Manufacturer_attr = std::make_shared<prop_attribute>();
        Manufacturer_attr->prop_name = "Manufacturer";
        Manufacturer_attr->read_only = true;
        add_property_attr("Manufacturer", Manufacturer_attr);

        auto HotspareType_attr = std::make_shared<prop_attribute>();
        HotspareType_attr->prop_name = "HotspareType";
        HotspareType_attr->read_only = true;
        HotspareType_attr->add_enum("None");
        HotspareType_attr->add_enum("Global");
        HotspareType_attr->add_enum("Chassis");
        HotspareType_attr->add_enum("Dedicated");
        add_property_attr("HotspareType", HotspareType_attr);

        auto Protocol_attr = std::make_shared<prop_attribute>();
        Protocol_attr->prop_name = "Protocol";
        Protocol_attr->read_only = true;
        Protocol_attr->add_enum("PCIe");
        Protocol_attr->add_enum("AHCI");
        Protocol_attr->add_enum("UHCI");
        Protocol_attr->add_enum("SAS");
        Protocol_attr->add_enum("SATA");
        Protocol_attr->add_enum("USB");
        Protocol_attr->add_enum("NVMe");
        Protocol_attr->add_enum("FC");
        Protocol_attr->add_enum("iSCSI");
        Protocol_attr->add_enum("FCoE");
        Protocol_attr->add_enum("FCP");
        Protocol_attr->add_enum("FICON");
        Protocol_attr->add_enum("NVMeOverFabrics");
        Protocol_attr->add_enum("SMB");
        Protocol_attr->add_enum("NFSv3");
        Protocol_attr->add_enum("NFSv4");
        Protocol_attr->add_enum("HTTP");
        Protocol_attr->add_enum("HTTPS");
        Protocol_attr->add_enum("FTP");
        Protocol_attr->add_enum("SFTP");
        Protocol_attr->add_enum("iWARP");
        Protocol_attr->add_enum("RoCE");
        Protocol_attr->add_enum("RoCEv2");
        Protocol_attr->add_enum("OEM");
        add_property_attr("Protocol", Protocol_attr);

        auto NegotiatedSpeedGbs_attr = std::make_shared<prop_attribute>();
        NegotiatedSpeedGbs_attr->prop_name = "NegotiatedSpeedGbs";
        NegotiatedSpeedGbs_attr->read_only = true;
        add_property_attr("NegotiatedSpeedGbs", NegotiatedSpeedGbs_attr);

        auto CapacityBytes_attr = std::make_shared<prop_attribute>();
        CapacityBytes_attr->prop_name = "CapacityBytes";
        CapacityBytes_attr->read_only = true;
        add_property_attr("CapacityBytes", CapacityBytes_attr);

        auto Model_attr = std::make_shared<prop_attribute>();
        Model_attr->prop_name = "Model";
        Model_attr->read_only = true;
        add_property_attr("Model", Model_attr);

        auto Revision_attr = std::make_shared<prop_attribute>();
        Revision_attr->prop_name = "Revision";
        Revision_attr->read_only = true;
        add_property_attr("Revision", Revision_attr);

        auto MediaType_attr = std::make_shared<prop_attribute>();
        MediaType_attr->prop_name = "MediaType";
        MediaType_attr->read_only = true;
        MediaType_attr->add_enum("HDD");
        MediaType_attr->add_enum("SSD");
        MediaType_attr->add_enum("SMR");
        add_property_attr("MediaType", MediaType_attr);

        auto FailurePredicted_attr = std::make_shared<prop_attribute>();
        FailurePredicted_attr->prop_name = "FailurePredicted";
        FailurePredicted_attr->read_only = true;
        add_property_attr("FailurePredicted", FailurePredicted_attr);

        auto BlockSizeBytes_attr = std::make_shared<prop_attribute>();
        BlockSizeBytes_attr->prop_name = "BlockSizeBytes";
        BlockSizeBytes_attr->read_only = true;
        add_property_attr("BlockSizeBytes", BlockSizeBytes_attr);

        auto IndicatorLED_attr = std::make_shared<prop_attribute>();
        IndicatorLED_attr->prop_name = "IndicatorLED";
        IndicatorLED_attr->read_only = false;
        IndicatorLED_attr->add_enum("Lit");
        IndicatorLED_attr->add_enum("Blinking");
        IndicatorLED_attr->add_enum("Off");
        add_property_attr("IndicatorLED", IndicatorLED_attr);

        auto CapableSpeedGbs_attr = std::make_shared<prop_attribute>();
        CapableSpeedGbs_attr->prop_name = "CapableSpeedGbs";
        CapableSpeedGbs_attr->read_only = true;
        add_property_attr("CapableSpeedGbs", CapableSpeedGbs_attr);

        auto PredictedMediaLifeLeftPercent_attr = std::make_shared<prop_attribute>();
        PredictedMediaLifeLeftPercent_attr->prop_name = "PredictedMediaLifeLeftPercent";
        PredictedMediaLifeLeftPercent_attr->read_only = true;
        add_property_attr("PredictedMediaLifeLeftPercent", PredictedMediaLifeLeftPercent_attr);

        auto EncryptionStatus_attr = std::make_shared<prop_attribute>();
        EncryptionStatus_attr->prop_name = "EncryptionStatus";
        EncryptionStatus_attr->read_only = true;
        EncryptionStatus_attr->add_enum("Unecrypted");
        EncryptionStatus_attr->add_enum("Unlocked");
        EncryptionStatus_attr->add_enum("Locked");
        EncryptionStatus_attr->add_enum("Foreign");
        EncryptionStatus_attr->add_enum("Unencrypted");
        add_property_attr("EncryptionStatus", EncryptionStatus_attr);

        auto StatusIndicator_attr = std::make_shared<prop_attribute>();
        StatusIndicator_attr->prop_name = "StatusIndicator";
        StatusIndicator_attr->read_only = false;
        StatusIndicator_attr->add_enum("OK");
        StatusIndicator_attr->add_enum("Fail");
        StatusIndicator_attr->add_enum("Rebuild");
        StatusIndicator_attr->add_enum("PredictiveFailureAnalysis");
        StatusIndicator_attr->add_enum("Hotspare");
        StatusIndicator_attr->add_enum("InACriticalArray");
        StatusIndicator_attr->add_enum("InAFailedArray");
        add_property_attr("StatusIndicator", StatusIndicator_attr);

        auto SKU_attr = std::make_shared<prop_attribute>();
        SKU_attr->prop_name = "SKU";
        SKU_attr->read_only = true;
        add_property_attr("SKU", SKU_attr);

        auto PartNumber_attr = std::make_shared<prop_attribute>();
        PartNumber_attr->prop_name = "PartNumber";
        PartNumber_attr->read_only = true;
        add_property_attr("PartNumber", PartNumber_attr);

        auto AssetTag_attr = std::make_shared<prop_attribute>();
        AssetTag_attr->prop_name = "AssetTag";
        AssetTag_attr->read_only = false;
        add_property_attr("AssetTag", AssetTag_attr);

        auto EncryptionAbility_attr = std::make_shared<prop_attribute>();
        EncryptionAbility_attr->prop_name = "EncryptionAbility";
        EncryptionAbility_attr->read_only = true;
        EncryptionAbility_attr->add_enum("None");
        EncryptionAbility_attr->add_enum("SelfEncryptingDrive");
        EncryptionAbility_attr->add_enum("Other");
        add_property_attr("EncryptionAbility", EncryptionAbility_attr);

        auto SerialNumber_attr = std::make_shared<prop_attribute>();
        SerialNumber_attr->prop_name = "SerialNumber";
        SerialNumber_attr->read_only = true;
        add_property_attr("SerialNumber", SerialNumber_attr);

        auto RotationSpeedRPM_attr = std::make_shared<prop_attribute>();
        RotationSpeedRPM_attr->prop_name = "RotationSpeedRPM";
        RotationSpeedRPM_attr->read_only = true;
        add_property_attr("RotationSpeedRPM", RotationSpeedRPM_attr);

        auto Assembly_attr = std::make_shared<prop_attribute>();
        Assembly_attr->prop_name = "Assembly";
        Assembly_attr->read_only = true;
        add_property_attr("Assembly", Assembly_attr);

     }

};

}}

