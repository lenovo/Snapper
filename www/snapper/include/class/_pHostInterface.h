//---------------------------------------------------------------------
// <copyright file="_pHostInterface.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pHostInterface : public ResourceProvider
{
public:
    _pHostInterface() : ResourceProvider("HostInterface")    
    {
        enum AuthenticationMode 
        {
            AuthenticationMode_AuthNone,
            AuthenticationMode_BasicAuth,
            AuthenticationMode_RedfishSessionAuth,
            AuthenticationMode_OemAuth,
        };

        enum HostInterfaceType 
        {
            HostInterfaceType_NetworkHostInterface,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("AuthenticationModes",  nullptr);
        create_prop("ExternallyAccessible",  nullptr);
        create_prop("FirmwareAuthEnabled",  nullptr);
        create_prop("FirmwareAuthRoleId",  nullptr);
        create_prop("HostEthernetInterfaces",  nullptr);
        create_prop("HostInterfaceType",  nullptr);
        create_prop("InterfaceEnabled",  nullptr);
        create_prop("KernelAuthEnabled",  nullptr);
        create_prop("KernelAuthRoleId",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("ManagerEthernetInterface",  nullptr);
        create_prop("NetworkProtocol",  nullptr);
        create_prop("Status",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("HostInterface.v1_1_2");
        set_desc("This schema defines a single Host Interface resource.");
    }

    virtual ~_pHostInterface()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("HostEthernetInterfaces");
        add_navigation_refer_props("NetworkProtocol");
        add_navigation_refer_props("ManagerEthernetInterface");
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["ComputerSystems"] = nullptr;
        m_Links_prop_objs["ComputerSystems@odata.count"] = nullptr;
        m_Links_prop_objs["ComputerSystems@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["FirmwareAuthRole"] = nullptr;
        m_Links_prop_objs["KernelAuthRole"] = nullptr;
        add_Links_arr_props("ComputerSystems");
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("AuthenticationModes", "Collection Type.", "AuthenticationMode");
        add_property_class("ExternallyAccessible", "Primitive Type.", "Edm.Boolean");
        add_property_class("FirmwareAuthEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("FirmwareAuthRoleId", "Primitive Type.", "Edm.String");
        add_property_class("HostEthernetInterfaces", "Navigation Type.Entity", "EthernetInterfaceCollection");
        add_property_class("HostInterfaceType", "Enum Type.", "HostInterfaceType");
        add_property_class("InterfaceEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("KernelAuthEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("KernelAuthRoleId", "Primitive Type.", "Edm.String");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("ManagerEthernetInterface", "Navigation Type.Entity", "EthernetInterface");
        add_property_class("NetworkProtocol", "Navigation Type.Entity", "ManagerNetworkProtocol");
        add_property_class("Status", "Complex Type.", "Status");
    }

    void prep_prop_attrs()
    {
        auto NetworkProtocol_attr = std::make_shared<prop_attribute>();
        NetworkProtocol_attr->prop_name = "NetworkProtocol";
        NetworkProtocol_attr->read_only = true;
        add_property_attr("NetworkProtocol", NetworkProtocol_attr);

        auto ManagerEthernetInterface_attr = std::make_shared<prop_attribute>();
        ManagerEthernetInterface_attr->prop_name = "ManagerEthernetInterface";
        ManagerEthernetInterface_attr->read_only = true;
        add_property_attr("ManagerEthernetInterface", ManagerEthernetInterface_attr);

        auto ExternallyAccessible_attr = std::make_shared<prop_attribute>();
        ExternallyAccessible_attr->prop_name = "ExternallyAccessible";
        ExternallyAccessible_attr->read_only = true;
        add_property_attr("ExternallyAccessible", ExternallyAccessible_attr);

        auto InterfaceEnabled_attr = std::make_shared<prop_attribute>();
        InterfaceEnabled_attr->prop_name = "InterfaceEnabled";
        InterfaceEnabled_attr->read_only = false;
        add_property_attr("InterfaceEnabled", InterfaceEnabled_attr);

        auto AuthenticationModes_attr = std::make_shared<prop_attribute>();
        AuthenticationModes_attr->prop_name = "AuthenticationModes";
        AuthenticationModes_attr->read_only = false;
        AuthenticationModes_attr->add_enum("AuthNone");
        AuthenticationModes_attr->add_enum("BasicAuth");
        AuthenticationModes_attr->add_enum("RedfishSessionAuth");
        AuthenticationModes_attr->add_enum("OemAuth");
        add_property_attr("AuthenticationModes", AuthenticationModes_attr);

        auto FirmwareAuthEnabled_attr = std::make_shared<prop_attribute>();
        FirmwareAuthEnabled_attr->prop_name = "FirmwareAuthEnabled";
        FirmwareAuthEnabled_attr->read_only = false;
        add_property_attr("FirmwareAuthEnabled", FirmwareAuthEnabled_attr);

        auto KernelAuthEnabled_attr = std::make_shared<prop_attribute>();
        KernelAuthEnabled_attr->prop_name = "KernelAuthEnabled";
        KernelAuthEnabled_attr->read_only = false;
        add_property_attr("KernelAuthEnabled", KernelAuthEnabled_attr);

        auto FirmwareAuthRoleId_attr = std::make_shared<prop_attribute>();
        FirmwareAuthRoleId_attr->prop_name = "FirmwareAuthRoleId";
        FirmwareAuthRoleId_attr->read_only = false;
        add_property_attr("FirmwareAuthRoleId", FirmwareAuthRoleId_attr);

        auto HostInterfaceType_attr = std::make_shared<prop_attribute>();
        HostInterfaceType_attr->prop_name = "HostInterfaceType";
        HostInterfaceType_attr->read_only = true;
        HostInterfaceType_attr->add_enum("NetworkHostInterface");
        add_property_attr("HostInterfaceType", HostInterfaceType_attr);

        auto KernelAuthRoleId_attr = std::make_shared<prop_attribute>();
        KernelAuthRoleId_attr->prop_name = "KernelAuthRoleId";
        KernelAuthRoleId_attr->read_only = false;
        add_property_attr("KernelAuthRoleId", KernelAuthRoleId_attr);

        auto HostEthernetInterfaces_attr = std::make_shared<prop_attribute>();
        HostEthernetInterfaces_attr->prop_name = "HostEthernetInterfaces";
        HostEthernetInterfaces_attr->read_only = true;
        add_property_attr("HostEthernetInterfaces", HostEthernetInterfaces_attr);

     }

};

}}

