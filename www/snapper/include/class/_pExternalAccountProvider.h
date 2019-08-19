//---------------------------------------------------------------------
// <copyright file="_pExternalAccountProvider.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pExternalAccountProvider : public ResourceProvider
{
public:
    _pExternalAccountProvider() : ResourceProvider("ExternalAccountProvider")    
    {
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

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("AccountProviderType",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Authentication",  nullptr);
        create_prop("LDAPService",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("RemoteRoleMapping",  nullptr);
        create_prop("ServiceAddresses",  nullptr);
        create_prop("ServiceEnabled",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("ExternalAccountProvider.v1_0_0");
        set_desc("A remote service that can provide accounts for this manager to utilize for authentication.");
    }

    virtual ~_pExternalAccountProvider()    
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
        add_property_class("AccountProviderType", "Enum Type.", "AccountProviderTypes");
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("Authentication", "Complex Type.", "Authentication");
        add_property_class("LDAPService", "Complex Type.", "LDAPService");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("RemoteRoleMapping", "Collection Type.", "RoleMapping");
        add_property_class("ServiceAddresses", "Collection Type.", "Edm.String");
        add_property_class("ServiceEnabled", "Primitive Type.", "Edm.Boolean");
    }

    void prep_prop_attrs()
    {
        auto ServiceAddresses_attr = std::make_shared<prop_attribute>();
        ServiceAddresses_attr->prop_name = "ServiceAddresses";
        ServiceAddresses_attr->read_only = false;
        add_property_attr("ServiceAddresses", ServiceAddresses_attr);

        auto ServiceEnabled_attr = std::make_shared<prop_attribute>();
        ServiceEnabled_attr->prop_name = "ServiceEnabled";
        ServiceEnabled_attr->read_only = false;
        add_property_attr("ServiceEnabled", ServiceEnabled_attr);

        auto AccountProviderType_attr = std::make_shared<prop_attribute>();
        AccountProviderType_attr->prop_name = "AccountProviderType";
        AccountProviderType_attr->read_only = true;
        AccountProviderType_attr->add_enum("RedfishService");
        AccountProviderType_attr->add_enum("ActiveDirectoryService");
        AccountProviderType_attr->add_enum("LDAPService");
        AccountProviderType_attr->add_enum("OEM");
        AccountProviderType_attr->required_on_create = true;
        add_property_attr("AccountProviderType", AccountProviderType_attr);

     }

};

}}

