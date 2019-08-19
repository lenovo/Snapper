//---------------------------------------------------------------------
// <copyright file="BSONCache.cpp" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include <www/engine/rf_debug.h>
#include <www/engine/request_context.h>
#include <www/engine/BSONCache.h>

#include <time.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <map>
#include <vector>
#include <pthread.h>

#define DELIMITER   "||"
#define BFLAG    "[bcache]: "

using namespace bson;
namespace snapper { namespace datamgr
{
static bool enabled_cache_l2 = true;

static BSON_Cache cache_level2; 
static pthread_mutex_t cachelock=PTHREAD_MUTEX_INITIALIZER;

BSON_Cache::BSON_Cache()
{
    bson_cache_config(m_config);
}

void BSON_Cache::Add_BSON(std::string key, std::string args, bson::BSONObj& data)
{
    if(enabled_cache_l2 == false) return;

    struct sysinfo s_info;
    time_t cur = time(NULL);
    if(sysinfo(&s_info) == 0)
        cur = s_info.uptime;
    if(m_config.find(key) == m_config.end())//not configured for caching
        return;

    if(m_bson.size() >= MAX_BSONCACHE_ENTRIES)
    {
        pthread_mutex_lock( &cachelock ); 
        std::vector<std::string> ids;
        std::map<const std::string, std::shared_ptr<BCache_Entry>>::iterator it;
        for(it=m_bson.begin();it!=m_bson.end();++it)
        {
            auto id = it->first;
            auto entry = it->second;
            if((entry->create_time + m_config[key]->life_time) < cur )
                ids.push_back(id);
        }
        for(int i = 0; i < ids.size(); i++)
        {
            if(m_bson.find(ids[i]) == m_bson.end())
                continue;
            m_bson[ids[i]] = nullptr;
            m_bson.erase(ids[i]);
            RF_PRINT_DBG(BFLAG "remove cached bson id %s\n", ids[i].c_str());
        }
        pthread_mutex_unlock( &cachelock );

        if(m_bson.size() >= MAX_BSONCACHE_ENTRIES)
        {
            RF_PRINT_WARN(BFLAG "bson cache full\n");
            return;   
        }
    }

    std::string index = key + DELIMITER + args;
    auto newentry = std::make_shared<BCache_Entry>();
    newentry->create_time = cur;
    newentry->key = key;
    newentry->result = data;
    RF_PRINT_DBG(BFLAG "bson cache added for %s\n", index.c_str());

    pthread_mutex_lock( &cachelock ); 
    m_bson[index] = newentry;
    pthread_mutex_unlock( &cachelock );
}

//search cache entry by key name of xml metadata +  arguments of getData()
std::shared_ptr<BCache_Entry> BSON_Cache::Find_BSON(std::string key, std::string args)
{
    struct sysinfo s_info;
    time_t cur = time(NULL);
    if(sysinfo(&s_info) == 0)
        cur = s_info.uptime;
    std::string index = key + DELIMITER + args;
    std::shared_ptr<BCache_Entry> entry = nullptr;

    if(m_config.find(key) == m_config.end())
        return nullptr;

    pthread_mutex_lock( &cachelock ); 
    if(m_bson.find(index) != m_bson.end())
        entry = m_bson[index];
    pthread_mutex_unlock( &cachelock );
    //RF_PRINT_DBG(BFLAG "search bson cache for %s  %d\n", index.c_str(), (entry?1:0));

    if(entry != nullptr)
    {
        if((entry->create_time + m_config[key]->life_time) < cur )
        {
            pthread_mutex_lock( &cachelock ); 
            m_bson[index] = nullptr;
            m_bson.erase(index);
            pthread_mutex_unlock( &cachelock );
            RF_PRINT_DBG(BFLAG "bson cache expired %s, %d %d\n", index.c_str(), entry->create_time, (int)cur);
            return nullptr;
        }
        RF_PRINT_DBG(BFLAG "return cached bson %s\n", index.c_str());
        return entry;
    }

    return nullptr;
}
//refresh cache by key of metadata xml
void BSON_Cache::Refresh_BSON(std::map<const std::string, bool> & keylist)
{
    pthread_mutex_lock( &cachelock ); 

    std::vector<std::string> ids;
    std::map<const std::string, std::shared_ptr<BCache_Entry>>::iterator it;
    for(it=m_bson.begin();it!=m_bson.end();++it)
    {
        auto id = it->first;
        auto entry = it->second;
        if(keylist.find(entry->key) != keylist.end())//stale entry
            ids.push_back(id);
    }
    for(int i = 0; i < ids.size(); i++)
    {
        if(m_bson.find(ids[i]) == m_bson.end())
            continue;
        m_bson[ids[i]] = nullptr;
        m_bson.erase(ids[i]);
        RF_PRINT_DBG(BFLAG "refresh stale bson cache %s\n", ids[i].c_str());
    }

    pthread_mutex_unlock( &cachelock );

}
void BSON_Cache::ClearData()
{
    pthread_mutex_lock( &cachelock ); 
    m_bson.clear();
    pthread_mutex_unlock( &cachelock );
}
/////////////////////////////////////////////////////////////

void add_bson_cache(std::string key, std::string args, bson::BSONObj& data)
{
    cache_level2.Add_BSON(key, args, data);
}

std::shared_ptr<BCache_Entry> find_bson_cache(std::string key, std::string args)
{
    return cache_level2.Find_BSON(key, args);
}

void clear_bson_cache()
{
    cache_level2.ClearData();
}

//refresh cache entry when multiple data types triggering 
//map data types to key name in metadata
void refresh_bson_cache(std::vector<unsigned int> types)
{
    std::map<const std::string, bool> stalelist;
    auto config = cache_level2.getconfig();

    std::map<const std::string, std::shared_ptr<BCache_Config>>::iterator it;
    for(it=config.begin();it!=config.end();++it)
    {
        auto key = it->first;
        auto cfgentry = it->second;
        for(int i = 0; i < types.size(); i++)
            for(int j=0;j<cfgentry->refresh_types.size();j++)
                if(types[i] == cfgentry->refresh_types[j])//any type associated with the key data, should refresh key related cache
                    stalelist[key] = true;
    }

    for(int k = 0; k < types.size(); k++)
        RF_PRINT_DBG(BFLAG "to refresh data type %d\n", types[k]);

    cache_level2.Refresh_BSON(stalelist);

}
//after sucessfully PATCH/POST/DELETE a resource, the related cache with metadata key shall be removed.
void refresh_bson_cache_by_keys(std::map<const std::string, bool> & keylist)
{
    cache_level2.Refresh_BSON(keylist);
}

}}
