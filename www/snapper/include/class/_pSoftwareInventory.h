//---------------------------------------------------------------------
// <copyright file="_pSoftwareInventory.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pSoftwareInventory : public ResourceProvider
{
public:
    _pSoftwareInventory() : ResourceProvider("SoftwareInventory")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("LowestSupportedVersion",  nullptr);
        create_prop("Manufacturer",  nullptr);
        create_prop("RelatedItem",  nullptr);
        create_prop("RelatedItem@odata.count",  nullptr);
        create_prop("RelatedItem@odata.navigationLink",  nullptr);
        create_prop("ReleaseDate",  nullptr);
        create_prop("SoftwareId",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("UefiDevicePaths",  nullptr);
        create_prop("Updateable",  nullptr);
        create_prop("Version",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("SoftwareInventory.v1_2_0");
        set_desc("This schema defines an inventory of software components.");
    }

    virtual ~_pSoftwareInventory()    
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
        add_property_class("LowestSupportedVersion", "Primitive Type.", "Edm.String");
        add_property_class("Manufacturer", "Primitive Type.", "Edm.String");
        add_property_class("RelatedItem", "Navigation Type.Collection", "Item");
        add_property_class("ReleaseDate", "Primitive Type.", "Edm.DateTimeOffset");
        add_property_class("SoftwareId", "Primitive Type.", "Edm.String");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("UefiDevicePaths", "Collection Type.", "Edm.String");
        add_property_class("Updateable", "Primitive Type.", "Edm.Boolean");
        add_property_class("Version", "Primitive Type.", "Edm.String");
    }

    void prep_prop_attrs()
    {
        auto Updateable_attr = std::make_shared<prop_attribute>();
        Updateable_attr->prop_name = "Updateable";
        Updateable_attr->read_only = true;
        add_property_attr("Updateable", Updateable_attr);

        auto Version_attr = std::make_shared<prop_attribute>();
        Version_attr->prop_name = "Version";
        Version_attr->read_only = true;
        add_property_attr("Version", Version_attr);

        auto RelatedItem_attr = std::make_shared<prop_attribute>();
        RelatedItem_attr->prop_name = "RelatedItem";
        RelatedItem_attr->read_only = true;
        add_property_attr("RelatedItem", RelatedItem_attr);

        auto UefiDevicePaths_attr = std::make_shared<prop_attribute>();
        UefiDevicePaths_attr->prop_name = "UefiDevicePaths";
        UefiDevicePaths_attr->read_only = true;
        add_property_attr("UefiDevicePaths", UefiDevicePaths_attr);

        auto LowestSupportedVersion_attr = std::make_shared<prop_attribute>();
        LowestSupportedVersion_attr->prop_name = "LowestSupportedVersion";
        LowestSupportedVersion_attr->read_only = true;
        add_property_attr("LowestSupportedVersion", LowestSupportedVersion_attr);

        auto SoftwareId_attr = std::make_shared<prop_attribute>();
        SoftwareId_attr->prop_name = "SoftwareId";
        SoftwareId_attr->read_only = true;
        add_property_attr("SoftwareId", SoftwareId_attr);

        auto ReleaseDate_attr = std::make_shared<prop_attribute>();
        ReleaseDate_attr->prop_name = "ReleaseDate";
        ReleaseDate_attr->read_only = true;
        add_property_attr("ReleaseDate", ReleaseDate_attr);

        auto Manufacturer_attr = std::make_shared<prop_attribute>();
        Manufacturer_attr->prop_name = "Manufacturer";
        Manufacturer_attr->read_only = true;
        add_property_attr("Manufacturer", Manufacturer_attr);

     }

};

}}

