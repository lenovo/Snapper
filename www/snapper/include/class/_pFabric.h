//---------------------------------------------------------------------
// <copyright file="_pFabric.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pFabric : public ResourceProvider
{
public:
    _pFabric() : ResourceProvider("Fabric")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("Endpoints",  nullptr);
        create_prop("FabricType",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("MaxZones",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("Switches",  nullptr);
        create_prop("Zones",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Fabric.v1_0_3");
        set_desc("The Fabric schema represents a simple fabric consisting of one or more switches, zero or more endpoints, and zero or more zones.");
    }

    virtual ~_pFabric()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("Switches");
        add_navigation_contained_props("Endpoints");
        add_navigation_contained_props("Zones");
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
        add_property_class("Endpoints", "Navigation Type.Entity", "EndpointCollection");
        add_property_class("FabricType", "Enum Type.", "Protocol");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("MaxZones", "Primitive Type.", "Edm.Int64");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("Switches", "Navigation Type.Entity", "SwitchCollection");
        add_property_class("Zones", "Navigation Type.Entity", "ZoneCollection");
    }

    void prep_prop_attrs()
    {
        auto Switches_attr = std::make_shared<prop_attribute>();
        Switches_attr->prop_name = "Switches";
        Switches_attr->read_only = true;
        add_property_attr("Switches", Switches_attr);

        auto Endpoints_attr = std::make_shared<prop_attribute>();
        Endpoints_attr->prop_name = "Endpoints";
        Endpoints_attr->read_only = true;
        add_property_attr("Endpoints", Endpoints_attr);

        auto Zones_attr = std::make_shared<prop_attribute>();
        Zones_attr->prop_name = "Zones";
        Zones_attr->read_only = true;
        add_property_attr("Zones", Zones_attr);

        auto MaxZones_attr = std::make_shared<prop_attribute>();
        MaxZones_attr->prop_name = "MaxZones";
        MaxZones_attr->read_only = true;
        add_property_attr("MaxZones", MaxZones_attr);

        auto FabricType_attr = std::make_shared<prop_attribute>();
        FabricType_attr->prop_name = "FabricType";
        FabricType_attr->read_only = true;
        FabricType_attr->add_enum("PCIe");
        FabricType_attr->add_enum("AHCI");
        FabricType_attr->add_enum("UHCI");
        FabricType_attr->add_enum("SAS");
        FabricType_attr->add_enum("SATA");
        FabricType_attr->add_enum("USB");
        FabricType_attr->add_enum("NVMe");
        FabricType_attr->add_enum("FC");
        FabricType_attr->add_enum("iSCSI");
        FabricType_attr->add_enum("FCoE");
        FabricType_attr->add_enum("FCP");
        FabricType_attr->add_enum("FICON");
        FabricType_attr->add_enum("NVMeOverFabrics");
        FabricType_attr->add_enum("SMB");
        FabricType_attr->add_enum("NFSv3");
        FabricType_attr->add_enum("NFSv4");
        FabricType_attr->add_enum("HTTP");
        FabricType_attr->add_enum("HTTPS");
        FabricType_attr->add_enum("FTP");
        FabricType_attr->add_enum("SFTP");
        FabricType_attr->add_enum("iWARP");
        FabricType_attr->add_enum("RoCE");
        FabricType_attr->add_enum("RoCEv2");
        FabricType_attr->add_enum("OEM");
        add_property_attr("FabricType", FabricType_attr);

     }

};

}}

