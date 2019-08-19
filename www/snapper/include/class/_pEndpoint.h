//---------------------------------------------------------------------
// <copyright file="_pEndpoint.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pEndpoint : public ResourceProvider
{
public:
    _pEndpoint() : ResourceProvider("Endpoint")    
    {
        enum EntityRole 
        {
            EntityRole_Initiator,
            EntityRole_Target,
            EntityRole_Both,
        };

        enum EntityType 
        {
            EntityType_StorageInitiator,
            EntityType_RootComplex,
            EntityType_NetworkController,
            EntityType_Drive,
            EntityType_StorageExpander,
            EntityType_DisplayController,
            EntityType_Bridge,
            EntityType_Processor,
            EntityType_Volume,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("ConnectedEntities",  nullptr);
        create_prop("EndpointProtocol",  nullptr);
        create_prop("HostReservationMemoryBytes",  nullptr);
        create_prop("IPTransportDetails",  nullptr);
        create_prop("Identifiers",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("PciId",  nullptr);
        create_prop("Redundancy",  nullptr);
        create_prop("Redundancy@odata.count",  nullptr);
        create_prop("Redundancy@odata.navigationLink",  nullptr);
        create_prop("Status",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("Endpoint.v1_1_0");
        set_desc("This is the schema definition for the Endpoint resource. It represents the properties of an entity that sends or receives protocol defined messages over a transport.");
    }

    virtual ~_pEndpoint()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_arr_props("Redundancy");
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["MutuallyExclusiveEndpoints"] = nullptr;
        m_Links_prop_objs["MutuallyExclusiveEndpoints@odata.count"] = nullptr;
        m_Links_prop_objs["MutuallyExclusiveEndpoints@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["NetworkDeviceFunction"] = nullptr;
        m_Links_prop_objs["NetworkDeviceFunction@odata.count"] = nullptr;
        m_Links_prop_objs["NetworkDeviceFunction@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["Ports"] = nullptr;
        m_Links_prop_objs["Ports@odata.count"] = nullptr;
        m_Links_prop_objs["Ports@odata.navigationLink"] = nullptr;
        add_Links_arr_props("MutuallyExclusiveEndpoints");
        add_Links_arr_props("NetworkDeviceFunction");
        add_Links_arr_props("Ports");
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("ConnectedEntities", "Collection Type.", "ConnectedEntity");
        add_property_class("EndpointProtocol", "Enum Type.", "Protocol");
        add_property_class("HostReservationMemoryBytes", "Primitive Type.", "Edm.Int64");
        add_property_class("IPTransportDetails", "Collection Type.", "IPTransportDetails");
        add_property_class("Identifiers", "Collection Type.", "Identifier");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("PciId", "Complex Type.", "PciId");
        add_property_class("Redundancy", "Navigation Type.Collection", "Redundancy");
        add_property_class("Status", "Complex Type.", "Status");
    }

    void prep_prop_attrs()
    {
        auto HostReservationMemoryBytes_attr = std::make_shared<prop_attribute>();
        HostReservationMemoryBytes_attr->prop_name = "HostReservationMemoryBytes";
        HostReservationMemoryBytes_attr->read_only = true;
        add_property_attr("HostReservationMemoryBytes", HostReservationMemoryBytes_attr);

        auto EndpointProtocol_attr = std::make_shared<prop_attribute>();
        EndpointProtocol_attr->prop_name = "EndpointProtocol";
        EndpointProtocol_attr->read_only = true;
        EndpointProtocol_attr->add_enum("PCIe");
        EndpointProtocol_attr->add_enum("AHCI");
        EndpointProtocol_attr->add_enum("UHCI");
        EndpointProtocol_attr->add_enum("SAS");
        EndpointProtocol_attr->add_enum("SATA");
        EndpointProtocol_attr->add_enum("USB");
        EndpointProtocol_attr->add_enum("NVMe");
        EndpointProtocol_attr->add_enum("FC");
        EndpointProtocol_attr->add_enum("iSCSI");
        EndpointProtocol_attr->add_enum("FCoE");
        EndpointProtocol_attr->add_enum("FCP");
        EndpointProtocol_attr->add_enum("FICON");
        EndpointProtocol_attr->add_enum("NVMeOverFabrics");
        EndpointProtocol_attr->add_enum("SMB");
        EndpointProtocol_attr->add_enum("NFSv3");
        EndpointProtocol_attr->add_enum("NFSv4");
        EndpointProtocol_attr->add_enum("HTTP");
        EndpointProtocol_attr->add_enum("HTTPS");
        EndpointProtocol_attr->add_enum("FTP");
        EndpointProtocol_attr->add_enum("SFTP");
        EndpointProtocol_attr->add_enum("iWARP");
        EndpointProtocol_attr->add_enum("RoCE");
        EndpointProtocol_attr->add_enum("RoCEv2");
        EndpointProtocol_attr->add_enum("OEM");
        add_property_attr("EndpointProtocol", EndpointProtocol_attr);

     }

};

}}

