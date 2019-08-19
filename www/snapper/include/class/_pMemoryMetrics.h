//---------------------------------------------------------------------
// <copyright file="_pMemoryMetrics.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pMemoryMetrics : public ResourceProvider
{
public:
    _pMemoryMetrics() : ResourceProvider("MemoryMetrics")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("BlockSizeBytes",  nullptr);
        create_prop("CurrentPeriod",  nullptr);
        create_prop("HealthData",  nullptr);
        create_prop("LifeTime",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("MemoryMetrics.v1_1_3");
        set_desc("MemoryMetrics contains usage and health statistics for a single Memory module or device instance.");
    }

    virtual ~_pMemoryMetrics()    
    {}

    void prepare_navigation_property()
    {
    }

        
    void prepare_Links()
    {
    }

    void prepare_OemLenovo()
    {
    }

    virtual void set_actions_obj()
    {
         create_prop( "Actions",   std::make_shared<bson::BSONObj>(BSON("Actions" << BSON(
                "#MemoryMetrics.ClearCurrentPeriod"
                << BSON("target" << (get_base_odata_id() + "/Actions/MemoryMetrics.ClearCurrentPeriod")
                << "title" << "ClearCurrentPeriod")
                )
                )) );
     }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("BlockSizeBytes", "Primitive Type.", "Edm.Int64");
        add_property_class("CurrentPeriod", "Complex Type.", "CurrentPeriod");
        add_property_class("HealthData", "Complex Type.", "HealthData");
        add_property_class("LifeTime", "Complex Type.", "LifeTime");
    }

    void prep_prop_attrs()
    {
        auto BlockSizeBytes_attr = std::make_shared<prop_attribute>();
        BlockSizeBytes_attr->prop_name = "BlockSizeBytes";
        BlockSizeBytes_attr->read_only = true;
        add_property_attr("BlockSizeBytes", BlockSizeBytes_attr);

     }

};

}}

