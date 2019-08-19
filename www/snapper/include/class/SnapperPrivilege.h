//---------------------------------------------------------------------
// <copyright file="SnapperMessage.h" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details. 
// </copyright>
//---------------------------------------------------------------------

#pragma once

#include "bson/bson.h"
#include "bson/util/json.h"
#include "SnapperType.h"
#include "SnapperRegistry.h"
using namespace ::std;

namespace snapper { namespace providers
{
    
#define IMM_PRIV_DENY_ALWAYS                 0x0001  
#define IMM_PRIV_SUPERVISOR                  0x0002
#define IMM_PRIV_READ_ONLY                   0x0004 
#define IMM_PRIV_NETWORKING_AND_SECURITY     0x0008
#define IMM_PRIV_USER_ACCOUNT                0x0010
#define IMM_PRIV_REMOTE_CONSOLE              0x0020
#define IMM_PRIV_VIRTUAL_MEDIA               0x0040
#define IMM_PRIV_POWER_RESTART               0x0080
#define IMM_PRIV_CONFIG_BASIC                0x0100
#define IMM_PRIV_CLEAR_EVENT_LOGS            0x0200
#define IMM_PRIV_CONFIG_ADVANCED             0x0400


class SnapperPrivilege
{
public:
    
    enum http_method_
    {
        http_get,
        http_head,
        http_post,
        http_put,
        http_patch,
        http_delete,
        http_max
    };
    
    enum override_status
    {
        override_none = 0x00,
        property_override = 0x01,
        subordinate_override = 0x02,
        url_override = 0x04
    };

    enum override_check_status
    {
        override_ok,
        override_fail,
        override_not_found
    };

    struct http_method_privilege_array
    {
        unsigned long array[http_max];
    };

    
    SnapperPrivilege(string name) : m_name(name)  
    {
        init_m_priv_map();
        init_m_method_map();
    }

    virtual ~SnapperPrivilege()    
    {} 

    const string& get_name() const 
    {
        return m_name;
    }  
    
    void init_m_priv_map()
    {
        //m_priv_map.insert(pair<string, int>("Supervisor", IMM_PRIV_SUPERVISOR));
        //m_priv_map.insert(pair<string, int>("ReadOnly", IMM_PRIV_READ_ONLY));
        m_priv_map.insert(pair<string, int>("Login", 0x07FE)); // any user is ok
        m_priv_map.insert(pair<string, int>("ConfigureComponents", 0x00)); // not support
        m_priv_map.insert(pair<string, int>("ConfigureManager", 0x00)); // not support
        m_priv_map.insert(pair<string, int>("ConfigureSelf", 0x00)); // not support
        m_priv_map.insert(pair<string, int>("ConfigureUsers", IMM_PRIV_USER_ACCOUNT)); 
        m_priv_map.insert(pair<string, int>("UserAccountManagement", IMM_PRIV_USER_ACCOUNT));
        m_priv_map.insert(pair<string, int>("RemoteConsoleAccess", IMM_PRIV_REMOTE_CONSOLE));
        m_priv_map.insert(pair<string, int>("RemoteConsoleAndVirtualMediaAcccess", IMM_PRIV_VIRTUAL_MEDIA));
        m_priv_map.insert(pair<string, int>("RemoteServerPowerRestartAccess", IMM_PRIV_POWER_RESTART));
        m_priv_map.insert(pair<string, int>("AbilityClearEventLogs", IMM_PRIV_CLEAR_EVENT_LOGS));
        m_priv_map.insert(pair<string, int>("ConfigureBasic", IMM_PRIV_CONFIG_BASIC));
        m_priv_map.insert(pair<string, int>("ConfigureNetworkingAndSecurity", IMM_PRIV_NETWORKING_AND_SECURITY));
        m_priv_map.insert(pair<string, int>("ConfigureAdvanced", IMM_PRIV_CONFIG_ADVANCED));
    }

    void init_m_method_map()
    {
        m_method_map.insert(pair<string, int>("GET", http_get));
        m_method_map.insert(pair<string, int>("POST", http_post));
        m_method_map.insert(pair<string, int>("PUT", http_put));
        m_method_map.insert(pair<string, int>("PATCH", http_patch));
        m_method_map.insert(pair<string, int>("DELETE", http_delete));
        m_method_map.insert(pair<string, int>("HEAD", http_head));
    }
    
    int to_priv_bits(string priv_str)
    {
        auto it = m_priv_map.find(priv_str);
        if(it != m_priv_map.end())
            return it->second;
        else
            return 0x00;        
    }

    int to_method(string method_str)
    {
        auto it = m_method_map.find(method_str);
        if(it != m_method_map.end())
            return it->second;
        else
            return 0x00;        
    }

    unsigned char override_status()
    {
        unsigned char status = override_none; 
        if(m_prop_override_map.size())
            status |= property_override;
        if(m_subordinate_override_map.size())
            status |= subordinate_override;
        if(m_url_override_map.size())
            status |= url_override;

        return status;            
    }

    int check_base_priv(int method, unsigned long priv)
    {        
        if(m_priv_array.array[method] & priv)
            return override_ok;

        return override_fail;
    }

