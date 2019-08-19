/*---------------------------------------------------------------------------
//  Copyright (c) 2018-present, Lenovo. All rights reserved.
//  Licensed under BSD, see COPYING.BSD file for details.
//---------------------------------------------------------------------------
*/

#include <www/engine/rf_debug.h>
#include "class/SnapperProvider.h"
#include <algorithm>
#include <string.h>
#include "datainf/DataInterfaceMgr.h"
#include <www/engine/protocol.h>
#include <www/engine/json_cache.h>
#include <www/engine/BSONCache.h>

namespace snapper { namespace providers
{
#define DEBUG_ON
    
#ifdef DEBUG_ON
#define ODATA_DEBUG_V(x) ODATA_TRACE_V(x)
#define ODATA_DEBUG      ODATA_TRACE
#else
#define ODATA_DEBUG_V(x) 
#define ODATA_DEBUG      
#endif
    
#ifdef DEBUG_X_ON
#define ODATA_DEBUG_X(x) ODATA_TRACE_X(x)
#else
#define ODATA_DEBUG_X(x)
#endif

map<string, std::shared_ptr<SnapperProvider>> ProviderObjectFactory::objMap;

//////////////////////////////////////////////////////////////////////////////
// utilities
string build_str(const string s1, const string s2, const string s3, const string s4)
{
    return s1+s2+s3+s4;
}

string get_raw_enum_str(const char* str)
{
    string enum_str(str);
    size_t pos = enum_str.find_first_of("_");
    if (pos != string::npos)
        return enum_str.substr(pos + 1);
    else
        return enum_str;
}

//////helper function for BSONElement. print log if there's eoo or type mismatch ///
int BE_Int(const bson::BSONElement &e)
{
    int result = std::numeric_limits< int >::min();
    if(e.eoo())
        RF_PRINT_DBG("eoo element\n");
    else if(e.type() != bson::NumberInt)
        RF_PRINT_DBG("wrong type. '%s' is type %d\n", e.fieldName(), e.type());
    else
        result = e.Int();
    return result;
}

std::string BE_String(const bson::BSONElement &e)
{
    std::string result = "";
    if(e.eoo())
        RF_PRINT_DBG("eoo element\n");
    else if(e.type() != bson::String)
        RF_PRINT_DBG("wrong type. '%s' is type %d\n", e.fieldName(), e.type());
    else
        result = e.String();
    return result;
}

bool BE_Bool(const bson::BSONElement &e)
{
    bool result = false;
    if(e.eoo())
        RF_PRINT_DBG("eoo element\n");
    else if(e.type() != bson::Bool)
        RF_PRINT_DBG("wrong type. '%s' is type %d\n", e.fieldName(), e.type());
    else
        result = e.Bool();
    return result;
}

long long BE_Long(const bson::BSONElement &e)
{
    long long result = std::numeric_limits< long long >::min();
    if(e.eoo())
        RF_PRINT_DBG("eoo element\n");
    else if(e.type() != bson::NumberLong)
        RF_PRINT_DBG("wrong type. '%s' is type %d\n", e.fieldName(), e.type());
    else
        result = e.Long();
    return result;
}

double BE_Double(const bson::BSONElement &e)
{
    double result = std::numeric_limits< double >::min();
    if(e.eoo())
        RF_PRINT_DBG("eoo element\n");
    else if(e.type() != bson::NumberDouble)
        RF_PRINT_DBG("wrong type. '%s' is type %d\n", e.fieldName(), e.type());
    else
        result = e.Double();
    return result;
}

char * BE_Binary(const bson::BSONElement &e, int &len, string & o)
{
    char *result = NULL;
    if(e.eoo())
        RF_PRINT_DBG("eoo element\n");
    else if(e.type() == bson::BinData)
        result = (char *)e.binData(len);
    else if(e.type() == bson::String)// workaround. dmdb returns BLOB type for TEXT type column somehow
    { // return NULL for binary, but set string o
        o = e.String();
        //RF_PRINT_DBG(" o ---- %s\n", o.c_str());
        result = NULL;
    }
    else
        RF_PRINT_DBG("wrong type. '%s' is type %d\n", e.fieldName(), e.type());
    return result;
}

std::vector<bson::BSONElement> BE_Array(const bson::BSONElement &e)
{
    std::vector<bson::BSONElement> result;
    if(e.eoo())
        RF_PRINT_DBG("eoo element\n");
    else if(e.type() != bson::Array)
        RF_PRINT_DBG("wrong type. '%s' is type %d\n", e.fieldName(), e.type());
    else
        result = e.Array();
    return result;
}

bson::BSONObj BE_Object(const bson::BSONElement &e)
{
    bson::BSONObj result;
    if(e.eoo())
        RF_PRINT_DBG("eoo element\n");
    else if(e.type() != bson::Object)
        RF_PRINT_DBG("wrong type. '%s' is type %d\n", e.fieldName(), e.type());
    else
        result = e.Obj();
    return result;
}

//////////////////////////////////////////////////////////////////////////////
// SnapperProvider Class
//
//////////////////////////////////////////////////////////////////////////////
const char* SnapperProvider::get_type_str() const
{
    switch (m_type)
    {
        case Provider_Resource:           return "Resource"; break;
        case Provider_ResourceCollection: return "ResourceCollection"; break;
        case Provider_ReferenceableMember: return "ReferenceableMember"; break;
        default: return "Unknown"; break;
    }
}

bool SnapperProvider::is_array_property(const string& prop_name)
{ 
    for(auto it = m_navigation_arr_props.begin();it != m_navigation_arr_props.end();it++)
    {
        if (prop_name.compare(*it) == 0 )
            return true;
    }

    for(auto it = m_OemLenovo_nav_arr_props.begin();it != m_OemLenovo_nav_arr_props.end();it++)
    {
        if (prop_name.compare(*it) == 0 )
            return true;
    }

    return false;
}


void SnapperProvider::reset_obj()
{
    std::map<const std::string, std::shared_ptr<bson::BSONObj>>::iterator it;
    for(it=m_prop_objs.begin();it!=m_prop_objs.end();++it)
    {
        ::odata::utility::string_t name = it->first;
        m_prop_objs[name] = nullptr;
    }

    for(it=m_Links_prop_objs.begin();it!=m_Links_prop_objs.end();++it)
    {
        ::odata::utility::string_t name = it->first;
        m_Links_prop_objs[name] = nullptr;
    }

    for(it=m_OemLenovo_prop_objs.begin();it!=m_OemLenovo_prop_objs.end();++it)
    {
        ::odata::utility::string_t name = it->first;
        if(name.compare(ODATA_TYPE) == 0)
            continue;
        m_OemLenovo_prop_objs[name] = nullptr;
    }

    m_message.reset_obj();
    override_http_code(0);
    m_resp_hdr.clear();
    task_output.clear();
}

std::string SnapperProvider::serialize_objs()
{
    bson::BSONObjBuilder rsltobjs;
    string to_hash_str;

    if(task_output.length() > 0)
    {
        return task_output;
    }

    build_settings_obj();

    std::map<const std::string, std::shared_ptr<bson::BSONObj>>::iterator it;
    for(it=m_prop_objs.begin();it!=m_prop_objs.end();++it)
    {
        ::odata::utility::string_t name = it->first;
        if(m_prop_objs[name] != nullptr)
        {
            rsltobjs.appendElementsUnique(*(m_prop_objs[name]));
            to_hash_str += (*(m_prop_objs[name])).jsonString();
        }
//		else
//			rsltobjs.appendElementsUnique(BSON( name << ""));
    }

    if (etag_needed)
    {
        stringstream ss;
        ss << "W/\"" << hex << HASH_STRING(to_hash_str.c_str()) << "\"";
    
        m_prop_objs[ODATA_ETAG] = MAKE_BSON_OBJ(ODATA_ETAG, ss.str().c_str());
        rsltobjs.appendElementsUnique(*(m_prop_objs[ODATA_ETAG]));

        set_resp_hdr("ETag", ss.str());
        set_etag(ss.str());
    }
    
    return rsltobjs.obj().jsonString();
}
std::string SnapperProvider::serialize_resp_hdr(int method)
{
    std::string orig(snapper::service::PROTOCOL::get_cur_session().hdr_orig);
    //RF_PRINT_DBG("Origin: %s\n", orig.c_str());
    if(orig.length())
        set_resp_hdr("Access-Control-Allow-Origin", orig);

    bson::BSONObjBuilder rsltobjs;
    std::map<const std::string, std::string>::iterator it;
    for(it=m_resp_hdr.begin();it!=m_resp_hdr.end();++it)
    {
        std::string fieldname = it->first;
        std::string value = it->second;
        if(value.length() > 0)
            rsltobjs.append(fieldname, value);
    }

    // for Allow
    if (m_resp_hdr.find("Allow") == m_resp_hdr.end() || m_resp_hdr["Allow"].length() == 0)
    {

        char *methodstr[] = {"GET", "HEAD", "POST", "PUT", "PATCH", "DELETE"}; //order defined in allows() 
        char *m = allows();
        std::string Allow;
        for(int i = 0; i < 6; i++)
        {
            if(m[i] == 0) continue;
            if(Allow.length() == 0)
                Allow = std::string(methodstr[i]);
            else
                Allow += ", " + std::string(methodstr[i]);
        }
        rsltobjs.append("Allow", Allow);
    }

    // for Link
    if (m_resp_hdr.find("Link") == m_resp_hdr.end() || m_resp_hdr["Link"].length() == 0)
    {
        std::string value="</redfish/v1/schemas/";
        value += get_namespace() + ".json>; rel=describedby";
        if(method == snapper::service::http_get || method == snapper::service::http_head)
            rsltobjs.append("Link", value);
    }

    return rsltobjs.obj().jsonString();
}


std::string SnapperProvider::serialize_error_obj()
{
    return m_message.serialize_err_obj();
}

bool SnapperProvider::setobj(string name, std::shared_ptr<bson::BSONObj> obj)
{
    if (m_prop_objs.find(name) == m_prop_objs.end())
    {
        RF_PRINT_ERR("property %s is not found\n", name.c_str());
        return false;
    }
    if( obj != nullptr && (obj->firstElement().eoo() == true || name.compare(obj->firstElement().fieldName())) )
    {
        RF_PRINT_ERR("property %s is an invalid object: %s\n", name.c_str(), obj->jsonString().c_str());
        return false;
    }

    //validate navigation collection property
    std::vector<std::string>::iterator col = find(m_navigation_arr_props.begin(), m_navigation_arr_props.end(), name);
    if( obj != nullptr && col != m_navigation_arr_props.end())
    {
        bson::BSONElement e = obj->getField(name);
        if(e.type() != bson::Array){
            RF_PRINT_ERR("Navigation Property %s is not a Collection\n", name.c_str());
            return false;
        }
    }

    m_prop_objs[name] = obj;
    return true;
}

bool SnapperProvider::setLinksobj(string name, std::shared_ptr<bson::BSONObj> obj)
{
    if (m_Links_prop_objs.find(name) == m_Links_prop_objs.end())
    {
        RF_PRINT_ERR("Links property %s is not found\n", name.c_str());
        return false;
    }
    if( obj != nullptr && (obj->firstElement().eoo() == true || name.compare(obj->firstElement().fieldName())) )
    {
        RF_PRINT_ERR("Links  property %s is an invalid object: %s\n", name.c_str(), obj->jsonString().c_str());
        return false;
    }

    //Links contain either Collection or Entity navigation properties
    //validate collection/array property in Links
    std::vector<std::string>::iterator col = find(m_Links_arr_props.begin(), m_Links_arr_props.end(), name);
    if( obj != nullptr && col != m_Links_arr_props.end())
    {
        bson::BSONElement e = obj->getField(name);
        if(e.type() != bson::Array){
            RF_PRINT_ERR("Links property %s is not a Collection\n", name.c_str());
            return false;
        }
    }

    m_Links_prop_objs[name] = obj;

    return true;
}

void SnapperProvider::set_Links_arr_prop(std::string classname, std::string propname, std::string containing_path)
{
    std::shared_ptr<std::string> uri;
    std::string accessor_key = "";
    std::shared_ptr<memid_acckey_map> idlist = nullptr;


    idlist = getlist_memid_acckey_fromclass(classname, containing_path);//TODO containing_path?
    bson::BSONArrayBuilder refarr;
    if (idlist != nullptr) {
        for (auto it=idlist->begin();it != idlist->end();++it) {
            accessor_key = it->second;
            uri = snapper::service::ResourceTopology::search_url(accessor_key);
            if(uri != nullptr)
                refarr.append(BSON(ODATA_ID << uri->c_str()));
        }
    }
    setLinksobj(propname, MAKE_BSON_OBJ(propname, refarr.arr()));
}

void SnapperProvider::set_Links_arr_by_keys(std::string classname, std::string propname, vector<std::string> keys)
{
    unsigned int i;
    std::shared_ptr<std::string> uri;
    bson::BSONArrayBuilder refarr;

    for (i=0; i<keys.size(); ++i)
        if ((uri = snapper::service::ResourceTopology::search_url(keys[i])) != nullptr)
            refarr.append(BSON(ODATA_ID << uri->c_str()));

    setLinksobj(propname, MAKE_BSON_OBJ(propname, refarr.arr()));
}

bool SnapperProvider::setOemLenovoobj(string name, std::shared_ptr<bson::BSONObj> obj)
{
    if (m_OemLenovo_prop_objs.find(name) == m_OemLenovo_prop_objs.end())
    {
        RF_PRINT_ERR("Oem property %s is not found\n", name.c_str());
        return false;
    }
    if( obj != nullptr && (obj->firstElement().eoo() == true || name.compare(obj->firstElement().fieldName())) )
    {
        RF_PRINT_ERR("Oem  property %s is an invalid object: %s\n", name.c_str(), obj->jsonString().c_str());
        return false;
    }

    m_OemLenovo_prop_objs[name] = obj;

    return true;
}

void SnapperProvider::initSettingsobj(struct tm *time)
{
    settings_obj_flag = true;
    // get settings_namespace from schema, TBD
    string settings_namespace = "Settings.v1_2_0";
    string odata_type_str = settings_namespace + ".Settings";
    create_settings_prop(ODATA_TYPE, MAKE_BSON_OBJ(ODATA_TYPE, odata_type_str));
    
    bson::BSONObjBuilder o;
    o.append(ODATA_ID, get_base_odata_id() + "/Pending");
    create_settings_prop("SettingsObject", MAKE_BSON_OBJ("SettingsObject", o.obj()));
    
    bson::BSONObjBuilder tm_args;
    bson::BSONObjBuilder tm_results;

    if(time != NULL)
    {
        string tm_keyname = "tm"; 
        DataInterfaceMgr::getData(tm_keyname, tm_args.obj(), tm_results);
                 
        stringstream ss;
        ss.str("");
        ss << (1900 + time->tm_year) << "-"
           << std::setfill('0') << std::setw(2) << (1 + time->tm_mon) << "-"
           << std::setfill('0') << std::setw(2) << time->tm_mday << "T"
           << std::setfill('0') << std::setw(2) << time->tm_hour << ":"
           << std::setfill('0') << std::setw(2) << time->tm_min << ":"
            << std::setfill('0') << std::setw(2) << time->tm_sec << ":";
        bson::BSONObj tm_obj = tm_results.obj();
        ss << tm_obj.getStringField("date_gmt");  
        create_settings_prop("Time", MAKE_BSON_OBJ("Time", ss.str()));
    }
    else
    {
        create_settings_prop("Time", nullptr);
    }
    
    create_settings_prop("ETag", nullptr);
    create_settings_prop("Messages", nullptr);
    create_settings_prop("SupportedApplyTimes", nullptr);
    create_prop(REDFISH_SETTINGS,  nullptr);
}

bool SnapperProvider::setSettingsobj(std::string name, std::shared_ptr<bson::BSONObj> obj)
{
    if (m_settings_prop_objs.find(name) == m_settings_prop_objs.end())
    {
        RF_PRINT_ERR("property %s for Settings object is not found\n", name.c_str());
        return false;
    }
    if( obj != nullptr && (obj->firstElement().eoo() == true || name.compare(obj->firstElement().fieldName())) )
    {
        RF_PRINT_ERR("property %s for Settings object is an invalid object: %s\n", name.c_str(), obj->jsonString().c_str());
        return false;
    }

    m_settings_prop_objs[name] = obj;
    return true;
}

void SnapperProvider::build_settings_obj()
{
    if(!settings_obj_flag)
        return;
    
    bson::BSONObjBuilder rsltobjs;
    std::map<const std::string, std::shared_ptr<bson::BSONObj>>::iterator it;
    for(it=m_settings_prop_objs.begin();it!=m_settings_prop_objs.end();++it)
    {
        ::odata::utility::string_t name = it->first;
        if(m_settings_prop_objs[name] != nullptr)
        {
            rsltobjs.appendElementsUnique(*(m_settings_prop_objs[name]));
        }
    }
    setobj(REDFISH_SETTINGS, MAKE_BSON_OBJ(REDFISH_SETTINGS, rsltobjs.obj())); 
    //clearSettingobj();
    settings_obj_flag = false;
}


// build common objs for all types of resource and collection
// including @odata.id/@odata.type/@odata.context/Name/Description
// @odata.etag is assigned in serialize_objs()
void SnapperProvider::set_common_objs()
{
    // should be from entity base type, but just use the entity name to compose here, can revise if needed in the future
    string resource_type = build_str(get_name(), ".", get_name()); 
    create_prop( ODATA_CONTEXT,  MAKE_BSON_OBJ(ODATA_CONTEXT, build_str(root_uri, "/", ROOT_METADATA, resource_type)) );
    create_prop( ODATA_ID,       MAKE_BSON_OBJ(ODATA_ID, get_base_odata_id()) );
    create_prop( ODATA_TYPE,     MAKE_BSON_OBJ(ODATA_TYPE, build_str("#", get_namespace(), ".", get_name())) );    
    
    if(getobj(RESOURCE_NAME) == nullptr)
        setobj(RESOURCE_NAME,   MAKE_BSON_OBJ(RESOURCE_NAME, get_name()));

    if(getobj(RESOURCE_DESC) == nullptr)
        setobj(RESOURCE_DESC,   MAKE_BSON_OBJ(RESOURCE_DESC, get_desc()));
}

// set referenceable member array
void SnapperProvider::set_prop_autoexpand_arr(string class_name, string prop_name, std::shared_ptr<bson::BSONObj> q_param)
{
    bson::BSONArrayBuilder autoexpandArr;
    auto provider = ProviderObjectFactory::GetObject(class_name);
    if(provider == nullptr)
        return;

    if(provider->get_type() == Provider_ReferenceableMember)
    {
        ReferenceableMemberProvider *ptr = provider->as<ReferenceableMemberProvider>();
        if(ptr && !ptr->autoexpand_array(&autoexpandArr, get_base_odata_id(), q_param))
        { 
            setobj( prop_name,         MAKE_BSON_OBJ(prop_name, autoexpandArr.arr()) );
        }
    }
    else if(provider->get_type() == Provider_Resource)
    {
        ResourceProvider *ptr = provider->as<ResourceProvider>();
        if(ptr && !ptr->autoexpand_array(&autoexpandArr, get_base_odata_id(), q_param))
        { 
            setobj( prop_name,         MAKE_BSON_OBJ(prop_name, autoexpandArr.arr()) );
        }
    }
}


//build object for "@Message.ExtendedInfo" or "xxx@Message.ExtendedInfo"
void SnapperProvider::set_extended_message_objs(string prefix)
{
    string name = prefix + MESSAGE_EXTENDED;
    std::shared_ptr<bson::BSONObj> extended_obj = m_message.get_extended_info_obj(prefix);
    if(extended_obj)
        m_prop_objs[name] = extended_obj;
}


void SnapperProvider::prepare_ResGet(shared_ptr<::snapper::service::request_context> request)
{
    string path = request->get_raw_path();

    if(request->get_method() == snapper::service::http_post)
    {
        RF_PRINT_DBG("wrong preparation for %s", path.c_str());
        return;
    }

    set_base_odata_id(path);

    if(m_type == Provider_Resource)
    {
        ResourceProvider *ptr = this->as<ResourceProvider>();
        if(ptr && ptr->is_navprop_query(request) == nullptr)
            ptr->set_id_key(path);
    }
}
void SnapperProvider::prepare_ResDelete(shared_ptr<::snapper::service::request_context> request)
{
    prepare_ResGet(request);
}
void SnapperProvider::prepare_ResPatch(shared_ptr<::snapper::service::request_context> request)
{
    prepare_ResGet(request);
}

int SnapperProvider::prepare_ResPOST(shared_ptr<::snapper::service::request_context> request, std::string new_id) 
{
    if(m_type == Provider_Resource && request->is_op_create() == false) //for Action
    {
        ResourceProvider *ptr = this->as<ResourceProvider>();
        if(ptr)
        {            
            unsigned int size = request->get_path_str().size();
            string last = request->get_path_str()[size - 2];
            string oid;
            
            if (last.compare("Actions"))
            {
                RF_PRINT_WARN("Unsupported POST  \n");
                
                m_message.add_error_message_obj(BaseMessage::MMO_ActionNotSupported(last));
                return RFRC_INVALID_PARAMS;
            }
            else
            { 
                // remove the Actions from the path, prepare oid for the resoure return.
                oid = request->get_raw_path();
                size_t pos = oid.find("/Actions");
                oid = oid.substr(0, pos);                
                set_base_odata_id(oid);
                ptr->set_id_key(oid);
            }
        }
    }
    else if(m_type == Provider_Resource && request->is_op_create() == true) //for CREATE
    {
        ResourceProvider *ptr = this->as<ResourceProvider>();
        string path = request->get_raw_path();

        set_base_odata_id(path+"/"+new_id);//collection odataid + member id
        if(ptr)
        {
            ptr->set_id_key(new_id);
        }
    }
    else
        RF_PRINT_WARN("wrong resource type for prepare_ResPOST\n");

    return RFRC_SUCCESS;
}

void SnapperProvider::auto_build_objects_ResPOST(shared_ptr<::snapper::service::request_context> request)
{
    string odataid = request->get_raw_path();
    if(request->is_op_create() == false) //for Action
        odataid = odataid.substr(0, odataid.find("/Actions/")); 
    else
        odataid = get_base_odata_id();//newid created should be set by prepare_ResPOST already

    auto_build_objects_ResGET(odataid);
}

void SnapperProvider::auto_build_objects_ResGET(const string odataid)
{
    //odata, name, id, desc etc
    set_common_objs();
    if(m_type == Provider_Resource)
    {
        ResourceProvider *ptr = this->as<ResourceProvider>();
        if(ptr)
            ptr->set_id_obj();
    }

    // @odata.id for ReferenceableMember needs special handle
    if(m_type == Provider_ReferenceableMember)
    {        
        std::shared_ptr<memid_acckey_map> idlist = getlist_memid_acckey(odataid);
        std::shared_ptr<bson::BSONObj> o = getobj("MemberId");
        if(o && idlist != nullptr)
        {
            string key = o->getStringField("MemberId");            
            auto it = idlist->find(key);
            if(it != idlist->end())
            {
                auto uri = snapper::service::ResourceTopology::search_url(it->second, get_name());
                if(uri != nullptr)
                    setobj( ODATA_ID,       MAKE_BSON_OBJ(ODATA_ID, uri->c_str()) );
            }
        }
    }

    // auto set Members
    if(m_type == Provider_ResourceCollection)
    {
        ResourceCollectionProvider *ptr = this->as<ResourceCollectionProvider>();
        if(ptr && getobj(RESOURCE_MEMBERS) == nullptr)//ResourceCollection and Memebers has no data
        {
            auto accessor_key = ::snapper::service::ResourceTopology::search_accessor(odataid);
            if (accessor_key != nullptr)
            {
                std::string containing_path = odataid + " " + (*accessor_key);
                ptr->set_member_objs(containing_path);
            }
            else
                ptr->set_member_objs(odataid);
        }
    }

    //collection nav props, set count and the same base odataid path
    for(int i = 0; i < m_navigation_arr_props.size(); i++)
    {
        const std::string propname = m_navigation_arr_props[i];
        std::shared_ptr<bson::BSONObj> obj = getobj(propname);
        if(obj == nullptr)
            continue;
        std::string cnt = propname + ODATA_COUNT;
        //std::string navlink = propname + ODATA_NAVLINK;
        bson::BSONElement e = obj->getField(propname);
        int count = BE_Array(e).size();

        setobj(cnt, MAKE_BSON_OBJ(cnt, count));
        //setobj(navlink, MAKE_BSON_OBJ(navlink, (get_base_odata_id() + "/" + propname))); //2018.1 schema removed @odata.navigationLink
        //RF_PRINT_DBG("collection nav prop: %s, %d\n", propname.c_str(), count);
    }


    //contained nav props have the same odataid path
    for(int i = 0; i < m_navigation_contained_props.size(); i++)
    {
        const std::string propname = m_navigation_contained_props[i];
        if(getobj(propname) != nullptr)
            continue;
        setobj(propname, MAKE_BSON_NAV_OBJ(propname)); 
        //RF_PRINT_DBG("contained nav prop: %s\n", propname.c_str());
    }

    // referred nav props
    for(int i = 0; i < m_navigation_refer_props.size(); i++)
    {
        // referred nav props MAY have different odataid path
        // if it was not set with different odataid, use the default one as contained nav props
        const std::string propname = m_navigation_refer_props[i];
        if(getobj(propname) == nullptr){ 
            setobj(propname, MAKE_BSON_NAV_OBJ(propname)); 
            //RF_PRINT_DBG("referred nav prop: %s\n", propname.c_str());
        }
    }

    // Links property
    for(int i = 0; i < m_Links_arr_props.size(); i++)//set count,navigationLink for Collection in Links
    {
        const std::string propname = m_Links_arr_props[i];
        std::shared_ptr<bson::BSONObj> obj = getLinksobj(propname);
        if(obj == nullptr)
            continue;
        std::string cnt = propname + ODATA_COUNT;
        //std::string navlink = propname + ODATA_NAVLINK;
        bson::BSONElement e = obj->getField(propname);
        int count = BE_Array(e).size();

        setLinksobj(cnt, MAKE_BSON_OBJ(cnt, count));
        std::string uri_str = "";
        if(count)//remove last member id as navigationLink
        {
            uri_str = (e.Array())[0][ODATA_ID].String();
            if(uri_str.find_last_of("/") != string::npos)
                uri_str = uri_str.substr(0, uri_str.find_last_of("/"));
        }
        //setLinksobj(navlink, MAKE_BSON_OBJ(navlink, uri_str)); //2018.1 schema removed @odata.navigationLink
        //RF_PRINT_DBG("Links collection prop: %s, %d %s\n", propname.c_str(), count, uri_str.c_str());
    }
    if(getobj("Links") == nullptr)
    {
        bson::BSONObjBuilder links;

        std::map<const std::string, std::shared_ptr<bson::BSONObj>>::iterator it;
        for(it=m_Links_prop_objs.begin();it!=m_Links_prop_objs.end();++it)
        {
            ::odata::utility::string_t name = it->first;
            if(m_Links_prop_objs[name] != nullptr)
            {
                links.appendElementsUnique(*(m_Links_prop_objs[name]));
            }
        }
        bson::BSONObj linkobj = links.obj();
        //RF_PRINT_DBG("Links content: %s\n", linkobj.jsonString().c_str());
        setobj("Links", MAKE_BSON_OBJ("Links", linkobj));
    }

    // Oem/Lenovo properties
    if(getobj("Oem") == nullptr)
    {
        bson::BSONObjBuilder lenovo;
        bool hasdata = false;

        std::map<const std::string, std::shared_ptr<bson::BSONObj>>::iterator it;
        for(it=m_OemLenovo_prop_objs.begin();it!=m_OemLenovo_prop_objs.end();++it)
        {
            ::odata::utility::string_t name = it->first;
            if(m_OemLenovo_prop_objs[name] != nullptr)
            {
                //RF_PRINT_DBG("OEM name %s \n", name.c_str());
                lenovo.appendElementsUnique(*(m_OemLenovo_prop_objs[name]));
                hasdata = true;
            }
        }
        if(hasdata == true)
        {
            bson::BSONObj oemobj = BSON("Lenovo" << lenovo.obj());
            //RF_PRINT_DBG("Oem content: %s\n", oemobj.jsonString().c_str());
            setobj("Oem", MAKE_BSON_OBJ("Oem", oemobj));
        }
    }

    // set action property
    if (m_prop_objs.find("Actions") != m_prop_objs.end())
    {
        if(m_type == Provider_Resource)
        {
            ResourceProvider *ptr = this->as<ResourceProvider>();
            if(ptr && (ptr->get_id_key() != "Pending"))
                ptr->set_actions_obj();
        }
    }

}

// if request url queries navigation property of the resource, return property name
const char* SnapperProvider::is_navprop_query(shared_ptr<::snapper::service::request_context> request)
{
    auto segments = request->get_odata_path()->segments();
    etag_needed = true;
    if(request->get_method() == snapper::service::http_get && segments.size() > 0)
    {
        std::vector<std::string> &path = request->get_path_str();
        std::string &pname = path[path.size()-1];
        std::shared_ptr<::odata::core::odata_path_segment> seg = segments[segments.size()-1];
        RF_PRINT_DBG("is_navprop_query: %d - %s\n", seg->segment_type(), pname.c_str());

        if(seg->segment_type() == odata_path_segment_type::NavigationProperty && 
             m_prop_objs.find(pname) != m_prop_objs.end())
        {
            etag_needed = false;
            return pname.c_str();
        }
    }

    return nullptr;
}

bool SnapperProvider::validate_key(const string& key_value, std::string containing_path)
{
    if(containing_path.find(TASK_MONITOR_PATH) == 0 && key_value.find(TASK_MONITOR_ID_PRE) != string::npos)
    {
        // the task monitor uses url "/redfish/v1/Tasks/Tasks/Mon_tid". tid is task id, Mon_ is to differentiate Task resource
        RF_PRINT_DBG("task monitor  %s %s\n", containing_path.c_str(), key_value.c_str());
        return true;
    }

    auto containing_acckey = snapper::service::ResourceTopology::search_accessor(containing_path);
    if(containing_acckey != nullptr)
    {
        containing_path += " " + (*containing_acckey);// path and accessor
        RF_PRINT_DBG("path & acckey %s\n", containing_path.c_str());
        return true;
    }

    std::shared_ptr<memid_acckey_map> idlist = getlist_memid_acckey(containing_path);
    if(idlist == nullptr)//pass by default
        return true;

    if(idlist != nullptr && idlist->find(key_value) != idlist->end())
    {
        RF_PRINT_DBG("class %s  find key ^^^^^^^^ %s under %s\n",get_name().c_str(), key_value.c_str(), containing_path.c_str());
        return true;
    }
    return false;
}

// build "Status" obj
void SnapperProvider::set_status_obj(const string state_str, const string health_str, const string health_rollup_str)
{
    if( state_str.empty())
    {
        return;
    }
    
    if( health_str.empty())
    {
        m_prop_objs["Status"] = std::make_shared<bson::BSONObj>(BSON("Status" << BSON( "State" << state_str))); 
        return;
    }
    if(health_rollup_str.empty())
    {
        m_prop_objs["Status"] = std::make_shared<bson::BSONObj>(BSON("Status" << BSON( "State" << state_str 
                            << "Health" << health_str))); 
    }  
    else
    {        
        m_prop_objs["Status"] = std::make_shared<bson::BSONObj>(BSON("Status" << BSON( "State" << state_str 
                            << "Health" << health_str << "HealthRollup" << health_rollup_str))); 
    }
    return;
}

//clear json cache by resource name when create/patch/put/delete
void SnapperProvider::jcache_clean(shared_ptr<::snapper::service::request_context> request)
{
    if(request->get_method() == snapper::service::http_patch ||
       request->get_method() == snapper::service::http_put ||
       request->get_method() == snapper::service::http_delete ||
       (request->get_method() == snapper::service::http_post && request->is_op_create() == true))
    {
        if(jcache_schemas.size() == 0)//by default clean resource itself named cache
            jcache_schemas.push_back(get_name());
        snapper::service::refresh_json_cache(jcache_schemas);
    }
}

//clear bson cache by metadata key of getData when create/patch/put/delete
void SnapperProvider::bcache_clean(shared_ptr<::snapper::service::request_context> request)
{
    if(request->get_method() == snapper::service::http_patch ||
       request->get_method() == snapper::service::http_put ||
       request->get_method() == snapper::service::http_delete ||
       (request->get_method() == snapper::service::http_post && request->is_op_create() == true))
    {
        if(bcache_keys.size() == 0)//by default clean key with resource name itself 
            bcache_keys[get_name()] = true;
        snapper::datamgr::refresh_bson_cache_by_keys(bcache_keys);
    }
}


//////////////////////////////////////////////////////////////////////////////
// ResourceProvider Class
//
//////////////////////////////////////////////////////////////////////////////

// build "Id" obj
void ResourceProvider::set_id_obj()
{
    create_prop( RESOURCE_ID,         MAKE_BSON_OBJ(RESOURCE_ID, get_id_key()) );
}

int ResourceCollectionProvider::handle_patch(shared_ptr<::snapper::service::request_context> request)
{
    // Resource Collection doesn't support PATCH
    m_message.add_error_message_obj(StandardErrorMessage::MMO_MethodNotAllowed(get_name(), request->get_method_str()));
    override_http_code(HTTP_METHOD_NOT_ALLOWED);
    return RFRC_METHOD_NOT_ALLOWED;
}

int ResourceCollectionProvider::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    // Resource Collection doesn't support PATCH
    m_message.add_error_message_obj(StandardErrorMessage::MMO_MethodNotAllowed(get_name(), request->get_method_str()));
    override_http_code(HTTP_METHOD_NOT_ALLOWED);
    return RFRC_METHOD_NOT_ALLOWED;
}

int ResourceCollectionProvider::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    // Resource Collection doesn't support PATCH
    m_message.add_error_message_obj(StandardErrorMessage::MMO_MethodNotAllowed(get_name(), request->get_method_str()));
    override_http_code(HTTP_METHOD_NOT_ALLOWED);
    return RFRC_METHOD_NOT_ALLOWED;
}


