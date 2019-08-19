//---------------------------------------------------------------------
// <copyright file="_pTemperature.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pTemperature : public ReferenceableMemberProvider
{
public:
    _pTemperature() : ReferenceableMemberProvider("Temperature")    
    {
        create_prop("Oem",  nullptr);
        create_prop("MemberId",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("AdjustedMaxAllowableOperatingValue",  nullptr);
        create_prop("AdjustedMinAllowableOperatingValue",  nullptr);
        create_prop("DeltaPhysicalContext",  nullptr);
        create_prop("DeltaReadingCelsius",  nullptr);
        create_prop("LowerThresholdCritical",  nullptr);
        create_prop("LowerThresholdFatal",  nullptr);
        create_prop("LowerThresholdNonCritical",  nullptr);
        create_prop("MaxAllowableOperatingValue",  nullptr);
        create_prop("MaxReadingRangeTemp",  nullptr);
        create_prop("MinAllowableOperatingValue",  nullptr);
        create_prop("MinReadingRangeTemp",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("PhysicalContext",  nullptr);
        create_prop("ReadingCelsius",  nullptr);
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
        
        set_namespace("Thermal.v1_4_0");
    }

    virtual ~_pTemperature()    
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
        add_property_class("Actions", "Complex Type.", "TemperatureActions");
        add_property_class("AdjustedMaxAllowableOperatingValue", "Primitive Type.", "Edm.Int64");
        add_property_class("AdjustedMinAllowableOperatingValue", "Primitive Type.", "Edm.Int64");
        add_property_class("DeltaPhysicalContext", "Enum Type.", "PhysicalContext");
        add_property_class("DeltaReadingCelsius", "Primitive Type.", "Edm.Decimal");
        add_property_class("LowerThresholdCritical", "Primitive Type.", "Edm.Decimal");
        add_property_class("LowerThresholdFatal", "Primitive Type.", "Edm.Decimal");
        add_property_class("LowerThresholdNonCritical", "Primitive Type.", "Edm.Decimal");
        add_property_class("MaxAllowableOperatingValue", "Primitive Type.", "Edm.Int64");
        add_property_class("MaxReadingRangeTemp", "Primitive Type.", "Edm.Decimal");
        add_property_class("MinAllowableOperatingValue", "Primitive Type.", "Edm.Int64");
        add_property_class("MinReadingRangeTemp", "Primitive Type.", "Edm.Decimal");
        add_property_class("Name", "Primitive Type.", "Edm.String");
        add_property_class("PhysicalContext", "Enum Type.", "PhysicalContext");
        add_property_class("ReadingCelsius", "Primitive Type.", "Edm.Decimal");
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

        auto MaxReadingRangeTemp_attr = std::make_shared<prop_attribute>();
        MaxReadingRangeTemp_attr->prop_name = "MaxReadingRangeTemp";
        MaxReadingRangeTemp_attr->read_only = true;
        add_property_attr("MaxReadingRangeTemp", MaxReadingRangeTemp_attr);

        auto Name_attr = std::make_shared<prop_attribute>();
        Name_attr->prop_name = "Name";
        Name_attr->read_only = true;
        add_property_attr("Name", Name_attr);

        auto ReadingCelsius_attr = std::make_shared<prop_attribute>();
        ReadingCelsius_attr->prop_name = "ReadingCelsius";
        ReadingCelsius_attr->read_only = true;
        add_property_attr("ReadingCelsius", ReadingCelsius_attr);

        auto MinReadingRangeTemp_attr = std::make_shared<prop_attribute>();
        MinReadingRangeTemp_attr->prop_name = "MinReadingRangeTemp";
        MinReadingRangeTemp_attr->read_only = true;
        add_property_attr("MinReadingRangeTemp", MinReadingRangeTemp_attr);

        auto UpperThresholdFatal_attr = std::make_shared<prop_attribute>();
        UpperThresholdFatal_attr->prop_name = "UpperThresholdFatal";
        UpperThresholdFatal_attr->read_only = true;
        add_property_attr("UpperThresholdFatal", UpperThresholdFatal_attr);

        auto UpperThresholdNonCritical_attr = std::make_shared<prop_attribute>();
        UpperThresholdNonCritical_attr->prop_name = "UpperThresholdNonCritical";
        UpperThresholdNonCritical_attr->read_only = true;
        add_property_attr("UpperThresholdNonCritical", UpperThresholdNonCritical_attr);

        auto SensorNumber_attr = std::make_shared<prop_attribute>();
        SensorNumber_attr->prop_name = "SensorNumber";
        SensorNumber_attr->read_only = true;
        add_property_attr("SensorNumber", SensorNumber_attr);

        auto LowerThresholdCritical_attr = std::make_shared<prop_attribute>();
        LowerThresholdCritical_attr->prop_name = "LowerThresholdCritical";
        LowerThresholdCritical_attr->read_only = true;
        add_property_attr("LowerThresholdCritical", LowerThresholdCritical_attr);

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

        auto AdjustedMinAllowableOperatingValue_attr = std::make_shared<prop_attribute>();
        AdjustedMinAllowableOperatingValue_attr->prop_name = "AdjustedMinAllowableOperatingValue";
        AdjustedMinAllowableOperatingValue_attr->read_only = true;
        add_property_attr("AdjustedMinAllowableOperatingValue", AdjustedMinAllowableOperatingValue_attr);

        auto AdjustedMaxAllowableOperatingValue_attr = std::make_shared<prop_attribute>();
        AdjustedMaxAllowableOperatingValue_attr->prop_name = "AdjustedMaxAllowableOperatingValue";
        AdjustedMaxAllowableOperatingValue_attr->read_only = true;
        add_property_attr("AdjustedMaxAllowableOperatingValue", AdjustedMaxAllowableOperatingValue_attr);

        auto MinAllowableOperatingValue_attr = std::make_shared<prop_attribute>();
        MinAllowableOperatingValue_attr->prop_name = "MinAllowableOperatingValue";
        MinAllowableOperatingValue_attr->read_only = true;
        add_property_attr("MinAllowableOperatingValue", MinAllowableOperatingValue_attr);

        auto MaxAllowableOperatingValue_attr = std::make_shared<prop_attribute>();
        MaxAllowableOperatingValue_attr->prop_name = "MaxAllowableOperatingValue";
        MaxAllowableOperatingValue_attr->read_only = true;
        add_property_attr("MaxAllowableOperatingValue", MaxAllowableOperatingValue_attr);

        auto DeltaPhysicalContext_attr = std::make_shared<prop_attribute>();
        DeltaPhysicalContext_attr->prop_name = "DeltaPhysicalContext";
        DeltaPhysicalContext_attr->read_only = true;
        DeltaPhysicalContext_attr->add_enum("Room");
        DeltaPhysicalContext_attr->add_enum("Intake");
        DeltaPhysicalContext_attr->add_enum("Exhaust");
        DeltaPhysicalContext_attr->add_enum("LiquidInlet");
        DeltaPhysicalContext_attr->add_enum("LiquidOutlet");
        DeltaPhysicalContext_attr->add_enum("Front");
        DeltaPhysicalContext_attr->add_enum("Back");
        DeltaPhysicalContext_attr->add_enum("Upper");
        DeltaPhysicalContext_attr->add_enum("Lower");
        DeltaPhysicalContext_attr->add_enum("CPU");
        DeltaPhysicalContext_attr->add_enum("GPU");
        DeltaPhysicalContext_attr->add_enum("ASIC");
        DeltaPhysicalContext_attr->add_enum("Backplane");
        DeltaPhysicalContext_attr->add_enum("SystemBoard");
        DeltaPhysicalContext_attr->add_enum("PowerSupply");
        DeltaPhysicalContext_attr->add_enum("VoltageRegulator");
        DeltaPhysicalContext_attr->add_enum("StorageDevice");
        DeltaPhysicalContext_attr->add_enum("NetworkingDevice");
        DeltaPhysicalContext_attr->add_enum("ComputeBay");
        DeltaPhysicalContext_attr->add_enum("StorageBay");
        DeltaPhysicalContext_attr->add_enum("NetworkBay");
        DeltaPhysicalContext_attr->add_enum("ExpansionBay");
        DeltaPhysicalContext_attr->add_enum("PowerSupplyBay");
        DeltaPhysicalContext_attr->add_enum("Memory");
        DeltaPhysicalContext_attr->add_enum("Chassis");
        DeltaPhysicalContext_attr->add_enum("Fan");
        add_property_attr("DeltaPhysicalContext", DeltaPhysicalContext_attr);

        auto DeltaReadingCelsius_attr = std::make_shared<prop_attribute>();
        DeltaReadingCelsius_attr->prop_name = "DeltaReadingCelsius";
        DeltaReadingCelsius_attr->read_only = true;
        add_property_attr("DeltaReadingCelsius", DeltaReadingCelsius_attr);

     }

};

}}

