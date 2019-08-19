//---------------------------------------------------------------------
// <copyright file="_pComputerSystem.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pComputerSystem : public ResourceProvider
{
public:
    _pComputerSystem() : ResourceProvider("ComputerSystem")    
    {
        enum BootSource 
        {
            BootSource_None,
            BootSource_Pxe,
            BootSource_Floppy,
            BootSource_Cd,
            BootSource_Usb,
            BootSource_Hdd,
            BootSource_BiosSetup,
            BootSource_Utilities,
            BootSource_Diags,
            BootSource_UefiShell,
            BootSource_UefiTarget,
            BootSource_SDCard,
            BootSource_UefiHttp,
            BootSource_RemoteDrive,
            BootSource_UefiBootNext,
        };

        enum PowerState 
        {
            PowerState_On,
            PowerState_Off,
            PowerState_PoweringOn,
            PowerState_PoweringOff,
        };

        enum IndicatorLED 
        {
            IndicatorLED_Lit,
            IndicatorLED_Blinking,
            IndicatorLED_Off,
        };

        enum BootSourceOverrideEnabled 
        {
            BootSourceOverrideEnabled_Disabled,
            BootSourceOverrideEnabled_Once,
            BootSourceOverrideEnabled_Continuous,
        };

        enum SystemType 
        {
            SystemType_Physical,
            SystemType_Virtual,
            SystemType_OS,
            SystemType_PhysicallyPartitioned,
            SystemType_VirtuallyPartitioned,
            SystemType_Composed,
        };

        enum InterfaceType 
        {
            InterfaceType_TPM1_2,
            InterfaceType_TPM2_0,
            InterfaceType_TCM1_0,
        };

        enum BootSourceOverrideMode 
        {
            BootSourceOverrideMode_Legacy,
            BootSourceOverrideMode_UEFI,
        };

        enum MemoryMirroring 
        {
            MemoryMirroring_System,
            MemoryMirroring_DIMM,
            MemoryMirroring_Hybrid,
            MemoryMirroring_None,
        };

        enum HostingRole 
        {
            HostingRole_ApplicationServer,
            HostingRole_StorageServer,
            HostingRole_Switch,
        };

        enum InterfaceTypeSelection 
        {
            InterfaceTypeSelection_None,
            InterfaceTypeSelection_FirmwareUpdate,
            InterfaceTypeSelection_BiosSetting,
            InterfaceTypeSelection_OemMethod,
        };

        enum WatchdogTimeoutActions 
        {
            WatchdogTimeoutActions_None,
            WatchdogTimeoutActions_ResetSystem,
            WatchdogTimeoutActions_PowerCycle,
            WatchdogTimeoutActions_PowerDown,
            WatchdogTimeoutActions_OEM,
        };

        enum WatchdogWarningActions 
        {
            WatchdogWarningActions_None,
            WatchdogWarningActions_DiagnosticInterrupt,
            WatchdogWarningActions_SMI,
            WatchdogWarningActions_MessagingInterrupt,
            WatchdogWarningActions_SCI,
            WatchdogWarningActions_OEM,
        };

        enum IDBtnState 
        {
            IDBtnState_On,
            IDBtnState_Off,
        };

        enum FPUSBOwner 
        {
            FPUSBOwner_BMC,
            FPUSBOwner_Server,
        };

        enum FPUSBMode 
        {
            FPUSBMode_Server,
            FPUSBMode_BMC,
            FPUSBMode_Shared,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("AssetTag",  nullptr);
        create_prop("Bios",  nullptr);
        create_prop("BiosVersion",  nullptr);
        create_prop("Boot",  nullptr);
        create_prop("EthernetInterfaces",  nullptr);
        create_prop("HostName",  nullptr);
        create_prop("HostWatchdogTimer",  nullptr);
        create_prop("HostedServices",  nullptr);
        create_prop("HostingRoles",  nullptr);
        create_prop("IndicatorLED",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("LogServices",  nullptr);
        create_prop("Manufacturer",  nullptr);
        create_prop("Memory",  nullptr);
        create_prop("MemoryDomains",  nullptr);
        create_prop("MemorySummary",  nullptr);
        create_prop("Model",  nullptr);
        create_prop("NetworkInterfaces",  nullptr);
        create_prop("PCIeDevices",  nullptr);
        create_prop("PCIeDevices@odata.count",  nullptr);
        create_prop("PCIeDevices@odata.navigationLink",  nullptr);
        create_prop("PCIeFunctions",  nullptr);
        create_prop("PCIeFunctions@odata.count",  nullptr);
        create_prop("PCIeFunctions@odata.navigationLink",  nullptr);
        create_prop("PartNumber",  nullptr);
        create_prop("PowerState",  nullptr);
        create_prop("ProcessorSummary",  nullptr);
        create_prop("Processors",  nullptr);
        create_prop("Redundancy",  nullptr);
        create_prop("Redundancy@odata.count",  nullptr);
        create_prop("Redundancy@odata.navigationLink",  nullptr);
        create_prop("SKU",  nullptr);
        create_prop("SecureBoot",  nullptr);
        create_prop("SerialNumber",  nullptr);
        create_prop("SimpleStorage",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("Storage",  nullptr);
        create_prop("SubModel",  nullptr);
        create_prop("SystemType",  nullptr);
        create_prop("TrustedModules",  nullptr);
        create_prop("UUID",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("ComputerSystem.v1_5_0");
        set_desc("This schema defines a computer system and its respective properties.  A computer system represents a machine (physical or virtual) and the local resources such as memory, cpu and other devices that can be accessed from that machine.");
    }

    virtual ~_pComputerSystem()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_arr_props("PCIeFunctions");
        add_navigation_arr_props("PCIeDevices");
        add_navigation_arr_props("Redundancy");
        add_navigation_contained_props("LogServices");
        add_navigation_contained_props("EthernetInterfaces");
        add_navigation_contained_props("Processors");
        add_navigation_contained_props("SimpleStorage");
        add_navigation_contained_props("Memory");
        add_navigation_contained_props("Bios");
        add_navigation_contained_props("Storage");
        add_navigation_contained_props("SecureBoot");
        add_navigation_contained_props("MemoryDomains");
        add_navigation_contained_props("NetworkInterfaces");
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["Chassis"] = nullptr;
        m_Links_prop_objs["Chassis@odata.count"] = nullptr;
        m_Links_prop_objs["Chassis@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["ConsumingComputerSystems"] = nullptr;
        m_Links_prop_objs["ConsumingComputerSystems@odata.count"] = nullptr;
        m_Links_prop_objs["ConsumingComputerSystems@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["CooledBy"] = nullptr;
        m_Links_prop_objs["CooledBy@odata.count"] = nullptr;
        m_Links_prop_objs["CooledBy@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["Endpoints"] = nullptr;
        m_Links_prop_objs["Endpoints@odata.count"] = nullptr;
        m_Links_prop_objs["Endpoints@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["ManagedBy"] = nullptr;
        m_Links_prop_objs["ManagedBy@odata.count"] = nullptr;
        m_Links_prop_objs["ManagedBy@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["PoweredBy"] = nullptr;
        m_Links_prop_objs["PoweredBy@odata.count"] = nullptr;
        m_Links_prop_objs["PoweredBy@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["ResourceBlocks"] = nullptr;
        m_Links_prop_objs["ResourceBlocks@odata.count"] = nullptr;
        m_Links_prop_objs["ResourceBlocks@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["SupplyingComputerSystems"] = nullptr;
        m_Links_prop_objs["SupplyingComputerSystems@odata.count"] = nullptr;
        m_Links_prop_objs["SupplyingComputerSystems@odata.navigationLink"] = nullptr;
        add_Links_arr_props("Chassis");
        add_Links_arr_props("ConsumingComputerSystems");
        add_Links_arr_props("CooledBy");
        add_Links_arr_props("Endpoints");
        add_Links_arr_props("ManagedBy");
        add_Links_arr_props("PoweredBy");
        add_Links_arr_props("ResourceBlocks");
        add_Links_arr_props("SupplyingComputerSystems");
    }

    void prepare_OemLenovo()
    {
        create_OemLenovo_prop("@odata.type", std::make_shared<bson::BSONObj>(BSON("@odata.type" << "#LenovoComputerSystem.v1_0_0.Lenovo")));
        create_OemLenovo_prop("BootSettings", nullptr);
        create_OemLenovo_prop("FrontPanelUSB", nullptr);
        create_OemLenovo_prop("Metrics", nullptr);
        
        add_property_class("Oem/Lenovo/BootSettings", "Navigation Type.Entity", "LenovoBootManagerCollection");
        add_property_class("Oem/Lenovo/FrontPanelUSB", "Complex Type.", "FrontPanelUSBPort");
        add_property_class("Oem/Lenovo/Metrics", "Navigation Type.Entity", "LenovoHistoryMetricValueContainerCollection");
    }

    virtual void set_actions_obj()
    {
         create_prop( "Actions",   std::make_shared<bson::BSONObj>(BSON("Actions" << BSON(
                "#ComputerSystem.SetDefaultBootOrder"
                << BSON("target" << (get_base_odata_id() + "/Actions/ComputerSystem.SetDefaultBootOrder")
                << "title" << "SetDefaultBootOrder")
                << "#ComputerSystem.Reset"
                << BSON("target" << (get_base_odata_id() + "/Actions/ComputerSystem.Reset")
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
        add_property_class("Bios", "Navigation Type.Entity", "Bios");
        add_property_class("BiosVersion", "Primitive Type.", "Edm.String");
        add_property_class("Boot", "Complex Type.", "Boot");
        add_property_class("EthernetInterfaces", "Navigation Type.Entity", "EthernetInterfaceCollection");
        add_property_class("HostName", "Primitive Type.", "Edm.String");
        add_property_class("HostWatchdogTimer", "Complex Type.", "WatchdogTimer");
        add_property_class("HostedServices", "Complex Type.", "HostedServices");
        add_property_class("HostingRoles", "Collection Type.", "HostingRole");
        add_property_class("IndicatorLED", "Enum Type.", "IndicatorLED");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("LogServices", "Navigation Type.Entity", "LogServiceCollection");
        add_property_class("Manufacturer", "Primitive Type.", "Edm.String");
        add_property_class("Memory", "Navigation Type.Entity", "MemoryCollection");
        add_property_class("MemoryDomains", "Navigation Type.Entity", "MemoryDomainCollection");
        add_property_class("MemorySummary", "Complex Type.", "MemorySummary");
        add_property_class("Model", "Primitive Type.", "Edm.String");
        add_property_class("NetworkInterfaces", "Navigation Type.Entity", "NetworkInterfaceCollection");
        add_property_class("PCIeDevices", "Navigation Type.Collection", "PCIeDevice");
        add_property_class("PCIeFunctions", "Navigation Type.Collection", "PCIeFunction");
        add_property_class("PartNumber", "Primitive Type.", "Edm.String");
        add_property_class("PowerState", "Enum Type.", "PowerState");
        add_property_class("ProcessorSummary", "Complex Type.", "ProcessorSummary");
        add_property_class("Processors", "Navigation Type.Entity", "ProcessorCollection");
        add_property_class("Redundancy", "Navigation Type.Collection", "Redundancy");
        add_property_class("SKU", "Primitive Type.", "Edm.String");
        add_property_class("SecureBoot", "Navigation Type.Entity", "SecureBoot");
        add_property_class("SerialNumber", "Primitive Type.", "Edm.String");
        add_property_class("SimpleStorage", "Navigation Type.Entity", "SimpleStorageCollection");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("Storage", "Navigation Type.Entity", "StorageCollection");
        add_property_class("SubModel", "Primitive Type.", "Edm.String");
        add_property_class("SystemType", "Enum Type.", "SystemType");
        add_property_class("TrustedModules", "Collection Type.", "TrustedModules");
        add_property_class("UUID", "Type Definition.", "Edm.Guid");
    }

    void prep_prop_attrs()
    {
        auto LogServices_attr = std::make_shared<prop_attribute>();
        LogServices_attr->prop_name = "LogServices";
        LogServices_attr->read_only = true;
        add_property_attr("LogServices", LogServices_attr);

        auto EthernetInterfaces_attr = std::make_shared<prop_attribute>();
        EthernetInterfaces_attr->prop_name = "EthernetInterfaces";
        EthernetInterfaces_attr->read_only = true;
        add_property_attr("EthernetInterfaces", EthernetInterfaces_attr);

        auto Processors_attr = std::make_shared<prop_attribute>();
        Processors_attr->prop_name = "Processors";
        Processors_attr->read_only = true;
        add_property_attr("Processors", Processors_attr);

        auto SimpleStorage_attr = std::make_shared<prop_attribute>();
        SimpleStorage_attr->prop_name = "SimpleStorage";
        SimpleStorage_attr->read_only = true;
        add_property_attr("SimpleStorage", SimpleStorage_attr);

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
        IndicatorLED_attr->add_enum("Unknown");
        IndicatorLED_attr->add_enum("Lit");
        IndicatorLED_attr->add_enum("Blinking");
        IndicatorLED_attr->add_enum("Off");
        add_property_attr("IndicatorLED", IndicatorLED_attr);

        auto SystemType_attr = std::make_shared<prop_attribute>();
        SystemType_attr->prop_name = "SystemType";
        SystemType_attr->read_only = true;
        SystemType_attr->add_enum("Physical");
        SystemType_attr->add_enum("Virtual");
        SystemType_attr->add_enum("OS");
        SystemType_attr->add_enum("PhysicallyPartitioned");
        SystemType_attr->add_enum("VirtuallyPartitioned");
        SystemType_attr->add_enum("Composed");
        add_property_attr("SystemType", SystemType_attr);

        auto BiosVersion_attr = std::make_shared<prop_attribute>();
        BiosVersion_attr->prop_name = "BiosVersion";
        BiosVersion_attr->read_only = true;
        add_property_attr("BiosVersion", BiosVersion_attr);

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

        auto UUID_attr = std::make_shared<prop_attribute>();
        UUID_attr->prop_name = "UUID";
        UUID_attr->read_only = true;
        add_property_attr("UUID", UUID_attr);

        auto AssetTag_attr = std::make_shared<prop_attribute>();
        AssetTag_attr->prop_name = "AssetTag";
        AssetTag_attr->read_only = false;
        add_property_attr("AssetTag", AssetTag_attr);

        auto HostName_attr = std::make_shared<prop_attribute>();
        HostName_attr->prop_name = "HostName";
        HostName_attr->read_only = false;
        add_property_attr("HostName", HostName_attr);

        auto Memory_attr = std::make_shared<prop_attribute>();
        Memory_attr->prop_name = "Memory";
        Memory_attr->read_only = true;
        add_property_attr("Memory", Memory_attr);

        auto Bios_attr = std::make_shared<prop_attribute>();
        Bios_attr->prop_name = "Bios";
        Bios_attr->read_only = true;
        add_property_attr("Bios", Bios_attr);

        auto Storage_attr = std::make_shared<prop_attribute>();
        Storage_attr->prop_name = "Storage";
        Storage_attr->read_only = true;
        add_property_attr("Storage", Storage_attr);

        auto SecureBoot_attr = std::make_shared<prop_attribute>();
        SecureBoot_attr->prop_name = "SecureBoot";
        SecureBoot_attr->read_only = true;
        add_property_attr("SecureBoot", SecureBoot_attr);

        auto MemoryDomains_attr = std::make_shared<prop_attribute>();
        MemoryDomains_attr->prop_name = "MemoryDomains";
        MemoryDomains_attr->read_only = true;
        add_property_attr("MemoryDomains", MemoryDomains_attr);

        auto PCIeFunctions_attr = std::make_shared<prop_attribute>();
        PCIeFunctions_attr->prop_name = "PCIeFunctions";
        PCIeFunctions_attr->read_only = true;
        add_property_attr("PCIeFunctions", PCIeFunctions_attr);

        auto PCIeDevices_attr = std::make_shared<prop_attribute>();
        PCIeDevices_attr->prop_name = "PCIeDevices";
        PCIeDevices_attr->read_only = true;
        add_property_attr("PCIeDevices", PCIeDevices_attr);

        auto HostingRoles_attr = std::make_shared<prop_attribute>();
        HostingRoles_attr->prop_name = "HostingRoles";
        HostingRoles_attr->read_only = true;
        HostingRoles_attr->add_enum("ApplicationServer");
        HostingRoles_attr->add_enum("StorageServer");
        HostingRoles_attr->add_enum("Switch");
        add_property_attr("HostingRoles", HostingRoles_attr);

        auto NetworkInterfaces_attr = std::make_shared<prop_attribute>();
        NetworkInterfaces_attr->prop_name = "NetworkInterfaces";
        NetworkInterfaces_attr->read_only = true;
        add_property_attr("NetworkInterfaces", NetworkInterfaces_attr);

        auto SubModel_attr = std::make_shared<prop_attribute>();
        SubModel_attr->prop_name = "SubModel";
        SubModel_attr->read_only = true;
        add_property_attr("SubModel", SubModel_attr);

        auto Redundancy_attr = std::make_shared<prop_attribute>();
        Redundancy_attr->prop_name = "Redundancy";
        Redundancy_attr->read_only = true;
        add_property_attr("Redundancy", Redundancy_attr);

     }

};

}}

