//---------------------------------------------------------------------
// <copyright file="_pLenovoFoDService.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pLenovoFoDService : public ResourceProvider
{
public:
    _pLenovoFoDService() : ResourceProvider("LenovoFoDService")    
    {
        enum TierLevel 
        {
            TierLevel_Tier0,
            TierLevel_Tier1,
            TierLevel_Tier2,
            TierLevel_Tier3,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Keys",  nullptr);
        create_prop("Tier",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("LenovoFoDService.v1_0_0");
        set_desc("This resource represents the fod service for the resource or service to which it is associated.");
    }

    virtual ~_pLenovoFoDService()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("Keys");
    }

        
    void prepare_Links()
    {
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Keys", "Navigation Type.Entity", "LenovoFoDKeyCollection");
        add_property_class("Tier", "Enum Type.", "TierLevel");
    }

    void prep_prop_attrs()
    {
        auto Keys_attr = std::make_shared<prop_attribute>();
        Keys_attr->prop_name = "Keys";
        Keys_attr->read_only = true;
        add_property_attr("Keys", Keys_attr);

        auto Tier_attr = std::make_shared<prop_attribute>();
        Tier_attr->prop_name = "Tier";
        Tier_attr->read_only = true;
        Tier_attr->add_enum("Tier0");
        Tier_attr->add_enum("Tier1");
        Tier_attr->add_enum("Tier2");
        Tier_attr->add_enum("Tier3");
        add_property_attr("Tier", Tier_attr);

     }

};

}}

