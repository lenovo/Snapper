//---------------------------------------------------------------------
// <copyright file="edm_model_reader.cpp" company="Microsoft">
//      Copyright (C) Microsoft Corporation. All rights reserved. See License.txt in the project root for license information.
// </copyright>
//---------------------------------------------------------------------
#include "odata/edm/edm_model_reader.h"
#include "odata/edm/edm_model_utility.h"

#include <regex.h>
#include <dirent.h>


#define OEM_PREFIX    "OemShim"

#define T_EDM_TYPE_PRIMITIVE    "Primitive Type."
#define T_EDM_TYPE_DEFINITION   "Type Definition."
#define T_EDM_TYPE_COLLECTION   "Collection Type."
#define T_EDM_TYPE_COMPLEX      "Complex Type."
#define T_EDM_TYPE_ENUM         "Enum Type."
#define T_EDM_TYPE_ENTITY       "Entity Type."
#define T_EDM_TYPE_NAVIGATION   "Navigation Type."
#define T_EDM_TYPE_NAVIGATION_E   "Navigation Type.Entity"
#define T_EDM_TYPE_NAVIGATION_C   "Navigation Type.Collection"
#define T_EDM_TYPE_OPERATION    "Operation Type."
#define T_EDM_TYPE_UNKNOWN      "Unknown Type."

