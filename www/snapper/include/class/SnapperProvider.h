//---------------------------------------------------------------------
// <copyright file="SnapperProvider.h" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details. 
// </copyright>
//---------------------------------------------------------------------

#pragma once
#include "SnapperType.h"
#include "bson/bson.h"
#include "bson/util/json.h"
#include "BaseMessage.h"
#include "StandardErrorMessage.h"
#include "AuditEventMessage.h"
#include "SnapperMessage.h"
#include "rf_engine_error.h"
#include "datainf/DataInterfaceMgr.h"
#include <www/engine/topology.h>

#include <www/engine/request_context.h>
#include <www/engine/rf_debug.h>

using namespace std;
using namespace ::snapper::datamgr;

namespace snapper { namespace providers
{
#define TASK_MONITOR_PATH       "/redfish/v1/Tasks/Tasks"
#define TASK_MONITOR_ID_PRE     "Mon_"

#define EnumString(val) (#val)

#define MAKE_ENUM_STRING(val)   get_raw_enum_str(EnumString(val))

typedef map<string, string> memid_acckey_map;

typedef void *(*CREATE_OBJECT)();

class SnapperProvider;

class ProviderObjectFactory
{
public:
    static std::shared_ptr<SnapperProvider> GetObject(const string &name)
    {
        map<string, std::shared_ptr<SnapperProvider>>::const_iterator it;
        it = objMap.find(name);
        if (it == objMap.end())
            return nullptr;
        else
            return it->second;
    }

    static void Register(string name, std::shared_ptr<SnapperProvider> obj)
    {
        objMap[name] = obj;
    }    
    
private:
    static map<string, std::shared_ptr<SnapperProvider>> objMap;
};

class Register
{
public:
    Register(string name, std::shared_ptr<SnapperProvider> obj)
    {
        ProviderObjectFactory::Register(name, obj);   
    }
};

#define REGISTER_PROVIDER(class_name) \
    class class_name##Register { \
        private: \
            static Register reg; \
    }; \
    Register class_name##Register::reg(#class_name, std::make_shared<class_name>()); 

string build_str(const string s1, const string s2, const string s3 = "", const string s4 = "");
string get_raw_enum_str(const char* str); 

constexpr size_t HASH_STRING(const char *str, size_t hash_num = 0)
{
    return *str ? HASH_STRING(str + 1,(hash_num * 131) + *str) : hash_num;
}

constexpr size_t operator "" _HASH(const char *string_pice,size_t)
{
    return HASH_STRING(string_pice);
}

enum provider_type
{
    Provider_Resource,
    Provider_ResourceCollection,
    Provider_ReferenceableMember,
    Provider_Unknown,
};

class SnapperProvider
{    
    
public:
    
    enum
    {
        read_write = 0,
        read_only  = 1
    };

    struct prop_attribute
    {
        prop_attribute(): read_only(true), required_on_create(false)
        {}

        string prop_name;
        bool read_only; 
        bool required_on_create; 
        vector<string> enum_members;
        void add_enum(string str)
        {
            enum_members.push_back(str);
        }

        vector<string> get_enum_members()
        {
            return enum_members;
        }
    };


    virtual int handle_get(shared_ptr<::snapper::service::request_context> request) = 0;
    virtual int handle_post(shared_ptr<::snapper::service::request_context> request) = 0;
    virtual int handle_patch(shared_ptr<::snapper::service::request_context> request) = 0;    
    virtual int handle_put(shared_ptr<::snapper::service::request_context> request) = 0;    
    virtual int handle_delete(shared_ptr<::snapper::service::request_context> request) = 0;    
    virtual int autoexpand_array(bson::BSONArrayBuilder* a, std::string containing_path = "", std::shared_ptr<bson::BSONObj> q_param = nullptr) = 0;
    virtual char *allows() = 0; // methods allowed [6]: GET HEAD POST PUT PATCH DELETE . the order must match http_method

