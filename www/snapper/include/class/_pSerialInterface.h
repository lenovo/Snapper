//---------------------------------------------------------------------
// <copyright file="_pSerialInterface.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pSerialInterface : public ResourceProvider
{
public:
    _pSerialInterface() : ResourceProvider("SerialInterface")    
    {
        enum PinOut 
        {
            PinOut_Cisco,
            PinOut_Cyclades,
            PinOut_Digi,
        };

        enum FlowControl 
        {
            FlowControl_None,
            FlowControl_Software,
            FlowControl_Hardware,
        };

        enum Parity 
        {
            Parity_None,
            Parity_Even,
            Parity_Odd,
            Parity_Mark,
            Parity_Space,
        };

        enum SignalType 
        {
            SignalType_Rs232,
            SignalType_Rs485,
        };

        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("BitRate",  nullptr);
        create_prop("ConnectorType",  nullptr);
        create_prop("DataBits",  nullptr);
        create_prop("FlowControl",  nullptr);
        create_prop("InterfaceEnabled",  nullptr);
        create_prop("Parity",  nullptr);
        create_prop("PinOut",  nullptr);
        create_prop("SignalType",  nullptr);
        create_prop("StopBits",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("SerialInterface.v1_1_2");
        set_desc("This schema defines an asynchronous serial interface resource.");
    }

    virtual ~_pSerialInterface()    
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
        add_property_class("BitRate", "Type Definition.", "Edm.String");
        add_property_class("ConnectorType", "Type Definition.", "Edm.String");
        add_property_class("DataBits", "Type Definition.", "Edm.String");
        add_property_class("FlowControl", "Enum Type.", "FlowControl");
        add_property_class("InterfaceEnabled", "Primitive Type.", "Edm.Boolean");
        add_property_class("Parity", "Enum Type.", "Parity");
        add_property_class("PinOut", "Enum Type.", "PinOut");
        add_property_class("SignalType", "Enum Type.", "SignalType");
        add_property_class("StopBits", "Type Definition.", "Edm.String");
    }

    void prep_prop_attrs()
    {
        auto ConnectorType_attr = std::make_shared<prop_attribute>();
        ConnectorType_attr->prop_name = "ConnectorType";
        ConnectorType_attr->read_only = true;
        add_property_attr("ConnectorType", ConnectorType_attr);

        auto PinOut_attr = std::make_shared<prop_attribute>();
        PinOut_attr->prop_name = "PinOut";
        PinOut_attr->read_only = true;
        PinOut_attr->add_enum("Cisco");
        PinOut_attr->add_enum("Cyclades");
        PinOut_attr->add_enum("Digi");
        add_property_attr("PinOut", PinOut_attr);

        auto FlowControl_attr = std::make_shared<prop_attribute>();
        FlowControl_attr->prop_name = "FlowControl";
        FlowControl_attr->read_only = false;
        FlowControl_attr->add_enum("None");
        FlowControl_attr->add_enum("Software");
        FlowControl_attr->add_enum("Hardware");
        add_property_attr("FlowControl", FlowControl_attr);

        auto StopBits_attr = std::make_shared<prop_attribute>();
        StopBits_attr->prop_name = "StopBits";
        StopBits_attr->read_only = false;
        add_property_attr("StopBits", StopBits_attr);

        auto DataBits_attr = std::make_shared<prop_attribute>();
        DataBits_attr->prop_name = "DataBits";
        DataBits_attr->read_only = false;
        add_property_attr("DataBits", DataBits_attr);

        auto BitRate_attr = std::make_shared<prop_attribute>();
        BitRate_attr->prop_name = "BitRate";
        BitRate_attr->read_only = false;
        add_property_attr("BitRate", BitRate_attr);

        auto SignalType_attr = std::make_shared<prop_attribute>();
        SignalType_attr->prop_name = "SignalType";
        SignalType_attr->read_only = true;
        SignalType_attr->add_enum("Rs232");
        SignalType_attr->add_enum("Rs485");
        add_property_attr("SignalType", SignalType_attr);

        auto Parity_attr = std::make_shared<prop_attribute>();
        Parity_attr->prop_name = "Parity";
        Parity_attr->read_only = false;
        Parity_attr->add_enum("None");
        Parity_attr->add_enum("Even");
        Parity_attr->add_enum("Odd");
        Parity_attr->add_enum("Mark");
        Parity_attr->add_enum("Space");
        add_property_attr("Parity", Parity_attr);

        auto InterfaceEnabled_attr = std::make_shared<prop_attribute>();
        InterfaceEnabled_attr->prop_name = "InterfaceEnabled";
        InterfaceEnabled_attr->read_only = false;
        add_property_attr("InterfaceEnabled", InterfaceEnabled_attr);

     }

};

}}

