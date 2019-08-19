//---------------------------------------------------------------------
// <copyright file="_pVLanNetworkInterface.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pVLanNetworkInterface : public ResourceProvider
{
public:
    _pVLanNetworkInterface() : ResourceProvider("VLanNetworkInterface")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("VLANEnable",  nullptr);
        create_prop("VLANId",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("VLanNetworkInterface.v1_1_1");
        set_desc("This resource describes the attributes of a Virtual LAN.");
    }

    virtual ~_pVLanNetworkInterface()    
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

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("VLANEnable", "Primitive Type.", "Edm.Boolean");
        add_property_class("VLANId", "Type Definition.", "Edm.Int64");
    }

    void prep_prop_attrs()
    {
        auto VLANId_attr = std::make_shared<prop_attribute>();
        VLANId_attr->prop_name = "VLANId";
        VLANId_attr->read_only = false;
        VLANId_attr->required_on_create = true;
        add_property_attr("VLANId", VLANId_attr);

        auto VLANEnable_attr = std::make_shared<prop_attribute>();
        VLANEnable_attr->prop_name = "VLANEnable";
        VLANEnable_attr->read_only = false;
        VLANEnable_attr->required_on_create = true;
        add_property_attr("VLANEnable", VLANEnable_attr);

     }

};

}}