    // if containing path/uri is not empty, should only return member ids contained by the path
    // the containing_path is combination of containing path and accessor key of containing resource. E.g
    // "/redfish/v1/Systems/1/Storage StorageController_1_Ctlr1". Resource can customize and maintain
    // the definition of accessor key as it may add additional information into the accessor.
    // return nullptr, key validation always pass. return empty map<> will cause validation failure
    virtual std::shared_ptr<memid_acckey_map> getlist_memid_acckey(std::string containing_path = "") = 0; 
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SnapperProvider(std::string name, provider_type type = provider_type::Provider_Unknown):m_type(type), m_name(name) 
    {
        m_http_code = 0;
        settings_obj_flag = false;        
        etag_needed = true;
    }
    
    virtual ~SnapperProvider() {};  

	template <typename T> T *as()
	{
		return dynamic_cast<T *>(this);
	}

    bool check_allow(int method)
    {
        char *m = allows();
        if(m[method] == 0)
            return false;
        else
            return true;
    }

    // return map of <member id, accessor key>
    // if containing path/uri is not empty, should only return member ids contained by the path
    std::shared_ptr<memid_acckey_map> getlist_memid_acckey_fromclass(std::string classname, std::string containing_path = "") 
    {
        auto provider = ProviderObjectFactory::GetObject(classname);
        if(provider == nullptr)
            return nullptr;

        return provider->getlist_memid_acckey(containing_path);
    }

    bool validate_key(const string& key_value, std::string containing_path = "");

    //is Collection(Resource) which is OData.AutoExpand resource or OData.AutoExpandReferences
    bool is_array_property(const string& prop_name);

    const string& get_name() const 
    {
        return m_name;
    }

    const string& get_namespace() const 
    {
        return m_namespace;
    }
    
    std::map<const std::string, std::vector<std::string>> & get_property_class()
    {
        return m_property_class_map;
    }

    map<string, std::shared_ptr<prop_attribute>> & get_property_attr()
    {
        return m_property_attributes;
    }
	
    const provider_type& get_type() const 
    {
        return m_type;
    }    

    const char* get_type_str() const; 

    void override_http_code(int code)
    {
        m_http_code = code;
    }

    int get_http_code()
    {
        return m_http_code;
    }

    std::string serialize_objs();
    std::string serialize_error_obj();
    void reset_obj();
    std::string serialize_resp_hdr(int method);    
    
    std::shared_ptr<bson::BSONObj> MAKE_BSON_NAV_OBJ(const string x) 
    {
        string url = get_base_odata_id() + "/" + x;
        auto acc_key = ::snapper::service::ResourceTopology::search_accessor(url);
        if(acc_key)
            return  std::make_shared<bson::BSONObj>(BSON(x << BSON(ODATA_ID << (get_base_odata_id() + "/" + x))));
        else
            return nullptr;
    }

    std::shared_ptr<bson::BSONObj> MAKE_BSON_LINK_NAV_OBJ(const string name, const string uri) 
    {
        return  std::make_shared<bson::BSONObj>(BSON(name << BSON(ODATA_ID << uri)));
    }

    // make bson obj like {"name": null}
    std::shared_ptr<bson::BSONObj> MAKE_BSON_NULL_OBJ(const string name) 
    {
         bson::BSONObjBuilder b;
         b.appendNull(name);
        return  std::make_shared<bson::BSONObj>(b.obj());
    }
    
    // make bson array obj like {"name": []}
    std::shared_ptr<bson::BSONObj> MAKE_BSON_NULL_ARRAY(const string name) 
    {
         bson::BSONArrayBuilder b;
        return  std::make_shared<bson::BSONObj>(BSON(name << b.arr()));
    }

    int get_Members_class(string &classname)
    {
        if(m_property_class_map.find("Members") == m_property_class_map.end())
            return 0;
        std::vector<std::string> classtype = m_property_class_map["Members"];
        classname=classtype[1];
        return 1;
    }

    const string get_action(shared_ptr<::snapper::service::request_context> request)
    {
        if(request == nullptr)
            return "";
        std::string key = "/Actions/" + get_name();
        std::string path = request->get_raw_path();
        if(request->get_method() == snapper::service::http_post && path.find(key) != string::npos && path.find_last_of(".") != string::npos)
            return path.substr(path.find_last_of(".")+1);

        return "";
    }

