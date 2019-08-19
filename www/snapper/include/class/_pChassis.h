//---------------------------------------------------------------------
// <copyright file="_pChassis.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pChassis : public ResourceProvider
{
public:
    _pChassis() : ResourceProvider("Chassis")    
    {
        enum IndicatorLED 
        {
            IndicatorLED_Lit,
            IndicatorLED_Blinking,
            IndicatorLED_Off,
        };

        enum ChassisType 
        {
            ChassisType_Rack,
            ChassisType_Blade,
            ChassisType_Enclosure,
            ChassisType_StandAlone,
            ChassisType_RackMount,
            ChassisType_Card,
            ChassisType_Cartridge,
            ChassisType_Row,
            ChassisType_Pod,
            ChassisType_Expansion,
            ChassisType_Sidecar,
            ChassisType_Zone,
            ChassisType_Sled,
            ChassisType_Shelf,
            ChassisType_Drawer,
            ChassisType_Module,
            ChassisType_Component,
            ChassisType_IPBasedDrive,
            ChassisType_RackGroup,
            ChassisType_StorageEnclosure,
            ChassisType_Other,
        };

        enum PowerState 
        {
            PowerState_On,
            PowerState_Off,
            PowerState_PoweringOn,
            PowerState_PoweringOff,
        };

        enum IntrusionSensorReArm 
        {
            IntrusionSensorReArm_Manual,
            IntrusionSensorReArm_Automatic,
        };

        enum IntrusionSensor 
        {
            IntrusionSensor_Normal,
            IntrusionSensor_HardwareIntrusion,
            IntrusionSensor_TamperingDetected,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Assembly",  nullptr);
        create_prop("AssetTag",  nullptr);
        create_prop("ChassisType",  nullptr);
        create_prop("DepthMm",  nullptr);
        create_prop("HeightMm",  nullptr);
        create_prop("IndicatorLED",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("Location",  nullptr);
        create_prop("LogServices",  nullptr);
        create_prop("Manufacturer",  nullptr);
        create_prop("Model",  nullptr);
        create_prop("NetworkAdapters",  nullptr);
        create_prop("PartNumber",  nullptr);
        create_prop("PhysicalSecurity",  nullptr);
        create_prop("Power",  nullptr);
        create_prop("PowerState",  nullptr);
        create_prop("SKU",  nullptr);
        create_prop("SerialNumber",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("Thermal",  nullptr);
        create_prop("UUID",  nullptr);
        create_prop("WeightKg",  nullptr);
        create_prop("WidthMm",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Chassis.v1_7_0");
        set_desc("The Chassis schema represents the physical components of a system.  This resource represents the sheet-metal confined spaces and logical zones such as racks, enclosures, chassis and all other containers. Subsystems (like sensors) that operate outside of a system's data plane (meaning the resources are not accessible to software running on the system) are linked either directly or indirectly through this resource.");
    }

    virtual ~_pChassis()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("Power");
        add_navigation_contained_props("Thermal");
        add_navigation_contained_props("LogServices");
        add_navigation_contained_props("NetworkAdapters");
        add_navigation_contained_props("Assembly");
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["ComputerSystems"] = nullptr;
        m_Links_prop_objs["ComputerSystems@odata.count"] = nullptr;
        m_Links_prop_objs["ComputerSystems@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["ContainedBy"] = nullptr;
        m_Links_prop_objs["Contains"] = nullptr;
        m_Links_prop_objs["Contains@odata.count"] = nullptr;
        m_Links_prop_objs["Contains@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["CooledBy"] = nullptr;
        m_Links_prop_objs["CooledBy@odata.count"] = nullptr;
        m_Links_prop_objs["CooledBy@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["Drives"] = nullptr;
        m_Links_prop_objs["Drives@odata.count"] = nullptr;
        m_Links_prop_objs["Drives@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["ManagedBy"] = nullptr;
        m_Links_prop_objs["ManagedBy@odata.count"] = nullptr;
        m_Links_prop_objs["ManagedBy@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["ManagersInChassis"] = nullptr;
        m_Links_prop_objs["ManagersInChassis@odata.count"] = nullptr;
        m_Links_prop_objs["ManagersInChassis@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["PCIeDevices"] = nullptr;
        m_Links_prop_objs["PCIeDevices@odata.count"] = nullptr;
        m_Links_prop_objs["PCIeDevices@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["PoweredBy"] = nullptr;
        m_Links_prop_objs["PoweredBy@odata.count"] = nullptr;
        m_Links_prop_objs["PoweredBy@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["ResourceBlocks"] = nullptr;
        m_Links_prop_objs["ResourceBlocks@odata.count"] = nullptr;
        m_Links_prop_objs["ResourceBlocks@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["Storage"] = nullptr;
        m_Links_prop_objs["Storage@odata.count"] = nullptr;
        m_Links_prop_objs["Storage@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["Switches"] = nullptr;
        m_Links_prop_objs["Switches@odata.count"] = nullptr;
        m_Links_prop_objs["Switches@odata.navigationLink"] = nullptr;
        add_Links_arr_props("ComputerSystems");
        add_Links_arr_props("Contains");
        add_Links_arr_props("CooledBy");
        add_Links_arr_props("Drives");
        add_Links_arr_props("ManagedBy");
        add_Links_arr_props("ManagersInChassis");
        add_Links_arr_props("PCIeDevices");
        add_Links_arr_props("PoweredBy");
        add_Links_arr_props("ResourceBlocks");
        add_Links_arr_props("Storage");
        add_Links_arr_props("Switches");
    }

    void prepare_OemLenovo()
    {
        create_OemLenovo_prop("@odata.type", std::make_shared<bson::BSONObj>(BSON("@odata.type" << "#LenovoChassis.v1_0_0.Lenovo")));
        create_OemLenovo_prop("LEDs", nullptr);
        create_OemLenovo_prop("LocatedIn", nullptr);
        create_OemLenovo_prop("ProductName", nullptr);
        create_OemLenovo_prop("Sensors", nullptr);
        
        add_property_class("Oem/Lenovo/LEDs", "Navigation Type.Entity", "LenovoLEDCollection");
        add_property_class("Oem/Lenovo/LocatedIn", "Complex Type.", "LenovoGeneralInfo");
        add_property_class("Oem/Lenovo/ProductName", "Primitive Type.", "Edm.String");
        add_property_class("Oem/Lenovo/Sensors", "Navigation Type.Entity", "LenovoSensorCollection");
    }

    virtual void set_actions_obj()
    {
         create_prop( "Actions",   std::make_shared<bson::BSONObj>(BSON("Actions" << BSON(
                "#Chassis.Reset"
                << BSON("target" << (get_base_odata_id() + "/Actions/Chassis.Reset")
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
        add_property_class("Assembly", "Navigation Type.Entity", "Assembly");
        add_property_class("AssetTag", "Primitive Type.", "Edm.String");
        add_property_class("ChassisType", "Enum Type.", "ChassisType");
        add_property_class("DepthMm", "Primitive Type.", "Edm.Decimal");
        add_property_class("HeightMm", "Primitive Type.", "Edm.Decimal");
        add_property_class("IndicatorLED", "Enum Type.", "IndicatorLED");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("Location", "Complex Type.", "Location");
        add_property_class("LogServices", "Navigation Type.Entity", "LogServiceCollection");
        add_property_class("Manufacturer", "Primitive Type.", "Edm.String");
        add_property_class("Model", "Primitive Type.", "Edm.String");
        add_property_class("NetworkAdapters", "Navigation Type.Entity", "NetworkAdapterCollection");
        add_property_class("PartNumber", "Primitive Type.", "Edm.String");
        add_property_class("PhysicalSecurity", "Complex Type.", "PhysicalSecurity");
        add_property_class("Power", "Navigation Type.Entity", "Power");
        add_property_class("PowerState", "Enum Type.", "PowerState");
        add_property_class("SKU", "Primitive Type.", "Edm.String");
        add_property_class("SerialNumber", "Primitive Type.", "Edm.String");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("Thermal", "Navigation Type.Entity", "Thermal");
        add_property_class("UUID", "Type Definition.", "Edm.Guid");
        add_property_class("WeightKg", "Primitive Type.", "Edm.Decimal");
        add_property_class("WidthMm", "Primitive Type.", "Edm.Decimal");
    }

    void prep_prop_attrs()
    {
        auto Power_attr = std::make_shared<prop_attribute>();
        Power_attr->prop_name = "Power";
        Power_attr->read_only = true;
        add_property_attr("Power", Power_attr);

        auto Thermal_attr = std::make_shared<prop_attribute>();
        Thermal_attr->prop_name = "Thermal";
        Thermal_attr->read_only = true;
        add_property_attr("Thermal", Thermal_attr);

        auto LogServices_attr = std::make_shared<prop_attribute>();
        LogServices_attr->prop_name = "LogServices";
        LogServices_attr->read_only = true;
        add_property_attr("LogServices", LogServices_attr);

        auto Manufacturer_attr = std::make_shared<prop_attribute>();
        Manufacturer_attr->prop_name = "Manufacturer";
        Manufacturer_attr->read_only = true;
        add_property_attr("Manufacturer", Manufacturer_attr);

        auto Model_attr = std::make_shared<prop_attribute>();
        Model_attr->prop_name = "Model";
        Model_attr->read_only = true;
        add_property_attr("Model", Model_attr);

        auto SKU_attr = std::make_shared<prop_attribute>();
        SKU_attr->prop_name = "SKU";
        SKU_attr->read_only = true;
        add_property_attr("SKU", SKU_attr);

        auto SerialNumber_attr = std::make_shared<prop_attribute>();
        SerialNumber_attr->prop_name = "SerialNumber";
        SerialNumber_attr->read_only = true;
        add_property_attr("SerialNumber", SerialNumber_attr);

        auto PartNumber_attr = std::make_shared<prop_attribute>();
        PartNumber_attr->prop_name = "PartNumber";
        PartNumber_attr->read_only = true;
        add_property_attr("PartNumber", PartNumber_attr);

        auto ChassisType_attr = std::make_shared<prop_attribute>();
        ChassisType_attr->prop_name = "ChassisType";
        ChassisType_attr->read_only = true;
        ChassisType_attr->add_enum("Rack");
        ChassisType_attr->add_enum("Blade");
        ChassisType_attr->add_enum("Enclosure");
        ChassisType_attr->add_enum("StandAlone");
        ChassisType_attr->add_enum("RackMount");
        ChassisType_attr->add_enum("Card");
        ChassisType_attr->add_enum("Cartridge");
        ChassisType_attr->add_enum("Row");
        ChassisType_attr->add_enum("Pod");
        ChassisType_attr->add_enum("Expansion");
        ChassisType_attr->add_enum("Sidecar");
        ChassisType_attr->add_enum("Zone");
        ChassisType_attr->add_enum("Sled");
        ChassisType_attr->add_enum("Shelf");
        ChassisType_attr->add_enum("Drawer");
        ChassisType_attr->add_enum("Module");
        ChassisType_attr->add_enum("Component");
        ChassisType_attr->add_enum("IPBasedDrive");
        ChassisType_attr->add_enum("RackGroup");
        ChassisType_attr->add_enum("StorageEnclosure");
        ChassisType_attr->add_enum("Other");
        add_property_attr("ChassisType", ChassisType_attr);

        auto IndicatorLED_attr = std::make_shared<prop_attribute>();
        IndicatorLED_attr->prop_name = "IndicatorLED";
        IndicatorLED_attr->read_only = false;
        IndicatorLED_attr->add_enum("Unknown");
        IndicatorLED_attr->add_enum("Lit");
        IndicatorLED_attr->add_enum("Blinking");
        IndicatorLED_attr->add_enum("Off");
        add_property_attr("IndicatorLED", IndicatorLED_attr);

        auto AssetTag_attr = std::make_shared<prop_attribute>();
        AssetTag_attr->prop_name = "AssetTag";
        AssetTag_attr->read_only = false;
        add_property_attr("AssetTag", AssetTag_attr);

        auto PowerState_attr = std::make_shared<prop_attribute>();
        PowerState_attr->prop_name = "PowerState";
        PowerState_attr->read_only = true;
        PowerState_attr->add_enum("On");
        PowerState_attr->add_enum("Off");
        PowerState_attr->add_enum("PoweringOn");
        PowerState_attr->add_enum("PoweringOff");
        add_property_attr("PowerState", PowerState_attr);

        auto NetworkAdapters_attr = std::make_shared<prop_attribute>();
        NetworkAdapters_attr->prop_name = "NetworkAdapters";
        NetworkAdapters_attr->read_only = true;
        add_property_attr("NetworkAdapters", NetworkAdapters_attr);

        auto DepthMm_attr = std::make_shared<prop_attribute>();
        DepthMm_attr->prop_name = "DepthMm";
        DepthMm_attr->read_only = true;
        add_property_attr("DepthMm", DepthMm_attr);

        auto WidthMm_attr = std::make_shared<prop_attribute>();
        WidthMm_attr->prop_name = "WidthMm";
        WidthMm_attr->read_only = true;
        add_property_attr("WidthMm", WidthMm_attr);

        auto WeightKg_attr = std::make_shared<prop_attribute>();
        WeightKg_attr->prop_name = "WeightKg";
        WeightKg_attr->read_only = true;
        add_property_attr("WeightKg", WeightKg_attr);

        auto HeightMm_attr = std::make_shared<prop_attribute>();
        HeightMm_attr->prop_name = "HeightMm";
        HeightMm_attr->read_only = true;
        add_property_attr("HeightMm", HeightMm_attr);

        auto Assembly_attr = std::make_shared<prop_attribute>();
        Assembly_attr->prop_name = "Assembly";
        Assembly_attr->read_only = true;
        add_property_attr("Assembly", Assembly_attr);

        auto UUID_attr = std::make_shared<prop_attribute>();
        UUID_attr->prop_name = "UUID";
        UUID_attr->read_only = true;
        add_property_attr("UUID", UUID_attr);

     }

};

}}

