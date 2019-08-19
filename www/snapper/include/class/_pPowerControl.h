//---------------------------------------------------------------------
// <copyright file="_pPowerControl.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pPowerControl : public ReferenceableMemberProvider
{
public:
    _pPowerControl() : ReferenceableMemberProvider("PowerControl")    
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
        create_prop("Name",  nullptr);
        create_prop("PhysicalContext",  nullptr);
        create_prop("PowerAllocatedWatts",  nullptr);
        create_prop("PowerAvailableWatts",  nullptr);
        create_prop("PowerCapacityWatts",  nullptr);
        create_prop("PowerConsumedWatts",  nullptr);
        create_prop("PowerLimit",  nullptr);
        create_prop("PowerMetrics",  nullptr);
        create_prop("PowerRequestedWatts",  nullptr);
        create_prop("RelatedItem",  nullptr);
        create_prop("RelatedItem@odata.count",  nullptr);
        create_prop("RelatedItem@odata.navigationLink",  nullptr);
        create_prop("Status",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Power.v1_4_0");
    }

    virtual ~_pPowerControl()    
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
        add_property_class("Actions", "Complex Type.", "PowerControlActions");
        add_property_class("Name", "Primitive Type.", "Edm.String");
        add_property_class("PhysicalContext", "Enum Type.", "PhysicalContext");
        add_property_class("PowerAllocatedWatts", "Primitive Type.", "Edm.Decimal");
        add_property_class("PowerAvailableWatts", "Primitive Type.", "Edm.Decimal");
        add_property_class("PowerCapacityWatts", "Primitive Type.", "Edm.Decimal");
        add_property_class("PowerConsumedWatts", "Primitive Type.", "Edm.Decimal");
        add_property_class("PowerLimit", "Complex Type.", "PowerLimit");
        add_property_class("PowerMetrics", "Complex Type.", "PowerMetric");
        add_property_class("PowerRequestedWatts", "Primitive Type.", "Edm.Decimal");
        add_property_class("RelatedItem", "Navigation Type.Collection", "Item");
        add_property_class("Status", "Complex Type.", "Status");
    }

    void prep_prop_attrs()
    {
        auto RelatedItem_attr = std::make_shared<prop_attribute>();
        RelatedItem_attr->prop_name = "RelatedItem";
        RelatedItem_attr->read_only = true;
        add_property_attr("RelatedItem", RelatedItem_attr);

        auto PowerAllocatedWatts_attr = std::make_shared<prop_attribute>();
        PowerAllocatedWatts_attr->prop_name = "PowerAllocatedWatts";
        PowerAllocatedWatts_attr->read_only = true;
        add_property_attr("PowerAllocatedWatts", PowerAllocatedWatts_attr);

        auto PowerCapacityWatts_attr = std::make_shared<prop_attribute>();
        PowerCapacityWatts_attr->prop_name = "PowerCapacityWatts";
        PowerCapacityWatts_attr->read_only = true;
        add_property_attr("PowerCapacityWatts", PowerCapacityWatts_attr);

        auto PowerAvailableWatts_attr = std::make_shared<prop_attribute>();
        PowerAvailableWatts_attr->prop_name = "PowerAvailableWatts";
        PowerAvailableWatts_attr->read_only = true;
        add_property_attr("PowerAvailableWatts", PowerAvailableWatts_attr);

        auto PowerRequestedWatts_attr = std::make_shared<prop_attribute>();
        PowerRequestedWatts_attr->prop_name = "PowerRequestedWatts";
        PowerRequestedWatts_attr->read_only = true;
        add_property_attr("PowerRequestedWatts", PowerRequestedWatts_attr);

        auto PowerConsumedWatts_attr = std::make_shared<prop_attribute>();
        PowerConsumedWatts_attr->prop_name = "PowerConsumedWatts";
        PowerConsumedWatts_attr->read_only = true;
        add_property_attr("PowerConsumedWatts", PowerConsumedWatts_attr);

        auto Name_attr = std::make_shared<prop_attribute>();
        Name_attr->prop_name = "Name";
        Name_attr->read_only = true;
        add_property_attr("Name", Name_attr);

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

     }

};

}}

