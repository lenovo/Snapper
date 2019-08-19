//---------------------------------------------------------------------
// <copyright file="json_cache.h" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once

#include <map>
#include <string>
#include "bson/bson.h"
#include "bson/util/json.h"

using namespace ::std;

namespace snapper { namespace service
{
#define MAX_JSONCACHE_ENTRIES  20

#define JSONCACHE_LIFETIME     30
#define JSONCACHE_STALETIME    8

struct jcache_entry
{
    //cache time
    unsigned int create_time;
    unsigned int query_time;

    //cache identifier from request_context
    std::string raw_path;
    int method;
    int skip;
    int top;

    std::string res_name;//resource name

    //cache data
    std::string resp_body;
    std::string resp_hdr;
    int status_code;
};


class json_cache
{
public:
    json_cache();
    void cache_data(shared_ptr<request_context> reqctx, std::string& body, std::string& header, int httpcode, std::string resource_name);
    std::shared_ptr<jcache_entry> get_from_cache(shared_ptr<request_context> reqctx);
    void refresh_json(std::vector<std::string> reslist);
private:
    std::map<const std::string, std::shared_ptr<jcache_entry>> m_json;
    std::map<const std::string, unsigned int> longtime_config;
};

void add_json_cache(shared_ptr<request_context> request, std::string& resp_body, std::string& resp_hdr, int httpcode, std::string resource_name);
std::shared_ptr<jcache_entry> find_json_cache(shared_ptr<request_context> request);
void refresh_json_cache(std::vector<std::string> schema_nms);

}}
