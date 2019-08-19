//---------------------------------------------------------------------
// <copyright file="_pMemory.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pMemory : public ResourceProvider
{
public:
    _pMemory() : ResourceProvider("Memory")    
    {
        enum MemoryClassification 
        {
            MemoryClassification_Volatile,
            MemoryClassification_ByteAccessiblePersistent,
            MemoryClassification_Block,
        };

        enum ErrorCorrection 
        {
            ErrorCorrection_NoECC,
            ErrorCorrection_SingleBitECC,
            ErrorCorrection_MultiBitECC,
            ErrorCorrection_AddressParity,
        };

        enum SecurityStates 
        {
            SecurityStates_Enabled,
            SecurityStates_Disabled,
            SecurityStates_Unlocked,
            SecurityStates_Locked,
            SecurityStates_Frozen,
            SecurityStates_Passphraselimit,
        };

        enum BaseModuleType 
        {
            BaseModuleType_RDIMM,
            BaseModuleType_UDIMM,
            BaseModuleType_SO_DIMM,
            BaseModuleType_LRDIMM,
            BaseModuleType_Mini_RDIMM,
            BaseModuleType_Mini_UDIMM,
            BaseModuleType_SO_RDIMM_72b,
            BaseModuleType_SO_UDIMM_72b,
            BaseModuleType_SO_DIMM_16b,
            BaseModuleType_SO_DIMM_32b,
        };

        enum MemoryMedia 
        {
            MemoryMedia_DRAM,
            MemoryMedia_NAND,
            MemoryMedia_Proprietary,
        };

        enum MemoryDeviceType 
        {
            MemoryDeviceType_DDR,
            MemoryDeviceType_DDR2,
            MemoryDeviceType_DDR3,
            MemoryDeviceType_DDR4,
            MemoryDeviceType_DDR4_SDRAM,
            MemoryDeviceType_DDR4E_SDRAM,
            MemoryDeviceType_LPDDR4_SDRAM,
            MemoryDeviceType_DDR3_SDRAM,
            MemoryDeviceType_LPDDR3_SDRAM,
            MemoryDeviceType_DDR2_SDRAM,
            MemoryDeviceType_DDR2_SDRAM_FB_DIMM,
            MemoryDeviceType_DDR2_SDRAM_FB_DIMM_PROBE,
            MemoryDeviceType_DDR_SGRAM,
            MemoryDeviceType_DDR_SDRAM,
            MemoryDeviceType_ROM,
            MemoryDeviceType_SDRAM,
            MemoryDeviceType_EDO,
            MemoryDeviceType_FastPageMode,
            MemoryDeviceType_PipelinedNibble,
            MemoryDeviceType_Logical,
        };

        enum OperatingMemoryModes 
        {
            OperatingMemoryModes_Volatile,
            OperatingMemoryModes_PMEM,
            OperatingMemoryModes_Block,
        };

        enum MemoryType 
        {
            MemoryType_DRAM,
            MemoryType_NVDIMM_N,
            MemoryType_NVDIMM_F,
            MemoryType_NVDIMM_P,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("AllocationAlignmentMiB",  nullptr);
        create_prop("AllocationIncrementMiB",  nullptr);
        create_prop("AllowedSpeedsMHz",  nullptr);
        create_prop("Assembly",  nullptr);
        create_prop("BaseModuleType",  nullptr);
        create_prop("BusWidthBits",  nullptr);
        create_prop("CacheSizeMiB",  nullptr);
        create_prop("CapacityMiB",  nullptr);
        create_prop("DataWidthBits",  nullptr);
        create_prop("DeviceLocator",  nullptr);
        create_prop("ErrorCorrection",  nullptr);
        create_prop("FirmwareApiVersion",  nullptr);
        create_prop("FirmwareRevision",  nullptr);
        create_prop("IsRankSpareEnabled",  nullptr);
        create_prop("IsSpareDeviceEnabled",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("Location",  nullptr);
        create_prop("LogicalSizeMiB",  nullptr);
        create_prop("Manufacturer",  nullptr);
        create_prop("MaxTDPMilliWatts",  nullptr);
        create_prop("MemoryDeviceType",  nullptr);
        create_prop("MemoryLocation",  nullptr);
        create_prop("MemoryMedia",  nullptr);
        create_prop("MemorySubsystemControllerManufacturerID",  nullptr);
        create_prop("MemorySubsystemControllerProductID",  nullptr);
        create_prop("MemoryType",  nullptr);
        create_prop("Metrics",  nullptr);
        create_prop("ModuleManufacturerID",  nullptr);
        create_prop("ModuleProductID",  nullptr);
        create_prop("NonVolatileSizeMiB",  nullptr);
        create_prop("OperatingMemoryModes",  nullptr);
        create_prop("OperatingSpeedMhz",  nullptr);
        create_prop("PartNumber",  nullptr);
        create_prop("PersistentRegionNumberLimit",  nullptr);
        create_prop("PersistentRegionSizeLimitMiB",  nullptr);
        create_prop("PersistentRegionSizeMaxMiB",  nullptr);
        create_prop("PowerManagementPolicy",  nullptr);
        create_prop("RankCount",  nullptr);
        create_prop("Regions",  nullptr);
        create_prop("SecurityCapabilities",  nullptr);
        create_prop("SerialNumber",  nullptr);
        create_prop("SpareDeviceCount",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("VolatileRegionNumberLimit",  nullptr);
        create_prop("VolatileRegionSizeLimitMiB",  nullptr);
        create_prop("VolatileRegionSizeMaxMiB",  nullptr);
        create_prop("VolatileSizeMiB",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Memory.v1_5_0");
        set_desc("This is the schema definition for definition of a Memory and its configuration.");
    }

    virtual ~_pMemory()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("Metrics");
        add_navigation_refer_props("Assembly");
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["Chassis"] = nullptr;
    }

    void prepare_OemLenovo()
    {
    }

    virtual void set_actions_obj()
    {
         create_prop( "Actions",   std::make_shared<bson::BSONObj>(BSON("Actions" << BSON(
                "#Memory.SetPassphrase"
                << BSON("target" << (get_base_odata_id() + "/Actions/Memory.SetPassphrase")
                << "title" << "SetPassphrase")
                << "#Memory.DisablePassphrase"
                << BSON("target" << (get_base_odata_id() + "/Actions/Memory.DisablePassphrase")
                << "title" << "DisablePassphrase")
                << "#Memory.SecureEraseUnit"
                << BSON("target" << (get_base_odata_id() + "/Actions/Memory.SecureEraseUnit")
                << "title" << "SecureEraseUnit")
                << "#Memory.UnlockUnit"
                << BSON("target" << (get_base_odata_id() + "/Actions/Memory.UnlockUnit")
                << "title" << "UnlockUnit")
                )
                )) );
     }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("AllocationAlignmentMiB", "Primitive Type.", "Edm.Int64");
        add_property_class("AllocationIncrementMiB", "Primitive Type.", "Edm.Int64");
        add_property_class("AllowedSpeedsMHz", "Collection Type.", "Edm.Int64");
        add_property_class("Assembly", "Navigation Type.Entity", "Assembly");
        add_property_class("BaseModuleType", "Enum Type.", "BaseModuleType");
        add_property_class("BusWidthBits", "Primitive Type.", "Edm.Int64");
        add_property_class("CacheSizeMiB", "Primitive Type.", "Edm.Int64");
        add_property_class("CapacityMiB", "Primitive Type.", "Edm.Int64");
        add_property_class("DataWidthBits", "Primitive Type.", "Edm.Int64");
        add_property_class("DeviceID", "Primitive Type.", "Edm.String");
        add_property_class("DeviceLocator", "Primitive Type.", "Edm.String");
        add_property_class("ErrorCorrection", "Enum Type.", "ErrorCorrection");
        add_property_class("FirmwareApiVersion", "Primitive Type.", "Edm.String");
        add_property_class("FirmwareRevision", "Primitive Type.", "Edm.String");
        add_property_class("FunctionClasses", "Collection Type.", "Edm.String");
        add_property_class("IsRankSpareEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("IsSpareDeviceEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("Location", "Complex Type.", "Location");
        add_property_class("LogicalSizeMiB", "Primitive Type.", "Edm.Int64");
        add_property_class("Manufacturer", "Primitive Type.", "Edm.String");
        add_property_class("MaxTDPMilliWatts", "Collection Type.", "Edm.Int64");
        add_property_class("MemoryDeviceType", "Enum Type.", "MemoryDeviceType");
        add_property_class("MemoryLocation", "Complex Type.", "MemoryLocation");
        add_property_class("MemoryMedia", "Collection Type.", "MemoryMedia");
        add_property_class("MemorySubsystemControllerManufacturerID", "Primitive Type.", "Edm.String");
        add_property_class("MemorySubsystemControllerProductID", "Primitive Type.", "Edm.String");
        add_property_class("MemoryType", "Enum Type.", "MemoryType");
        add_property_class("Metrics", "Navigation Type.Entity", "MemoryMetrics");
        add_property_class("ModuleManufacturerID", "Primitive Type.", "Edm.String");
        add_property_class("ModuleProductID", "Primitive Type.", "Edm.String");
        add_property_class("NonVolatileSizeMiB", "Primitive Type.", "Edm.Int64");
        add_property_class("OperatingMemoryModes", "Collection Type.", "OperatingMemoryModes");
        add_property_class("OperatingSpeedMhz", "Primitive Type.", "Edm.Int64");
        add_property_class("PartNumber", "Primitive Type.", "Edm.String");
        add_property_class("PersistentRegionNumberLimit", "Primitive Type.", "Edm.Int64");
        add_property_class("PersistentRegionSizeLimitMiB", "Primitive Type.", "Edm.Int64");
        add_property_class("PersistentRegionSizeMaxMiB", "Primitive Type.", "Edm.Int64");
        add_property_class("PowerManagementPolicy", "Complex Type.", "PowerManagementPolicy");
        add_property_class("RankCount", "Primitive Type.", "Edm.Int64");
        add_property_class("Regions", "Collection Type.", "RegionSet");
        add_property_class("SecurityCapabilities", "Complex Type.", "SecurityCapabilities");
        add_property_class("SerialNumber", "Primitive Type.", "Edm.String");
        add_property_class("SpareDeviceCount", "Primitive Type.", "Edm.Int64");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("SubsystemDeviceID", "Primitive Type.", "Edm.String");
        add_property_class("SubsystemVendorID", "Primitive Type.", "Edm.String");
        add_property_class("VendorID", "Primitive Type.", "Edm.String");
        add_property_class("VolatileRegionNumberLimit", "Primitive Type.", "Edm.Int64");
        add_property_class("VolatileRegionSizeLimitMiB", "Primitive Type.", "Edm.Int64");
        add_property_class("VolatileRegionSizeMaxMiB", "Primitive Type.", "Edm.Int64");
        add_property_class("VolatileSizeMiB", "Primitive Type.", "Edm.Int64");
    }

    void prep_prop_attrs()
    {
        auto IsRankSpareEnabled_attr = std::make_shared<prop_attribute>();
        IsRankSpareEnabled_attr->prop_name = "IsRankSpareEnabled";
        IsRankSpareEnabled_attr->read_only = true;
        add_property_attr("IsRankSpareEnabled", IsRankSpareEnabled_attr);

        auto IsSpareDeviceEnabled_attr = std::make_shared<prop_attribute>();
        IsSpareDeviceEnabled_attr->prop_name = "IsSpareDeviceEnabled";
        IsSpareDeviceEnabled_attr->read_only = true;
        add_property_attr("IsSpareDeviceEnabled", IsSpareDeviceEnabled_attr);

        auto OperatingMemoryModes_attr = std::make_shared<prop_attribute>();
        OperatingMemoryModes_attr->prop_name = "OperatingMemoryModes";
        OperatingMemoryModes_attr->read_only = true;
        OperatingMemoryModes_attr->add_enum("Volatile");
        OperatingMemoryModes_attr->add_enum("PMEM");
        OperatingMemoryModes_attr->add_enum("Block");
        add_property_attr("OperatingMemoryModes", OperatingMemoryModes_attr);

        auto PersistentRegionSizeLimitMiB_attr = std::make_shared<prop_attribute>();
        PersistentRegionSizeLimitMiB_attr->prop_name = "PersistentRegionSizeLimitMiB";
        PersistentRegionSizeLimitMiB_attr->read_only = true;
        add_property_attr("PersistentRegionSizeLimitMiB", PersistentRegionSizeLimitMiB_attr);

        auto VolatileRegionSizeLimitMiB_attr = std::make_shared<prop_attribute>();
        VolatileRegionSizeLimitMiB_attr->prop_name = "VolatileRegionSizeLimitMiB";
        VolatileRegionSizeLimitMiB_attr->read_only = true;
        add_property_attr("VolatileRegionSizeLimitMiB", VolatileRegionSizeLimitMiB_attr);

        auto ErrorCorrection_attr = std::make_shared<prop_attribute>();
        ErrorCorrection_attr->prop_name = "ErrorCorrection";
        ErrorCorrection_attr->read_only = true;
        ErrorCorrection_attr->add_enum("NoECC");
        ErrorCorrection_attr->add_enum("SingleBitECC");
        ErrorCorrection_attr->add_enum("MultiBitECC");
        ErrorCorrection_attr->add_enum("AddressParity");
        add_property_attr("ErrorCorrection", ErrorCorrection_attr);

        auto DeviceLocator_attr = std::make_shared<prop_attribute>();
        DeviceLocator_attr->prop_name = "DeviceLocator";
        DeviceLocator_attr->read_only = true;
        add_property_attr("DeviceLocator", DeviceLocator_attr);

        auto PartNumber_attr = std::make_shared<prop_attribute>();
        PartNumber_attr->prop_name = "PartNumber";
        PartNumber_attr->read_only = true;
        add_property_attr("PartNumber", PartNumber_attr);

        auto BaseModuleType_attr = std::make_shared<prop_attribute>();
        BaseModuleType_attr->prop_name = "BaseModuleType";
        BaseModuleType_attr->read_only = true;
        BaseModuleType_attr->add_enum("RDIMM");
        BaseModuleType_attr->add_enum("UDIMM");
        BaseModuleType_attr->add_enum("SO_DIMM");
        BaseModuleType_attr->add_enum("LRDIMM");
        BaseModuleType_attr->add_enum("Mini_RDIMM");
        BaseModuleType_attr->add_enum("Mini_UDIMM");
        BaseModuleType_attr->add_enum("SO_RDIMM_72b");
        BaseModuleType_attr->add_enum("SO_UDIMM_72b");
        BaseModuleType_attr->add_enum("SO_DIMM_16b");
        BaseModuleType_attr->add_enum("SO_DIMM_32b");
        add_property_attr("BaseModuleType", BaseModuleType_attr);

        auto VendorID_attr = std::make_shared<prop_attribute>();
        VendorID_attr->prop_name = "VendorID";
        VendorID_attr->read_only = true;
        add_property_attr("VendorID", VendorID_attr);

        auto Manufacturer_attr = std::make_shared<prop_attribute>();
        Manufacturer_attr->prop_name = "Manufacturer";
        Manufacturer_attr->read_only = true;
        add_property_attr("Manufacturer", Manufacturer_attr);

        auto DeviceID_attr = std::make_shared<prop_attribute>();
        DeviceID_attr->prop_name = "DeviceID";
        DeviceID_attr->read_only = true;
        add_property_attr("DeviceID", DeviceID_attr);

        auto DataWidthBits_attr = std::make_shared<prop_attribute>();
        DataWidthBits_attr->prop_name = "DataWidthBits";
        DataWidthBits_attr->read_only = true;
        add_property_attr("DataWidthBits", DataWidthBits_attr);

        auto OperatingSpeedMhz_attr = std::make_shared<prop_attribute>();
        OperatingSpeedMhz_attr->prop_name = "OperatingSpeedMhz";
        OperatingSpeedMhz_attr->read_only = true;
        add_property_attr("OperatingSpeedMhz", OperatingSpeedMhz_attr);

        auto CapacityMiB_attr = std::make_shared<prop_attribute>();
        CapacityMiB_attr->prop_name = "CapacityMiB";
        CapacityMiB_attr->read_only = true;
        add_property_attr("CapacityMiB", CapacityMiB_attr);

        auto RankCount_attr = std::make_shared<prop_attribute>();
        RankCount_attr->prop_name = "RankCount";
        RankCount_attr->read_only = true;
        add_property_attr("RankCount", RankCount_attr);

        auto Metrics_attr = std::make_shared<prop_attribute>();
        Metrics_attr->prop_name = "Metrics";
        Metrics_attr->read_only = true;
        add_property_attr("Metrics", Metrics_attr);

        auto MemoryMedia_attr = std::make_shared<prop_attribute>();
        MemoryMedia_attr->prop_name = "MemoryMedia";
        MemoryMedia_attr->read_only = true;
        MemoryMedia_attr->add_enum("DRAM");
        MemoryMedia_attr->add_enum("NAND");
        MemoryMedia_attr->add_enum("Proprietary");
        add_property_attr("MemoryMedia", MemoryMedia_attr);

        auto MemoryType_attr = std::make_shared<prop_attribute>();
        MemoryType_attr->prop_name = "MemoryType";
        MemoryType_attr->read_only = true;
        MemoryType_attr->add_enum("DRAM");
        MemoryType_attr->add_enum("NVDIMM_N");
        MemoryType_attr->add_enum("NVDIMM_F");
        MemoryType_attr->add_enum("NVDIMM_P");
        add_property_attr("MemoryType", MemoryType_attr);

        auto SerialNumber_attr = std::make_shared<prop_attribute>();
        SerialNumber_attr->prop_name = "SerialNumber";
        SerialNumber_attr->read_only = true;
        add_property_attr("SerialNumber", SerialNumber_attr);

        auto FirmwareRevision_attr = std::make_shared<prop_attribute>();
        FirmwareRevision_attr->prop_name = "FirmwareRevision";
        FirmwareRevision_attr->read_only = true;
        add_property_attr("FirmwareRevision", FirmwareRevision_attr);

        auto FirmwareApiVersion_attr = std::make_shared<prop_attribute>();
        FirmwareApiVersion_attr->prop_name = "FirmwareApiVersion";
        FirmwareApiVersion_attr->read_only = true;
        add_property_attr("FirmwareApiVersion", FirmwareApiVersion_attr);

        auto FunctionClasses_attr = std::make_shared<prop_attribute>();
        FunctionClasses_attr->prop_name = "FunctionClasses";
        FunctionClasses_attr->read_only = true;
        add_property_attr("FunctionClasses", FunctionClasses_attr);

        auto SubsystemDeviceID_attr = std::make_shared<prop_attribute>();
        SubsystemDeviceID_attr->prop_name = "SubsystemDeviceID";
        SubsystemDeviceID_attr->read_only = true;
        add_property_attr("SubsystemDeviceID", SubsystemDeviceID_attr);

        auto SpareDeviceCount_attr = std::make_shared<prop_attribute>();
        SpareDeviceCount_attr->prop_name = "SpareDeviceCount";
        SpareDeviceCount_attr->read_only = true;
        add_property_attr("SpareDeviceCount", SpareDeviceCount_attr);

        auto AllowedSpeedsMHz_attr = std::make_shared<prop_attribute>();
        AllowedSpeedsMHz_attr->prop_name = "AllowedSpeedsMHz";
        AllowedSpeedsMHz_attr->read_only = true;
        add_property_attr("AllowedSpeedsMHz", AllowedSpeedsMHz_attr);

        auto MaxTDPMilliWatts_attr = std::make_shared<prop_attribute>();
        MaxTDPMilliWatts_attr->prop_name = "MaxTDPMilliWatts";
        MaxTDPMilliWatts_attr->read_only = true;
        add_property_attr("MaxTDPMilliWatts", MaxTDPMilliWatts_attr);

        auto BusWidthBits_attr = std::make_shared<prop_attribute>();
        BusWidthBits_attr->prop_name = "BusWidthBits";
        BusWidthBits_attr->read_only = true;
        add_property_attr("BusWidthBits", BusWidthBits_attr);

        auto MemoryDeviceType_attr = std::make_shared<prop_attribute>();
        MemoryDeviceType_attr->prop_name = "MemoryDeviceType";
        MemoryDeviceType_attr->read_only = true;
        MemoryDeviceType_attr->add_enum("DDR");
        MemoryDeviceType_attr->add_enum("DDR2");
        MemoryDeviceType_attr->add_enum("DDR3");
        MemoryDeviceType_attr->add_enum("DDR4");
        MemoryDeviceType_attr->add_enum("DDR4_SDRAM");
        MemoryDeviceType_attr->add_enum("DDR4E_SDRAM");
        MemoryDeviceType_attr->add_enum("LPDDR4_SDRAM");
        MemoryDeviceType_attr->add_enum("DDR3_SDRAM");
        MemoryDeviceType_attr->add_enum("LPDDR3_SDRAM");
        MemoryDeviceType_attr->add_enum("DDR2_SDRAM");
        MemoryDeviceType_attr->add_enum("DDR2_SDRAM_FB_DIMM");
        MemoryDeviceType_attr->add_enum("DDR2_SDRAM_FB_DIMM_PROBE");
        MemoryDeviceType_attr->add_enum("DDR_SGRAM");
        MemoryDeviceType_attr->add_enum("DDR_SDRAM");
        MemoryDeviceType_attr->add_enum("ROM");
        MemoryDeviceType_attr->add_enum("SDRAM");
        MemoryDeviceType_attr->add_enum("EDO");
        MemoryDeviceType_attr->add_enum("FastPageMode");
        MemoryDeviceType_attr->add_enum("PipelinedNibble");
        MemoryDeviceType_attr->add_enum("Logical");
        add_property_attr("MemoryDeviceType", MemoryDeviceType_attr);

        auto SubsystemVendorID_attr = std::make_shared<prop_attribute>();
        SubsystemVendorID_attr->prop_name = "SubsystemVendorID";
        SubsystemVendorID_attr->read_only = true;
        add_property_attr("SubsystemVendorID", SubsystemVendorID_attr);

        auto AllocationAlignmentMiB_attr = std::make_shared<prop_attribute>();
        AllocationAlignmentMiB_attr->prop_name = "AllocationAlignmentMiB";
        AllocationAlignmentMiB_attr->read_only = true;
        add_property_attr("AllocationAlignmentMiB", AllocationAlignmentMiB_attr);

        auto AllocationIncrementMiB_attr = std::make_shared<prop_attribute>();
        AllocationIncrementMiB_attr->prop_name = "AllocationIncrementMiB";
        AllocationIncrementMiB_attr->read_only = true;
        add_property_attr("AllocationIncrementMiB", AllocationIncrementMiB_attr);

        auto VolatileRegionSizeMaxMiB_attr = std::make_shared<prop_attribute>();
        VolatileRegionSizeMaxMiB_attr->prop_name = "VolatileRegionSizeMaxMiB";
        VolatileRegionSizeMaxMiB_attr->read_only = true;
        add_property_attr("VolatileRegionSizeMaxMiB", VolatileRegionSizeMaxMiB_attr);

        auto PersistentRegionNumberLimit_attr = std::make_shared<prop_attribute>();
        PersistentRegionNumberLimit_attr->prop_name = "PersistentRegionNumberLimit";
        PersistentRegionNumberLimit_attr->read_only = true;
        add_property_attr("PersistentRegionNumberLimit", PersistentRegionNumberLimit_attr);

        auto PersistentRegionSizeMaxMiB_attr = std::make_shared<prop_attribute>();
        PersistentRegionSizeMaxMiB_attr->prop_name = "PersistentRegionSizeMaxMiB";
        PersistentRegionSizeMaxMiB_attr->read_only = true;
        add_property_attr("PersistentRegionSizeMaxMiB", PersistentRegionSizeMaxMiB_attr);

        auto VolatileRegionNumberLimit_attr = std::make_shared<prop_attribute>();
        VolatileRegionNumberLimit_attr->prop_name = "VolatileRegionNumberLimit";
        VolatileRegionNumberLimit_attr->read_only = true;
        add_property_attr("VolatileRegionNumberLimit", VolatileRegionNumberLimit_attr);

        auto MemorySubsystemControllerProductID_attr = std::make_shared<prop_attribute>();
        MemorySubsystemControllerProductID_attr->prop_name = "MemorySubsystemControllerProductID";
        MemorySubsystemControllerProductID_attr->read_only = true;
        add_property_attr("MemorySubsystemControllerProductID", MemorySubsystemControllerProductID_attr);

        auto MemorySubsystemControllerManufacturerID_attr = std::make_shared<prop_attribute>();
        MemorySubsystemControllerManufacturerID_attr->prop_name = "MemorySubsystemControllerManufacturerID";
        MemorySubsystemControllerManufacturerID_attr->read_only = true;
        add_property_attr("MemorySubsystemControllerManufacturerID", MemorySubsystemControllerManufacturerID_attr);

        auto ModuleProductID_attr = std::make_shared<prop_attribute>();
        ModuleProductID_attr->prop_name = "ModuleProductID";
        ModuleProductID_attr->read_only = true;
        add_property_attr("ModuleProductID", ModuleProductID_attr);

        auto ModuleManufacturerID_attr = std::make_shared<prop_attribute>();
        ModuleManufacturerID_attr->prop_name = "ModuleManufacturerID";
        ModuleManufacturerID_attr->read_only = true;
        add_property_attr("ModuleManufacturerID", ModuleManufacturerID_attr);

        auto Assembly_attr = std::make_shared<prop_attribute>();
        Assembly_attr->prop_name = "Assembly";
        Assembly_attr->read_only = true;
        add_property_attr("Assembly", Assembly_attr);

        auto CacheSizeMiB_attr = std::make_shared<prop_attribute>();
        CacheSizeMiB_attr->prop_name = "CacheSizeMiB";
        CacheSizeMiB_attr->read_only = true;
        add_property_attr("CacheSizeMiB", CacheSizeMiB_attr);

        auto NonVolatileSizeMiB_attr = std::make_shared<prop_attribute>();
        NonVolatileSizeMiB_attr->prop_name = "NonVolatileSizeMiB";
        NonVolatileSizeMiB_attr->read_only = true;
        add_property_attr("NonVolatileSizeMiB", NonVolatileSizeMiB_attr);

        auto LogicalSizeMiB_attr = std::make_shared<prop_attribute>();
        LogicalSizeMiB_attr->prop_name = "LogicalSizeMiB";
        LogicalSizeMiB_attr->read_only = true;
        add_property_attr("LogicalSizeMiB", LogicalSizeMiB_attr);

        auto VolatileSizeMiB_attr = std::make_shared<prop_attribute>();
        VolatileSizeMiB_attr->prop_name = "VolatileSizeMiB";
        VolatileSizeMiB_attr->read_only = true;
        add_property_attr("VolatileSizeMiB", VolatileSizeMiB_attr);

     }

};

}}

