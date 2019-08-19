//---------------------------------------------------------------------
// <copyright file="_pSimpleStorage.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pSimpleStorage : public ResourceProvider
{
public:
    _pSimpleStorage() : ResourceProvider("SimpleStorage")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Devices",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("UefiDevicePath",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("SimpleStorage.v1_2_0");
        set_desc("This is the schema definition for the Simple Storage resource.  It represents the properties of a storage controller and its directly-attached devices.");
    }

    virtual ~_pSimpleStorage()    
    {}

    void prepare_navigation_property()
    {
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["Chassis"] = nullptr;
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("Devices", "Collection Type.", "Device");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("UefiDevicePath", "Primitive Type.", "Edm.String");
    }

    void prep_prop_attrs()
    {
        auto UefiDevicePath_attr = std::make_shared<prop_attribute>();
        UefiDevicePath_attr->prop_name = "UefiDevicePath";
        UefiDevicePath_attr->read_only = true;
        add_property_attr("UefiDevicePath", UefiDevicePath_attr);

     }

};

}}

