//---------------------------------------------------------------------
// <copyright file="_pBios.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pBios : public ResourceProvider
{
public:
    _pBios() : ResourceProvider("Bios")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("AttributeRegistry",  nullptr);
        create_prop("Attributes",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Bios.v1_0_3");
        set_desc("The Bios schema contains properties related to the BIOS Attribute Registry. The Attribute Registry describes the system-specific BIOS attributes and Actions for changing to BIOS settings. Changes to the BIOS typically require a system reset before they take effect.");
    }

    virtual ~_pBios()    
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
                "#Bios.ChangePassword"
                << BSON("target" << (get_base_odata_id() + "/Actions/Bios.ChangePassword")
                << "title" << "ChangePassword")
                << "#Bios.ResetBios"
                << BSON("target" << (get_base_odata_id() + "/Actions/Bios.ResetBios")
                << "title" << "ResetBios")
                )
                )) );
     }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("AttributeRegistry", "Primitive Type.", "Edm.String");
        add_property_class("Attributes", "Complex Type.", "Attributes");
    }

    void prep_prop_attrs()
    {
        auto AttributeRegistry_attr = std::make_shared<prop_attribute>();
        AttributeRegistry_attr->prop_name = "AttributeRegistry";
        AttributeRegistry_attr->read_only = true;
        add_property_attr("AttributeRegistry", AttributeRegistry_attr);

     }

};

}}

