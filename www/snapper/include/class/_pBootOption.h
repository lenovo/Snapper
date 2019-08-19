//---------------------------------------------------------------------
// <copyright file="_pBootOption.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pBootOption : public ResourceProvider
{
public:
    _pBootOption() : ResourceProvider("BootOption")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Alias",  nullptr);
        create_prop("BootOptionEnabled",  nullptr);
        create_prop("BootOptionReference",  nullptr);
        create_prop("DisplayName",  nullptr);
        create_prop("RelatedItem",  nullptr);
        create_prop("RelatedItem@odata.count",  nullptr);
        create_prop("RelatedItem@odata.navigationLink",  nullptr);
        create_prop("UefiDevicePath",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("BootOption.v1_0_0");
        set_desc("This is the schema definition for the BootOption resource. It represents the properties of a bootable device available in the System.");
    }

    virtual ~_pBootOption()    
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
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("Alias", "Enum Type.", "BootSource");
        add_property_class("BootOptionEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("BootOptionReference", "Primitive Type.", "Edm.String");
        add_property_class("DisplayName", "Primitive Type.", "Edm.String");
        add_property_class("RelatedItem", "Navigation Type.Collection", "Item");
        add_property_class("UefiDevicePath", "Primitive Type.", "Edm.String");
    }

    void prep_prop_attrs()
    {
        auto RelatedItem_attr = std::make_shared<prop_attribute>();
        RelatedItem_attr->prop_name = "RelatedItem";
        RelatedItem_attr->read_only = true;
        add_property_attr("RelatedItem", RelatedItem_attr);

        auto Alias_attr = std::make_shared<prop_attribute>();
        Alias_attr->prop_name = "Alias";
        Alias_attr->read_only = true;
        Alias_attr->add_enum("None");
        Alias_attr->add_enum("Pxe");
        Alias_attr->add_enum("Floppy");
        Alias_attr->add_enum("Cd");
        Alias_attr->add_enum("Usb");
        Alias_attr->add_enum("Hdd");
        Alias_attr->add_enum("BiosSetup");
        Alias_attr->add_enum("Utilities");
        Alias_attr->add_enum("Diags");
        Alias_attr->add_enum("UefiShell");
        Alias_attr->add_enum("UefiTarget");
        Alias_attr->add_enum("SDCard");
        Alias_attr->add_enum("UefiHttp");
        Alias_attr->add_enum("RemoteDrive");
        Alias_attr->add_enum("UefiBootNext");
        add_property_attr("Alias", Alias_attr);

        auto DisplayName_attr = std::make_shared<prop_attribute>();
        DisplayName_attr->prop_name = "DisplayName";
        DisplayName_attr->read_only = true;
        add_property_attr("DisplayName", DisplayName_attr);

        auto UefiDevicePath_attr = std::make_shared<prop_attribute>();
        UefiDevicePath_attr->prop_name = "UefiDevicePath";
        UefiDevicePath_attr->read_only = true;
        add_property_attr("UefiDevicePath", UefiDevicePath_attr);

        auto BootOptionEnabled_attr = std::make_shared<prop_attribute>();
        BootOptionEnabled_attr->prop_name = "BootOptionEnabled";
        BootOptionEnabled_attr->read_only = false;
        add_property_attr("BootOptionEnabled", BootOptionEnabled_attr);

        auto BootOptionReference_attr = std::make_shared<prop_attribute>();
        BootOptionReference_attr->prop_name = "BootOptionReference";
        BootOptionReference_attr->read_only = true;
        add_property_attr("BootOptionReference", BootOptionReference_attr);

     }

};

}}

