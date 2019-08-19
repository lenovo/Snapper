//---------------------------------------------------------------------
// <copyright file="_pAssemblyData.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pAssemblyData : public ReferenceableMemberProvider
{
public:
    _pAssemblyData() : ReferenceableMemberProvider("AssemblyData")    
    {
        create_prop("Oem",  nullptr);
        create_prop("MemberId",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("BinaryDataURI",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("EngineeringChangeLevel",  nullptr);
        create_prop("Model",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("PartNumber",  nullptr);
        create_prop("Producer",  nullptr);
        create_prop("ProductionDate",  nullptr);
        create_prop("SKU",  nullptr);
        create_prop("SparePartNumber",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("Vendor",  nullptr);
        create_prop("Version",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Assembly.v1_1_0");
    }

    virtual ~_pAssemblyData()    
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
        add_property_class("Actions", "Complex Type.", "AssemblyDataActions");
        add_property_class("BinaryDataURI", "Primitive Type.", "Edm.String");
        add_property_class("Description", "Primitive Type.", "Edm.String");
        add_property_class("EngineeringChangeLevel", "Primitive Type.", "Edm.String");
        add_property_class("Model", "Primitive Type.", "Edm.String");
        add_property_class("Name", "Primitive Type.", "Edm.String");
        add_property_class("PartNumber", "Primitive Type.", "Edm.String");
        add_property_class("Producer", "Primitive Type.", "Edm.String");
        add_property_class("ProductionDate", "Primitive Type.", "Edm.DateTimeOffset");
        add_property_class("SKU", "Primitive Type.", "Edm.String");
        add_property_class("SparePartNumber", "Primitive Type.", "Edm.String");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("Vendor", "Primitive Type.", "Edm.String");
        add_property_class("Version", "Primitive Type.", "Edm.String");
    }

    void prep_prop_attrs()
    {
        auto EngineeringChangeLevel_attr = std::make_shared<prop_attribute>();
        EngineeringChangeLevel_attr->prop_name = "EngineeringChangeLevel";
        EngineeringChangeLevel_attr->read_only = true;
        add_property_attr("EngineeringChangeLevel", EngineeringChangeLevel_attr);

        auto BinaryDataURI_attr = std::make_shared<prop_attribute>();
        BinaryDataURI_attr->prop_name = "BinaryDataURI";
        BinaryDataURI_attr->read_only = true;
        add_property_attr("BinaryDataURI", BinaryDataURI_attr);

        auto PartNumber_attr = std::make_shared<prop_attribute>();
        PartNumber_attr->prop_name = "PartNumber";
        PartNumber_attr->read_only = true;
        add_property_attr("PartNumber", PartNumber_attr);

        auto Description_attr = std::make_shared<prop_attribute>();
        Description_attr->prop_name = "Description";
        Description_attr->read_only = true;
        add_property_attr("Description", Description_attr);

        auto Name_attr = std::make_shared<prop_attribute>();
        Name_attr->prop_name = "Name";
        Name_attr->read_only = true;
        add_property_attr("Name", Name_attr);

        auto Version_attr = std::make_shared<prop_attribute>();
        Version_attr->prop_name = "Version";
        Version_attr->read_only = true;
        add_property_attr("Version", Version_attr);

        auto Model_attr = std::make_shared<prop_attribute>();
        Model_attr->prop_name = "Model";
        Model_attr->read_only = true;
        add_property_attr("Model", Model_attr);

        auto SparePartNumber_attr = std::make_shared<prop_attribute>();
        SparePartNumber_attr->prop_name = "SparePartNumber";
        SparePartNumber_attr->read_only = true;
        add_property_attr("SparePartNumber", SparePartNumber_attr);

        auto ProductionDate_attr = std::make_shared<prop_attribute>();
        ProductionDate_attr->prop_name = "ProductionDate";
        ProductionDate_attr->read_only = true;
        add_property_attr("ProductionDate", ProductionDate_attr);

        auto SKU_attr = std::make_shared<prop_attribute>();
        SKU_attr->prop_name = "SKU";
        SKU_attr->read_only = true;
        add_property_attr("SKU", SKU_attr);

        auto Vendor_attr = std::make_shared<prop_attribute>();
        Vendor_attr->prop_name = "Vendor";
        Vendor_attr->read_only = true;
        add_property_attr("Vendor", Vendor_attr);

        auto Producer_attr = std::make_shared<prop_attribute>();
        Producer_attr->prop_name = "Producer";
        Producer_attr->read_only = true;
        add_property_attr("Producer", Producer_attr);

     }

};

}}

