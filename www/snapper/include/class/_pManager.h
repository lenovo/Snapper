//---------------------------------------------------------------------
// <copyright file="_pManager.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pManager : public ResourceProvider
{
public:
    _pManager() : ResourceProvider("Manager")    
    {
        enum GraphicalConnectTypesSupported 
        {
            GraphicalConnectTypesSupported_KVMIP,
            GraphicalConnectTypesSupported_Oem,
        };

        enum CommandConnectTypesSupported 
        {
            CommandConnectTypesSupported_SSH,
            CommandConnectTypesSupported_Telnet,
            CommandConnectTypesSupported_IPMI,
            CommandConnectTypesSupported_Oem,
        };

        enum SerialConnectTypesSupported 
        {
            SerialConnectTypesSupported_SSH,
            SerialConnectTypesSupported_Telnet,
            SerialConnectTypesSupported_IPMI,
            SerialConnectTypesSupported_Oem,
        };

        enum ManagerType 
        {
            ManagerType_ManagementController,
            ManagerType_EnclosureManager,
            ManagerType_BMC,
            ManagerType_RackManager,
            ManagerType_AuxiliaryController,
            ManagerType_Service,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("AutoDSTEnabled",  nullptr);
        create_prop("CommandShell",  nullptr);
        create_prop("DateTime",  nullptr);
        create_prop("DateTimeLocalOffset",  nullptr);
        create_prop("EthernetInterfaces",  nullptr);
        create_prop("FirmwareVersion",  nullptr);
        create_prop("GraphicalConsole",  nullptr);
        create_prop("HostInterfaces",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("LogServices",  nullptr);
        create_prop("ManagerType",  nullptr);
        create_prop("Model",  nullptr);
        create_prop("NetworkProtocol",  nullptr);
        create_prop("PowerState",  nullptr);
        create_prop("Redundancy",  nullptr);
        create_prop("Redundancy@odata.count",  nullptr);
        create_prop("Redundancy@odata.navigationLink",  nullptr);
        create_prop("SerialConsole",  nullptr);
        create_prop("SerialInterfaces",  nullptr);
        create_prop("ServiceEntryPointUUID",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("UUID",  nullptr);
        create_prop("VirtualMedia",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Manager.v1_4_0");
        set_desc("This is the schema definition for a Manager.  Examples of managers are BMCs, Enclosure Managers, Management Controllers and other subsystems assigned managability functions.");
    }

    virtual ~_pManager()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_arr_props("Redundancy");
        add_navigation_contained_props("EthernetInterfaces");
        add_navigation_contained_props("NetworkProtocol");
        add_navigation_contained_props("LogServices");
        add_navigation_contained_props("SerialInterfaces");
        add_navigation_contained_props("VirtualMedia");
        add_navigation_refer_props("HostInterfaces");
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["ManagerForChassis"] = nullptr;
        m_Links_prop_objs["ManagerForChassis@odata.count"] = nullptr;
        m_Links_prop_objs["ManagerForChassis@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["ManagerForServers"] = nullptr;
        m_Links_prop_objs["ManagerForServers@odata.count"] = nullptr;
        m_Links_prop_objs["ManagerForServers@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["ManagerForSwitches"] = nullptr;
        m_Links_prop_objs["ManagerForSwitches@odata.count"] = nullptr;
        m_Links_prop_objs["ManagerForSwitches@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["ManagerInChassis"] = nullptr;
        add_Links_arr_props("ManagerForChassis");
        add_Links_arr_props("ManagerForServers");
        add_Links_arr_props("ManagerForSwitches");
    }

    void prepare_OemLenovo()
    {
        create_OemLenovo_prop("@odata.type", std::make_shared<bson::BSONObj>(BSON("@odata.type" << "#LenovoManager.v1_0_0.Lenovo")));
        create_OemLenovo_prop("Configuration", nullptr);
        create_OemLenovo_prop("DateTimeService", nullptr);
        create_OemLenovo_prop("FoD", nullptr);
        create_OemLenovo_prop("RemoteControl", nullptr);
        create_OemLenovo_prop("RemoteMap", nullptr);
        create_OemLenovo_prop("Security", nullptr);
        create_OemLenovo_prop("ServerProfile", nullptr);
        create_OemLenovo_prop("ServiceData", nullptr);
        
        add_property_class("Oem/Lenovo/Configuration", "Navigation Type.Entity", "LenovoConfigurationService");
        add_property_class("Oem/Lenovo/DateTimeService", "Navigation Type.Entity", "LenovoDateTimeService");
        add_property_class("Oem/Lenovo/FoD", "Navigation Type.Entity", "LenovoFoDService");
        add_property_class("Oem/Lenovo/RemoteControl", "Navigation Type.Entity", "LenovoRemoteControlService");
        add_property_class("Oem/Lenovo/RemoteMap", "Navigation Type.Entity", "LenovoRemoteMapService");
        add_property_class("Oem/Lenovo/Security", "Navigation Type.Entity", "LenovoSecurityService");
        add_property_class("Oem/Lenovo/ServerProfile", "Navigation Type.Entity", "LenovoServerProfileService");
        add_property_class("Oem/Lenovo/ServiceData", "Navigation Type.Entity", "LenovoServiceData");
    }

    virtual void set_actions_obj()
    {
         create_prop( "Actions",   std::make_shared<bson::BSONObj>(BSON("Actions" << BSON(
                "#Manager.ModifyRedundancySet"
                << BSON("target" << (get_base_odata_id() + "/Actions/Manager.ModifyRedundancySet")
                << "title" << "ModifyRedundancySet")
                << "#Manager.ForceFailover"
                << BSON("target" << (get_base_odata_id() + "/Actions/Manager.ForceFailover")
                << "title" << "ForceFailover")
                << "#Manager.Reset"
                << BSON("target" << (get_base_odata_id() + "/Actions/Manager.Reset")
                << "title" << "Reset"
                << "ResetType@Redfish.AllowableValues"
                << BSON_ARRAY("On"
                             << "ForceOff"
                             << "GracefulShutdown"
                             << "GracefulRestart"
                             << "ForceRestart"
                             << "Nmi"
                             << "ForceOn"
                             << "PushPowerButton"
                             << "PowerCycle"))
                )
                )) );
     }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("AutoDSTEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("CommandShell", "Complex Type.", "CommandShell");
        add_property_class("DateTime", "Primitive Type.", "Edm.DateTimeOffset");
        add_property_class("DateTimeLocalOffset", "Primitive Type.", "Edm.String");
        add_property_class("EthernetInterfaces", "Navigation Type.Entity", "EthernetInterfaceCollection");
        add_property_class("FirmwareVersion", "Primitive Type.", "Edm.String");
        add_property_class("GraphicalConsole", "Complex Type.", "GraphicalConsole");
        add_property_class("HostInterfaces", "Navigation Type.Entity", "HostInterfaceCollection");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("LogServices", "Navigation Type.Entity", "LogServiceCollection");
        add_property_class("ManagerType", "Enum Type.", "ManagerType");
        add_property_class("Model", "Primitive Type.", "Edm.String");
        add_property_class("NetworkProtocol", "Navigation Type.Entity", "ManagerNetworkProtocol");
        add_property_class("PowerState", "Enum Type.", "PowerState");
        add_property_class("Redundancy", "Navigation Type.Collection", "Redundancy");
        add_property_class("SerialConsole", "Complex Type.", "SerialConsole");
        add_property_class("SerialInterfaces", "Navigation Type.Entity", "SerialInterfaceCollection");
        add_property_class("ServiceEntryPointUUID", "Type Definition.", "Edm.Guid");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("UUID", "Type Definition.", "Edm.Guid");
        add_property_class("VirtualMedia", "Navigation Type.Entity", "VirtualMediaCollection");
    }

    void prep_prop_attrs()
    {
        auto FirmwareVersion_attr = std::make_shared<prop_attribute>();
        FirmwareVersion_attr->prop_name = "FirmwareVersion";
        FirmwareVersion_attr->read_only = true;
        add_property_attr("FirmwareVersion", FirmwareVersion_attr);

        auto DateTimeLocalOffset_attr = std::make_shared<prop_attribute>();
        DateTimeLocalOffset_attr->prop_name = "DateTimeLocalOffset";
        DateTimeLocalOffset_attr->read_only = false;
        add_property_attr("DateTimeLocalOffset", DateTimeLocalOffset_attr);

        auto DateTime_attr = std::make_shared<prop_attribute>();
        DateTime_attr->prop_name = "DateTime";
        DateTime_attr->read_only = false;
        add_property_attr("DateTime", DateTime_attr);

        auto ManagerType_attr = std::make_shared<prop_attribute>();
        ManagerType_attr->prop_name = "ManagerType";
        ManagerType_attr->read_only = true;
        ManagerType_attr->add_enum("ManagementController");
        ManagerType_attr->add_enum("EnclosureManager");
        ManagerType_attr->add_enum("BMC");
        ManagerType_attr->add_enum("RackManager");
        ManagerType_attr->add_enum("AuxiliaryController");
        ManagerType_attr->add_enum("Service");
        add_property_attr("ManagerType", ManagerType_attr);

        auto EthernetInterfaces_attr = std::make_shared<prop_attribute>();
        EthernetInterfaces_attr->prop_name = "EthernetInterfaces";
        EthernetInterfaces_attr->read_only = true;
        add_property_attr("EthernetInterfaces", EthernetInterfaces_attr);

        auto UUID_attr = std::make_shared<prop_attribute>();
        UUID_attr->prop_name = "UUID";
        UUID_attr->read_only = true;
        add_property_attr("UUID", UUID_attr);

        auto NetworkProtocol_attr = std::make_shared<prop_attribute>();
        NetworkProtocol_attr->prop_name = "NetworkProtocol";
        NetworkProtocol_attr->read_only = true;
        add_property_attr("NetworkProtocol", NetworkProtocol_attr);

        auto LogServices_attr = std::make_shared<prop_attribute>();
        LogServices_attr->prop_name = "LogServices";
        LogServices_attr->read_only = true;
        add_property_attr("LogServices", LogServices_attr);

        auto SerialInterfaces_attr = std::make_shared<prop_attribute>();
        SerialInterfaces_attr->prop_name = "SerialInterfaces";
        SerialInterfaces_attr->read_only = true;
        add_property_attr("SerialInterfaces", SerialInterfaces_attr);

        auto VirtualMedia_attr = std::make_shared<prop_attribute>();
        VirtualMedia_attr->prop_name = "VirtualMedia";
        VirtualMedia_attr->read_only = true;
        add_property_attr("VirtualMedia", VirtualMedia_attr);

        auto ServiceEntryPointUUID_attr = std::make_shared<prop_attribute>();
        ServiceEntryPointUUID_attr->prop_name = "ServiceEntryPointUUID";
        ServiceEntryPointUUID_attr->read_only = true;
        add_property_attr("ServiceEntryPointUUID", ServiceEntryPointUUID_attr);

        auto Model_attr = std::make_shared<prop_attribute>();
        Model_attr->prop_name = "Model";
        Model_attr->read_only = true;
        add_property_attr("Model", Model_attr);

        auto PowerState_attr = std::make_shared<prop_attribute>();
        PowerState_attr->prop_name = "PowerState";
        PowerState_attr->read_only = true;
        PowerState_attr->add_enum("On");
        PowerState_attr->add_enum("Off");
        PowerState_attr->add_enum("PoweringOn");
        PowerState_attr->add_enum("PoweringOff");
        add_property_attr("PowerState", PowerState_attr);

        auto HostInterfaces_attr = std::make_shared<prop_attribute>();
        HostInterfaces_attr->prop_name = "HostInterfaces";
        HostInterfaces_attr->read_only = true;
        add_property_attr("HostInterfaces", HostInterfaces_attr);

        auto AutoDSTEnabled_attr = std::make_shared<prop_attribute>();
        AutoDSTEnabled_attr->prop_name = "AutoDSTEnabled";
        AutoDSTEnabled_attr->read_only = false;
        add_property_attr("AutoDSTEnabled", AutoDSTEnabled_attr);

     }

};

}}

