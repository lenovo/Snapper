//---------------------------------------------------------------------
// <copyright file="_pSwitch.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pSwitch : public ResourceProvider
{
public:
    _pSwitch() : ResourceProvider("Switch")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("AssetTag",  nullptr);
        create_prop("DomainID",  nullptr);
        create_prop("IndicatorLED",  nullptr);
        create_prop("IsManaged",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("Location",  nullptr);
        create_prop("LogServices",  nullptr);
        create_prop("Manufacturer",  nullptr);
        create_prop("Model",  nullptr);
        create_prop("PartNumber",  nullptr);
        create_prop("Ports",  nullptr);
        create_prop("PowerState",  nullptr);
        create_prop("Redundancy",  nullptr);
        create_prop("Redundancy@odata.count",  nullptr);
        create_prop("Redundancy@odata.navigationLink",  nullptr);
        create_prop("SKU",  nullptr);
        create_prop("SerialNumber",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("SwitchType",  nullptr);
        create_prop("TotalSwitchWidth",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Switch.v1_1_0");
        set_desc("Switch contains properties describing a simple fabric switch.");
    }

    virtual ~_pSwitch()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_arr_props("Redundancy");
        add_navigation_contained_props("LogServices");
        add_navigation_contained_props("Ports");
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["Chassis"] = nullptr;
        m_Links_prop_objs["ManagedBy"] = nullptr;
        m_Links_prop_objs["ManagedBy@odata.count"] = nullptr;
        m_Links_prop_objs["ManagedBy@odata.navigationLink"] = nullptr;
        add_Links_arr_props("ManagedBy");
    }

    void prepare_OemLenovo()
    {
    }

    virtual void set_actions_obj()
    {
         create_prop( "Actions",   std::make_shared<bson::BSONObj>(BSON("Actions" << BSON(
                "#Switch.Reset"
                << BSON("target" << (get_base_odata_id() + "/Actions/Switch.Reset")
                << "title" << "Reset"
                << "ResetType@Redfish.AllowableValues"
                << BSON_ARRAY("On"
                             << "ForceOff"
                             << "GracefulShutdown"
                             << "GracefulRestart"
                             << "ForceRestart"
                             << "Nmi"
                             << "ForceOn"
                             << "PushPowerButton"
                             << "PowerCycle"))
                )
                )) );
     }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("AssetTag", "Primitive Type.", "Edm.String");
        add_property_class("DomainID", "Primitive Type.", "Edm.Int64");
        add_property_class("IndicatorLED", "Enum Type.", "IndicatorLED");
        add_property_class("IsManaged", "Primitive Type.", "Edm.Boolean");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("Location", "Complex Type.", "Location");
        add_property_class("LogServices", "Navigation Type.Entity", "LogServiceCollection");
        add_property_class("Manufacturer", "Primitive Type.", "Edm.String");
        add_property_class("Model", "Primitive Type.", "Edm.String");
        add_property_class("PartNumber", "Primitive Type.", "Edm.String");
        add_property_class("Ports", "Navigation Type.Entity", "PortCollection");
        add_property_class("PowerState", "Enum Type.", "PowerState");
        add_property_class("Redundancy", "Navigation Type.Collection", "Redundancy");
        add_property_class("SKU", "Primitive Type.", "Edm.String");
        add_property_class("SerialNumber", "Primitive Type.", "Edm.String");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("SwitchType", "Enum Type.", "Protocol");
        add_property_class("TotalSwitchWidth", "Primitive Type.", "Edm.Int64");
    }

    void prep_prop_attrs()
    {
        auto LogServices_attr = std::make_shared<prop_attribute>();
        LogServices_attr->prop_name = "LogServices";
        LogServices_attr->read_only = true;
        add_property_attr("LogServices", LogServices_attr);

        auto Ports_attr = std::make_shared<prop_attribute>();
        Ports_attr->prop_name = "Ports";
        Ports_attr->read_only = true;
        add_property_attr("Ports", Ports_attr);

        auto PowerState_attr = std::make_shared<prop_attribute>();
        PowerState_attr->prop_name = "PowerState";
        PowerState_attr->read_only = true;
        PowerState_attr->add_enum("On");
        PowerState_attr->add_enum("Off");
        PowerState_attr->add_enum("PoweringOn");
        PowerState_attr->add_enum("PoweringOff");
        add_property_attr("PowerState", PowerState_attr);

        auto IndicatorLED_attr = std::make_shared<prop_attribute>();
        IndicatorLED_attr->prop_name = "IndicatorLED";
        IndicatorLED_attr->read_only = false;
        IndicatorLED_attr->add_enum("Lit");
        IndicatorLED_attr->add_enum("Blinking");
        IndicatorLED_attr->add_enum("Off");
        add_property_attr("IndicatorLED", IndicatorLED_attr);

        auto SwitchType_attr = std::make_shared<prop_attribute>();
        SwitchType_attr->prop_name = "SwitchType";
        SwitchType_attr->read_only = true;
        SwitchType_attr->add_enum("PCIe");
        SwitchType_attr->add_enum("AHCI");
        SwitchType_attr->add_enum("UHCI");
        SwitchType_attr->add_enum("SAS");
        SwitchType_attr->add_enum("SATA");
        SwitchType_attr->add_enum("USB");
        SwitchType_attr->add_enum("NVMe");
        SwitchType_attr->add_enum("FC");
        SwitchType_attr->add_enum("iSCSI");
        SwitchType_attr->add_enum("FCoE");
        SwitchType_attr->add_enum("FCP");
        SwitchType_attr->add_enum("FICON");
        SwitchType_attr->add_enum("NVMeOverFabrics");
        SwitchType_attr->add_enum("SMB");
        SwitchType_attr->add_enum("NFSv3");
        SwitchType_attr->add_enum("NFSv4");
        SwitchType_attr->add_enum("HTTP");
        SwitchType_attr->add_enum("HTTPS");
        SwitchType_attr->add_enum("FTP");
        SwitchType_attr->add_enum("SFTP");
        SwitchType_attr->add_enum("iWARP");
        SwitchType_attr->add_enum("RoCE");
        SwitchType_attr->add_enum("RoCEv2");
        SwitchType_attr->add_enum("OEM");
        add_property_attr("SwitchType", SwitchType_attr);

        auto SKU_attr = std::make_shared<prop_attribute>();
        SKU_attr->prop_name = "SKU";
        SKU_attr->read_only = true;
        add_property_attr("SKU", SKU_attr);

        auto AssetTag_attr = std::make_shared<prop_attribute>();
        AssetTag_attr->prop_name = "AssetTag";
        AssetTag_attr->read_only = false;
        add_property_attr("AssetTag", AssetTag_attr);

        auto DomainID_attr = std::make_shared<prop_attribute>();
        DomainID_attr->prop_name = "DomainID";
        DomainID_attr->read_only = true;
        add_property_attr("DomainID", DomainID_attr);

        auto Manufacturer_attr = std::make_shared<prop_attribute>();
        Manufacturer_attr->prop_name = "Manufacturer";
        Manufacturer_attr->read_only = true;
        add_property_attr("Manufacturer", Manufacturer_attr);

        auto Model_attr = std::make_shared<prop_attribute>();
        Model_attr->prop_name = "Model";
        Model_attr->read_only = true;
        add_property_attr("Model", Model_attr);

        auto SerialNumber_attr = std::make_shared<prop_attribute>();
        SerialNumber_attr->prop_name = "SerialNumber";
        SerialNumber_attr->read_only = true;
        add_property_attr("SerialNumber", SerialNumber_attr);

        auto PartNumber_attr = std::make_shared<prop_attribute>();
        PartNumber_attr->prop_name = "PartNumber";
        PartNumber_attr->read_only = true;
        add_property_attr("PartNumber", PartNumber_attr);

        auto TotalSwitchWidth_attr = std::make_shared<prop_attribute>();
        TotalSwitchWidth_attr->prop_name = "TotalSwitchWidth";
        TotalSwitchWidth_attr->read_only = true;
        add_property_attr("TotalSwitchWidth", TotalSwitchWidth_attr);

        auto IsManaged_attr = std::make_shared<prop_attribute>();
        IsManaged_attr->prop_name = "IsManaged";
        IsManaged_attr->read_only = false;
        add_property_attr("IsManaged", IsManaged_attr);

     }

};

}}

