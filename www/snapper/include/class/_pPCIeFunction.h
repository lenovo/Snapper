//---------------------------------------------------------------------
// <copyright file="_pPCIeFunction.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pPCIeFunction : public ResourceProvider
{
public:
    _pPCIeFunction() : ResourceProvider("PCIeFunction")    
    {
        enum FunctionType 
        {
            FunctionType_Physical,
            FunctionType_Virtual,
        };

        enum DeviceClass 
        {
            DeviceClass_UnclassifiedDevice,
            DeviceClass_MassStorageController,
            DeviceClass_NetworkController,
            DeviceClass_DisplayController,
            DeviceClass_MultimediaController,
            DeviceClass_MemoryController,
            DeviceClass_Bridge,
            DeviceClass_CommunicationController,
            DeviceClass_GenericSystemPeripheral,
            DeviceClass_InputDeviceController,
            DeviceClass_DockingStation,
            DeviceClass_Processor,
            DeviceClass_SerialBusController,
            DeviceClass_WirelessController,
            DeviceClass_IntelligentController,
            DeviceClass_SatelliteCommunicationsController,
            DeviceClass_EncryptionController,
            DeviceClass_SignalProcessingController,
            DeviceClass_ProcessingAccelerators,
            DeviceClass_NonEssentialInstrumentation,
            DeviceClass_Coprocessor,
            DeviceClass_UnassignedClass,
            DeviceClass_Other,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("ClassCode",  nullptr);
        create_prop("DeviceClass",  nullptr);
        create_prop("DeviceId",  nullptr);
        create_prop("FunctionId",  nullptr);
        create_prop("FunctionType",  nullptr);
        create_prop("Links",  nullptr);
        create_prop("RevisionId",  nullptr);
        create_prop("Status",  nullptr);
        create_prop("SubsystemId",  nullptr);
        create_prop("SubsystemVendorId",  nullptr);
        create_prop("VendorId",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("PCIeFunction.v1_2_0");
        set_desc("This is the schema definition for the PCIeFunction resource.  It represents the properties of a PCIeFunction attached to a System.");
    }

    virtual ~_pPCIeFunction()    
    {}

    void prepare_navigation_property()
    {
    }

        
    void prepare_Links()
    {
        m_Links_prop_objs["Drives"] = nullptr;
        m_Links_prop_objs["Drives@odata.count"] = nullptr;
        m_Links_prop_objs["Drives@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["EthernetInterfaces"] = nullptr;
        m_Links_prop_objs["EthernetInterfaces@odata.count"] = nullptr;
        m_Links_prop_objs["EthernetInterfaces@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["NetworkDeviceFunctions"] = nullptr;
        m_Links_prop_objs["NetworkDeviceFunctions@odata.count"] = nullptr;
        m_Links_prop_objs["NetworkDeviceFunctions@odata.navigationLink"] = nullptr;
        m_Links_prop_objs["PCIeDevice"] = nullptr;
        m_Links_prop_objs["StorageControllers"] = nullptr;
        m_Links_prop_objs["StorageControllers@odata.count"] = nullptr;
        m_Links_prop_objs["StorageControllers@odata.navigationLink"] = nullptr;
        add_Links_arr_props("Drives");
        add_Links_arr_props("EthernetInterfaces");
        add_Links_arr_props("NetworkDeviceFunctions");
        add_Links_arr_props("StorageControllers");
    }

    void prepare_OemLenovo()
    {
    }

    void prepare_prop_class()
    {
        add_property_class("Actions", "Complex Type.", "Actions");
        add_property_class("ClassCode", "Primitive Type.", "Edm.String");
        add_property_class("DeviceClass", "Enum Type.", "DeviceClass");
        add_property_class("DeviceId", "Primitive Type.", "Edm.String");
        add_property_class("FunctionId", "Primitive Type.", "Edm.Int64");
        add_property_class("FunctionType", "Enum Type.", "FunctionType");
        add_property_class("Links", "Complex Type.", "Links");
        add_property_class("RevisionId", "Primitive Type.", "Edm.String");
        add_property_class("Status", "Complex Type.", "Status");
        add_property_class("SubsystemId", "Primitive Type.", "Edm.String");
        add_property_class("SubsystemVendorId", "Primitive Type.", "Edm.String");
        add_property_class("VendorId", "Primitive Type.", "Edm.String");
    }

    void prep_prop_attrs()
    {
        auto FunctionId_attr = std::make_shared<prop_attribute>();
        FunctionId_attr->prop_name = "FunctionId";
        FunctionId_attr->read_only = true;
        add_property_attr("FunctionId", FunctionId_attr);

        auto FunctionType_attr = std::make_shared<prop_attribute>();
        FunctionType_attr->prop_name = "FunctionType";
        FunctionType_attr->read_only = true;
        FunctionType_attr->add_enum("Physical");
        FunctionType_attr->add_enum("Virtual");
        add_property_attr("FunctionType", FunctionType_attr);

        auto DeviceClass_attr = std::make_shared<prop_attribute>();
        DeviceClass_attr->prop_name = "DeviceClass";
        DeviceClass_attr->read_only = true;
        DeviceClass_attr->add_enum("UnclassifiedDevice");
        DeviceClass_attr->add_enum("MassStorageController");
        DeviceClass_attr->add_enum("NetworkController");
        DeviceClass_attr->add_enum("DisplayController");
        DeviceClass_attr->add_enum("MultimediaController");
        DeviceClass_attr->add_enum("MemoryController");
        DeviceClass_attr->add_enum("Bridge");
        DeviceClass_attr->add_enum("CommunicationController");
        DeviceClass_attr->add_enum("GenericSystemPeripheral");
        DeviceClass_attr->add_enum("InputDeviceController");
        DeviceClass_attr->add_enum("DockingStation");
        DeviceClass_attr->add_enum("Processor");
        DeviceClass_attr->add_enum("SerialBusController");
        DeviceClass_attr->add_enum("WirelessController");
        DeviceClass_attr->add_enum("IntelligentController");
        DeviceClass_attr->add_enum("SatelliteCommunicationsController");
        DeviceClass_attr->add_enum("EncryptionController");
        DeviceClass_attr->add_enum("SignalProcessingController");
        DeviceClass_attr->add_enum("ProcessingAccelerators");
        DeviceClass_attr->add_enum("NonEssentialInstrumentation");
        DeviceClass_attr->add_enum("Coprocessor");
        DeviceClass_attr->add_enum("UnassignedClass");
        DeviceClass_attr->add_enum("Other");
        add_property_attr("DeviceClass", DeviceClass_attr);

        auto VendorId_attr = std::make_shared<prop_attribute>();
        VendorId_attr->prop_name = "VendorId";
        VendorId_attr->read_only = true;
        add_property_attr("VendorId", VendorId_attr);

        auto DeviceId_attr = std::make_shared<prop_attribute>();
        DeviceId_attr->prop_name = "DeviceId";
        DeviceId_attr->read_only = true;
        add_property_attr("DeviceId", DeviceId_attr);

        auto ClassCode_attr = std::make_shared<prop_attribute>();
        ClassCode_attr->prop_name = "ClassCode";
        ClassCode_attr->read_only = true;
        add_property_attr("ClassCode", ClassCode_attr);

        auto RevisionId_attr = std::make_shared<prop_attribute>();
        RevisionId_attr->prop_name = "RevisionId";
        RevisionId_attr->read_only = true;
        add_property_attr("RevisionId", RevisionId_attr);

        auto SubsystemId_attr = std::make_shared<prop_attribute>();
        SubsystemId_attr->prop_name = "SubsystemId";
        SubsystemId_attr->read_only = true;
        add_property_attr("SubsystemId", SubsystemId_attr);

        auto SubsystemVendorId_attr = std::make_shared<prop_attribute>();
        SubsystemVendorId_attr->prop_name = "SubsystemVendorId";
        SubsystemVendorId_attr->read_only = true;
        add_property_attr("SubsystemVendorId", SubsystemVendorId_attr);

     }

};

}}

