﻿//---------------------------------------------------------------------
// <copyright file="edm_entity_container.h" company="Microsoft">
//      Copyright (C) Microsoft Corporation. All rights reserved. See License.txt in the project root for license information.
// </copyright>
//---------------------------------------------------------------------

#pragma once

#include "odata/common/utility.h"
#include "odata/edm/edm_entity_set.h"
#include "odata/edm/edm_singleton.h"
#include "odata/edm/edm_operation_import.h"

namespace odata { namespace edm
{

/// <summary>
/// Represents a container of entities
/// </summary>
class edm_entity_container
{
public:
    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="name">The name of the entity container.</param>
    edm_entity_container(::odata::utility::string_t name, bool is_default) : 
        m_name(name), m_is_default(is_default)
    {
    }

	~edm_entity_container()
	{
#ifdef _MS_WINDOWS_DEBUG
		std::wcout << U("destroy edm_entity_container") << std::endl;
#endif
	}

    /// <summary>
    /// Gets the name of the entity container
    /// </summary>
    /// <returns>The name of the entity container.</returns>
    const ::odata::utility::string_t& get_name() const 
    {
        return m_name;
    }

    /// <summary>
    /// Gets the is_default_container property
    /// </summary>
    /// <returns>true if this is the default container of the service, false otherwise</returns>
    bool is_default_container() const 
    {
        return m_is_default;
    }

    /// <summary>
    /// 
    /// </summary>
    void add_entity_set(std::shared_ptr<edm_entity_set> et)
    {
		if (et)
		{
		    m_entity_sets[et->get_name()] = et;
            m_entity_set_vector.push_back(et);
		}
    }

    /// <summary>
    /// 
    /// </summary>
	void add_singleton(std::shared_ptr<edm_singleton> sg)
	{
		if (sg)
		{
			m_singletons[sg->get_name()] = sg;
            m_singleton_vector.push_back(sg);
		}
	}

	/// <summary>
    /// 
    /// </summary>
	const std::unordered_map<::odata::utility::string_t, std::shared_ptr<edm_operation_import>>& get_operation_imports() const
	{
		return m_operation_imports;
	}

	const std::unordered_map<::odata::utility::string_t, std::shared_ptr<edm_singleton>>& get_singletons() const
	{
		return m_singletons;
	}

    const std::vector<std::shared_ptr<edm_operation_import>>& get_operation_import_vector() const
	{
		return m_operation_import_vector;
	}

	const std::vector<std::shared_ptr<edm_singleton>>& get_singleton_vector() const
	{
		return m_singleton_vector;
	}

    const std::vector<std::shared_ptr<edm_entity_set>>& get_entity_set_vector() const
	{
		return m_entity_set_vector;
	}

    /// <summary>
    /// 
    /// </summary>
	void add_operation_import(std::shared_ptr<edm_operation_import> op)
	{
		if (op)
		{
		    m_operation_imports[op->get_name()] = op;
            m_operation_import_vector.push_back(op);
		}
	}

    /// <summary>
    /// Gets the beginning iterator of the properties of the type
    /// </summary>
    std::unordered_map<::odata::utility::string_t, std::shared_ptr<edm_entity_set>>::const_iterator begin() const
    {
        return m_entity_sets.cbegin();
    }

    /// <summary>
    /// Gets the end iterator of the properties of the type
    /// </summary>
    std::unordered_map<::odata::utility::string_t, std::shared_ptr<edm_entity_set>>::const_iterator end() const
    {
        return m_entity_sets.cend();
    }

    /// <summary>
    /// Looks up an entity set of the container by name.
    /// </summary>
    /// <param name="name">The qualified or unqualified name of the entity set.</param>
    /// <returns>A pointer to the type if found, an empty pointer otherwise.</returns>
    ODATACPP_API std::shared_ptr<edm_entity_set> find_entity_set(::odata::utility::string_t name) const;

    /// <summary>
    /// Looks up a singleton of the container by name.
    /// </summary>
    /// <param name="name">The qualified or unqualified name of the singleton.</param>
    /// <returns>A pointer to the type if found, an empty pointer otherwise.</returns>
	ODATACPP_API std::shared_ptr<edm_singleton> find_singleton(::odata::utility::string_t name) const;

    /// <summary>
    /// Looks up an operation import of the container by name.
    /// </summary>
    /// <param name="name">The qualified or unqualified name of the operation import.</param>
    /// <returns>A pointer to the type if found, an empty pointer otherwise.</returns>
    ODATACPP_API std::shared_ptr<edm_operation_import> find_operation_import(::odata::utility::string_t name) const;

    //snapper
    void add_annotation(edm_payload_annotation_type *p)
    {
        annotations.push_back(p);
    }
    std::vector<edm_payload_annotation_type *> & get_annotation_list()
    {
        return annotations;
    }
private:
    friend class edm_schema;

    bool m_is_default;
    ::odata::utility::string_t m_name;
	::odata::utility::string_t m_extends;
	std::unordered_map<::odata::utility::string_t, std::shared_ptr<edm_entity_set>> m_entity_sets;
	std::unordered_map<::odata::utility::string_t, std::shared_ptr<edm_singleton>> m_singletons;
	std::unordered_map<::odata::utility::string_t, std::shared_ptr<edm_operation_import>> m_operation_imports;
    std::vector<std::shared_ptr<edm_entity_set>> m_entity_set_vector;
	std::vector<std::shared_ptr<edm_singleton>> m_singleton_vector;
	std::vector<std::shared_ptr<edm_operation_import>> m_operation_import_vector;
    std::vector<edm_payload_annotation_type *> annotations;

};

}}