using namespace std;
namespace odata { namespace edm
{

string get_annotation_attr_value(std::vector<edm_payload_annotation_type *> & notations, string term, string attr_name)
{
    string desc("");
    for(int i = 0; i < notations.size() && notations[i] != nullptr; i++)
    {
        if(notations[i]->get_name().compare(term) != 0)
            continue;
        desc = notations[i]->get_attribute(attr_name);
        if(desc.length() == 0)
            continue;

        return desc;
    }
    return desc;
}
bool annotation_has_term(std::vector<edm_payload_annotation_type *> & notations, string term)
{
    for(int i = 0; i < notations.size() && notations[i] != nullptr; i++)
    {
        if(notations[i]->get_name().compare(term) == 0)
            return true;
    }
    return false;
}


void xml_stack_elem::attach_annotation(edm_payload_annotation_type *ptr)
{// in handle_begin_element, current element is not push_back to stack yet

    std::string elename("");

    if(type == XML_NODE_MODEL && n_model != nullptr)
    {
        n_model->add_annotation(ptr);
        elename = n_model->get_version();
    }
    else if(type == XML_NODE_SCHEMA && n_schema != nullptr)
    {
        n_schema->add_annotation(ptr);
        elename = n_schema->get_name();
    }
    else if(type == XML_NODE_CONTAINER && n_container != nullptr)
    {
        n_container->add_annotation(ptr);
        elename = n_container->get_name();
    }
    else if(type == XML_NODE_ENTITYSET && n_entity_set != nullptr)
    {
        n_entity_set->add_annotation(ptr);
        elename = n_entity_set->get_name();
    }
    else if(type == XML_NODE_SINGLETON && n_singleton != nullptr)
    {
        n_singleton->add_annotation(ptr);
        elename = n_singleton->get_name();
    }
    else if(type == XML_NODE_PROPTYPE && n_prop_type != nullptr)
    {
        n_prop_type->add_annotation(ptr);
        elename = n_prop_type->get_name();
    }
    else if(type == XML_NODE_ENUM_MEMBER && n_enum_member != nullptr)
    {
        n_enum_member->add_annotation(ptr);
        elename = n_enum_member->get_enum_member_name();
    }
    else if(type == XML_NODE_STRUCTURE && n_struct != nullptr)
    {
        n_struct->add_annotation(ptr);
        elename = n_struct->get_name();
    }
    else if(type == XML_NODE_IMPORT && n_op_import != nullptr)
    {
        n_op_import->add_annotation(ptr);
        elename = n_op_import->get_name();
    }
    else if(type == XML_NODE_OP && n_operation != nullptr)
    {
        n_operation->add_annotation(ptr);
        elename = n_operation->get_name();
    }
    else if(type == XML_NODE_ENUM && n_enum != nullptr)
    {
        n_enum->add_annotation(ptr);
        elename = n_enum->get_name();
    }
    else if(type == XML_NODE_TYPEDEF && n_typedef != nullptr)
    {
        n_typedef->add_annotation(ptr);
        elename = n_typedef->get_name();
    }
    else if(type == XML_NODE_NAVPROP_BINDING)
    {
    }
    else if(type == XML_NODE_NAVPROP && n_navprop != nullptr)
    {
        n_navprop->add_annotation(ptr);
        elename = n_navprop->get_name();
    }
    else if(type == XML_NODE_PARAM && n_param != nullptr)
    {
        n_param->add_annotation(ptr);
        elename = n_param->get_param_name();
    }
    else if(type == XML_NODE_RETURNTYPE && n_return_t != nullptr)
    {
        //n_return_t->add_annotation(ptr);
        //should define return type inherited from edm_named_type
    }
    else if(type == XML_NODE_EXP_COLLECTION && n_exp_collection != nullptr)
    {
        n_exp_collection->add_annotation(ptr);
        elename = n_exp_collection->get_expr_name();
    }
    else if(type == XML_NODE_EXP_RECORD && n_exp_record != nullptr)
    {
        n_exp_record->add_annotation(ptr);
        elename = n_exp_record->get_expr_name();
    }
    else if(type == XML_NODE_PROPVAL && n_propvalue != nullptr)
    {
        n_propvalue->add_annotation(ptr);
        elename = n_propvalue->get_propval_name();
    }
    else if(type == XML_NODE_PROPREF)
    {
    }
    else if(type == XML_NODE_KEY)
    {
    }
    else if(type == XML_NODE_ANNOTATION && n_annotation != nullptr)
    {
    }

    //std::cout << name << ":" << elename << " --- Annotation " << ptr->get_name() << std::endl;
}

bool edm_model_reader::parse()
{
    bool ret = ::odata::edm::xml_reader::parse();

    //_dump_results();

    edm_model_utility::resolve_edm_types_after_parsing(m_model);

    return ret;
}

bool edm_model_reader::parse_edm()
{
    return ::odata::edm::xml_reader::parse();
}

void edm_model_reader::resolve_edm()
{
    edm_model_utility::resolve_edm_types_after_parsing(m_model);
}

//snapper
std::shared_ptr<xml_elem> edm_model_reader::handle_begin_element(const ::odata::utility::string_t& elementName)
{
    std::shared_ptr<xml_stack_elem> resultnode = nullptr;

    if (elementName == U("Edmx"))
    {
        while (move_to_next_attribute())
        {
            if(get_current_element_name() == U("Version"))
            {
                m_model->set_version(get_current_element_text());
            }
        }

        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_MODEL, elementName);
        resultnode->n_model = m_model;
    }
    else if (elementName == U("Schema"))
    {
        ::odata::utility::string_t namesp;
        ::odata::utility::string_t alias;

        while (move_to_next_attribute())
        {
            if(get_current_element_name() == U("Namespace"))
            {
                namesp = get_current_element_text();
            }

            if(get_current_element_name() == U("Alias"))
            {
                alias = get_current_element_text();
            }
        }

        m_current_schema = m_model->add_schema(namesp, alias);
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_SCHEMA, elementName);
        resultnode->n_schema = m_current_schema;
    }
    else if (elementName == U("EntityContainer"))
    {
        ::odata::utility::string_t name;
        ::odata::utility::string_t extends;
        bool is_default = true;

        while (move_to_next_attribute())
        {
            if (get_current_element_name() == U("Name"))
            {
                name = get_current_element_text();
            }
            else if (get_current_element_name() == U("Extends"))
            {
                extends = get_current_element_text();
            }
        }

        m_current_container = std::make_shared<edm_entity_container>(name, is_default);
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_CONTAINER, elementName);
        resultnode->n_container = m_current_container;
    }
    else if (elementName == U("EntitySet"))
    {
        ::odata::utility::string_t name;
        ::odata::utility::string_t type;

        while (move_to_next_attribute())
        {
            if(get_current_element_name() == U("Name"))
            {
                name = get_current_element_text();
            }
            else if (get_current_element_name() == U("EntityType"))
            {
                type = get_current_element_text();
            }
        }

        m_current_entity_set = std::make_shared<edm_entity_set>(name, type);
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_ENTITYSET, elementName);
        resultnode->n_entity_set = m_current_entity_set;
    }
    else if (elementName == U("Singleton"))
    {
        ::odata::utility::string_t name;
        ::odata::utility::string_t type;

        while (move_to_next_attribute())
        {
            if(get_current_element_name() == U("Name"))
            {
                name = get_current_element_text();
            }
            else if (get_current_element_name() == U("Type"))
            {
                type = get_current_element_text();
            }
        }

        m_current_singleton = std::make_shared<edm_singleton>(name, type);
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_SINGLETON, elementName);
        resultnode->n_singleton = m_current_singleton;
    }
    else if (elementName == U("FunctionImport") || elementName == U("ActionImport"))
    {
        ::odata::utility::string_t name;
        ::odata::utility::string_t entity_set_path;
        bool is_in_service_document;
        OperationImportKind operation_import_kind = elementName == U("FunctionImport") ? OperationImportKind::FunctionImport : OperationImportKind::ActionImport;
        ::odata::utility::string_t operation_name;

        while (move_to_next_attribute())
        {
            if(get_current_element_name() == U("Name"))
            {
                name = get_current_element_text();
            }
            else if (get_current_element_name() == U("EntitySet"))
            {
                entity_set_path = get_current_element_text();
            }
            else if (get_current_element_name() == U("IncludeInServiceDocument"))
            {
                is_in_service_document = get_current_element_text()  == U("true") ? true : false;;
            }
            else if (get_current_element_name() == U("Function") || get_current_element_name() == U("Action"))
            {
                operation_name = get_current_element_text();
            }
        }

        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_IMPORT, elementName);
        if (m_current_container)
        {
            auto imp = std::make_shared<edm_operation_import>(name, operation_name, entity_set_path, is_in_service_document, operation_import_kind);
            m_current_container->add_operation_import(imp);
            resultnode->n_op_import = imp;
        }


    }
    else if (elementName == U("EntityType"))
    {
        ::odata::utility::string_t name;
        ::odata::utility::string_t baseType;
        bool isAbstract = false;
        bool isOpenType = false;
        bool hasStream = false;

        while (move_to_next_attribute())
        {
            if (get_current_element_name() == U("Name"))
            {
                name = get_current_element_text();
            }
            else if (get_current_element_name() == U("BaseType"))
            {
                baseType = get_current_element_text();
            }
            else if (get_current_element_name() == U("Abstract"))
            {
                isAbstract = get_current_element_text() == U("true") ? true : false;
            }
            else if (get_current_element_name() == U("OpenType"))
            {
                isOpenType = get_current_element_text() == U("true") ? true : false;
            }
            else if (get_current_element_name() == U("HasStream"))
            {
                hasStream = get_current_element_text() == U("true") ? true : false;
            }
        }

        m_current_st = new edm_entity_type(name, m_current_schema->get_name(), baseType, isAbstract, isOpenType, hasStream);
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_STRUCTURE, elementName);
        resultnode->n_struct = m_current_st;
    }
    else if (elementName == U("ComplexType"))
    {
        ::odata::utility::string_t name;
        ::odata::utility::string_t baseType;
        bool isAbstract = false;
        bool isOpenType = false;

        while (move_to_next_attribute())
        {
            if (get_current_element_name() == U("Name"))
            {
                name = get_current_element_text();
            }
            else if (get_current_element_name() == U("BaseType"))
            {
                baseType = get_current_element_text();
            }
            else if (get_current_element_name() == U("Abstract"))
            {
                isAbstract = get_current_element_text() == U("true") ? true : false;
            }
            else if (get_current_element_name() == U("OpenType"))
            {
                isOpenType = get_current_element_text() == U("true") ? true : false;
            }
        }

        m_current_st = new edm_complex_type(name, m_current_schema->get_name(), baseType, isAbstract, isOpenType);
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_STRUCTURE, elementName);
        resultnode->n_struct = m_current_st;
    }
    else if (elementName == U("EnumType"))
    {
        ::odata::utility::string_t name;
        ::odata::utility::string_t underlying_type = U("Edm.Int32");
        bool is_flag = false;

        while (move_to_next_attribute())
        {
            if (get_current_element_name() == U("Name"))
            {
                name = get_current_element_text();
            }
            else if (get_current_element_name() == U("UnderlyingType"))
            {
                underlying_type = get_current_element_text();
            }
            else if (get_current_element_name() == U("IsFlags"))
            {
                is_flag = get_current_element_text() == U("true") ? true : false;
            }
        }

        m_current_enum = new edm_enum_type(name, m_current_schema->get_name(), underlying_type, is_flag);
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_ENUM, elementName);
        resultnode->n_enum = m_current_enum;
    }
    else if (elementName == U("TypeDefinition"))//snapper: support  TypeDefinition
    {
        ::odata::utility::string_t name;
        ::odata::utility::string_t underlying_type = U("Edm.Int32");

        while (move_to_next_attribute())
        {
            if (get_current_element_name() == U("Name"))
            {
                name = get_current_element_text();
            }
            else if (get_current_element_name() == U("UnderlyingType"))
            {
                underlying_type = get_current_element_text();
            }
        }

        std::shared_ptr<edm_primitive_type> type = NULL;
        std::shared_ptr<edm_named_type> edm_type = edm_model_utility::get_edm_type_from_name(underlying_type);                
        if (edm_type)
        {
            type = std::dynamic_pointer_cast<edm_primitive_type>(edm_type);
        }

        m_current_typedef = new edm_type_def(name, m_current_schema->get_name(), type);
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_TYPEDEF, elementName);
        resultnode->n_typedef = m_current_typedef;
    }
    else if (elementName == U("Function") || elementName == U("Action"))
    {
        ::odata::utility::string_t name;
        ::odata::utility::string_t path;
        bool is_bound = false;
        bool is_composable = false;
        EdmOperationKind operation_kind = elementName == U("Function") ? EdmOperationKind::Function : EdmOperationKind::Action;

        while (move_to_next_attribute())
        {
            if (get_current_element_name() == U("Name"))
            {
                name = get_current_element_text();
            }
            else if (get_current_element_name() == U("EntitySetPath"))
            {
                path = get_current_element_text();
            }
            else if (get_current_element_name() == U("IsBound"))
            {
                is_bound = get_current_element_text() == U("true") ? true : false;
            }
            else if (get_current_element_name() == U("IsComposable"))
            {
                is_composable = get_current_element_text() == U("true") ? true : false;
            }
        }

        m_current_operation = new edm_operation_type(name, m_current_schema->get_name(),  is_bound, path, operation_kind, is_composable);
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_OP, elementName);
        resultnode->n_operation = m_current_operation;
    }
    else if (elementName == U("Property"))
    {
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_PROPTYPE, elementName);
        _process_property(resultnode);
    }
    else if (elementName == U("Member"))
    {
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_ENUM_MEMBER, elementName);
        _process_property(resultnode);
    }
    else if (elementName == U("NavigationPropertyBinding"))
    {
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_NAVPROP_BINDING, elementName);
        _process_navigation_property_binding();
    }
    else if (elementName == U("NavigationProperty"))
    {
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_NAVPROP, elementName);
        _process_navigation_property(resultnode);
    }
    else if (elementName == U("Parameter"))
    {
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_PARAM, elementName);
        _process_operation_parameter(resultnode);
    }
    else if (elementName == U("ReturnType"))
    {
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_RETURNTYPE, elementName);
        _process_operation_return_type(resultnode);
    }
    else if (m_parsing_key && elementName == U("PropertyRef"))
    {
        while (move_to_next_attribute())
        {
            if (get_current_element_name() == U("Name"))
            {
                dynamic_cast<edm_entity_type*>(m_current_st)->add_key_property(get_current_element_text());
                break;
            }
        }
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_PROPREF, elementName);        
    }
    else if (elementName == U("Key"))
    {
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_KEY, elementName);        
        m_parsing_key = true;
    }
    else if (elementName == U("Annotation"))
    {
        //Term, Qualifier, Target, const expression like Bool="true"
        ::odata::utility::string_t term;
        ::odata::utility::string_t qualifier;
        std::map<std::string, std::string> attrs;
        while (move_to_next_attribute())
        {
            if (get_current_element_name() == U("Term"))
            {
                term = get_current_element_text();
            }
            else if (get_current_element_name() == U("Qualifier"))
            {
                qualifier = get_current_element_text();
            }            
            //std::cout << "      " << get_current_element_name() << "=" << get_current_element_text() << std::endl;
            attrs[get_current_element_name()] = get_current_element_text();
        }

        m_current_at = new edm_payload_annotation_type(term);
        std::map<std::string, std::string>::iterator it;
        for(it=attrs.begin();it!=attrs.end();++it)
        {
            ::odata::utility::string_t name = it->first;
            ::odata::utility::string_t val = it->second;
            m_current_at->add_attribute(name, val);
        }

        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_ANNOTATION, elementName);
        resultnode->n_annotation = m_current_at;

        auto lastnode =  dynamic_pointer_cast<xml_stack_elem> (get_last_element());
        lastnode->attach_annotation(m_current_at);
        //std::cout << "Annotation " << term << " >>>>> " << lastnode->name << std::endl;
    }
    else if (elementName == U("Collection"))
    {
        m_current_exp_collection = std::make_shared<edm_expr_collection>(elementName);
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_EXP_COLLECTION, elementName);
        resultnode->n_exp_collection = m_current_exp_collection;

    }
    else if (elementName == U("Record"))
    {
        m_current_exp_record = std::make_shared<edm_expr_record>(elementName);
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_EXP_RECORD, elementName);
        resultnode->n_exp_record = m_current_exp_record;

    }
    else if (elementName == U("PropertyValue"))
    {
        //PropertyValue Property="Pattern" String="[A-Za-z0-9_.:]+"
        ::odata::utility::string_t propval_name;
        ::odata::utility::string_t expr_name;
        ::odata::utility::string_t expr;
        while (move_to_next_attribute())
        {
            if (get_current_element_name() == U("Property"))
            {
                propval_name = get_current_element_text();
            }
            else
            {
                expr_name = get_current_element_name();
                expr = get_current_element_text();
            }            
        }

        m_current_propvalue = std::make_shared<edm_prop_value>(propval_name, expr_name, expr);
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_PROPVAL, elementName);
        resultnode->n_propvalue = m_current_propvalue;
    }
    else
    {
        //std::cout << "unknown element " << elementName << std::endl;
    }
