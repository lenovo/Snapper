//---------------------------------------------------------------------
// <copyright file="_pPower.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pPower : public ResourceProvider
{
public:
    _pPower() : ResourceProvider("Power")    
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
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("PowerControl",  nullptr);
        create_prop("PowerControl@odata.count",  nullptr);
        create_prop("PowerControl@odata.navigationLink",  nullptr);
        create_prop("PowerSupplies",  nullptr);
        create_prop("PowerSupplies@odata.count",  nullptr);
        create_prop("PowerSupplies@odata.navigationLink",  nullptr);
        create_prop("Redundancy",  nullptr);
        create_prop("Redundancy@odata.count",  nullptr);
        create_prop("Redundancy@odata.navigationLink",  nullptr);
        create_prop("Voltages",  nullptr);
        create_prop("Voltages@odata.count",  nullptr);
        create_prop("Voltages@odata.navigationLink",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Power.v1_5_0");
        set_desc("This is the schema definition for the Power Metrics.  It represents the properties for Power Consumption and Power Limiting.");
    }

    virtual ~_pPower()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_arr_props("Redundancy");
        add_navigation_arr_props("Voltages");
        add_navigation_arr_props("PowerSupplies");
        add_navigation_arr_props("PowerControl");
    }

        
    void prepare_Links()
    {
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("PowerControl", "Navigation Type.Collection", "PowerControl");
        add_property_class("PowerSupplies", "Navigation Type.Collection", "PowerSupply");
        add_property_class("Redundancy", "Navigation Type.Collection", "Redundancy");
        add_property_class("Voltages", "Navigation Type.Collection", "Voltage");
    }

    void prep_prop_attrs()
    {
     }

};

}}

