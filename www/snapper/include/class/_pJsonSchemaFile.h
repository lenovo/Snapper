//---------------------------------------------------------------------
// <copyright file="_pJsonSchemaFile.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pJsonSchemaFile : public ResourceProvider
{
public:
    _pJsonSchemaFile() : ResourceProvider("JsonSchemaFile")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Languages",  nullptr);
        create_prop("Location",  nullptr);
        create_prop("Schema",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("JsonSchemaFile.v1_1_0");
        set_desc("This is the schema definition for the Schema File locator resource.");
    }

    virtual ~_pJsonSchemaFile()    
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
        add_property_class("Languages", "Collection Type.", "Edm.String");
        add_property_class("Location", "Collection Type.", "Location");
        add_property_class("Schema", "Primitive Type.", "Edm.String");
    }

    void prep_prop_attrs()
    {
        auto Schema_attr = std::make_shared<prop_attribute>();
        Schema_attr->prop_name = "Schema";
        Schema_attr->read_only = true;
        add_property_attr("Schema", Schema_attr);

        auto Languages_attr = std::make_shared<prop_attribute>();
        Languages_attr->prop_name = "Languages";
        Languages_attr->read_only = true;
        add_property_attr("Languages", Languages_attr);

     }

};

}}