#ifdef WIN32
    m_reader->MoveToElement();
#endif

    if(resultnode == nullptr)
        resultnode = std::make_shared<xml_stack_elem>(XML_NODE_UNKNOWN, elementName);        

    return std::shared_ptr<xml_elem>(resultnode);
}

void edm_model_reader::handle_end_element(const ::odata::utility::string_t& elementName)
{
    //std::cout << "handle_end_element:  " << elementName << std::endl;
    if (elementName == U("EntityContainer"))
    {
        m_current_schema->add_container(m_current_container);
        m_current_container.reset();
    }

    if (elementName == U("EntityType"))
    {
        m_current_schema->add_entity_type(std::shared_ptr<edm_entity_type>(static_cast<edm_entity_type*>(m_current_st)));
        m_current_st = nullptr;
    }

    if (elementName == U("ComplexType"))
    {
        m_current_schema->add_complex_type(std::shared_ptr<edm_complex_type>(static_cast<edm_complex_type*>(m_current_st)));
        m_current_st = nullptr;
    }

    if (elementName == U("Key"))
    {
        m_parsing_key = false;
    }

    if (elementName == U("EnumType"))
    {
        if(annotation_has_term(m_current_enum->get_annotation_list(), ANNOTATION_TERM_DEPRECATED) == false)
            m_current_schema->add_enum_type(std::shared_ptr<edm_enum_type>(static_cast<edm_enum_type*>(m_current_enum)));
        else
            std::cout << "end EnumType " << m_current_enum->get_name() << " is deprecated !!!" << std::endl;
        m_current_enum = nullptr;
    }

    if (elementName == U("TypeDefinition"))//snapper
    {
        m_current_schema->add_type_def(std::shared_ptr<edm_type_def>(static_cast<edm_type_def*>(m_current_typedef)));
        m_current_typedef = nullptr;
    }

    if (elementName == U("Function") || elementName == U("Action"))
    {
        m_current_schema->add_operation_type(std::shared_ptr<edm_operation_type>(static_cast<edm_operation_type*>(m_current_operation)));
        m_current_operation = nullptr;
    }

    if (elementName == U("EntitySet"))
    {
        if (m_current_container)
        {
            m_current_container->add_entity_set(m_current_entity_set);
        }

        m_current_entity_set = nullptr;        
    }

    if (elementName == U("Singleton"))
    {
        if (m_current_container)
        {
            m_current_container->add_singleton(m_current_singleton);
        }

        m_current_singleton = nullptr;
    }

    if (elementName == U("Annotation"))//snapper
    {
        //m_current_schema->add_annotation_type(std::shared_ptr<edm_payload_annotation_type>(static_cast<edm_payload_annotation_type*>(m_current_at)));
        m_current_at = nullptr;
    }

    if (elementName == U("Collection"))
    {
        // <Collection> is child of <Annotation>
        auto p = get_parent_element(0);
        std::shared_ptr<xml_stack_elem> parent = dynamic_pointer_cast<xml_stack_elem>(p);
        if (parent != nullptr && parent->type == XML_NODE_ANNOTATION && parent->n_annotation != nullptr)
        {
            //m_current_schema->add_exp_collection
            parent->n_annotation->set_subordinate_collection(m_current_exp_collection);
            //std::cout << "    Collection of " << parent->n_annotation->get_name() << std::endl;
        }
        m_current_exp_collection = nullptr;
    }

    if (elementName == U("Record"))
    {
        auto p = get_parent_element(0);
        std::shared_ptr<xml_stack_elem> parent = dynamic_pointer_cast<xml_stack_elem>(p);

        // <Record> is child of <Annotation>
        if (parent != nullptr && parent->type == XML_NODE_ANNOTATION && parent->n_annotation != nullptr)
        {
            //m_current_schema->add_exp_record
            parent->n_annotation->set_subordinate_record(m_current_exp_record);
            //std::cout << "    Record of Annotation " << parent->n_annotation->get_name() << std::endl;
        }

        // <Record> is child of <Collection>
        if (parent != nullptr && parent->type == XML_NODE_EXP_COLLECTION && parent->n_exp_collection != nullptr)
        {
            //m_current_schema->add_exp_record
            parent->n_exp_collection->add_record(m_current_exp_record);
            //std::cout << "    Record of Collection " << std::endl;
        }

        m_current_exp_record = nullptr;
    }

    if (elementName == U("PropertyValue"))
    {
        auto p = get_parent_element(0);
        std::shared_ptr<xml_stack_elem> parent = dynamic_pointer_cast<xml_stack_elem>(p);

       // <PropertyValue> is child of <Record>
        if (parent != nullptr && parent->type == XML_NODE_EXP_RECORD && parent->n_exp_record != nullptr)
        {
            //m_current_schema->add_propval
            parent->n_exp_record->add_propval(m_current_propvalue);
            //std::cout << "    PropertyValue " << m_current_propvalue->get_propval_name() << " of Record" << std::endl;
            //std::cout << "               " << m_current_propvalue->get_propval_exprname() << ":" << m_current_propvalue->get_propval_expr() << std::endl;
        }
        m_current_propvalue = nullptr;
    }


}

