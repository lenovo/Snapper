/*---------------------------------------------------------------------------
//  Copyright (c) 2018-present, Lenovo. All rights reserved.
//  Licensed under BSD, see COPYING.BSD file for details.
//---------------------------------------------------------------------------
*/

#include <www/engine/rf_debug.h>
#include "class/SnapperMessage.h"
#include <algorithm>
#include "class/SnapperRegistry.h"
#include "class/BaseMessage.h"
#include "class/StandardErrorMessage.h"
#include "class/AuditEventMessage.h"

namespace snapper { namespace providers
{

map<string, std::shared_ptr<SnapperRegistry>> RegistryObjectFactory::ObjMap;

vector<string> SnapperRegistry::registry_list;

void SnapperRegistry::register_to_snapper(string registry_name)
{
    std::cout  << "###############" << registry_name << " is registered to snapper ############# " << std::endl;
    registry_list.push_back(registry_name);
}

vector<string> & SnapperRegistry::get_registry_list()
{
    return registry_list;
}

ADD_REGISTRY(BaseMessage);  
ADD_REGISTRY(StandardErrorMessage);  
ADD_REGISTRY(AuditEventMessage);  

}}
