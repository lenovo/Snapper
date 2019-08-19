//---------------------------------------------------------------------
// <copyright file="_pPowerSupply.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pPowerSupply : public ReferenceableMemberProvider
{
public:
    _pPowerSupply() : ReferenceableMemberProvider("PowerSupply")    
    {
        enum LineInputVoltageType 
        {
            LineInputVoltageType_Unknown,
            LineInputVoltageType_DCNeg48V,
            LineInputVoltageType_DC380V,
            LineInputVoltageType_AC120V,
            LineInputVoltageType_AC240V,
            LineInputVoltageType_AC277V,
            LineInputVoltageType_ACandDCWideRange,
            LineInputVoltageType_ACWideRange,
            LineInputVoltageType_DC240V,
        };

        enum PowerSupplyType 
        {
            PowerSupplyType_Unknown,
            PowerSupplyType_AC,
            PowerSupplyType_DC,
            PowerSupplyType_ACorDC,
        };

        enum PowerLimitException 
        {
            PowerLimitException_NoAction,
            PowerLimitException_HardPowerOff,
            PowerLimitException_LogEventOnly,
            PowerLimitException_Oem,
        };

        enum InputType 
        {
            InputType_AC,
            InputType_DC,
        };

        create_prop("Oem",  nullptr);
        create_prop("MemberId",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Assembly",  nullptr);
        create_prop("EfficiencyPercent",  nullptr);
        create_prop("FirmwareVersion",  nullptr);
        create_prop("HotPluggable",  nullptr);
        create_prop("IndicatorLED",  nullptr);
        create_prop("InputRanges",  nullptr);
        create_prop("LastPowerOutputWatts",  nullptr);
        create_prop("LineInputVoltage",  nullptr);
        create_prop("LineInputVoltageType",  nullptr);
        create_prop("Location",  nullptr);
        create_prop("Manufacturer",  nullptr);
        create_prop("Model",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("PartNumber",  nullptr);
        create_prop("PowerCapacityWatts",  nullptr);
        create_prop("PowerInputWatts",  nullptr);
        create_prop("PowerOutputWatts",  nullptr);
        create_prop("PowerSupplyType",  nullptr);
        create_prop("Redundancy",  nullptr);
        create_prop("Redundancy@odata.count",  nullptr);
        create_prop("Redundancy@odata.navigationLink",  nullptr);
        create_prop("RelatedItem",  nullptr);
        create_prop("RelatedItem@odata.count",  nullptr);
        create_prop("RelatedItem@odata.navigationLink",  nullptr);
        create_prop("SerialNumber",  nullptr);
        create_prop("SparePartNumber",  nullptr);
        create_prop("Status",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Power.v1_5_0");
        set_desc("Details of a power supplies associated with this system or device.");
    }

    virtual ~_pPowerSupply()    
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
        add_property_class("Actions", "Complex Type.", "PowerSupplyActions");
        add_property_class("Assembly", "Navigation Type.Entity", "Assembly");
        add_property_class("EfficiencyPercent", "Primitive Type.", "Edm.Decimal");
        add_property_class("FirmwareVersion", "Primitive Type.", "Edm.String");
        add_property_class("HotPluggable", "Primitive Type.", "Edm.Boolean");
        add_property_class("IndicatorLED", "Enum Type.", "IndicatorLED");
        add_property_class("InputRanges", "Collection Type.", "InputRange");
        add_property_class("LastPowerOutputWatts", "Primitive Type.", "Edm.Decimal");
        add_property_class("LineInputVoltage", "Primitive Type.", "Edm.Decimal");
        add_property_class("LineInputVoltageType", "Enum Type.", "LineInputVoltageType");
        add_property_class("Location", "Complex Type.", "Location");
        add_property_class("Manufacturer", "Primitive Type.", "Edm.String");
        add_property_class("Model", "Primitive Type.", "Edm.String");
        add_property_class("Name", "Primitive Type.", "Edm.String");
        add_property_class("PartNumber", "Primitive Type.", "Edm.String");
        add_property_class("PowerCapacityWatts", "Primitive Type.", "Edm.Decimal");
        add_property_class("PowerInputWatts", "Primitive Type.", "Edm.Decimal");
        add_property_class("PowerOutputWatts", "Primitive Type.", "Edm.Decimal");
        add_property_class("PowerSupplyType", "Enum Type.", "PowerSupplyType");
        add_property_class("Redundancy", "Navigation Type.Collection", "Redundancy");
        add_property_class("RelatedItem", "Navigation Type.Collection", "Item");
        add_property_class("SerialNumber", "Primitive Type.", "Edm.String");
        add_property_class("SparePartNumber", "Primitive Type.", "Edm.String");
        add_property_class("Status", "Complex Type.", "Status");
    }

    void prep_prop_attrs()
    {
        auto SparePartNumber_attr = std::make_shared<prop_attribute>();
        SparePartNumber_attr->prop_name = "SparePartNumber";
        SparePartNumber_attr->read_only = true;
        add_property_attr("SparePartNumber", SparePartNumber_attr);

        auto Name_attr = std::make_shared<prop_attribute>();
        Name_attr->prop_name = "Name";
        Name_attr->read_only = true;
        add_property_attr("Name", Name_attr);

        auto PartNumber_attr = std::make_shared<prop_attribute>();
        PartNumber_attr->prop_name = "PartNumber";
        PartNumber_attr->read_only = true;
        add_property_attr("PartNumber", PartNumber_attr);

        auto PowerSupplyType_attr = std::make_shared<prop_attribute>();
        PowerSupplyType_attr->prop_name = "PowerSupplyType";
        PowerSupplyType_attr->read_only = true;
        PowerSupplyType_attr->add_enum("Unknown");
        PowerSupplyType_attr->add_enum("AC");
        PowerSupplyType_attr->add_enum("DC");
        PowerSupplyType_attr->add_enum("ACorDC");
        add_property_attr("PowerSupplyType", PowerSupplyType_attr);

        auto LineInputVoltage_attr = std::make_shared<prop_attribute>();
        LineInputVoltage_attr->prop_name = "LineInputVoltage";
        LineInputVoltage_attr->read_only = true;
        add_property_attr("LineInputVoltage", LineInputVoltage_attr);

        auto PowerCapacityWatts_attr = std::make_shared<prop_attribute>();
        PowerCapacityWatts_attr->prop_name = "PowerCapacityWatts";
        PowerCapacityWatts_attr->read_only = true;
        add_property_attr("PowerCapacityWatts", PowerCapacityWatts_attr);

        auto Model_attr = std::make_shared<prop_attribute>();
        Model_attr->prop_name = "Model";
        Model_attr->read_only = true;
        add_property_attr("Model", Model_attr);

        auto LineInputVoltageType_attr = std::make_shared<prop_attribute>();
        LineInputVoltageType_attr->prop_name = "LineInputVoltageType";
        LineInputVoltageType_attr->read_only = true;
        LineInputVoltageType_attr->add_enum("Unknown");
        LineInputVoltageType_attr->add_enum("ACLowLine");
        LineInputVoltageType_attr->add_enum("ACMidLine");
        LineInputVoltageType_attr->add_enum("ACHighLine");
        LineInputVoltageType_attr->add_enum("DCNeg48V");
        LineInputVoltageType_attr->add_enum("DC380V");
        LineInputVoltageType_attr->add_enum("AC120V");
        LineInputVoltageType_attr->add_enum("AC240V");
        LineInputVoltageType_attr->add_enum("AC277V");
        LineInputVoltageType_attr->add_enum("ACandDCWideRange");
        LineInputVoltageType_attr->add_enum("ACWideRange");
        LineInputVoltageType_attr->add_enum("DC240V");
        add_property_attr("LineInputVoltageType", LineInputVoltageType_attr);

        auto FirmwareVersion_attr = std::make_shared<prop_attribute>();
        FirmwareVersion_attr->prop_name = "FirmwareVersion";
        FirmwareVersion_attr->read_only = true;
        add_property_attr("FirmwareVersion", FirmwareVersion_attr);

        auto LastPowerOutputWatts_attr = std::make_shared<prop_attribute>();
        LastPowerOutputWatts_attr->prop_name = "LastPowerOutputWatts";
        LastPowerOutputWatts_attr->read_only = true;
        add_property_attr("LastPowerOutputWatts", LastPowerOutputWatts_attr);

        auto SerialNumber_attr = std::make_shared<prop_attribute>();
        SerialNumber_attr->prop_name = "SerialNumber";
        SerialNumber_attr->read_only = true;
        add_property_attr("SerialNumber", SerialNumber_attr);

        auto Manufacturer_attr = std::make_shared<prop_attribute>();
        Manufacturer_attr->prop_name = "Manufacturer";
        Manufacturer_attr->read_only = true;
        add_property_attr("Manufacturer", Manufacturer_attr);

        auto IndicatorLED_attr = std::make_shared<prop_attribute>();
        IndicatorLED_attr->prop_name = "IndicatorLED";
        IndicatorLED_attr->read_only = false;
        IndicatorLED_attr->add_enum("Lit");
        IndicatorLED_attr->add_enum("Blinking");
        IndicatorLED_attr->add_enum("Off");
        add_property_attr("IndicatorLED", IndicatorLED_attr);

        auto HotPluggable_attr = std::make_shared<prop_attribute>();
        HotPluggable_attr->prop_name = "HotPluggable";
        HotPluggable_attr->read_only = true;
        add_property_attr("HotPluggable", HotPluggable_attr);

        auto EfficiencyPercent_attr = std::make_shared<prop_attribute>();
        EfficiencyPercent_attr->prop_name = "EfficiencyPercent";
        EfficiencyPercent_attr->read_only = true;
        add_property_attr("EfficiencyPercent", EfficiencyPercent_attr);

        auto PowerOutputWatts_attr = std::make_shared<prop_attribute>();
        PowerOutputWatts_attr->prop_name = "PowerOutputWatts";
        PowerOutputWatts_attr->read_only = true;
        add_property_attr("PowerOutputWatts", PowerOutputWatts_attr);

        auto Assembly_attr = std::make_shared<prop_attribute>();
        Assembly_attr->prop_name = "Assembly";
        Assembly_attr->read_only = true;
        add_property_attr("Assembly", Assembly_attr);

        auto PowerInputWatts_attr = std::make_shared<prop_attribute>();
        PowerInputWatts_attr->prop_name = "PowerInputWatts";
        PowerInputWatts_attr->read_only = true;
        add_property_attr("PowerInputWatts", PowerInputWatts_attr);

     }

};

}}

