//---------------------------------------------------------------------
// <copyright file="BSONCache.h" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once

#include <map>
#include <string>
#include "bson/bson.h"
#include "bson/util/json.h"

using namespace ::std;

namespace snapper { namespace datamgr
{

#define MAX_BSONCACHE_ENTRIES  60

struct BCache_Config
{
    BCache_Config(unsigned int t)
    {
        life_time = t;
    }

    unsigned int life_time; // life time in seconds. if data are non-volatile, you can set a big number...
    std::vector<unsigned int> refresh_types; // refresh_data_type. any data change in the types, the cache related to the key should be cleared
    void addtype(unsigned int t)
    {
        refresh_types.push_back(t);
    }
};

struct BCache_Entry
{
    unsigned int create_time;
    std::string key;
    bson::BSONObj result;
};


class BSON_Cache
{
public:
    BSON_Cache();
    void Add_BSON(std::string key, std::string args, bson::BSONObj& data);
    std::shared_ptr<BCache_Entry> Find_BSON(std::string key, std::string args);
    void Refresh_BSON(std::map<const std::string, bool> & keylist);
    void ClearData();
    std::map<const std::string, std::shared_ptr<BCache_Config>> & getconfig()
    {
        return m_config;
    }
private:
    std::map<const std::string, std::shared_ptr<BCache_Entry>> m_bson;       //identifier = key+ "||" + args
    std::map<const std::string, std::shared_ptr<BCache_Config>> m_config;    //identifier = key. one key/config may have several cache entries by args
};

void add_bson_cache(std::string key, std::string args, bson::BSONObj& data);
std::shared_ptr<BCache_Entry> find_bson_cache(std::string key, std::string args);
void refresh_bson_cache(std::vector<unsigned int> types);
void refresh_bson_cache_by_keys(std::map<const std::string, bool> & keylist);
void bson_cache_config(std::map<const std::string, std::shared_ptr<BCache_Config>> & config);
void clear_bson_cache();

}}
