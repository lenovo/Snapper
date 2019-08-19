//---------------------------------------------------------------------
// <copyright file="edm_model_reader.h" company="Microsoft">
//      Copyright (C) Microsoft Corporation. All rights reserved. See License.txt in the project root for license information.
// </copyright>
//---------------------------------------------------------------------

#pragma once

#include "odata/edm/odata_edm.h"
#include "odata/common/xmlhelpers.h"
#include "bson/bson.h"
#include "bson/util/json.h"

using namespace bson;
namespace odata { namespace edm
{

//snapper
class xml_stack_elem : public ::odata::edm::xml_elem
{
public:
    std::shared_ptr<edm_model> n_model;
    std::shared_ptr<edm_schema> n_schema;
    std::shared_ptr<edm_entity_container> n_container;
    std::shared_ptr<edm_entity_set> n_entity_set;
    std::shared_ptr<edm_singleton> n_singleton;
    std::shared_ptr<edm_operation_import> n_op_import;
    edm_structured_type* n_struct;
    edm_enum_type* n_enum;
    edm_type_def* n_typedef;
    edm_operation_type* n_operation;
    std::shared_ptr<edm_property_type> n_prop_type;
    std::shared_ptr<edm_enum_member> n_enum_member;
    std::shared_ptr<edm_property_type> n_navprop;
    std::shared_ptr<edm_operation_parameter> n_param;
    std::shared_ptr<edm_named_type> n_return_t;
    edm_payload_annotation_type* n_annotation;
    std::shared_ptr<edm_expr_collection> n_exp_collection;
    std::shared_ptr<edm_expr_record> n_exp_record;
    std::shared_ptr<edm_prop_value> n_propvalue;

    xml_stack_elem(XML_ELEM_TYPE t, ::odata::utility::string_t n)
    {
        type = t;
        name = n;
        reset();
    }
    virtual void reset() 
    {
        n_model = nullptr;
        n_schema = nullptr;
        n_container = nullptr;
        n_entity_set = nullptr;
        n_singleton = nullptr;
        n_op_import = nullptr;
        n_struct = NULL;
        n_enum = NULL;
        n_typedef = NULL;
        n_operation = NULL;
        n_prop_type = nullptr;
        n_enum_member = nullptr;
        n_navprop = nullptr;
        n_param = nullptr;
        n_return_t = nullptr;
        n_annotation = NULL;
        n_exp_collection = nullptr;
        n_exp_record = nullptr;
    }
    void attach_annotation(edm_payload_annotation_type *);
};

class edm_model_reader : public ::odata::edm::xml_reader
{
public:
    edm_model_reader(std::istream& stream) : 
		xml_reader(stream), m_parsing_key(false), m_model(std::make_shared<edm_model>()), 
		m_current_st(nullptr), m_current_enum(nullptr), m_current_typedef(nullptr), m_current_operation(nullptr), 
		m_current_at(nullptr), m_current_exp_record(nullptr), m_current_exp_collection(nullptr), m_current_propvalue(nullptr)
    {
    }

    //snapper: multiple readers share same model pointer
    edm_model_reader(std::istream& stream, std::shared_ptr<edm_model> onemodel) : 
		xml_reader(stream), m_parsing_key(false), m_model(onemodel), 
		m_current_st(nullptr), m_current_enum(nullptr), m_current_typedef(nullptr), m_current_operation(nullptr),
		m_current_at(nullptr), m_current_exp_record(nullptr), m_current_exp_collection(nullptr), m_current_propvalue(nullptr)
    {
    }


    std::shared_ptr<edm_model> get_model()
    {
        return m_model;
    }

	ODATACPP_API bool parse();

    //snapper: separate parsing and resolving of types
	ODATACPP_API bool parse_edm();
	void resolve_edm();