void edm_model_reader::handle_element(const ::odata::utility::string_t&)
{
}

void edm_model_reader::_process_property(std::shared_ptr<xml_stack_elem> node)
{
    if (m_current_st)
    {
        ::odata::utility::string_t property_name;
        bool is_nullable = false;
        std::shared_ptr<edm_named_type> type;
        unsigned int max_length = undefined_value;
        bool is_unicode = false;
        unsigned int scale = undefined_value;
        unsigned int precision = undefined_value;

        while (move_to_next_attribute())
        {
            auto name  = get_current_element_name();
            auto value = get_current_element_text();

            if (name == U("Name"))
            {
                property_name = value;
            }
            else if (name == U("Nullable"))
            {
                is_nullable = (value == U("true"));
            }
            else if (name == U("Type"))
            {           
                type = edm_model_utility::get_edm_type_from_name(value);
                
                if (!type)
                {
                    // we have to parse the real type after first round parsing
                    type = std::make_shared<edm_named_type>(value, U(""), edm_type_kind_t::Unknown);
                }
            }
            else if (name == U("MaxLength"))
            {
                odata::utility::bind(value.c_str(), max_length);
            }
            else if (name == U("Unicode"))
            {
                is_unicode = (value == U("true"));
            }
            else if (name == U("Scale"))
            {
                odata::utility::bind(value.c_str(), scale);
            }
            else if (name == U("Precision"))
            {
                odata::utility::bind(value.c_str(), precision);
            }
        }

        auto prop = std::make_shared<edm_property_type>(property_name, is_nullable, max_length, is_unicode, scale);
        prop->set_property_type(type);
        prop->set_precision(precision);
        m_current_st->add_property(prop);
        node->n_prop_type = prop; //snapper
    }
    else if (m_current_enum)
    {
        ::odata::utility::string_t enum_name;
        unsigned long enum_value;

        while (move_to_next_attribute())
        {
            auto name  = get_current_element_name();
            auto value = get_current_element_text();

            if (name == U("Name"))
            {
                enum_name = value;
            }
            else if (name == U("Value"))
            {
                odata::utility::bind(value.c_str(), enum_value);
            }
        }

        auto prop = std::make_shared<edm_enum_member>(enum_name, enum_value);
        m_current_enum->add_enum_member(prop);
        node->n_enum_member = prop; //snapper
    }

}

