//---------------------------------------------------------------------
// <copyright file="_pServiceRoot.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pServiceRoot : public ResourceProvider
{
public:
    _pServiceRoot() : ResourceProvider("ServiceRoot")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("AccountService",  nullptr);
        create_prop("Chassis",  nullptr);
        create_prop("CompositionService",  nullptr);
        create_prop("EventService",  nullptr);
        create_prop("Fabrics",  nullptr);
        create_prop("JsonSchemas",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("Managers",  nullptr);
        create_prop("Product",  nullptr);
        create_prop("ProtocolFeaturesSupported",  nullptr);
        create_prop("RedfishVersion",  nullptr);
        create_prop("Registries",  nullptr);
        create_prop("SessionService",  nullptr);
        create_prop("StorageServices",  nullptr);
        create_prop("StorageSystems",  nullptr);
        create_prop("Systems",  nullptr);
        create_prop("Tasks",  nullptr);
        create_prop("UUID",  nullptr);
        create_prop("UpdateService",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("ServiceRoot.v1_3_1");
        set_desc("This object represents the root Redfish service.");
    }

    virtual ~_pServiceRoot()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("Managers");
        add_navigation_contained_props("JsonSchemas");
        add_navigation_contained_props("EventService");
        add_navigation_contained_props("Chassis");
        add_navigation_contained_props("Tasks");
        add_navigation_contained_props("SessionService");
        add_navigation_contained_props("AccountService");
        add_navigation_contained_props("Systems");
        add_navigation_contained_props("Registries");
        add_navigation_contained_props("UpdateService");
        add_navigation_contained_props("Fabrics");
        add_navigation_contained_props("StorageServices");
        add_navigation_contained_props("StorageSystems");
        add_navigation_refer_props("CompositionService");
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["Sessions"] = nullptr;
    }

    void prepare_OemLenovo()
    {
        create_OemLenovo_prop("@odata.type", std::make_shared<bson::BSONObj>(BSON("@odata.type" << "#LenovoServiceRoot.v1_0_0.Lenovo")));
        create_OemLenovo_prop("FirmwareServices", nullptr);
        
        add_property_class("Oem/Lenovo/FirmwareServices", "Navigation Type.Entity", "LenovoFirmwareServiceCollection");
    }

    void prepare_prop_class()
    {
        add_property_class("AccountService", "Navigation Type.Entity", "AccountService");
        add_property_class("Chassis", "Navigation Type.Entity", "ChassisCollection");
        add_property_class("CompositionService", "Navigation Type.Entity", "CompositionService");
        add_property_class("EventService", "Navigation Type.Entity", "EventService");
        add_property_class("Fabrics", "Navigation Type.Entity", "FabricCollection");
        add_property_class("JsonSchemas", "Navigation Type.Entity", "JsonSchemaFileCollection");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("Managers", "Navigation Type.Entity", "ManagerCollection");
        add_property_class("Product", "Primitive Type.", "Edm.String");
        add_property_class("ProtocolFeaturesSupported", "Complex Type.", "ProtocolFeaturesSupported");
        add_property_class("RedfishVersion", "Primitive Type.", "Edm.String");
        add_property_class("Registries", "Navigation Type.Entity", "MessageRegistryFileCollection");
        add_property_class("SessionService", "Navigation Type.Entity", "SessionService");
        add_property_class("StorageServices", "Navigation Type.", "StorageServiceCollection.StorageServiceCollection");
        add_property_class("StorageSystems", "Navigation Type.", "StorageSystemCollection.StorageSystemCollection");
        add_property_class("Systems", "Navigation Type.Entity", "ComputerSystemCollection");
        add_property_class("Tasks", "Navigation Type.Entity", "TaskService");
        add_property_class("UUID", "Type Definition.", "Edm.Guid");
        add_property_class("UpdateService", "Navigation Type.Entity", "UpdateService");
    }

    void prep_prop_attrs()
    {
        auto RedfishVersion_attr = std::make_shared<prop_attribute>();
        RedfishVersion_attr->prop_name = "RedfishVersion";
        RedfishVersion_attr->read_only = true;
        add_property_attr("RedfishVersion", RedfishVersion_attr);

        auto Managers_attr = std::make_shared<prop_attribute>();
        Managers_attr->prop_name = "Managers";
        Managers_attr->read_only = true;
        add_property_attr("Managers", Managers_attr);

        auto UUID_attr = std::make_shared<prop_attribute>();
        UUID_attr->prop_name = "UUID";
        UUID_attr->read_only = true;
        add_property_attr("UUID", UUID_attr);

        auto JsonSchemas_attr = std::make_shared<prop_attribute>();
        JsonSchemas_attr->prop_name = "JsonSchemas";
        JsonSchemas_attr->read_only = true;
        add_property_attr("JsonSchemas", JsonSchemas_attr);

        auto EventService_attr = std::make_shared<prop_attribute>();
        EventService_attr->prop_name = "EventService";
        EventService_attr->read_only = true;
        add_property_attr("EventService", EventService_attr);

        auto Chassis_attr = std::make_shared<prop_attribute>();
        Chassis_attr->prop_name = "Chassis";
        Chassis_attr->read_only = true;
        add_property_attr("Chassis", Chassis_attr);

        auto Tasks_attr = std::make_shared<prop_attribute>();
        Tasks_attr->prop_name = "Tasks";
        Tasks_attr->read_only = true;
        add_property_attr("Tasks", Tasks_attr);

        auto SessionService_attr = std::make_shared<prop_attribute>();
        SessionService_attr->prop_name = "SessionService";
        SessionService_attr->read_only = true;
        add_property_attr("SessionService", SessionService_attr);

        auto AccountService_attr = std::make_shared<prop_attribute>();
        AccountService_attr->prop_name = "AccountService";
        AccountService_attr->read_only = true;
        add_property_attr("AccountService", AccountService_attr);

        auto Systems_attr = std::make_shared<prop_attribute>();
        Systems_attr->prop_name = "Systems";
        Systems_attr->read_only = true;
        add_property_attr("Systems", Systems_attr);

        auto Registries_attr = std::make_shared<prop_attribute>();
        Registries_attr->prop_name = "Registries";
        Registries_attr->read_only = true;
        add_property_attr("Registries", Registries_attr);

        auto UpdateService_attr = std::make_shared<prop_attribute>();
        UpdateService_attr->prop_name = "UpdateService";
        UpdateService_attr->read_only = true;
        add_property_attr("UpdateService", UpdateService_attr);

        auto Fabrics_attr = std::make_shared<prop_attribute>();
        Fabrics_attr->prop_name = "Fabrics";
        Fabrics_attr->read_only = true;
        add_property_attr("Fabrics", Fabrics_attr);

        auto StorageServices_attr = std::make_shared<prop_attribute>();
        StorageServices_attr->prop_name = "StorageServices";
        StorageServices_attr->read_only = true;
        add_property_attr("StorageServices", StorageServices_attr);

        auto StorageSystems_attr = std::make_shared<prop_attribute>();
        StorageSystems_attr->prop_name = "StorageSystems";
        StorageSystems_attr->read_only = true;
        add_property_attr("StorageSystems", StorageSystems_attr);

        auto CompositionService_attr = std::make_shared<prop_attribute>();
        CompositionService_attr->prop_name = "CompositionService";
        CompositionService_attr->read_only = true;
        add_property_attr("CompositionService", CompositionService_attr);

        auto Product_attr = std::make_shared<prop_attribute>();
        Product_attr->prop_name = "Product";
        Product_attr->read_only = true;
        add_property_attr("Product", Product_attr);

     }

};

}}