// build common objs for resource collection
// including "Members@odata.count" and "Members@odata.navigationLink"
void ResourceCollectionProvider::set_member_objs(std::string containing_path)
{

    auto propclass = get_property_class();
    auto itp = propclass.find(RESOURCE_MEMBERS);
    if (itp == propclass.end())
        return;
    auto classtype = itp->second; // vector < type, classname>
    if(classtype.size() < 2)
        return;

    std::shared_ptr<memid_acckey_map> idlist = SnapperProvider::getlist_memid_acckey_fromclass(classtype[1], containing_path);
    if(idlist == nullptr)
        return;

    bson::BSONArrayBuilder arr_builder;
    unsigned char member_count = 0;
    for(auto it=idlist->begin();it != idlist->end();++it)
    {
        std::string memberid = it->first;
        std::string accessor_key = it->second;
        member_count++;
        auto uri = ::snapper::service::ResourceTopology::search_url(accessor_key, get_name());

        if(uri != nullptr){
            bson::BSONObjBuilder o;
            o << ODATA_ID << uri->c_str() ;
            RF_PRINT_DBG(" %s -- %s -- %s \n", memberid.c_str(), accessor_key.c_str(), uri->c_str());
            arr_builder << o.obj();
        }
        else
            RF_PRINT_WARN("set_member_objs: URI for %s -- %s not found, topology out of date! \n", memberid.c_str(), accessor_key.c_str() );
    }

    setobj(RESOURCE_MEMBERS, MAKE_BSON_OBJ(RESOURCE_MEMBERS, arr_builder.arr()));    
    setobj(MEMBERS_COUNT, MAKE_BSON_OBJ(MEMBERS_COUNT, member_count));
    std::string ref(get_base_odata_id().c_str());
    ref += "/";
    ref += RESOURCE_MEMBERS;
    setobj(MEMBERS_NAV_LINK, MAKE_BSON_OBJ(MEMBERS_NAV_LINK, ref));

}

