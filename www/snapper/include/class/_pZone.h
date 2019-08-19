//---------------------------------------------------------------------
// <copyright file="_pZone.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pZone : public ResourceProvider
{
public:
    _pZone() : ResourceProvider("Zone")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Identifiers",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("Status",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Zone.v1_2_0");
        set_desc("The Zone schema represents a fabric zone.");
    }

    virtual ~_pZone()    
    {}

    void prepare_navigation_property()
    {
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["Endpoints"] = nullptr;
        m_Links_prop_objs["Endpoints@odata.count"] = nullptr;
        m_Links_prop_objs["Endpoints@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["InvolvedSwitches"] = nullptr;
        m_Links_prop_objs["InvolvedSwitches@odata.count"] = nullptr;
        m_Links_prop_objs["InvolvedSwitches@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["ResourceBlocks"] = nullptr;
        m_Links_prop_objs["ResourceBlocks@odata.count"] = nullptr;
        m_Links_prop_objs["ResourceBlocks@odata.navigationLink"] = nullptr;
        add_Links_arr_props("Endpoints");
        add_Links_arr_props("InvolvedSwitches");
        add_Links_arr_props("ResourceBlocks");
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("Identifiers", "Collection Type.", "Identifier");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("Status", "Complex Type.", "Status");
    }

    void prep_prop_attrs()
    {
     }

};

}}

