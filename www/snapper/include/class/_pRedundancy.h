//---------------------------------------------------------------------
// <copyright file="_pRedundancy.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pRedundancy : public ReferenceableMemberProvider
{
public:
    _pRedundancy() : ReferenceableMemberProvider("Redundancy")    
    {
        create_prop("Oem",  nullptr);
        create_prop("MemberId",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("MaxNumSupported",  nullptr);
        create_prop("MinNumNeeded",  nullptr);
        create_prop("Mode",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("RedundancyEnabled",  nullptr);
        create_prop("RedundancySet",  nullptr);
        create_prop("RedundancySet@odata.count",  nullptr);
        create_prop("RedundancySet@odata.navigationLink",  nullptr);
        create_prop("Status",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Redundancy.v1_3_0");
        set_desc("This is the redundancy definition to be used in other resource schemas.");
    }

    virtual ~_pRedundancy()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_arr_props("RedundancySet");
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
        add_property_class("MaxNumSupported", "Primitive Type.", "Edm.Int64");
        add_property_class("MinNumNeeded", "Primitive Type.", "Edm.Int64");
        add_property_class("Mode", "Type Definition.", "Edm.String");
        add_property_class("Name", "Primitive Type.", "Edm.String");
        add_property_class("RedundancyEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("RedundancySet", "Navigation Type.Collection", "Item");
        add_property_class("Status", "Complex Type.", "Status");
    }

    void prep_prop_attrs()
    {
        auto RedundancySet_attr = std::make_shared<prop_attribute>();
        RedundancySet_attr->prop_name = "RedundancySet";
        RedundancySet_attr->read_only = true;
        add_property_attr("RedundancySet", RedundancySet_attr);

        auto MinNumNeeded_attr = std::make_shared<prop_attribute>();
        MinNumNeeded_attr->prop_name = "MinNumNeeded";
        MinNumNeeded_attr->read_only = true;
        add_property_attr("MinNumNeeded", MinNumNeeded_attr);

        auto MaxNumSupported_attr = std::make_shared<prop_attribute>();
        MaxNumSupported_attr->prop_name = "MaxNumSupported";
        MaxNumSupported_attr->read_only = true;
        add_property_attr("MaxNumSupported", MaxNumSupported_attr);

        auto Mode_attr = std::make_shared<prop_attribute>();
        Mode_attr->prop_name = "Mode";
        Mode_attr->read_only = false;
        add_property_attr("Mode", Mode_attr);

        auto Name_attr = std::make_shared<prop_attribute>();
        Name_attr->prop_name = "Name";
        Name_attr->read_only = true;
        add_property_attr("Name", Name_attr);

        auto RedundancyEnabled_attr = std::make_shared<prop_attribute>();
        RedundancyEnabled_attr->prop_name = "RedundancyEnabled";
        RedundancyEnabled_attr->read_only = false;
        add_property_attr("RedundancyEnabled", RedundancyEnabled_attr);

     }

};

}}

