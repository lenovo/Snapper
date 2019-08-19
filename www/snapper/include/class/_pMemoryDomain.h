//---------------------------------------------------------------------
// <copyright file="_pMemoryDomain.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "_pResource.h"
#include "SnapperProvider.h"
namespace snapper { namespace providers 
{

class _pMemoryDomain : public ResourceProvider
{
public:
    _pMemoryDomain() : ResourceProvider("MemoryDomain")    
    {
        create_prop("Oem",  nullptr);
        create_prop("Name",  nullptr);
        create_prop("Description",  nullptr);
        create_prop("Id",  nullptr);
        create_prop("Actions",  nullptr);
        create_prop("AllowsBlockProvisioning",  nullptr);
        create_prop("AllowsMemoryChunkCreation",  nullptr);
        create_prop("AllowsMirroring",  nullptr);
        create_prop("AllowsSparing",  nullptr);
        create_prop("InterleavableMemorySets",  nullptr);
        create_prop("MemoryChunks",  nullptr);
        
        // direct GET request for following navigation properties should be handled in this provider
        prepare_navigation_property();
        
        prepare_Links();
        
        prepare_OemLenovo();
        
        prepare_prop_class();
        
        prep_prop_attrs();
        
        set_namespace("MemoryDomain.v1_2_0");
        set_desc("This is the schema definition of a Memory Domain and its configuration. Memory Domains are used to indicate to the client which Memory (DIMMs) can be grouped together in Memory Chunks to form interleave sets or otherwise grouped together.");
    }

    virtual ~_pMemoryDomain()    
    {}

    void prepare_navigation_property()
    {
        add_navigation_contained_props("MemoryChunks");
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
        add_property_class("AllowsBlockProvisioning", "Primitive Type.", "Edm.Boolean");
        add_property_class("AllowsMemoryChunkCreation", "Primitive Type.", "Edm.Boolean");
        add_property_class("AllowsMirroring", "Primitive Type.", "Edm.Boolean");
        add_property_class("AllowsSparing", "Primitive Type.", "Edm.Boolean");
        add_property_class("InterleavableMemorySets", "Collection Type.", "MemorySet");
        add_property_class("MemoryChunks", "Navigation Type.Entity", "MemoryChunksCollection");
    }

    void prep_prop_attrs()
    {
        auto MemoryChunks_attr = std::make_shared<prop_attribute>();
        MemoryChunks_attr->prop_name = "MemoryChunks";
        MemoryChunks_attr->read_only = true;
        add_property_attr("MemoryChunks", MemoryChunks_attr);

        auto AllowsBlockProvisioning_attr = std::make_shared<prop_attribute>();
        AllowsBlockProvisioning_attr->prop_name = "AllowsBlockProvisioning";
        AllowsBlockProvisioning_attr->read_only = true;
        add_property_attr("AllowsBlockProvisioning", AllowsBlockProvisioning_attr);

        auto AllowsMemoryChunkCreation_attr = std::make_shared<prop_attribute>();
        AllowsMemoryChunkCreation_attr->prop_name = "AllowsMemoryChunkCreation";
        AllowsMemoryChunkCreation_attr->read_only = true;
        add_property_attr("AllowsMemoryChunkCreation", AllowsMemoryChunkCreation_attr);

        auto AllowsSparing_attr = std::make_shared<prop_attribute>();
        AllowsSparing_attr->prop_name = "AllowsSparing";
        AllowsSparing_attr->read_only = true;
        add_property_attr("AllowsSparing", AllowsSparing_attr);

        auto AllowsMirroring_attr = std::make_shared<prop_attribute>();
        AllowsMirroring_attr->prop_name = "AllowsMirroring";
        AllowsMirroring_attr->read_only = true;
        add_property_attr("AllowsMirroring", AllowsMirroring_attr);

     }

};

}}