    //snapper
    void gen_resource_provider(std::string tgtdir, std::string xmldir, std::string jsondir);
    void gen_root_metadata_file(std::string tgtdir, std::string xmldir);
    std::shared_ptr<bson::BSONObj> resolve_json(std::string srcdir, std::string ns);
    void dump_model();
    std::string  m_xmldir;
    std::string  m_jsondir;


protected:
    ODATACPP_API virtual std::shared_ptr<xml_elem> handle_begin_element(const ::odata::utility::string_t& elementName);
    ODATACPP_API virtual void handle_end_element(const ::odata::utility::string_t& elementName);
    ODATACPP_API virtual void handle_element(const ::odata::utility::string_t& elementName);


private:
    void _process_property(std::shared_ptr<xml_stack_elem> node);
	void _process_navigation_property(std::shared_ptr<xml_stack_elem> node);
	void _process_operation_parameter(std::shared_ptr<xml_stack_elem> node);
	void _process_operation_return_type(std::shared_ptr<xml_stack_elem> node);
	void _process_navigation_property_binding();
    void _dump_results();

    void _gen_ResourceName(std::map<std::string, std::string> &resouces);
    void _gen_baseClass(std::string dir, std::map<std::string, std::vector<std::string>> &baseClassProp);
    void _gen_write_hdr(FILE *fp, char *entity, char *classname);
    void _gen_write_enum(FILE *fp, ::odata::utility::string_t entityname);
    void _gen_enum_only(std::string dir);
    void _gen_write_prop(FILE *fp, ::odata::utility::string_t entityname);
    void property_class_map(std::map< std::string, std::vector<std::string> > & prop_class, std::shared_ptr<edm_property_type> prop);
    void _gen_write_prop_classmap(FILE *fp, std::map<std::string, std::string> &resouces, ::odata::utility::string_t entityname);
    void _gen_write_Links_prop(FILE *fp, ::odata::utility::string_t entityname);
    void _gen_set_nav_prop(FILE *fp, ::odata::utility::string_t entityname);
    std::string _gen_write_cur_namespace(FILE *fp, ::odata::utility::string_t entityname);
    void _gen_write_action(FILE *fp, ::odata::utility::string_t entityname);    
    void _gen_write_prop_attributes(FILE *fp, ::odata::utility::string_t entityname, ::odata::utility::string_t nm);
    void _gen_get_OemLenovo_complex(::odata::utility::string_t entityname, std::vector<std::string> &lenovoNamespace, std::vector<std::string> &lenovoComplex);
    void _gen_write_Oem_prop(FILE *fp, std::map<std::string, std::string> &resouces, ::odata::utility::string_t entityname);
    void _gen_write_Lenovo_complex(FILE *fp, std::map<std::string, std::string> &resouces, ::odata::utility::string_t ns, ::odata::utility::string_t complexname);
    bool m_parsing_key;

    // These variables are used to cache values for each entity
    std::shared_ptr<edm_model> m_model;
    std::shared_ptr<edm_schema> m_current_schema;
    std::shared_ptr<edm_entity_container> m_current_container;
	std::shared_ptr<edm_entity_set> m_current_entity_set;
	std::shared_ptr<edm_singleton> m_current_singleton;
    edm_structured_type* m_current_st;
	edm_enum_type* m_current_enum;
	edm_operation_type* m_current_operation;
//snapper
	edm_type_def* m_current_typedef;
    edm_payload_annotation_type* m_current_at;
	std::shared_ptr<edm_expr_record> m_current_exp_record;
	std::shared_ptr<edm_expr_collection> m_current_exp_collection;
	std::shared_ptr<edm_prop_value> m_current_propvalue;

/////////////////////////////////////////////
// define static text of header code
/////////////////////////////////////////////
    const char *sHdr = 
"//---------------------------------------------------------------------\n"
"// <copyright file=\"_p%s.h\" company=\"Lenovo\">\n"
"//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.\n"
"// </copyright>\n"
"//---------------------------------------------------------------------\n\n"
"#pragma once \n\n";

    const char *sHdr_Includes =
"#include \"_pResource.h\"\n"
"#include \"SnapperProvider.h\"\n";

    const char *sNS_Class_Hdr = 
"namespace snapper { namespace providers \n"
"{\n\n"
"class _p%s : public %s\n"
"{\n"
"public:\n";

    const char *sNS_Class_Func1 = 
"    _p%s() : %s(\"%s\")    \n"
"    {\n";

    const char *sNS_Class_enum_header = 
"        enum %s \n"
"        {\n";

const char *sNS_Class_enum_body = 
"            %s,\n";

    const char *sNS_Class_enum_tail = 
"        };\n\n";

    const char *sNS_Class_Prop1 = 
"        create_prop(\"%s\",  nullptr);\n";

