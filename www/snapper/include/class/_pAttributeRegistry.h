//---------------------------------------------------------------------
// <copyright file="_pAttributeRegistry.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pAttributeRegistry : public ResourceProvider
{
public:
    _pAttributeRegistry() : ResourceProvider("AttributeRegistry")    
    {
        enum MapToProperty 
        {
            MapToProperty_CurrentValue,
            MapToProperty_DefaultValue,
            MapToProperty_ReadOnly,
            MapToProperty_WriteOnly,
            MapToProperty_GrayOut,
            MapToProperty_Hidden,
            MapToProperty_Immutable,
            MapToProperty_HelpText,
            MapToProperty_WarningText,
            MapToProperty_DisplayName,
            MapToProperty_DisplayOrder,
            MapToProperty_LowerBound,
            MapToProperty_UpperBound,
            MapToProperty_MinLength,
            MapToProperty_MaxLength,
            MapToProperty_ScalarIncrement,
            MapToProperty_ValueExpression,
        };

        enum MapFromProperty 
        {
            MapFromProperty_CurrentValue,
            MapFromProperty_DefaultValue,
            MapFromProperty_ReadOnly,
            MapFromProperty_WriteOnly,
            MapFromProperty_GrayOut,
            MapFromProperty_Hidden,
            MapFromProperty_LowerBound,
            MapFromProperty_UpperBound,
            MapFromProperty_MinLength,
            MapFromProperty_MaxLength,
            MapFromProperty_ScalarIncrement,
        };

        enum MapTerms 
        {
            MapTerms_AND,
            MapTerms_OR,
        };

        enum MapFromCondition 
        {
            MapFromCondition_EQU,
            MapFromCondition_NEQ,
            MapFromCondition_GTR,
            MapFromCondition_GEQ,
            MapFromCondition_LSS,
            MapFromCondition_LEQ,
        };

        enum DependencyType 
        {
            DependencyType_Map,
        };

        enum AttributeType 
        {
            AttributeType_Enumeration,
            AttributeType_String,
            AttributeType_Integer,
            AttributeType_Boolean,
            AttributeType_Password,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Language",  nullptr);
        create_prop("OwningEntity",  nullptr);
        create_prop("RegistryEntries",  nullptr);
        create_prop("RegistryVersion",  nullptr);
        create_prop("SupportedSystems",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("AttributeRegistry.v1_2_0");
        set_desc("The AttributeRegistry schema contains a set of key-value pairs that represents the structure of a Registry. It includes mechanisms for building user interfaces (menus), allowing consistent navigation of the contents. The Attribute Registry is specific to a particular implementation or product. The attributes and property names are not standardized.");
    }

    virtual ~_pAttributeRegistry()    
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
        add_property_class("Language", "Primitive Type.", "Edm.String");
        add_property_class("OwningEntity", "Primitive Type.", "Edm.String");
        add_property_class("RegistryEntries", "Complex Type.", "RegistryEntries");
        add_property_class("RegistryVersion", "Primitive Type.", "Edm.String");
        add_property_class("SupportedSystems", "Collection Type.", "SupportedSystems");
    }

    void prep_prop_attrs()
    {
        auto OwningEntity_attr = std::make_shared<prop_attribute>();
        OwningEntity_attr->prop_name = "OwningEntity";
        OwningEntity_attr->read_only = true;
        add_property_attr("OwningEntity", OwningEntity_attr);

        auto RegistryVersion_attr = std::make_shared<prop_attribute>();
        RegistryVersion_attr->prop_name = "RegistryVersion";
        RegistryVersion_attr->read_only = true;
        add_property_attr("RegistryVersion", RegistryVersion_attr);

        auto Language_attr = std::make_shared<prop_attribute>();
        Language_attr->prop_name = "Language";
        Language_attr->read_only = true;
        add_property_attr("Language", Language_attr);

     }

};

}}

