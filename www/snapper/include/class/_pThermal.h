//---------------------------------------------------------------------
// <copyright file="_pThermal.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pThermal : public ResourceProvider
{
public:
    _pThermal() : ResourceProvider("Thermal")    
    {
        enum ReadingUnits 
        {
            ReadingUnits_RPM,
            ReadingUnits_Percent,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Fans",  nullptr);
        create_prop("Fans@odata.count",  nullptr);
        create_prop("Fans@odata.navigationLink",  nullptr);
        create_prop("Redundancy",  nullptr);
        create_prop("Redundancy@odata.count",  nullptr);
        create_prop("Redundancy@odata.navigationLink",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("Temperatures",  nullptr);
        create_prop("Temperatures@odata.count",  nullptr);
        create_prop("Temperatures@odata.navigationLink",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Thermal.v1_4_0");
        set_desc("This is the schema definition for the Thermal properties.  It represents the properties for Temperature and Cooling.");
    }

    virtual ~_pThermal()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_arr_props("Redundancy");
        add_navigation_arr_props("Fans");
        add_navigation_arr_props("Temperatures");
    }

        
    void prepare_Links()
    {
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "ThermalActions");
        add_property_class("Fans", "Navigation Type.Collection", "Fan");
        add_property_class("Redundancy", "Navigation Type.Collection", "Redundancy");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("Temperatures", "Navigation Type.Collection", "Temperature");
    }

    void prep_prop_attrs()
    {
        auto Fans_attr = std::make_shared<prop_attribute>();
        Fans_attr->prop_name = "Fans";
        Fans_attr->read_only = false;
        add_property_attr("Fans", Fans_attr);

        auto Temperatures_attr = std::make_shared<prop_attribute>();
        Temperatures_attr->prop_name = "Temperatures";
        Temperatures_attr->read_only = false;
        add_property_attr("Temperatures", Temperatures_attr);

     }

};

}}

