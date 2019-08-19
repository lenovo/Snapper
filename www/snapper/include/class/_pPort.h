//---------------------------------------------------------------------
// <copyright file="_pPort.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pPort : public ResourceProvider
{
public:
    _pPort() : ResourceProvider("Port")    
    {
        enum PortType 
        {
            PortType_UpstreamPort,
            PortType_DownstreamPort,
            PortType_InterswitchPort,
            PortType_ManagementPort,
            PortType_BidirectionalPort,
            PortType_UnconfiguredPort,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("CurrentSpeedGbps",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("Location",  nullptr);
        create_prop("MaxSpeedGbps",  nullptr);
        create_prop("PortId",  nullptr);
        create_prop("PortProtocol",  nullptr);
        create_prop("PortType",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("Width",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Port.v1_1_0");
        set_desc("Port contains properties describing a port of a switch.");
    }

    virtual ~_pPort()    
    {}

    void prepare_navigation_property()
    {
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["AssociatedEndpoints"] = nullptr;
        m_Links_prop_objs["AssociatedEndpoints@odata.count"] = nullptr;
        m_Links_prop_objs["AssociatedEndpoints@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["ConnectedSwitchPorts"] = nullptr;
        m_Links_prop_objs["ConnectedSwitchPorts@odata.count"] = nullptr;
        m_Links_prop_objs["ConnectedSwitchPorts@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["ConnectedSwitches"] = nullptr;
        m_Links_prop_objs["ConnectedSwitches@odata.count"] = nullptr;
        m_Links_prop_objs["ConnectedSwitches@odata.navigationLink"] = nullptr;
        add_Links_arr_props("AssociatedEndpoints");
        add_Links_arr_props("ConnectedSwitchPorts");
        add_Links_arr_props("ConnectedSwitches");
    }

    void prepare_OemLenovo()
    {
    }

    virtual void set_actions_obj()
    {
         create_prop( "Actions",   std::make_shared<bson::BSONObj>(BSON("Actions" << BSON(
                "#Port.Reset"
                << BSON("target" << (get_base_odata_id() + "/Actions/Port.Reset")
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
        add_property_class("CurrentSpeedGbps", "Primitive Type.", "Edm.Decimal");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("Location", "Complex Type.", "Location");
        add_property_class("MaxSpeedGbps", "Primitive Type.", "Edm.Decimal");
        add_property_class("PortId", "Primitive Type.", "Edm.String");
        add_property_class("PortProtocol", "Enum Type.", "Protocol");
        add_property_class("PortType", "Enum Type.", "PortType");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("Width", "Primitive Type.", "Edm.Int64");
    }

    void prep_prop_attrs()
    {
        auto MaxSpeedGbps_attr = std::make_shared<prop_attribute>();
        MaxSpeedGbps_attr->prop_name = "MaxSpeedGbps";
        MaxSpeedGbps_attr->read_only = true;
        add_property_attr("MaxSpeedGbps", MaxSpeedGbps_attr);

        auto Width_attr = std::make_shared<prop_attribute>();
        Width_attr->prop_name = "Width";
        Width_attr->read_only = true;
        add_property_attr("Width", Width_attr);

        auto CurrentSpeedGbps_attr = std::make_shared<prop_attribute>();
        CurrentSpeedGbps_attr->prop_name = "CurrentSpeedGbps";
        CurrentSpeedGbps_attr->read_only = true;
        add_property_attr("CurrentSpeedGbps", CurrentSpeedGbps_attr);

        auto PortType_attr = std::make_shared<prop_attribute>();
        PortType_attr->prop_name = "PortType";
        PortType_attr->read_only = true;
        PortType_attr->add_enum("UpstreamPort");
        PortType_attr->add_enum("DownstreamPort");
        PortType_attr->add_enum("InterswitchPort");
        PortType_attr->add_enum("ManagementPort");
        PortType_attr->add_enum("BidirectionalPort");
        PortType_attr->add_enum("UnconfiguredPort");
        add_property_attr("PortType", PortType_attr);

        auto PortProtocol_attr = std::make_shared<prop_attribute>();
        PortProtocol_attr->prop_name = "PortProtocol";
        PortProtocol_attr->read_only = true;
        PortProtocol_attr->add_enum("PCIe");
        PortProtocol_attr->add_enum("AHCI");
        PortProtocol_attr->add_enum("UHCI");
        PortProtocol_attr->add_enum("SAS");
        PortProtocol_attr->add_enum("SATA");
        PortProtocol_attr->add_enum("USB");
        PortProtocol_attr->add_enum("NVMe");
        PortProtocol_attr->add_enum("FC");
        PortProtocol_attr->add_enum("iSCSI");
        PortProtocol_attr->add_enum("FCoE");
        PortProtocol_attr->add_enum("FCP");
        PortProtocol_attr->add_enum("FICON");
        PortProtocol_attr->add_enum("NVMeOverFabrics");
        PortProtocol_attr->add_enum("SMB");
        PortProtocol_attr->add_enum("NFSv3");
        PortProtocol_attr->add_enum("NFSv4");
        PortProtocol_attr->add_enum("HTTP");
        PortProtocol_attr->add_enum("HTTPS");
        PortProtocol_attr->add_enum("FTP");
        PortProtocol_attr->add_enum("SFTP");
        PortProtocol_attr->add_enum("iWARP");
        PortProtocol_attr->add_enum("RoCE");
        PortProtocol_attr->add_enum("RoCEv2");
        PortProtocol_attr->add_enum("OEM");
        add_property_attr("PortProtocol", PortProtocol_attr);

        auto PortId_attr = std::make_shared<prop_attribute>();
        PortId_attr->prop_name = "PortId";
        PortId_attr->read_only = true;
        add_property_attr("PortId", PortId_attr);

     }

};

}}

