//---------------------------------------------------------------------
// <copyright file="_pRole.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pRole : public ResourceProvider
{
public:
    _pRole() : ResourceProvider("Role")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("AssignedPrivileges",  nullptr);
        create_prop("IsPredefined",  nullptr);
        create_prop("OemPrivileges",  nullptr);
        create_prop("RoleId",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Role.v1_2_1");
        set_desc("This resource defines a user role to be used in conjunction with a Manager Account.");
    }

    virtual ~_pRole()    
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
        add_property_class("AssignedPrivileges", "Collection Type.", "PrivilegeType");
        add_property_class("IsPredefined", "Primitive Type.", "Edm.Boolean");
        add_property_class("OemPrivileges", "Collection Type.", "Edm.String");
        add_property_class("RoleId", "Primitive Type.", "Edm.String");
    }

    void prep_prop_attrs()
    {
        auto AssignedPrivileges_attr = std::make_shared<prop_attribute>();
        AssignedPrivileges_attr->prop_name = "AssignedPrivileges";
        AssignedPrivileges_attr->read_only = false;
        AssignedPrivileges_attr->add_enum("Login");
        AssignedPrivileges_attr->add_enum("ConfigureManager");
        AssignedPrivileges_attr->add_enum("ConfigureUsers");
        AssignedPrivileges_attr->add_enum("ConfigureSelf");
        AssignedPrivileges_attr->add_enum("ConfigureComponents");
        add_property_attr("AssignedPrivileges", AssignedPrivileges_attr);

        auto OemPrivileges_attr = std::make_shared<prop_attribute>();
        OemPrivileges_attr->prop_name = "OemPrivileges";
        OemPrivileges_attr->read_only = false;
        add_property_attr("OemPrivileges", OemPrivileges_attr);

        auto IsPredefined_attr = std::make_shared<prop_attribute>();
        IsPredefined_attr->prop_name = "IsPredefined";
        IsPredefined_attr->read_only = true;
        add_property_attr("IsPredefined", IsPredefined_attr);

        auto RoleId_attr = std::make_shared<prop_attribute>();
        RoleId_attr->prop_name = "RoleId";
        RoleId_attr->read_only = true;
        RoleId_attr->required_on_create = true;
        add_property_attr("RoleId", RoleId_attr);

     }

};

}}

