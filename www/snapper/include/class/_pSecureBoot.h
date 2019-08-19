//---------------------------------------------------------------------
// <copyright file="_pSecureBoot.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pSecureBoot : public ResourceProvider
{
public:
    _pSecureBoot() : ResourceProvider("SecureBoot")    
    {
        enum ResetKeysType 
        {
            ResetKeysType_ResetAllKeysToDefault,
            ResetKeysType_DeleteAllKeys,
            ResetKeysType_DeletePK,
        };

        enum SecureBootModeType 
        {
            SecureBootModeType_SetupMode,
            SecureBootModeType_UserMode,
            SecureBootModeType_AuditMode,
            SecureBootModeType_DeployedMode,
        };

        enum SecureBootCurrentBootType 
        {
            SecureBootCurrentBootType_Enabled,
            SecureBootCurrentBootType_Disabled,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("SecureBootCurrentBoot",  nullptr);
        create_prop("SecureBootEnable",  nullptr);
        create_prop("SecureBootMode",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("SecureBoot.v1_0_3");
        set_desc("This resource contains UEFI Secure Boot information. It represents properties for managing the UEFI Secure Boot functionality of a system.");
    }

    virtual ~_pSecureBoot()    
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
                "#SecureBoot.ResetKeys"
                << BSON("target" << (get_base_odata_id() + "/Actions/SecureBoot.ResetKeys")
                << "title" << "ResetKeys"
                << "ResetKeysType@Redfish.AllowableValues"
                << BSON_ARRAY("ResetAllKeysToDefault"
                             << "DeleteAllKeys"
                             << "DeletePK"))
                )
                )) );
     }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("SecureBootCurrentBoot", "Enum Type.", "SecureBootCurrentBootType");
        add_property_class("SecureBootEnable", "Primitive Type.", "Edm.Boolean");
        add_property_class("SecureBootMode", "Enum Type.", "SecureBootModeType");
    }

    void prep_prop_attrs()
    {
        auto SecureBootMode_attr = std::make_shared<prop_attribute>();
        SecureBootMode_attr->prop_name = "SecureBootMode";
        SecureBootMode_attr->read_only = true;
        SecureBootMode_attr->add_enum("SetupMode");
        SecureBootMode_attr->add_enum("UserMode");
        SecureBootMode_attr->add_enum("AuditMode");
        SecureBootMode_attr->add_enum("DeployedMode");
        add_property_attr("SecureBootMode", SecureBootMode_attr);

        auto SecureBootCurrentBoot_attr = std::make_shared<prop_attribute>();
        SecureBootCurrentBoot_attr->prop_name = "SecureBootCurrentBoot";
        SecureBootCurrentBoot_attr->read_only = true;
        SecureBootCurrentBoot_attr->add_enum("Enabled");
        SecureBootCurrentBoot_attr->add_enum("Disabled");
        add_property_attr("SecureBootCurrentBoot", SecureBootCurrentBoot_attr);

        auto SecureBootEnable_attr = std::make_shared<prop_attribute>();
        SecureBootEnable_attr->prop_name = "SecureBootEnable";
        SecureBootEnable_attr->read_only = false;
        add_property_attr("SecureBootEnable", SecureBootEnable_attr);

     }

};

}}