    int check_property_priv(string prop_name, int method, unsigned long priv)
    {        
        auto it = m_prop_override_map.find(prop_name);
        if(it != m_prop_override_map.end())
        {
            auto arr_p = it->second;
            if(arr_p->array[method] & priv)
                return override_ok;
            else
                return override_fail;
        }

        return override_not_found;
    }

    int check_subordinate_priv(string subordinate_name, int method, unsigned long priv)
    {
        for(auto it = m_subordinate_override_map.begin(); it != m_subordinate_override_map.end(); it++)
        {
            string target_str = it->first;
            if(subordinate_name.find(target_str) != string::npos)
            {
                auto arr_p = it->second;
                if(arr_p->array[method] & priv)
                    return override_ok;
                else
                    return override_fail;
            }
        }
        return override_not_found;
    }

    int check_url_priv(string url_name, int method, unsigned long priv)
    {        
        auto it = m_url_override_map.find(url_name);
        if(it != m_url_override_map.end())
        {
            auto arr_p = it->second;
            if(arr_p->array[method] & priv)
                return override_ok;
            else
                return override_fail;
        }
    
        return override_not_found;
    }

    void add_base_priv(string method_str, string priv_str)
    {
        int method = to_method(method_str);
        m_priv_array.array[method] += to_priv_bits(priv_str);
    }

    void add_prop_priv(string prop_name, string method_str, string priv_str)
    {
        int method = to_method(method_str);
        auto it = m_prop_override_map.find(prop_name);
        if(it != m_prop_override_map.end())
        {
            auto arr_p = it->second;
            arr_p->array[method] += to_priv_bits(priv_str);
        }
        else
        {
            std::shared_ptr<http_method_privilege_array> arr_p = std::make_shared<http_method_privilege_array>();
            for(int i = 0; i < http_max; i++)
                arr_p->array[i] = 0;
            arr_p->array[method] = to_priv_bits(priv_str);
            m_prop_override_map[prop_name] = arr_p;
        }
    }

    void add_subordinate_priv(string subordinate_name, string method_str, string priv_str)
    {
        int method = to_method(method_str);
        auto it = m_subordinate_override_map.find(subordinate_name);
        if(it != m_subordinate_override_map.end())
        {
            auto arr_p = it->second;
            arr_p->array[method] += to_priv_bits(priv_str);
        }
        else
        {
            std::shared_ptr<http_method_privilege_array> arr_p = std::make_shared<http_method_privilege_array>();
            for(int i = 0; i < http_max; i++)
                arr_p->array[i] = 0;
            arr_p->array[method] = to_priv_bits(priv_str);
            m_subordinate_override_map[subordinate_name] = arr_p;
        }
    }

    void add_url_priv(string url_name, string method_str, string priv_str)
    {
        int method = to_method(method_str);
        auto it = m_url_override_map.find(url_name);
        if(it != m_url_override_map.end())
        {
            auto arr_p = it->second;
            arr_p->array[method] += to_priv_bits(priv_str);
        }
        else
        {
            std::shared_ptr<http_method_privilege_array> arr_p = std::make_shared<http_method_privilege_array>();
            for(int i = 0; i < http_max; i++)
                arr_p->array[i] = 0;
            arr_p->array[method] = to_priv_bits(priv_str);
            m_url_override_map[url_name] = arr_p;
        }
    }

    bool has_prop_override()
    {
        return m_prop_override_map.size() ? true : false;
    }

    bool has_subordinate_override()
    {
        return m_subordinate_override_map.size() ? true : false;
    }
    
    bool has_url_override()
    {
        return m_url_override_map.size() ? true : false;
    }

    bool has_override()
    {
        if(m_prop_override_map.size() || m_subordinate_override_map.size() || m_url_override_map.size())
            return true;
        else
            return false;
    }
   
private:  
    string m_name;
    map<string, int> m_priv_map;
    map<string, int> m_method_map;
    http_method_privilege_array m_priv_array;
    map<string, std::shared_ptr<http_method_privilege_array>> m_prop_override_map; // the first element is resource_name + property
    map<string, std::shared_ptr<http_method_privilege_array>> m_subordinate_override_map;  // the first element is resource_name + subordinates
    map<string, std::shared_ptr<http_method_privilege_array>> m_url_override_map;     // the first element is resource_name + url
};

class PrivilegeObjectFactory
{
public:
    static std::shared_ptr<SnapperPrivilege> GetObject(const string &name)
    {
        map<string, std::shared_ptr<SnapperPrivilege>>::const_iterator it;
        it = ObjMap.find(name);
        if (it == ObjMap.end())
            return nullptr;
        else
            return it->second;
    }
    
    static void Register(string name, std::shared_ptr<SnapperPrivilege> obj)
    {
        string resource_name = obj->get_name();
        ObjMap[resource_name] = obj;
    }    
        
private:
    static map<string, std::shared_ptr<SnapperPrivilege>> ObjMap;
};

class PrivilegeRegister
{
public:
    PrivilegeRegister(string name, std::shared_ptr<SnapperPrivilege> obj)
    {
        PrivilegeObjectFactory::Register(name, obj);   
    }
};

#define REGISTER_PRIVILEGE(class_name) \
    class class_name##PrivilegeRegister { \
        private: \
            static PrivilegeRegister reg; \
    }; \
    PrivilegeRegister class_name##PrivilegeRegister::reg(#class_name, std::make_shared<class_name>()); 
}}
 