void edm_model_reader::_process_navigation_property(std::shared_ptr<xml_stack_elem> node)
{
    if (m_current_st)
    {
        ::odata::utility::string_t property_name;
        ::odata::utility::string_t partner_name;
        ::odata::utility::string_t type_name;
        bool is_contained = false;
        bool is_nullable = false;

        while (move_to_next_attribute())
        {
            auto name  = get_current_element_name();
            auto value = get_current_element_text();

            if (name == U("Name"))
            {
                property_name = value;
            }
            else if (name == U("Nullable"))
            {
                is_nullable = (value == U("true"));
            }
            else if (name == U("Partner"))
            {
                partner_name = value;
            }
            else if (name == U("Type"))
            {
                type_name = value;
            }
            else if (name == U("ContainsTarget"))
            {
                is_contained = (value == U("true"));
            }
        }

        
        auto type = std::make_shared<edm_navigation_type>(type_name, partner_name, is_contained); 
        auto prop = std::make_shared<edm_property_type>(property_name, is_nullable, type);
        m_current_st->add_property(prop);
		node->n_navprop = prop;
    }
}

void edm_model_reader::_process_navigation_property_binding()
{
    ::odata::utility::string_t property_path_name;
    ::odata::utility::string_t target_name;

    while (move_to_next_attribute())
    {
        auto name  = get_current_element_name();
        auto value = get_current_element_text();

        if (name == U("Path"))
        {
            property_path_name = value;
        }
        else if (name == U("Target"))
        {
            target_name = value;
        }
    }

    if (m_current_entity_set)
    {
        m_current_entity_set->add_navigation_source(property_path_name, target_name);
    }
    else if (m_current_singleton)
    {
        m_current_singleton->add_navigation_source(property_path_name, target_name);
    }
}

void edm_model_reader::_process_operation_parameter(std::shared_ptr<xml_stack_elem> node)
{
    if (m_current_operation)
    {
        ::odata::utility::string_t param_name;
        std::shared_ptr<edm_named_type> param_type;

        while (move_to_next_attribute())
        {
            auto name  = get_current_element_name();
            auto value = get_current_element_text();

            if (name == U("Name"))
            {
                param_name = value;
            }
            else if (name == U("Type"))
            {
                param_type = std::make_shared<edm_named_type>(value, U(""), edm_type_kind_t::Unknown);
            }
        }

        auto param = std::make_shared<edm_operation_parameter>(param_name, param_type);

        m_current_operation->add_operation_parameter(param);
        node->n_param =  param;
    }
}

void edm_model_reader::_process_operation_return_type(std::shared_ptr<xml_stack_elem> node)
{
    if (m_current_operation)
    {
        auto return_type = std::make_shared<edm_named_type>();

        while (move_to_next_attribute())
        {
            auto name  = get_current_element_name();
            auto value = get_current_element_text();

            if (name == U("Type"))
            {
                return_type = std::make_shared<edm_named_type>(value, U(""), edm_type_kind_t::Unknown);
            }
        }        

        m_current_operation->set_return_type(return_type);
        node->n_return_t = return_type;
    }
}

void edm_model_reader::_dump_results()
{    
    std::cout << "******data model dump results: version " << m_model->get_version() << " schema number " << m_model->get_schema().size() << "******"<< std::endl;
    for (auto sc = m_model->get_schema().cbegin(); sc != m_model->get_schema().cend(); ++sc)
    {
        ::odata::utility::string_t schema_name = (*sc)->get_name();
        std::cout << " ---- schema             [" << schema_name << "] ---- " << std::endl;
        auto ets = (*sc)->get_entity_types_vector();
        for (auto ele = ets.cbegin(); ele != ets.cend(); ++ele)
        {            
           ::odata::utility::string_t name = (*ele)->get_name();
           std::cout << "    Entity Type name    [" << name << "]: "<<(*ele)->get_base_type_name() <<"  , key name ";

           std::vector<::odata::utility::string_t> keyname = (*ele)->key();
           for (auto it = keyname.begin(); it != keyname.end(); ++it)
               std::cout << "<" << (*it) << "> ";
           std::cout << std::endl;

           auto props = (*ele)->get_properties_vector();
           for (auto it = props.begin(); it != props.end(); ++it)
           std::cout << "        property  <" << (*it)->get_name() << "> : " << (*it)->get_property_type()->get_name() << std::endl;

        }

        auto cts = (*sc)->get_complex_types_vector();
        for (auto ele = cts.cbegin(); ele != cts.cend(); ++ele)
        {            
           ::odata::utility::string_t name = (*ele)->get_name();
           std::cout << "    Complex Type name   [" << name << "]: " << (*ele)->get_base_type_name() << std::endl;

           auto props = (*ele)->get_properties_vector();
           for (auto it = props.begin(); it != props.end(); ++it)
               std::cout << "        property  <" << (*it)->get_name() << "> : " << (*it)->get_property_type()->get_name() << std::endl;

        }

        auto ents = (*sc)->get_enum_types_vector();
        for (auto ele = ents.cbegin(); ele != ents.cend(); ++ele)
        {            
           ::odata::utility::string_t name = (*ele)->get_name();
           std::cout << "    Enum Type name      [" << name << "]" << std::endl;
        }

        //snapper
        auto tdefs = (*sc)->get_type_defs_vector();
        for (auto ele = tdefs.cbegin(); ele != tdefs.cend(); ++ele)
        {            
           ::odata::utility::string_t name = (*ele)->get_name();
           std::cout << "    Type Definition name      [" << name << "]" << std::endl;
        }

        auto opts = (*sc)->get_operation_types_vector();
        for (auto ele = opts.cbegin(); ele != opts.cend(); ++ele)
        {            
           ::odata::utility::string_t name = (*ele)->get_name();
           std::cout << "    Operation Type name [" << name << "]" << std::endl;
        }

        auto conts = (*sc)->get_containers_vector();
        for (auto ele = conts.cbegin(); ele != conts.cend(); ++ele)
        {            
           ::odata::utility::string_t name = (*ele)->get_name();
           std::cout << "    Container name      [" << name << "]" << std::endl;

           auto es = (*ele)->get_entity_set_vector();
           for (auto it = es.begin(); it != es.end(); ++it)
               std::cout << "        entity set :  <" << (*it)->get_name() << ">" << std::endl;

           auto st = (*ele)->get_singleton_vector();
           for (auto it = st.begin(); it != st.end(); ++it)
               std::cout << "        singleton :  <" << (*it)->get_name() << ">" << std::endl;

           auto op = (*ele)->get_operation_import_vector();
           for (auto it = op.begin(); it != op.end(); ++it)
               std::cout << "        operation :  <" << (*it)->get_name() << ">" << std::endl;
        }

        std::cout << std::endl;
    }
    std::cout << "end of model schemas " << std::endl;

}
//snapper dump types in model
void edm_model_reader::dump_model()
{
    _dump_results();
}