    void jcache_clean(shared_ptr<::snapper::service::request_context> request);//clear json cache by resource name when create/patch/put/delete
    void bcache_clean(shared_ptr<::snapper::service::request_context> request);//clear bson cache by metadata key of getData() when create/patch/put/delete
    
    const string& get_etag()
    {
        return m_etag;
    }

#ifdef __SIM_X86__            
    void enum_property_values(bson::BSONObj & dataobjs)
    {
        for( bson::BSONObj::iterator ie = dataobjs.begin(); ie.more(); ) 
        {
            bson::BSONElement e = ie.next();
            if(e.eoo() == true) 
                break;
            bson::BSONObjBuilder t;
            t.append(e);

            if(strlen(e.fieldName()))
               setobj(e.fieldName(), std::make_shared<bson::BSONObj>(t.obj()) );
        }
    }
#endif

protected:    
    void  prepare_ResGet(shared_ptr<::snapper::service::request_context> request); // call at the beginning
    void  prepare_ResDelete(shared_ptr<::snapper::service::request_context> request);
    void  prepare_ResPatch(shared_ptr<::snapper::service::request_context> request);
    int   prepare_ResPOST(shared_ptr<::snapper::service::request_context> request, std::string new_id = ""); // call at the beginning
    void  auto_build_objects_ResGET(const string odataid); //call at the end. auto-build objs for resource GET
    void  auto_build_objects_ResPOST(shared_ptr<::snapper::service::request_context> request);

    void set_namespace(const string ns) 
    {
        m_namespace = ns;
    }

    const string& get_base_odata_id() const 
    {
        return m_base_odata_id;
    }

    void set_base_odata_id(const string identifer) 
    {
        m_base_odata_id = identifer;
    }

    void set_desc(const string desc) 
    {
        m_desc = desc;
    }

    void set_task_output(string t)    
    {
        task_output = t;

        bson::BSONObj output = ::bson::fromjson(t);
        set_resp_hdr("ETag", output.getStringField(ODATA_ETAG));
    }

    void add_navigation_arr_props(const string name)
    {
        m_navigation_arr_props.push_back(name);
    }

    void add_navigation_contained_props(const string name)
    {
        m_navigation_contained_props.push_back(name);
    }

    void add_navigation_refer_props(const string name)
    {
        m_navigation_refer_props.push_back(name);
    }

    void add_Links_arr_props(const string name)
    {
        m_Links_arr_props.push_back(name);
    }

    //property API
    bool setobj(std::string name, std::shared_ptr<bson::BSONObj> obj);
    
    void initSettingsobj(struct tm *time = NULL);
    void clearSettingobj() 
    {
        m_settings_prop_objs.clear();
        settings_obj_flag = false;
    }
    void create_settings_prop(string name, std::shared_ptr<bson::BSONObj> obj)
    {
        m_settings_prop_objs[name] = obj;
    }
    bool setSettingsobj(std::string name, std::shared_ptr<bson::BSONObj> obj);
    std::shared_ptr<bson::BSONObj> getobj(std::string name)
    {
        if(m_prop_objs.find(name) == m_prop_objs.end())
            return nullptr;
        return m_prop_objs[name];
    }
    void create_prop(string name, std::shared_ptr<bson::BSONObj> obj)
    {
        m_prop_objs[name] = obj;
    }

    //Links property API
    bool setLinksobj(std::string name, std::shared_ptr<bson::BSONObj> obj);

    //oem lenovo property API
    bool setOemLenovoobj(std::string name, std::shared_ptr<bson::BSONObj> obj);
    void create_OemLenovo_prop(string name, std::shared_ptr<bson::BSONObj> obj)
    {
        m_OemLenovo_prop_objs[name] = obj;
    }
    void add_OemLenovo_nav_arr_props(const string name)
    {
        m_OemLenovo_nav_arr_props.push_back(name);
    }