    const char *sNS_Class_Prop2 = 
"        create_prop(\"%s%s\",  nullptr);\n";

    const char *sNS_Class_Nav_Prop1 = 
"        add_navigation_arr_props(\"%s\");\n";

    const char *sNS_Class_Nav_Prop2 = 
"        add_navigation_contained_props(\"%s\");\n";

    const char *sNS_Class_Nav_Prop3 = 
"        add_navigation_refer_props(\"%s\");\n";

    const char *sNS_Class_OEMLenovo_Nav_Prop4 = 
"        add_OemLenovo_nav_arr_props(\"%s\");\n";

    const char *sNS_Class_Nav_Prop_comment = 
"        // direct GET request for following navigation properties should be handled in this provider\n";

    const char *sNS_Prep_Nav_Prop = 
"        prepare_navigation_property();\n";

    const char *sNS_Prep_Links_Prop = 
"        prepare_Links();\n";

    const char *sNS_Prep_OemLenovo_Prop = 
"        prepare_OemLenovo();\n";

    const char *sNS_Prep_Prop_Class_Map = 
"        prepare_prop_class();\n";

    const char *sNS_Prep_Prop_Attr_Map = 
"        prep_prop_attrs();\n";

    const char *sNS_Class_blank_line = 
"        \n";

    const char *sNS_Class_Prop3 = 
"        m_Links_prop_objs[\"%s\"] = nullptr;\n";

    const char *sNS_Class_Prop4 = 
"        m_Links_prop_objs[\"%s%s\"] = nullptr;\n";

    const char *sNS_Class_Prop5 = 
"        add_Links_arr_props(\"%s\");\n";

    const char *sNS_Class_Prop6 = 
"        create_OemLenovo_prop(\"%s\", nullptr);\n";

    const char *sNS_Class_Prop7 = 
"        create_OemLenovo_prop(\"%s\", std::make_shared<bson::BSONObj>(BSON(\"%s\" << \"#%s.%s\")));\n";

    const char *sNS_Class_Set_Version = 
"        set_namespace(\"%s\");\n";

    const char *sNS_Class_Set_Description = 
"        set_desc(\"%s\");\n";

    const char *sNS_Class_Func1_end = 
"    }\n\n"
"    virtual ~_p%s()    \n"
"    {}\n\n";

    const char *sNS_Prep_Nav_Func = 
"    void prepare_navigation_property()\n"
"    {\n";

    const char *sNS_Prep_Links_Func = 
"    void prepare_Links()\n"
"    {\n";

    const char *sNS_Prep_OemLenovo_Func = 
"    void prepare_OemLenovo()\n"
"    {\n";

    const char *sNS_Prep_Prop_Class_Map_Func = 
"    void prepare_prop_class()\n"
"    {\n";
    
    const char *sNS_Add_Prop_Class = 
"        add_property_class(\"%s\", \"%s\", \"%s\");\n";

    const char *sNS_Add_OemProp_Class = 
"        add_property_class(\"Oem/Lenovo/%s\", \"%s\", \"%s\");\n";


    const char *sNS_Func_END = 
"    }\n\n";

    const char *sNS_Class_add_actions_start = 
"    virtual void set_actions_obj()\n"
"    {\n ";

    const char *sNS_Class_add_actions_end = 
"        create_prop( \"Actions\",   std::make_shared<bson::BSONObj>(BSON(\"Actions\" << %s)) );\n "
"    }\n\n";
    
    const char *sNS_Class_add_prop_attr_start = 
"    void prep_prop_attrs()\n"
"    {\n ";

    const char *sNs_Class_add_Prop_enum_start =
"       auto %s_attr = std::make_shared<prop_attribute>();\n"
"        %s_attr->prop_name = \"%s\";\n";
    
    const char *sNs_Prep_add_Prop_readonly =
"        %s_attr->read_only = %s;\n";

    const char *sNs_Prep_add_Prop_requiredOnCreate =
"        %s_attr->required_on_create = true;\n";

    const char *sNs_Prep_add_Prop_enum =
"        %s_attr->add_enum(\"%s\");\n";
        
    const char *sNS_Class_add_prop_attr_body = 
"        add_property_attr(\"%s\", %s_attr);\n\n ";

    const char *sNS_Class_Tail = 
"};\n\n"
"}}\n\n"; 


};

}}
