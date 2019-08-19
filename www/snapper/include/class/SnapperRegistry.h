//---------------------------------------------------------------------
// <copyright file="SnapperMessage.h" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details. 
// </copyright>
//---------------------------------------------------------------------

#pragma once

#include "bson/bson.h"
#include "bson/util/json.h"
#include "SnapperType.h"
using namespace ::std;

namespace snapper { namespace providers
{
    
class SnapperRegistry;
class RegistryObjectFactory
{
public:
    static std::shared_ptr<SnapperRegistry> GetObject(const string &name)
    {
        map<string, std::shared_ptr<SnapperRegistry>>::const_iterator it;
        it = ObjMap.find(name);
        if (it == ObjMap.end())
            return nullptr;
        else
            return it->second;
    }

    static map<string, std::shared_ptr<SnapperRegistry>> & GetRegistryMap()
    {
        return ObjMap;
    }
    
    static void Register(string name, std::shared_ptr<SnapperRegistry> obj)
    {
        ObjMap[name] = obj;
    }    
        
private:
    static map<string, std::shared_ptr<SnapperRegistry>> ObjMap;
};
    
class Registry
{
public:
    Registry(string name, std::shared_ptr<SnapperRegistry> obj)
    {
        RegistryObjectFactory::Register(name, obj);   
    }
};
    
#define ADD_REGISTRY(class_name) \
        class class_name##Registry { \
            private: \
                static Registry reg; \
        }; \
        Registry class_name##Registry::reg(#class_name, std::make_shared<class_name>()); 


class SnapperRegistry
{
    const string up_dir = "registries/";
public:
    SnapperRegistry(string name, string id, string version, string file_name): m_name(name), 
        m_id(id), m_version(version)
    {
        register_to_snapper(id);
        m_file_name = up_dir + file_name;
    }
    
    virtual ~SnapperRegistry() {};  
    
        
    
    const string& get_name() const 
    {
        return m_name;
    }  

    const string& get_id() const 
    {
        return m_id;
    }

    const string& get_version() const 
    {
        return m_version;
    }  

    const string& get_file_name() const
    {
        return m_file_name;
    }

    static vector<string> registry_list;    
    void register_to_snapper(string registry_name);
    static vector<string> & get_registry_list();

private:

    string m_name;
    string m_id;
    string m_version;
    string m_file_name;

};



}}
 