std::shared_ptr<bson::BSONObj> edm_model_reader::resolve_json(std::string srcdir, std::string ns)
{
    std::string jsonschema_dir(srcdir);
    DIR *dp;
    struct dirent *dirp;
    if ((dp  = opendir(jsonschema_dir.c_str())) == NULL) 
    {
        std::cout << "opendir error" << std::endl;
        return nullptr;
    }

    vector<::odata::utility::string_t> fileNameList;
    while ((dirp = readdir(dp)) != NULL) 
    {
        std::string filename = string(dirp->d_name);

        std::size_t found = filename.find_first_of(".");
        if (found != std::string::npos && found > 1)
        {
            ::odata::utility::string_t fileExt  = filename.substr(found);

            if (fileExt.find(".json") !=  std::string::npos)
            {
                ::odata::utility::string_t absFilename = jsonschema_dir + "/" + filename;
                fileNameList.push_back(absFilename);
                //std::cout << absFilename << std::endl;
            }
        }
    }
    closedir(dp);


    for (unsigned int i = 0; i < fileNameList.size(); i++)
    {
        std::string fileName = fileNameList[i];
        std::ifstream ifs(fileName);        
        std::stringstream buffer;  

        buffer << ifs.rdbuf();  
        std::string contents(buffer.str());  

        std::string jstr = contents.substr(0, contents.find_last_of("}")+1);//remove \n \r 
        bson::BSONObj c= bson::fromjson(jstr);
        std::string title =  c.getStringField("title");

        if(title.find(ns) == 1)// pos 1 "#XXXX"
        {
            //std::cout << "find namespace " << ns << " from " << fileName << std::endl;
            return std::make_shared<bson::BSONObj>(c);
        }
    }

    //std::cout << "name space " << ns <<" not found from json schema " << std::endl;
    return nullptr;
}

///////////////////////////////////////////////////////////////////////
// get properties of base class/resource in Resource_v1.xml
// and generate _pResource.h
///////////////////////////////////////////////////////////////////////
void edm_model_reader::_gen_baseClass(std::string dir, std::map<std::string, std::vector<std::string>> &baseClassProp)
{
    
    std::stringstream fname;
    FILE *fp_resource = NULL;
    
    fname.str("");
    fname << dir << "/_pResource.h";
    //std::cout << it->first << " : "<< it->second << std::endl;
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
#pragma GCC diagnostic ignored "-Wformat-security"		
    
    fp_resource = fopen(fname.str().c_str(), "w+");
    if(fp_resource == NULL){
        std::cout << "failed to generate class " << fname.str().c_str() << std::endl;
        return;
    }
    else
    {
        fprintf(fp_resource, sHdr, "Resource");
    }

    //workaround Oem property in Resource.Item
    baseClassProp["ResourceProvider"].push_back("Oem");
    baseClassProp["ReferenceableMemberProvider"].push_back("Oem");

    for (auto sc = m_model->get_schema().cbegin(); sc != m_model->get_schema().cend(); ++sc)
    {
        auto ets = (*sc)->get_entity_types_vector();
        for (auto ele = ets.cbegin(); ele != ets.cend(); ++ele)
        {              
            ::odata::utility::string_t name = (*ele)->get_name();
            if(name.compare("Resource") && name.compare("ResourceCollection") && name.compare("ReferenceableMember"))
                continue;

            // enum type definition in Resource_v1.xml, like ResetType,Health,State
            if((name.compare("Resource") == 0) && fp_resource)
            {
                for(auto ite = (*sc)->get_enum_types().cbegin(); ite != (*sc)->get_enum_types().cend(); ite++)
                {
                    fprintf(fp_resource, sNS_Class_enum_header, ite->first.c_str()); 
                                    
                    auto enum_members = ite->second;
                    for(auto it = enum_members->get_enum_members().cbegin(); it != enum_members->get_enum_members().cend(); it++)
                    {
                        ::odata::utility::string_t member = ite->first + "_" + (*it)->get_enum_member_name();
                        fprintf(fp_resource, sNS_Class_enum_body, member.c_str());
                    }
                                
                    fprintf(fp_resource, sNS_Class_enum_tail);
                } 
            }
            
            auto props = (*ele)->get_properties_vector();//properties of base resource classes. like "Description", "Name", "Oem", "MemberId", "Id" etc
            for (auto itp = props.begin(); itp != props.end(); ++itp){
                if(name.compare("Resource") == 0)
                    baseClassProp["ResourceProvider"].push_back((*itp)->get_name());
                else if(name.compare("ResourceCollection") == 0)
                    baseClassProp["ResourceCollectionProvider"].push_back((*itp)->get_name());
                else if(name.compare("ReferenceableMember") == 0)
                    baseClassProp["ReferenceableMemberProvider"].push_back((*itp)->get_name());
                //std::cout << name << "  property <" << (*itp)->get_name() << "> : " << (*itp)->get_property_type()->get_name() << std::endl;
            }
        }
    }

    fclose(fp_resource);

}
void edm_model_reader::_gen_write_hdr(FILE *fp, char *entity, char *classname)
{
	//file header
	fprintf(fp, sHdr, entity);
	fprintf(fp, sHdr_Includes, entity);
	//class header
	fprintf(fp, sNS_Class_Hdr, entity, classname);

}
void edm_model_reader::_gen_write_enum(FILE *fp, ::odata::utility::string_t entityname)
{
    //find additional oem schema: 
    //   entity AccountService->schema OemShimAccountService, lenovo complex  LenovoAccountService.v1_0_0 . LenovoAccountServiceInfo
    //           -> AuthMode defined in LenovoAccountService.v1_0_0
    std::vector<std::string> lenovoNamespace;
    std::vector<std::string> lenovoComplex;
    _gen_get_OemLenovo_complex(entityname, lenovoNamespace, lenovoComplex);

    for (auto sc = m_model->get_schema().cbegin(); sc != m_model->get_schema().cend(); ++sc)
    {            
        bool foundschema = false;

        // oem schema
        for(int n = 0; n < lenovoNamespace.size(); n++)
        {
            if(lenovoNamespace[n].compare((*sc)->get_name()) == 0)
                foundschema = true;
        }

        // standard schema
        auto ets = (*sc)->get_entity_types_vector();
        for (auto ele = ets.cbegin(); ele != ets.cend(); ++ele)
        {             
            ::odata::utility::string_t name = (*ele)->get_name();
            if(name.compare(entityname) == 0)
                foundschema = true;

        }

        if(foundschema == false)
            continue;

        // enum type definition
        for(auto ite = (*sc)->get_enum_types().cbegin(); ite != (*sc)->get_enum_types().cend(); ite++)
        {
            auto enum_members = ite->second;
            if(annotation_has_term(enum_members->get_annotation_list(), ANNOTATION_TERM_DEPRECATED) == true)
            {
                std::cout << "EnumType " << enum_members->get_name() << " is deprecated !!!" << std::endl;
                continue;
            }

            fprintf(fp, sNS_Class_enum_header, ite->first.c_str()); 
            
            for(auto it = enum_members->get_enum_members().cbegin(); it != enum_members->get_enum_members().cend(); it++)
            {
                ::odata::utility::string_t member = ite->first + "_" + (*it)->get_enum_member_name();

                if(annotation_has_term((*it)->get_annotation_list(), ANNOTATION_TERM_DEPRECATED) == true)
                {
                    std::cout << "enum member " << member << " is deprecated !!!" << std::endl;
                    continue;
                }

                fprintf(fp, sNS_Class_enum_body, member.c_str());
            }
        
            fprintf(fp, sNS_Class_enum_tail);
        }                
         
    }

}

