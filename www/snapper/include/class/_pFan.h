//---------------------------------------------------------------------
// <copyright file="_pFan.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pFan : public ReferenceableMemberProvider
{
public:
    _pFan() : ReferenceableMemberProvider("Fan")    
    {
        enum ReadingUnits 
        {
            ReadingUnits_RPM,
            ReadingUnits_Percent,
        };

        create_prop("Oem",  nullptr);
        create_prop("MemberId",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Assembly",  nullptr);
        create_prop("HotPluggable",  nullptr);
        create_prop("IndicatorLED",  nullptr);
        create_prop("Location",  nullptr);
        create_prop("LowerThresholdCritical",  nullptr);
        create_prop("LowerThresholdFatal",  nullptr);
        create_prop("LowerThresholdNonCritical",  nullptr);
        create_prop("Manufacturer",  nullptr);
        create_prop("MaxReadingRange",  nullptr);
        create_prop("MinReadingRange",  nullptr);
        create_prop("Model",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("PartNumber",  nullptr);
        create_prop("PhysicalContext",  nullptr);
        create_prop("Reading",  nullptr);
        create_prop("ReadingUnits",  nullptr);
        create_prop("Redundancy",  nullptr);
        create_prop("Redundancy@odata.count",  nullptr);
        create_prop("Redundancy@odata.navigationLink",  nullptr);
        create_prop("RelatedItem",  nullptr);
        create_prop("RelatedItem@odata.count",  nullptr);
        create_prop("RelatedItem@odata.navigationLink",  nullptr);
        create_prop("SerialNumber",  nullptr);
        create_prop("SparePartNumber",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("UpperThresholdCritical",  nullptr);
        create_prop("UpperThresholdFatal",  nullptr);
        create_prop("UpperThresholdNonCritical",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Thermal.v1_4_0");
    }

    virtual ~_pFan()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_arr_props("Redundancy");
        add_navigation_arr_props("RelatedItem");
        add_navigation_contained_props("Assembly");
    }

        
    void prepare_Links()
    {
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "FanActions");
        add_property_class("Assembly", "Navigation Type.Entity", "Assembly");
        add_property_class("FanName", "Primitive Type.", "Edm.String");
        add_property_class("HotPluggable", "Primitive Type.", "Edm.Boolean");
        add_property_class("IndicatorLED", "Enum Type.", "IndicatorLED");
        add_property_class("Location", "Complex Type.", "Location");
        add_property_class("LowerThresholdCritical", "Primitive Type.", "Edm.Int64");
        add_property_class("LowerThresholdFatal", "Primitive Type.", "Edm.Int64");
        add_property_class("LowerThresholdNonCritical", "Primitive Type.", "Edm.Int64");
        add_property_class("Manufacturer", "Primitive Type.", "Edm.String");
        add_property_class("MaxReadingRange", "Primitive Type.", "Edm.Int64");
        add_property_class("MinReadingRange", "Primitive Type.", "Edm.Int64");
        add_property_class("Model", "Primitive Type.", "Edm.String");
        add_property_class("Name", "Primitive Type.", "Edm.String");
        add_property_class("PartNumber", "Primitive Type.", "Edm.String");
        add_property_class("PhysicalContext", "Enum Type.", "PhysicalContext");
        add_property_class("Reading", "Primitive Type.", "Edm.Int64");
        add_property_class("ReadingUnits", "Enum Type.", "ReadingUnits");
        add_property_class("Redundancy", "Navigation Type.Collection", "Redundancy");
        add_property_class("RelatedItem", "Navigation Type.Collection", "Item");
        add_property_class("SerialNumber", "Primitive Type.", "Edm.String");
        add_property_class("SparePartNumber", "Primitive Type.", "Edm.String");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("UpperThresholdCritical", "Primitive Type.", "Edm.Int64");
        add_property_class("UpperThresholdFatal", "Primitive Type.", "Edm.Int64");
        add_property_class("UpperThresholdNonCritical", "Primitive Type.", "Edm.Int64");
    }

    void prep_prop_attrs()
    {
        auto RelatedItem_attr = std::make_shared<prop_attribute>();
        RelatedItem_attr->prop_name = "RelatedItem";
        RelatedItem_attr->read_only = true;
        add_property_attr("RelatedItem", RelatedItem_attr);

        auto MaxReadingRange_attr = std::make_shared<prop_attribute>();
        MaxReadingRange_attr->prop_name = "MaxReadingRange";
        MaxReadingRange_attr->read_only = true;
        add_property_attr("MaxReadingRange", MaxReadingRange_attr);

        auto MinReadingRange_attr = std::make_shared<prop_attribute>();
        MinReadingRange_attr->prop_name = "MinReadingRange";
        MinReadingRange_attr->read_only = true;
        add_property_attr("MinReadingRange", MinReadingRange_attr);

        auto FanName_attr = std::make_shared<prop_attribute>();
        FanName_attr->prop_name = "FanName";
        FanName_attr->read_only = true;
        add_property_attr("FanName", FanName_attr);

        auto PhysicalContext_attr = std::make_shared<prop_attribute>();
        PhysicalContext_attr->prop_name = "PhysicalContext";
        PhysicalContext_attr->read_only = true;
        PhysicalContext_attr->add_enum("Room");
        PhysicalContext_attr->add_enum("Intake");
        PhysicalContext_attr->add_enum("Exhaust");
        PhysicalContext_attr->add_enum("LiquidInlet");
        PhysicalContext_attr->add_enum("LiquidOutlet");
        PhysicalContext_attr->add_enum("Front");
        PhysicalContext_attr->add_enum("Back");
        PhysicalContext_attr->add_enum("Upper");
        PhysicalContext_attr->add_enum("Lower");
        PhysicalContext_attr->add_enum("CPU");
        PhysicalContext_attr->add_enum("GPU");
        PhysicalContext_attr->add_enum("ASIC");
        PhysicalContext_attr->add_enum("Backplane");
        PhysicalContext_attr->add_enum("SystemBoard");
        PhysicalContext_attr->add_enum("PowerSupply");
        PhysicalContext_attr->add_enum("VoltageRegulator");
        PhysicalContext_attr->add_enum("StorageDevice");
        PhysicalContext_attr->add_enum("NetworkingDevice");
        PhysicalContext_attr->add_enum("ComputeBay");
        PhysicalContext_attr->add_enum("StorageBay");
        PhysicalContext_attr->add_enum("NetworkBay");
        PhysicalContext_attr->add_enum("ExpansionBay");
        PhysicalContext_attr->add_enum("PowerSupplyBay");
        PhysicalContext_attr->add_enum("Memory");
        PhysicalContext_attr->add_enum("Chassis");
        PhysicalContext_attr->add_enum("Fan");
        add_property_attr("PhysicalContext", PhysicalContext_attr);

        auto LowerThresholdCritical_attr = std::make_shared<prop_attribute>();
        LowerThresholdCritical_attr->prop_name = "LowerThresholdCritical";
        LowerThresholdCritical_attr->read_only = true;
        add_property_attr("LowerThresholdCritical", LowerThresholdCritical_attr);

        auto Reading_attr = std::make_shared<prop_attribute>();
        Reading_attr->prop_name = "Reading";
        Reading_attr->read_only = true;
        add_property_attr("Reading", Reading_attr);

        auto UpperThresholdNonCritical_attr = std::make_shared<prop_attribute>();
        UpperThresholdNonCritical_attr->prop_name = "UpperThresholdNonCritical";
        UpperThresholdNonCritical_attr->read_only = true;
        add_property_attr("UpperThresholdNonCritical", UpperThresholdNonCritical_attr);

        auto UpperThresholdFatal_attr = std::make_shared<prop_attribute>();
        UpperThresholdFatal_attr->prop_name = "UpperThresholdFatal";
        UpperThresholdFatal_attr->read_only = true;
        add_property_attr("UpperThresholdFatal", UpperThresholdFatal_attr);

        auto UpperThresholdCritical_attr = std::make_shared<prop_attribute>();
        UpperThresholdCritical_attr->prop_name = "UpperThresholdCritical";
        UpperThresholdCritical_attr->read_only = true;
        add_property_attr("UpperThresholdCritical", UpperThresholdCritical_attr);

        auto LowerThresholdNonCritical_attr = std::make_shared<prop_attribute>();
        LowerThresholdNonCritical_attr->prop_name = "LowerThresholdNonCritical";
        LowerThresholdNonCritical_attr->read_only = true;
        add_property_attr("LowerThresholdNonCritical", LowerThresholdNonCritical_attr);

        auto LowerThresholdFatal_attr = std::make_shared<prop_attribute>();
        LowerThresholdFatal_attr->prop_name = "LowerThresholdFatal";
        LowerThresholdFatal_attr->read_only = true;
        add_property_attr("LowerThresholdFatal", LowerThresholdFatal_attr);

        auto ReadingUnits_attr = std::make_shared<prop_attribute>();
        ReadingUnits_attr->prop_name = "ReadingUnits";
        ReadingUnits_attr->read_only = true;
        ReadingUnits_attr->add_enum("RPM");
        ReadingUnits_attr->add_enum("Percent");
        add_property_attr("ReadingUnits", ReadingUnits_attr);

        auto Name_attr = std::make_shared<prop_attribute>();
        Name_attr->prop_name = "Name";
        Name_attr->read_only = true;
        add_property_attr("Name", Name_attr);

        auto IndicatorLED_attr = std::make_shared<prop_attribute>();
        IndicatorLED_attr->prop_name = "IndicatorLED";
        IndicatorLED_attr->read_only = false;
        IndicatorLED_attr->add_enum("Lit");
        IndicatorLED_attr->add_enum("Blinking");
        IndicatorLED_attr->add_enum("Off");
        add_property_attr("IndicatorLED", IndicatorLED_attr);

        auto PartNumber_attr = std::make_shared<prop_attribute>();
        PartNumber_attr->prop_name = "PartNumber";
        PartNumber_attr->read_only = true;
        add_property_attr("PartNumber", PartNumber_attr);

        auto SerialNumber_attr = std::make_shared<prop_attribute>();
        SerialNumber_attr->prop_name = "SerialNumber";
        SerialNumber_attr->read_only = true;
        add_property_attr("SerialNumber", SerialNumber_attr);

        auto SparePartNumber_attr = std::make_shared<prop_attribute>();
        SparePartNumber_attr->prop_name = "SparePartNumber";
        SparePartNumber_attr->read_only = true;
        add_property_attr("SparePartNumber", SparePartNumber_attr);

        auto Model_attr = std::make_shared<prop_attribute>();
        Model_attr->prop_name = "Model";
        Model_attr->read_only = true;
        add_property_attr("Model", Model_attr);

        auto Manufacturer_attr = std::make_shared<prop_attribute>();
        Manufacturer_attr->prop_name = "Manufacturer";
        Manufacturer_attr->read_only = true;
        add_property_attr("Manufacturer", Manufacturer_attr);

        auto Assembly_attr = std::make_shared<prop_attribute>();
        Assembly_attr->prop_name = "Assembly";
        Assembly_attr->read_only = true;
        add_property_attr("Assembly", Assembly_attr);

        auto HotPluggable_attr = std::make_shared<prop_attribute>();
        HotPluggable_attr->prop_name = "HotPluggable";
        HotPluggable_attr->read_only = true;
        add_property_attr("HotPluggable", HotPluggable_attr);

     }

};

}}

