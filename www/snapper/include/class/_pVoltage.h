//---------------------------------------------------------------------
// <copyright file="_pVoltage.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pVoltage : public ReferenceableMemberProvider
{
public:
    _pVoltage() : ReferenceableMemberProvider("Voltage")    
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

        create_prop("Oem",  nullptr);
        create_prop("MemberId",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("LowerThresholdCritical",  nullptr);
        create_prop("LowerThresholdFatal",  nullptr);
        create_prop("LowerThresholdNonCritical",  nullptr);
        create_prop("MaxReadingRange",  nullptr);
        create_prop("MinReadingRange",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("PhysicalContext",  nullptr);
        create_prop("ReadingVolts",  nullptr);
        create_prop("RelatedItem",  nullptr);
        create_prop("RelatedItem@odata.count",  nullptr);
        create_prop("RelatedItem@odata.navigationLink",  nullptr);
        create_prop("SensorNumber",  nullptr);
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
        
        set_namespace("Power.v1_3_0");
    }

    virtual ~_pVoltage()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_arr_props("RelatedItem");
    }

        
    void prepare_Links()
    {
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "VoltageActions");
        add_property_class("LowerThresholdCritical", "Primitive Type.", "Edm.Decimal");
        add_property_class("LowerThresholdFatal", "Primitive Type.", "Edm.Decimal");
        add_property_class("LowerThresholdNonCritical", "Primitive Type.", "Edm.Decimal");
        add_property_class("MaxReadingRange", "Primitive Type.", "Edm.Decimal");
        add_property_class("MinReadingRange", "Primitive Type.", "Edm.Decimal");
        add_property_class("Name", "Primitive Type.", "Edm.String");
        add_property_class("PhysicalContext", "Enum Type.", "PhysicalContext");
        add_property_class("ReadingVolts", "Primitive Type.", "Edm.Decimal");
        add_property_class("RelatedItem", "Navigation Type.Collection", "Item");
        add_property_class("SensorNumber", "Primitive Type.", "Edm.Int64");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("UpperThresholdCritical", "Primitive Type.", "Edm.Decimal");
        add_property_class("UpperThresholdFatal", "Primitive Type.", "Edm.Decimal");
        add_property_class("UpperThresholdNonCritical", "Primitive Type.", "Edm.Decimal");
    }

    void prep_prop_attrs()
    {
        auto RelatedItem_attr = std::make_shared<prop_attribute>();
        RelatedItem_attr->prop_name = "RelatedItem";
        RelatedItem_attr->read_only = true;
        add_property_attr("RelatedItem", RelatedItem_attr);

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

        auto MaxReadingRange_attr = std::make_shared<prop_attribute>();
        MaxReadingRange_attr->prop_name = "MaxReadingRange";
        MaxReadingRange_attr->read_only = true;
        add_property_attr("MaxReadingRange", MaxReadingRange_attr);

        auto MinReadingRange_attr = std::make_shared<prop_attribute>();
        MinReadingRange_attr->prop_name = "MinReadingRange";
        MinReadingRange_attr->read_only = true;
        add_property_attr("MinReadingRange", MinReadingRange_attr);

        auto Name_attr = std::make_shared<prop_attribute>();
        Name_attr->prop_name = "Name";
        Name_attr->read_only = true;
        add_property_attr("Name", Name_attr);

        auto SensorNumber_attr = std::make_shared<prop_attribute>();
        SensorNumber_attr->prop_name = "SensorNumber";
        SensorNumber_attr->read_only = true;
        add_property_attr("SensorNumber", SensorNumber_attr);

        auto LowerThresholdCritical_attr = std::make_shared<prop_attribute>();
        LowerThresholdCritical_attr->prop_name = "LowerThresholdCritical";
        LowerThresholdCritical_attr->read_only = true;
        add_property_attr("LowerThresholdCritical", LowerThresholdCritical_attr);

        auto UpperThresholdNonCritical_attr = std::make_shared<prop_attribute>();
        UpperThresholdNonCritical_attr->prop_name = "UpperThresholdNonCritical";
        UpperThresholdNonCritical_attr->read_only = true;
        add_property_attr("UpperThresholdNonCritical", UpperThresholdNonCritical_attr);

        auto UpperThresholdFatal_attr = std::make_shared<prop_attribute>();
        UpperThresholdFatal_attr->prop_name = "UpperThresholdFatal";
        UpperThresholdFatal_attr->read_only = true;
        add_property_attr("UpperThresholdFatal", UpperThresholdFatal_attr);

        auto ReadingVolts_attr = std::make_shared<prop_attribute>();
        ReadingVolts_attr->prop_name = "ReadingVolts";
        ReadingVolts_attr->read_only = true;
        add_property_attr("ReadingVolts", ReadingVolts_attr);

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

     }

};

}}

