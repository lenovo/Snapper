//---------------------------------------------------------------------
// <copyright file="edm_model.h" company="Microsoft">
//      Copyright (C) Microsoft Corporation. All rights reserved. See License.txt in the project root for license information.
// </copyright>
//---------------------------------------------------------------------

#pragma once

#include "odata/common/utility.h"
#include "odata/edm/edm_schema.h"

namespace odata { namespace edm
{

class edm_model
{
public:

#ifdef _MS_WINDOWS_DEBUG
	~edm_model()
	{
		std::wcout << U("destroy model") << std::endl;
	}
#endif

    std::shared_ptr<edm_schema> operator[](const ::odata::utility::string_t& name)
    {
        for (size_t i = 0; i < m_schemata.size(); ++i)
        {
            if (m_schemata[i]->get_name() == name)
            {
                return m_schemata[i];
            }
        }
        return nullptr;
    }
    
    std::shared_ptr<edm_schema> add_schema(const ::odata::utility::string_t& name, const ::odata::utility::string_t& alias)
    {
        auto val = std::make_shared<edm_schema>(name, alias);
        m_schemata.push_back(val);
        return val;
    }

	const std::vector<std::shared_ptr<edm_schema>>& get_schema()
	{
		return m_schemata;
	}

	const ::odata::utility::string_t& get_version() const
	{
		return m_version;
	}

	void set_version(const ::odata::utility::string_t& version)
	{
		m_version = version;
	}

    /// <summary>
    /// Looks up an entity type of the schema by name.
    /// </summary>
    /// <param name="name">The qualified or unqualified name of the entity type.</param>
    /// <returns>A pointer to the type if found, an empty pointer otherwise.</returns>
    ODATACPP_API std::shared_ptr<edm_entity_type> find_entity_type(::odata::utility::string_t name) const;

    /// <summary>
    /// snapper
    /// Looks up an entity type of the schema by entity type name and property name.
    /// </summary>
    /// <param name="name">The qualified or unqualified name of the entity type.</param>
    /// <returns>A pointer to the type found, an empty pointer otherwise.</returns>
    ODATACPP_API std::shared_ptr<edm_entity_type> find_entity_type(::odata::utility::string_t type_name, ::odata::utility::string_t prop_name) const;

    /// <summary>
    /// snapper
    /// Looks up an entity type of the schema by entity type name 
    //  and return a vector including all properties required on create
    /// </summary>
    /// <param name="name">The qualified or unqualified name of the entity type.</param>
    /// <returns>A vector to the properties required on create.</returns>
    ODATACPP_API std::vector<::odata::utility::string_t> find_entity_properties_required_on_create(::odata::utility::string_t type_name) const;

    /// <summary>
    /// snapper
    /// Looks up an property of the schema by entity type name and property name.
    /// </summary>
    /// <param name="name">The qualified or unqualified name of the entity type.</param>
    /// <returns>A pointer to the property  found, an empty pointer otherwise.</returns>
    ODATACPP_API std::shared_ptr<edm_property_type> find_entity_property(::odata::utility::string_t type_name, ::odata::utility::string_t prop_name) const;

    /// <summary>
    /// Looks up a complex type of the schema by name.
    /// </summary>
    /// <param name="name">The qualified or unqualified name of the entity type.</param>
    /// <returns>A pointer to the type if found, an empty pointer otherwise.</returns>
    ODATACPP_API std::shared_ptr<edm_complex_type> find_complex_type(::odata::utility::string_t name) const;

    // find the complex type which has specific property
    ODATACPP_API std::shared_ptr<edm_complex_type> find_complex_type(::odata::utility::string_t name, ::odata::utility::string_t prop_name) const;

    // find the complex type which has specific property of specific entity name
    ODATACPP_API std::shared_ptr<edm_complex_type> find_complex_type(::odata::utility::string_t name, ::odata::utility::string_t prop_name, ::odata::utility::string_t entity_name) const;

    // find the complex type which has specific property of specific namespace of schema
    ODATACPP_API std::shared_ptr<edm_complex_type> find_complex_type_by_ns(::odata::utility::string_t name, ::odata::utility::string_t prop_name, ::odata::utility::string_t name_space) const;

    /// <summary>
    /// snapper
    /// Looks up an property of the schema by complex type name and property name.
    /// </summary>
    /// <param name="name">The qualified or unqualified name of the complex type.</param>
    /// <returns>A pointer to the property  found, an empty pointer otherwise.</returns>    
    ODATACPP_API std::shared_ptr<edm_property_type> find_complex_property(::odata::utility::string_t name, ::odata::utility::string_t prop_name) const;

	/// <summary>
    /// Looks up an enum type of the schema by name.
    /// </summary>
    /// <param name="name">The qualified or unqualified name of the enum type.</param>
    /// <returns>A pointer to the type if found, an empty pointer otherwise.</returns>
	ODATACPP_API std::shared_ptr<edm_enum_type> find_enum_type(::odata::utility::string_t name) const;

	//snapper
	ODATACPP_API std::shared_ptr<edm_type_def> find_type_def(::odata::utility::string_t name) const;

	/// <summary>
    /// Looks up an operation type of the schema by name.
    /// </summary>
    /// <param name="name">The qualified or unqualified name of the operation type.</param>
    /// <returns>A pointer to the type if found, an empty pointer otherwise.</returns>
	ODATACPP_API std::shared_ptr<edm_operation_type> find_operation_type(::odata::utility::string_t name) const;

    /// <summary>
    /// Looks up an entity container of the schema by name.
    /// </summary>
    /// <param name="name">The qualified or unqualified name of the entity container; an empty string refers to the default container</param>
    /// <returns>A pointer to the container if found, an empty pointer otherwise.</returns>
    ODATACPP_API std::shared_ptr<edm_entity_container> find_container(::odata::utility::string_t name = U("")) const;

    // snapper: schemas has multiple containers with same name
    ODATACPP_API std::vector<std::shared_ptr<edm_entity_container>> find_all_containers(::odata::utility::string_t name = U("")) const;

    //snapper
    std::vector<edm_payload_annotation_type *> annotations;
    void add_annotation(edm_payload_annotation_type *p)
    {
        annotations.push_back(p);
    }
    std::vector<edm_payload_annotation_type *> & get_annotation_list()
    {
        return annotations;
    }
private:
    std::vector<std::shared_ptr<edm_schema>> m_schemata;
	::odata::utility::string_t  m_version;
};

}}