    //if element of Links is an array, use this API to set the uri odataid 
    void set_Links_arr_prop(std::string classname, std::string propname, std::string containing_path = "");
    void set_Links_arr_by_keys(std::string classname, std::string propname, vector<std::string> keys);

    void add_property_class(string name, string proptype, string propclass)
    {
        m_property_class_map[name].push_back(proptype);//as for navprop type, auto-gen code will diff entity and collection
        m_property_class_map[name].push_back(propclass);
    }

    void add_property_attr(string name, std::shared_ptr<prop_attribute> attr)
    {
        m_property_attributes.insert(pair<string, std::shared_ptr<prop_attribute>>(name, attr));
    }

    void update_property_attr(string name, std::shared_ptr<prop_attribute> attr)
    {
        m_property_attributes.erase(name);
        m_property_attributes.insert(pair<string, std::shared_ptr<prop_attribute>>(name, attr));        
    }

    //auto-expand navigation for ReferenceableMember (Power/Voltages) or Resource (LogEntryCollection.Members/LogEntry)
    void set_prop_autoexpand_arr(string class_name, string prop_name, std::shared_ptr<bson::BSONObj> q_param = nullptr);
    
    //build object for "@Message.ExtendedInfo" or "xxx@Message.ExtendedInfo"
    void set_extended_message_objs(string prefix);

    const char* is_navprop_query(shared_ptr<::snapper::service::request_context> request);
    
    void set_status_obj(const string state_str, const string health_str = "", const string health_rollup_str = "");

    void set_resp_hdr(string fieldname, string value)
    {
        m_resp_hdr[fieldname] = value;
    }

    void add_jcache_schema(string schema_name)
    {
        jcache_schemas.push_back(schema_name);
    }
    void add_bcache_key(string key)
    {
        bcache_keys[key] = true;
    }

private:

    // build common objs for all types of resource and collection
    // including @odata.id/@odata.type/@odata.context/Name/Description
    // the individual provider should call set_base_odata_id() and set_desc() first
    // then @odata.id/@odata.type/@odata.context/Name can be built automatically
    void set_common_objs();
    
    void build_settings_obj();

    const string& get_desc() const 
    {
        return m_desc;
    }

    std::shared_ptr<bson::BSONObj> getLinksobj(std::string name)
    {
        if(m_Links_prop_objs.find(name) == m_Links_prop_objs.end())
            return nullptr;
        return m_Links_prop_objs[name];
    }

    std::shared_ptr<bson::BSONObj> getOemLenovoobj(std::string name)
    {
        if(m_OemLenovo_prop_objs.find(name) == m_OemLenovo_prop_objs.end())
            return nullptr;
        return m_OemLenovo_prop_objs[name];
    }

    void set_etag(string etag) 
    {
        m_etag = etag;
    }


protected:    

    std::map<const std::string, std::shared_ptr<bson::BSONObj>> m_Links_prop_objs;
    std::vector<std::string> m_Links_arr_props;

    SnapperMessage m_message;

    
    void set_etag_flag(bool flag)
    {
        etag_needed = flag;
    }

private:
    //index is the property name, and the BSONObj should also contain the 
    //property name like {@odata.id:"/redfish/v1/Chassis/1/"}, {SKU:"Default"}
    std::map<const std::string, std::shared_ptr<bson::BSONObj>> m_prop_objs;

    std::map<const std::string, std::vector<std::string>> m_property_class_map; //class type of the property:  property nanme, type|classname

    map<string, std::shared_ptr<prop_attribute>> m_property_attributes;

    //directly (subordinate) referenced navigation properties (in the ROOT of the resource)
    std::vector<std::string> m_navigation_arr_props;//NAVPROP name list. for NAVPROP, NAVPROP@odata.navigationLink, NAVPROP@odata.count
    std::vector<std::string> m_navigation_contained_props;//contained nav prop, under the same odata.id of entity type
    std::vector<std::string> m_navigation_refer_props;//nav prop which MAY has different odata.id path referenced by entity type

    //oem lenovo property
    std::map<const std::string, std::shared_ptr<bson::BSONObj>> m_OemLenovo_prop_objs;
    std::vector<std::string> m_OemLenovo_nav_arr_props;//Oem NAVPROP name list

