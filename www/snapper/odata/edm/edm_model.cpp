//---------------------------------------------------------------------
// <copyright file="edm_model.cpp" company="Microsoft">
//      Copyright (C) Microsoft Corporation. All rights reserved. See License.txt in the project root for license information.
// </copyright>
//---------------------------------------------------------------------

#include "odata/edm/odata_edm.h"

namespace odata { namespace edm
{

std::shared_ptr<edm_entity_container> edm_schema::find_container(::odata::utility::string_t name) const
{
    if (name.empty())
    {
        for (auto ent = m_entity_containers.begin(); ent != m_entity_containers.end(); ++ent)
        {
			if (ent->second->is_default_container())
			{
				return ent->second;
			}
        }
    }
    else
    {
        for (auto ent = m_entity_containers.begin(); ent != m_entity_containers.end(); ++ent)
        {
			if (ent->second->get_name() == name)
			{
				return ent->second;
			}
        }
    }

    return nullptr;
}

std::shared_ptr<edm_entity_type> edm_model::find_entity_type(::odata::utility::string_t name) const
{
    for (auto sc = m_schemata.cbegin(); sc != m_schemata.cend(); ++sc)
    {
        auto et_ptr = (*sc)->find_entity_type(name);
        if (et_ptr)
		{
            return et_ptr;
		}
    }

    return nullptr;
}


std::shared_ptr<edm_entity_type> edm_model::find_entity_type(::odata::utility::string_t type_name, ::odata::utility::string_t prop_name) const
{
    for (auto sc = m_schemata.cbegin(); sc != m_schemata.cend(); ++sc)
    {
        auto et_ptr = (*sc)->find_entity_type(type_name);
        if (et_ptr && et_ptr->find_property(prop_name))
        {
            return et_ptr;
        }
    }
    return nullptr;
    
}

std::shared_ptr<edm_property_type> edm_model::find_entity_property(::odata::utility::string_t type_name, ::odata::utility::string_t prop_name) const
{
    for (auto sc = m_schemata.cbegin(); sc != m_schemata.cend(); ++sc)
    {
        auto et_ptr = (*sc)->find_entity_type(type_name);
        if (et_ptr)
        {
            auto prop_ptr = et_ptr->find_property(prop_name);
            if (prop_ptr)
                return prop_ptr;
        }
    }
	return nullptr;
    
}

std::vector<::odata::utility::string_t> edm_model::find_entity_properties_required_on_create(::odata::utility::string_t type_name) const
{
    std::vector<::odata::utility::string_t> properties_required_on_create;
    for (auto sc = m_schemata.cbegin(); sc != m_schemata.cend(); ++sc)
    {
        auto et_ptr = (*sc)->find_entity_type(type_name);
        if (et_ptr)
        {
            auto prop_vec = et_ptr->get_properties_vector();
            for(auto it = prop_vec.begin(); it != prop_vec.end(); it++)
            {
                auto annotations = (*it)->get_annotation_list();
                for(int i = 0; i < annotations.size() && annotations[i] != nullptr; i++)
                {
                    if(annotations[i]->get_name().compare(ANNOTATION_TERM_REQUIRED) == 0)
                        properties_required_on_create.push_back((*it)->get_name());
                }
            }
        }
    }
	return properties_required_on_create;
    
}


std::shared_ptr<edm_complex_type> edm_model::find_complex_type(::odata::utility::string_t name) const
{
    for (auto sc = m_schemata.cbegin(); sc != m_schemata.cend(); ++sc)
    {
        auto cp_ptr = (*sc)->find_complex_type(name);
        if (cp_ptr)
		{
            return cp_ptr;
		}
    }

    return nullptr;
}

std::shared_ptr<edm_complex_type> edm_model::find_complex_type(::odata::utility::string_t name, ::odata::utility::string_t prop_name) const
{
    for (auto sc = m_schemata.cbegin(); sc != m_schemata.cend(); ++sc)
    {
        auto cp_ptr = (*sc)->find_complex_type(name);
        if (cp_ptr && cp_ptr->find_property(prop_name))
		{
            return cp_ptr;
		}
    }

    return nullptr;
}

std::shared_ptr<edm_complex_type> edm_model::find_complex_type(::odata::utility::string_t name, ::odata::utility::string_t prop_name, ::odata::utility::string_t entity_name) const
{
    for (auto sc = m_schemata.cbegin(); sc != m_schemata.cend(); ++sc)
    {
        auto ets = (*sc)->get_entity_types_vector();//find the entity needed
        for (auto ele = ets.cbegin(); ele != ets.cend(); ++ele)
        {             
            if((*ele)->get_name().compare(entity_name))
                continue;

            auto cp_ptr = (*sc)->find_complex_type(name);
            if (cp_ptr && cp_ptr->find_property(prop_name))
		    {
                //std::cout << "find complex " << name << " by entity " << entity_name << " and property name " << prop_name << std::endl;
                return cp_ptr;
		    }
        }
    }

    return nullptr;
}

std::shared_ptr<edm_complex_type> edm_model::find_complex_type_by_ns(::odata::utility::string_t name, ::odata::utility::string_t prop_name, ::odata::utility::string_t name_space) const
{
    for (auto sc = m_schemata.cbegin(); sc != m_schemata.cend(); ++sc)
    {
        if((*sc)->get_name().compare(name_space))
            continue;

        //std::cout << "find complex " << name << " by name space " << name_space << " and property name " << prop_name << std::endl;
        auto cp_ptr = (*sc)->find_complex_type(name);
        if (cp_ptr && cp_ptr->find_property(prop_name))
		{
            return cp_ptr;
		}
    }

    return nullptr;
}

std::shared_ptr<edm_property_type> edm_model::find_complex_property(::odata::utility::string_t name, ::odata::utility::string_t prop_name) const
{
    for (auto sc = m_schemata.cbegin(); sc != m_schemata.cend(); ++sc)
    {
        auto et_ptr = (*sc)->find_complex_type(name);
        if (et_ptr)
        {
            auto prop_ptr = et_ptr->find_property(prop_name);
            if (prop_ptr)
                return prop_ptr;
        }
    }
	return nullptr;    
}

std::shared_ptr<edm_enum_type> edm_model::find_enum_type(::odata::utility::string_t name) const
{
    for (auto sc = m_schemata.cbegin(); sc != m_schemata.cend(); ++sc)
    {
        auto en_ptr = (*sc)->find_enum_type(name);
        if (en_ptr)
		{
            return en_ptr;
		}
    }

    return nullptr;
}

//snapper
std::shared_ptr<edm_type_def> edm_model::find_type_def(::odata::utility::string_t name) const
{
    for (auto sc = m_schemata.cbegin(); sc != m_schemata.cend(); ++sc)
    {
        auto en_ptr = (*sc)->find_type_def(name);
        if (en_ptr)
		{
            return en_ptr;
		}
    }

    return nullptr;
}

std::shared_ptr<edm_operation_type> edm_model::find_operation_type(::odata::utility::string_t name) const
{
    for (auto sc = m_schemata.cbegin(); sc != m_schemata.cend(); ++sc)
    {
        auto op_ptr = (*sc)->find_operation_type(name);
        if (op_ptr)
		{
            return op_ptr;
		}
    }

    return nullptr;
}

std::shared_ptr<edm_entity_container> edm_model::find_container(::odata::utility::string_t name) const
{
    for (auto sc = m_schemata.cbegin(); sc != m_schemata.cend(); ++sc)
    {
        auto cn_ptr = (*sc)->find_container(name);
        if (cn_ptr)
		{
            return cn_ptr;
		}
    }

    return nullptr;
}

std::vector<std::shared_ptr<edm_entity_container>> edm_model::find_all_containers(::odata::utility::string_t name) const
{
	std::vector<std::shared_ptr<edm_entity_container>> ret;
    for (auto sc = m_schemata.cbegin(); sc != m_schemata.cend(); ++sc)
    {
        auto cn_ptr = (*sc)->find_container(name);
        if (cn_ptr)
		{
			ret.push_back(cn_ptr);
		}
    }

	return ret;
}

}}