//generate header file for schemas which has no entity type but has enum type
void edm_model_reader::_gen_enum_only(std::string dir)
{
    std::map<string, int> file_map;
    for (auto sc = m_model->get_schema().cbegin(); sc != m_model->get_schema().cend(); ++sc)
    {            
        auto ets = (*sc)->get_entity_types_vector();
        auto enums = (*sc)->get_enum_types_vector();
        if(ets.empty() && !enums.empty())
        {
            string sc_name = (*sc)->get_name();
            sc_name = sc_name.substr(0, sc_name.find_first_of("."));
            if(sc_name.compare("Resource") == 0)
                continue;
            
            std::stringstream fname;
            FILE *fp = NULL;
    
            fname.str("");
            fname << dir << "/_p" << sc_name << ".h";
            if(file_map.find(fname.str().c_str()) != file_map.end())
            {
                fp = fopen(fname.str().c_str(), "a+");
            }
            else
            {
                fp = fopen(fname.str().c_str(), "w+");                
                fprintf(fp, sHdr, sc_name.c_str());
                file_map.insert(std::make_pair(fname.str().c_str(), 1));                
            }
            
            if(fp == NULL){
                std::cout << "failed to generate class " << fname.str().c_str() << std::endl;
                return;
            }
            
             // enum type definition
            for(auto ite = (*sc)->get_enum_types().cbegin(); ite != (*sc)->get_enum_types().cend(); ite++)
            {
                fprintf(fp, sNS_Class_enum_header, ite->first.c_str()); 
                
                auto enum_members = ite->second;
                for(auto it = enum_members->get_enum_members().cbegin(); it != enum_members->get_enum_members().cend(); it++)
                {
                    ::odata::utility::string_t member = ite->first + "_" + (*it)->get_enum_member_name();
                    fprintf(fp, sNS_Class_enum_body, member.c_str());
                }
            
                fprintf(fp, sNS_Class_enum_tail);
            }
            fclose(fp);
        }
        
    }

}


void edm_model_reader::_gen_write_prop(FILE *fp, ::odata::utility::string_t entityname)
{
    std::map<std::string, int> props_of_entity;
    for (auto sc = m_model->get_schema().cbegin(); sc != m_model->get_schema().cend(); ++sc)
    {            
        auto ets = (*sc)->get_entity_types_vector();
        for (auto ele = ets.cbegin(); ele != ets.cend(); ++ele)
        {             
            ::odata::utility::string_t name = (*ele)->get_name();
            if(name.compare(entityname))
                continue;

            auto props = (*ele)->get_properties_vector();
            for (auto itp = props.begin(); itp != props.end(); ++itp){
				//std::cout << "	  property	<" << (*itp)->get_name() << "> : " << (*itp)->get_property_type()->get_name() << std::endl;

                string prop_name = (*itp)->get_name().c_str();
                if(annotation_has_term((*itp)->get_annotation_list(), ANNOTATION_TERM_DEPRECATED) == true)
                {
                    std::cout << "property " << prop_name << " is deprecated !!!" << std::endl;
                    continue;
                }
				props_of_entity[prop_name] = 0; //normal property

                //navigation property
                if ((*itp)->get_property_type()->get_type_kind() == edm_type_kind_t::Navigation)
                {
                   auto navigation_type = std::static_pointer_cast<::odata::edm::edm_navigation_type>((*itp)->get_property_type());
                   auto type = navigation_type->get_navigation_type();
                   
                   if (type)
                   {
                       auto type_name = type->get_name();
                       //std::cout << entityname << ": NavProp " << type_name << " " << type->get_type_kind() << ", " << (*itp)->get_name() << std::endl;

                       // in this case type->get_type_kind() == edm_type_kind_t::Collection(4), the type is "Collection(ResourceType)" in xml
                       // and type is "array" in json. the prop name likes  "Members", "Temperatures"
                       // example of response PCIeDevices@odata.navigationLink:"/redfish/v1/Systems/1/PCIeDevices", Members@odata.navigationLink:"/redfish/v1/Systems/Members"
                       if(type_name.find("Collection(") != std::string::npos && type_name.find(")") != std::string::npos)
                            props_of_entity[prop_name] = 1; //navigation array property
                       else if(type->get_type_kind() == edm_type_kind_t::Entity)
                            props_of_entity[prop_name] = 2; //navigation ref property
                   }


                }

            }

         }
    }

    std::map<std::string, int>::iterator it;
    for(it=props_of_entity.begin();it!=props_of_entity.end();++it)
    {
        std::string propname = it->first;
        int proptype = it->second;

        fprintf(fp, sNS_Class_Prop1, propname.c_str());
        if(proptype == 1)//navprop collection
        {
            fprintf(fp, sNS_Class_Prop2, propname.c_str(), "@odata.count");
            fprintf(fp, sNS_Class_Prop2, propname.c_str(), "@odata.navigationLink");
        }
    }

}
void edm_model_reader::property_class_map(std::map< std::string, std::vector<std::string> > & prop_class, std::shared_ptr<edm_property_type> prop)
{
/*
removed proprietary code
*/
}