    string m_name;
    provider_type m_type;
    string m_namespace;
    string m_base_odata_id; // the base uri path from the request url
    string m_desc;
    bool   etag_needed; 
    string m_etag;
    int m_http_code;
    std::map<const std::string, std::string> m_resp_hdr;

    string task_output;//for schema that initiates task and returns task information

    std::vector<std::string> jcache_schemas; // schema list to clear dirty json cache for create/patch/put/delete
    std::map<const std::string, bool>  bcache_keys; // key list of metadata xml for getData to clear dirty bson cache for create/patch/put/delete

    // for @Redfish.Settings object
    std::map<const std::string, std::shared_ptr<bson::BSONObj>> m_settings_prop_objs;
    bool settings_obj_flag;
    
};
    
class ResourceProvider : public SnapperProvider
{
public:
    ResourceProvider(string name) : SnapperProvider(name, provider_type::Provider_Resource) 
    {}    
        
    virtual ~ResourceProvider() {};   
    
    void set_id_obj();
    virtual void set_actions_obj() {}
    
    const string& get_id_key() const 
    {
        return m_id_key;
    }

    void set_id_key(const string identifier) 
    {
        size_t pos = identifier.find_last_of("/");
        if (pos != string::npos)//url passed in
        {
            string last_str = identifier.substr(pos+1);
            m_id_key = last_str;            
        }
        else//id passed
            m_id_key = identifier;            
    }

    //Resource can override it. E.g. LogEntryCollection-Members Collection(LogEntry)
    virtual int autoexpand_array(bson::BSONArrayBuilder* a, std::string containing_path = "", std::shared_ptr<bson::BSONObj> q_param = nullptr)
    { 
        return RFRC_FAILURE; 
    }

protected:

private:
    string m_id_key;
    
};
    
class ResourceCollectionProvider : public SnapperProvider
{
public:
    ResourceCollectionProvider(string name) : SnapperProvider(name, provider_type::Provider_ResourceCollection) 
    {}    
    
    virtual ~ResourceCollectionProvider() {};   
    void set_member_objs(std::string containing_path = "");
    int  access_member_prop(std::string uri_seg, std::string classname, std::string containing_path = "");

    //resource collection never allows patch or delete or put
    virtual int handle_patch(shared_ptr<::snapper::service::request_context> request);
    virtual int handle_delete(shared_ptr<::snapper::service::request_context> request);
    virtual int handle_put(shared_ptr<::snapper::service::request_context> request);

    virtual std::shared_ptr<memid_acckey_map> getlist_memid_acckey(std::string containing_path = "")
    {
        return nullptr;//collection does not have memid
    }

    //ResourceCollection does not support
    virtual int autoexpand_array(bson::BSONArrayBuilder* a, std::string containing_path = "", std::shared_ptr<bson::BSONObj> q_param = nullptr)
    { 
        return RFRC_FAILURE; 
    } 


protected:    

private:
    
};
    
class ReferenceableMemberProvider : public SnapperProvider
{
public:
    ReferenceableMemberProvider(string name) : SnapperProvider(name, provider_type::Provider_ReferenceableMember) 
    {}    
    
    virtual ~ReferenceableMemberProvider() {}; 

    //ReferenceableMember MUST implement it to support auto-expand
    virtual int autoexpand_array(bson::BSONArrayBuilder* a, std::string containing_path = "", std::shared_ptr<bson::BSONObj> q_param = nullptr) = 0;

protected:    

private:
};


////////////helper function for BSONElement. print log if there's eoo or type mismatch //////////
int BE_Int(const bson::BSONElement &e);
std::string BE_String(const bson::BSONElement &e);
bool BE_Bool(const bson::BSONElement &e);
long long BE_Long(const bson::BSONElement &e);
double BE_Double(const bson::BSONElement &e);
char * BE_Binary(const bson::BSONElement &e, int &len, string & o);
std::vector<bson::BSONElement> BE_Array(const bson::BSONElement &e);
bson::BSONObj BE_Object(const bson::BSONElement &e);

}}
 
