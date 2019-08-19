//---------------------------------------------------------------------
// <copyright file="_pLenovoFoDKey.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pLenovoFoDKey : public ResourceProvider
{
public:
    _pLenovoFoDKey() : ResourceProvider("LenovoFoDKey")    
    {
        enum KeyStatus 
        {
            KeyStatus_Valid,
            KeyStatus_Invalid,
            KeyStatus_Validating,
            KeyStatus_Expired,
            KeyStatus_ReachUseLimit,
            KeyStatus_NeedValidationElsewhere,
        };

        enum IdentifierType 
        {
            IdentifierType_MTSN,
            IdentifierType_MAC,
            IdentifierType_EmulexASIC,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Bytes",  nullptr);
        create_prop("DescTypeCode",  nullptr);
        create_prop("Expires",  nullptr);
        create_prop("IdTypes",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("UseCount",  nullptr);
        create_prop("UseLimit",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("LenovoFoDKey.v1_0_0");
        set_desc("This is the schema definition for the FoDKey resource. It represents the properties of a FoDKey.");
    }

    virtual ~_pLenovoFoDKey()    
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
        add_property_class("Bytes", "Collection Type.", "Edm.Int64");
        add_property_class("DescTypeCode", "Primitive Type.", "Edm.Int64");
        add_property_class("Expires", "Primitive Type.", "Edm.String");
        add_property_class("IdTypes", "Collection Type.", "IdentifierType");
        add_property_class("Status", "Enum Type.", "KeyStatus");
        add_property_class("UseCount", "Primitive Type.", "Edm.Int64");
        add_property_class("UseLimit", "Primitive Type.", "Edm.Int64");
    }

    void prep_prop_attrs()
    {
        auto Bytes_attr = std::make_shared<prop_attribute>();
        Bytes_attr->prop_name = "Bytes";
        Bytes_attr->read_only = true;
        Bytes_attr->required_on_create = true;
        add_property_attr("Bytes", Bytes_attr);

        auto UseCount_attr = std::make_shared<prop_attribute>();
        UseCount_attr->prop_name = "UseCount";
        UseCount_attr->read_only = false;
        add_property_attr("UseCount", UseCount_attr);

        auto Status_attr = std::make_shared<prop_attribute>();
        Status_attr->prop_name = "Status";
        Status_attr->add_enum("Valid");
        Status_attr->add_enum("Invalid");
        Status_attr->add_enum("Validating");
        Status_attr->add_enum("Expired");
        Status_attr->add_enum("ReachUseLimit");
        Status_attr->add_enum("NeedValidationElsewhere");
        add_property_attr("Status", Status_attr);

        auto IdTypes_attr = std::make_shared<prop_attribute>();
        IdTypes_attr->prop_name = "IdTypes";
        IdTypes_attr->add_enum("MTSN");
        IdTypes_attr->add_enum("MAC");
        IdTypes_attr->add_enum("EmulexASIC");
        add_property_attr("IdTypes", IdTypes_attr);

     }

};

}}

