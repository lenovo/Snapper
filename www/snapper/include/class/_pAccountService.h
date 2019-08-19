//---------------------------------------------------------------------
// <copyright file="_pAccountService.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pAccountService : public ResourceProvider
{
public:
    _pAccountService() : ResourceProvider("AccountService")    
    {
        enum AuthMode 
        {
            AuthMode_LocalOnly,
            AuthMode_LDAPOnly,
            AuthMode_LocalFirstThenLDAP,
            AuthMode_LDAPFirstThenLocal,
        };

        enum AuthenticationTypes 
        {
            AuthenticationTypes_Token,
            AuthenticationTypes_KerberosKeytab,
            AuthenticationTypes_UsernameAndPassword,
            AuthenticationTypes_OEM,
        };

        enum AccountProviderTypes 
        {
            AccountProviderTypes_RedfishService,
            AccountProviderTypes_ActiveDirectoryService,
            AccountProviderTypes_LDAPService,
            AccountProviderTypes_OEM,
        };

        enum LocalAccountAuth 
        {
            LocalAccountAuth_Enabled,
            LocalAccountAuth_Disabled,
            LocalAccountAuth_Fallback,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("AccountLockoutCounterResetAfter",  nullptr);
        create_prop("AccountLockoutDuration",  nullptr);
        create_prop("AccountLockoutThreshold",  nullptr);
        create_prop("Accounts",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("ActiveDirectory",  nullptr);
        create_prop("AdditionalExternalAccountProviders",  nullptr);
        create_prop("AuthFailureLoggingThreshold",  nullptr);
        create_prop("LDAP",  nullptr);
        create_prop("LocalAccountAuth",  nullptr);
        create_prop("MaxPasswordLength",  nullptr);
        create_prop("MinPasswordLength",  nullptr);
        create_prop("PrivilegeMap",  nullptr);
        create_prop("Roles",  nullptr);
        create_prop("ServiceEnabled",  nullptr);
        create_prop("Status",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("AccountService.v1_3_0");
        set_desc("The AccountService schema contains properties for managing user accounts. The properties are common to all user accounts, such as password requirements, and control features such as account lockout. The schema also contains links to the collections of Manager Accounts and Roles.");
    }

    virtual ~_pAccountService()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("Accounts");
        add_navigation_contained_props("Roles");
        add_navigation_contained_props("PrivilegeMap");
        add_navigation_contained_props("AdditionalExternalAccountProviders");
    }

        
    void prepare_Links()
    {
    }

    void prepare_OemLenovo()
    {
        create_OemLenovo_prop("@odata.type", std::make_shared<bson::BSONObj>(BSON("@odata.type" << "#LenovoAccountService.v1_0_0.Lenovo")));
        create_OemLenovo_prop("AuthenticationMethod", nullptr);
        create_OemLenovo_prop("MinimumPasswordChangeIntervalHours", nullptr);
        create_OemLenovo_prop("MinimumPasswordLength", nullptr);
        create_OemLenovo_prop("MinimumPasswordReuseCycle", nullptr);
        create_OemLenovo_prop("PasswordChangeOnFirstAccess", nullptr);
        create_OemLenovo_prop("PasswordChangeOnNextLogin", nullptr);
        create_OemLenovo_prop("PasswordExpirationPeriodDays", nullptr);
        create_OemLenovo_prop("PasswordExpirationWarningPeriod", nullptr);
        create_OemLenovo_prop("WebInactivitySessionTimeout", nullptr);
        
        add_property_class("Oem/Lenovo/AuthenticationMethod", "Enum Type.", "AuthMode");
        add_property_class("Oem/Lenovo/MinimumPasswordChangeIntervalHours", "Primitive Type.", "Edm.Int64");
        add_property_class("Oem/Lenovo/MinimumPasswordLength", "Primitive Type.", "Edm.Int64");
        add_property_class("Oem/Lenovo/MinimumPasswordReuseCycle", "Primitive Type.", "Edm.Int64");
        add_property_class("Oem/Lenovo/PasswordChangeOnFirstAccess", "Primitive Type.", "Edm.Boolean");
        add_property_class("Oem/Lenovo/PasswordChangeOnNextLogin", "Primitive Type.", "Edm.Boolean");
        add_property_class("Oem/Lenovo/PasswordExpirationPeriodDays", "Primitive Type.", "Edm.Int64");
        add_property_class("Oem/Lenovo/PasswordExpirationWarningPeriod", "Primitive Type.", "Edm.Int64");
        add_property_class("Oem/Lenovo/WebInactivitySessionTimeout", "Primitive Type.", "Edm.Int64");
    }

    void prepare_prop_class()
    {
        add_property_class("AccountLockoutCounterResetAfter", "Primitive Type.", "Edm.Int64");
        add_property_class("AccountLockoutDuration", "Primitive Type.", "Edm.Int64");
        add_property_class("AccountLockoutThreshold", "Primitive Type.", "Edm.Int64");
        add_property_class("Accounts", "Navigation Type.Entity", "ManagerAccountCollection");
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("ActiveDirectory", "Complex Type.", "ExternalAccountProvider");
        add_property_class("AdditionalExternalAccountProviders", "Navigation Type.Entity", "ExternalAccountProviderCollection");
        add_property_class("AuthFailureLoggingThreshold", "Primitive Type.", "Edm.Int64");
        add_property_class("LDAP", "Complex Type.", "ExternalAccountProvider");
        add_property_class("LocalAccountAuth", "Enum Type.", "LocalAccountAuth");
        add_property_class("MaxPasswordLength", "Primitive Type.", "Edm.Int64");
        add_property_class("MinPasswordLength", "Primitive Type.", "Edm.Int64");
        add_property_class("PrivilegeMap", "Navigation Type.Entity", "PrivilegeRegistry");
        add_property_class("Roles", "Navigation Type.Entity", "RoleCollection");
        add_property_class("ServiceEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("Status", "Complex Type.", "Status");
    }

    void prep_prop_attrs()
    {
        auto Accounts_attr = std::make_shared<prop_attribute>();
        Accounts_attr->prop_name = "Accounts";
        Accounts_attr->read_only = true;
        add_property_attr("Accounts", Accounts_attr);

        auto AccountLockoutCounterResetAfter_attr = std::make_shared<prop_attribute>();
        AccountLockoutCounterResetAfter_attr->prop_name = "AccountLockoutCounterResetAfter";
        AccountLockoutCounterResetAfter_attr->read_only = false;
        add_property_attr("AccountLockoutCounterResetAfter", AccountLockoutCounterResetAfter_attr);

        auto AccountLockoutThreshold_attr = std::make_shared<prop_attribute>();
        AccountLockoutThreshold_attr->prop_name = "AccountLockoutThreshold";
        AccountLockoutThreshold_attr->read_only = false;
        add_property_attr("AccountLockoutThreshold", AccountLockoutThreshold_attr);

        auto MaxPasswordLength_attr = std::make_shared<prop_attribute>();
        MaxPasswordLength_attr->prop_name = "MaxPasswordLength";
        MaxPasswordLength_attr->read_only = true;
        add_property_attr("MaxPasswordLength", MaxPasswordLength_attr);

        auto AccountLockoutDuration_attr = std::make_shared<prop_attribute>();
        AccountLockoutDuration_attr->prop_name = "AccountLockoutDuration";
        AccountLockoutDuration_attr->read_only = false;
        add_property_attr("AccountLockoutDuration", AccountLockoutDuration_attr);

        auto MinPasswordLength_attr = std::make_shared<prop_attribute>();
        MinPasswordLength_attr->prop_name = "MinPasswordLength";
        MinPasswordLength_attr->read_only = true;
        add_property_attr("MinPasswordLength", MinPasswordLength_attr);

        auto AuthFailureLoggingThreshold_attr = std::make_shared<prop_attribute>();
        AuthFailureLoggingThreshold_attr->prop_name = "AuthFailureLoggingThreshold";
        AuthFailureLoggingThreshold_attr->read_only = false;
        add_property_attr("AuthFailureLoggingThreshold", AuthFailureLoggingThreshold_attr);

        auto Roles_attr = std::make_shared<prop_attribute>();
        Roles_attr->prop_name = "Roles";
        Roles_attr->read_only = true;
        add_property_attr("Roles", Roles_attr);

        auto ServiceEnabled_attr = std::make_shared<prop_attribute>();
        ServiceEnabled_attr->prop_name = "ServiceEnabled";
        ServiceEnabled_attr->read_only = false;
        add_property_attr("ServiceEnabled", ServiceEnabled_attr);

        auto PrivilegeMap_attr = std::make_shared<prop_attribute>();
        PrivilegeMap_attr->prop_name = "PrivilegeMap";
        PrivilegeMap_attr->read_only = true;
        add_property_attr("PrivilegeMap", PrivilegeMap_attr);

        auto AdditionalExternalAccountProviders_attr = std::make_shared<prop_attribute>();
        AdditionalExternalAccountProviders_attr->prop_name = "AdditionalExternalAccountProviders";
        AdditionalExternalAccountProviders_attr->read_only = true;
        add_property_attr("AdditionalExternalAccountProviders", AdditionalExternalAccountProviders_attr);

        auto LocalAccountAuth_attr = std::make_shared<prop_attribute>();
        LocalAccountAuth_attr->prop_name = "LocalAccountAuth";
        LocalAccountAuth_attr->read_only = false;
        LocalAccountAuth_attr->add_enum("Enabled");
        LocalAccountAuth_attr->add_enum("Disabled");
        LocalAccountAuth_attr->add_enum("Fallback");
        add_property_attr("LocalAccountAuth", LocalAccountAuth_attr);

     }

};

}}