// common function to access "Members" of resource collection
int ResourceCollectionProvider::access_member_prop(std::string prop_in, std::string classname, std::string containing_path)
{
    if(prop_in.compare(RESOURCE_MEMBERS))
    {
        m_message.add_error_message_obj(StandardErrorMessage::MMO_RequestUriNotFound());
        override_http_code(::snapper::providers::HTTP_NOT_FOUND);
        return RFRC_DATA_NOT_FOUND;
    }

    std::shared_ptr<memid_acckey_map> idlist = SnapperProvider::getlist_memid_acckey_fromclass(classname, containing_path);
    bson::BSONArrayBuilder arr_builder;
    if(idlist != nullptr)
    {
        for(auto it=idlist->begin();it != idlist->end();++it)
        {
            std::string memberid = it->first;
            std::string accessor_key = it->second;
            auto uri = ::snapper::service::ResourceTopology::search_url(accessor_key, get_name());

            if(uri != nullptr){
                bson::BSONObjBuilder o;
                o << ODATA_ID << uri->c_str() ;
                RF_PRINT_DBG(" %s -- %s -coll- %s \n", memberid.c_str(), accessor_key.c_str(), uri->c_str());
                arr_builder << o.obj();
            }
            else
                RF_PRINT_WARN("access_member_prop: URI for %s -- %s not found, topology out of date! \n", memberid.c_str(), accessor_key.c_str() );

        }
    }

    //specifically "value" is not in properties, so access objs directly
    create_prop( "value",  MAKE_BSON_OBJ("value", arr_builder.arr()) );
    return RFRC_SUCCESS;
}

}}
