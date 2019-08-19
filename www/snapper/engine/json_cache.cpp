//---------------------------------------------------------------------
// <copyright file="json_cache.cpp" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include <www/engine/rf_debug.h>
#include <www/engine/request_context.h>

#include "json_cache.h"

#include <pthread.h>
#include <time.h>
#include <sys/sysinfo.h>
#include <sys/types.h>

#include <map>
#include <vector>

#define JFLAG    "[jcache]: "

namespace snapper { namespace service
{
static bool enabled_cache_l1 = true;

static json_cache cache_level1; 
static pthread_mutex_t jsonlock=PTHREAD_MUTEX_INITIALIZER;

json_cache::json_cache()
{
    //special cases of config which need longer or shorter life time in json cache than default life time
    // [Schema class name] = seconds
    longtime_config["LogEntryCollection"] = 600; // long time L1 cache for event log

    //longtime_config["TaskCollection"] = 3; //short time L1 cache for task
    //longtime_config["Task"] = 3;
    //longtime_config["SessionCollection"] = 3; //short time L1 cache for session
    //longtime_config["Session"] = 3;
}

//check cache life time by resource name
void json_cache::cache_data(shared_ptr<request_context> reqctx, std::string& body, std::string& header, int httpcode, std::string resource_name)
{
    if(enabled_cache_l1 == false) return;

    struct sysinfo s_info;
    time_t cur = time(NULL);
    if(sysinfo(&s_info) == 0)
        cur = s_info.uptime;

    if(m_json.size() >= MAX_JSONCACHE_ENTRIES)
    {
        pthread_mutex_lock( &jsonlock ); 
        std::vector<std::string> urls;
        std::map<const std::string, std::shared_ptr<jcache_entry>>::iterator it;
        for(it=m_json.begin();it!=m_json.end();++it)
        {
            unsigned int LIFE_TIME = JSONCACHE_LIFETIME;
            unsigned int STALE_TIME = JSONCACHE_STALETIME;
            auto key = it->first;
            auto entry = it->second;

            if(longtime_config.find(entry->res_name) != longtime_config.end())
                LIFE_TIME = STALE_TIME = longtime_config[entry->res_name];

            if((entry->create_time + LIFE_TIME) < cur || (entry->query_time + STALE_TIME) < cur)
                urls.push_back(key);
        }
        for(int i = 0; i < urls.size(); i++)
        {
            if(m_json.find(urls[i]) == m_json.end())
                continue;
            m_json[urls[i]] = nullptr;
            m_json.erase(urls[i]);
            RF_PRINT_DBG(JFLAG "remove cached url %s\n", urls[i].c_str());
        }
        pthread_mutex_unlock( &jsonlock );

        if(m_json.size() >= MAX_JSONCACHE_ENTRIES)
        {
            RF_PRINT_WARN(JFLAG "json cache full\n");
            return;   
        }
    }

    auto entry = std::make_shared<jcache_entry>();
    entry->create_time = cur;
    entry->query_time = cur;
    entry->raw_path = reqctx->get_raw_path();
    entry->method = reqctx->get_method();
    entry->skip = reqctx->skip();
    entry->top = reqctx->top();
    entry->res_name = resource_name;

    entry->resp_body = body;
    entry->resp_hdr = header;
    entry->status_code = httpcode;

    pthread_mutex_lock( &jsonlock ); 
    m_json[reqctx->get_raw_path()] = entry;
    pthread_mutex_unlock( &jsonlock );
}

//search cache entry by uri+method+fragment
//check cache life time by resource name
std::shared_ptr<jcache_entry> json_cache::get_from_cache(shared_ptr<request_context> reqctx)
{
    struct sysinfo s_info;
    time_t cur = time(NULL);
    if(sysinfo(&s_info) == 0)
        cur = s_info.uptime;

    std::shared_ptr<jcache_entry> entry = nullptr;

    pthread_mutex_lock( &jsonlock ); 
    if(m_json.find(reqctx->get_raw_path()) != m_json.end())
        entry = m_json[reqctx->get_raw_path()];
    pthread_mutex_unlock( &jsonlock );

    if(entry != nullptr)
    {
        unsigned int LIFE_TIME = JSONCACHE_LIFETIME;
        unsigned int STALE_TIME = JSONCACHE_STALETIME;
        if(longtime_config.find(entry->res_name) != longtime_config.end())
            LIFE_TIME = STALE_TIME = longtime_config[entry->res_name];

        if(entry->method != reqctx->get_method() || entry->skip != reqctx->skip() || entry->top != reqctx->top())
            return nullptr;

        if((entry->create_time + LIFE_TIME) < cur || (entry->query_time + STALE_TIME) < cur)
        {
            pthread_mutex_lock( &jsonlock ); 
            m_json[reqctx->get_raw_path()] = nullptr;
            m_json.erase(reqctx->get_raw_path());
            pthread_mutex_unlock( &jsonlock );
            RF_PRINT_DBG(JFLAG "json cache expired (%d %d). url %s\n", LIFE_TIME, STALE_TIME, reqctx->get_raw_path().c_str());
            return nullptr;
        }

        RF_PRINT_DBG(JFLAG "return cached %s, url %s\n", entry->res_name.c_str(), reqctx->get_raw_path().c_str());
        entry->query_time = cur;
        return entry;
    }

    return nullptr;
}

//refresh cache entry by resource name
//  - data change will trigger cache refresh
//  - after sucessfully PATCH/POST/DELETE a resource, the related cache shall be removed.
void json_cache::refresh_json(std::vector<std::string> reslist)
{
    pthread_mutex_lock( &jsonlock ); 
    std::vector<std::string> urls;
    std::map<const std::string, std::shared_ptr<jcache_entry>>::iterator it;
    for(it=m_json.begin();it!=m_json.end();++it)
    {
        auto key = it->first;
        auto entry = it->second;

        for(int i = 0; i < reslist.size(); i++)
        {
            if(reslist[i].compare(entry->res_name) == 0)
            {
                urls.push_back(key);
                break;
            }
        }
    }
    for(int i = 0; i < urls.size(); i++)
    {
        if(m_json.find(urls[i]) == m_json.end())
            continue;
        m_json[urls[i]] = nullptr;
        m_json.erase(urls[i]);
        RF_PRINT_DBG(JFLAG "remove cached url %s\n", urls[i].c_str());
    }
    pthread_mutex_unlock( &jsonlock );

}
/////////////////////////////////////////////////////////////
void add_json_cache(shared_ptr<request_context> request, std::string& resp_body, std::string& resp_hdr, int httpcode, std::string resource_name)
{
    cache_level1.cache_data(request, resp_body, resp_hdr, httpcode, resource_name);
}

std::shared_ptr<jcache_entry> find_json_cache(shared_ptr<request_context> request)
{
    return cache_level1.get_from_cache(request);
}
void refresh_json_cache(std::vector<std::string> schema_nms)
{
    cache_level1.refresh_json(schema_nms);
}

}}
