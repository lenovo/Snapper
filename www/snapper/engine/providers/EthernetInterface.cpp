//---------------------------------------------------------------------
// <copyright file="EthernetInterface.cpp" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------
#include "class/EthernetInterface.h"
#include "datainf/DataInterfaceMgr.h"
#include <www/engine/topology.h>
#include <www/engine/rf_debug.h>
#include "class/ClassNames.h"
#include "protocol.h"
#include "class/ClassCommon.h"
#include "class/ProviderHelper.h"

using namespace snapper::service;
using namespace std;

#define HOST_USBLAN "ToManager"
#define HOST_NIC    "NIC"
#define BMC_USBLAN "ToHost"
#define BMC_NIC "NIC"

namespace snapper { namespace providers 
{


std::shared_ptr<memid_acckey_map> EthernetInterface::getlist_memid_acckey(std::string containing_path)
{
    std::shared_ptr<memid_acckey_map> list = std::make_shared<memid_acckey_map>();
    std::vector<string> m;
    int rc = DataInterfaceMgr::mockupMemberList(containing_path, m);

    for(int i = 0; i < m.size(); i++)
    {
        (*list)[m[i]] = std::string(m[i])+"@"+"EthernetInterface";
    }
    return list;

}


int EthernetInterface::handle_get(shared_ptr<::snapper::service::request_context> request)
{
    //inovke at the BEGINNING for resource GET
    SnapperProvider::prepare_ResGet(request);


    //////////////////////////////////////////////////////
    // handle navigation property query under the resource
    const char* prop_in = is_navprop_query(request);
    if(prop_in)
        return RFRC_METHOD_NOT_ALLOWED;

    bson::BSONObj dataobjs;
    DataInterfaceMgr::mockupGetData(request->get_raw_path(), dataobjs);
    //std::cout << dataobjs.jsonString(bson::Strict) << std::endl;

    //////////////////////////////////////////////////////
    // GET resource query
    string oid_in = request->get_raw_path();

    enum_property_values(dataobjs);

    set_status_obj(MAKE_ENUM_STRING(State_Enabled),
                       MAKE_ENUM_STRING(Health_OK),
                       MAKE_ENUM_STRING(Health_OK)); //build object for Staus    

    // invoke at the END for resource GET
    SnapperProvider::auto_build_objects_ResGET(oid_in);
    return RFRC_SUCCESS;
}

int EthernetInterface::handle_post(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}


int EthernetInterface::handle_patch(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int EthernetInterface::handle_put(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}

int EthernetInterface::handle_delete(shared_ptr<::snapper::service::request_context> request)
{
    return RFRC_METHOD_NOT_ALLOWED;
}


REGISTER_PROVIDER(EthernetInterface);

}}