void edm_model_reader::_gen_write_prop_classmap(FILE *fp, std::map<std::string, std::string> &resouces, ::odata::utility::string_t entityname)
{
/*
removed proprietary code
*/
}

void edm_model_reader::_gen_set_nav_prop(FILE *fp, ::odata::utility::string_t entityname)
{
/*
removed proprietary code
*/
}

void edm_model_reader::_gen_write_Links_prop(FILE *fp, ::odata::utility::string_t entityname)
{
/*
removed proprietary code
*/
}

string edm_model_reader::_gen_write_cur_namespace(FILE *fp, ::odata::utility::string_t entityname)
{
    ::odata::utility::string_t current_namespace(""); //namespace includes the version information
    ::odata::utility::string_t current_desc("");
    ::odata::utility::string_t ns_for_desc("");
    for (auto sc = m_model->get_schema().cbegin(); sc != m_model->get_schema().cend(); ++sc)
    {            
        auto ets = (*sc)->get_entity_types_vector();
        for (auto ele = ets.cbegin(); ele != ets.cend(); ++ele)
        {             
            ::odata::utility::string_t name = (*ele)->get_name();
            if(name.compare(entityname))
                continue;

            auto enm = (*sc)->get_name();//get latest version
            ::odata::utility::string_t entity_namespace = enm;
            if(enm.find(OEM_PREFIX) != std::string::npos)//oem schema
            {
                entity_namespace = enm.substr(enm.find(OEM_PREFIX)+strlen(OEM_PREFIX));
                //std::cout << enm << " -> " << entity_namespace << std::endl;
            }
            if (current_namespace.empty() || (!current_namespace.empty() && (entity_namespace.compare(current_namespace) > 0)))
            {
                current_namespace = entity_namespace;
            }

            //get description of latest namespace if it has description
            auto notations = (*ele)->get_annotation_list();
            for(int i = 0; i < notations.size() && notations[i] != nullptr; i++)
            {
                string desc;
                if(notations[i]->get_name().compare(ANNOTATION_TERM_DESC) != 0)
                    continue;
                desc = notations[i]->get_attribute(ANNOTATION_ATTR_STRING);
                if(desc.length() == 0)
                    continue;

                if (current_desc.empty() || (!current_desc.empty() && (entity_namespace.compare(ns_for_desc) > 0)))
                {
                    current_desc = desc;
                    //std::cout << ns_for_desc << " --> " << entity_namespace << std::endl;
                    ns_for_desc = entity_namespace;
                    //std::cout << ns_for_desc << "    ---  :" << notations[i]->get_attribute(ANNOTATION_ATTR_STRING) << std::endl;
                }
            }


        }
    }

    fprintf(fp, sNS_Class_Set_Version, current_namespace.c_str());
    if(!current_desc.empty())
        fprintf(fp, sNS_Class_Set_Description, current_desc.c_str());
    //std::cout <<  current_namespace << "---" << current_desc << std::endl;

#if 0
    //get description of schema
    std::shared_ptr<bson::BSONObj> jobj = resolve_json(m_jsondir, current_namespace);
    if(jobj == nullptr)
    {
        std::cout << "no namespace " << current_namespace << " found from jsonschema " << std::endl;
        return current_namespace;
    }
    std::string path = "definitions."+entityname+".description";
    bson::BSONElement be= jobj->getFieldDotted(path);
    if(be.eoo() == true || be.type() != bson::String)
    {
        std::cout << "description element not found for: " << path << std::endl;
        return current_namespace;
    }
    std::string description = be.String();
    //std::cout <<  entityname << "---" << description << std::endl;

    fprintf(fp, sNS_Class_Set_Description, description.c_str());
#endif
    return current_namespace;
}
void edm_model_reader::_gen_get_OemLenovo_complex(::odata::utility::string_t entityname, std::vector<std::string> &lenovoNamespace, std::vector<std::string> &lenovoComplex)
{
/*
removed proprietary code
*/
}

void edm_model_reader::_gen_write_Oem_prop(FILE *fp, std::map<std::string, std::string> &resouces, ::odata::utility::string_t entityname)
{
/*
removed proprietary code
*/
}

void edm_model_reader::_gen_write_Lenovo_complex(FILE *fp, std::map<std::string, std::string> &resouces, ::odata::utility::string_t schemaname, ::odata::utility::string_t complexname)
{
/*
removed proprietary code
*/
}

void edm_model_reader::_gen_write_action(FILE *fp, ::odata::utility::string_t entityname)
{
/*
removed proprietary code
*/
}

void edm_model_reader::_gen_write_prop_attributes(FILE *fp, ::odata::utility::string_t entityname, ::odata::utility::string_t nm)
{
/*
removed proprietary code
*/
}

void edm_model_reader::_gen_ResourceName(std::map<std::string, std::string> &resouces)
{
/*
removed proprietary code
*/
}

void edm_model_reader::gen_resource_provider(std::string dir, std::string xmldir, std::string jsondir)
{
/*
removed proprietary code
*/
}

void edm_model_reader::gen_root_metadata_file(std::string tgtdir, std::string xmldir)
{
/*
removed proprietary code
*/
}

}}
