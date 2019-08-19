#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

#include <memory>
#include <fstream>
#include <iostream>

#include "DataInterfaceConfigMgr.h"

using namespace std;

namespace snapper { namespace datamgr
{




/**
 * @brief  constructor
 */
DataInterfaceConfigMgr::DataInterfaceConfigMgr()
   : isready(false)
{
}


/**
 * @brief  destructor
 */
DataInterfaceConfigMgr::~DataInterfaceConfigMgr()
{
}


/**
 * @brief   get the pointer to config manager singleton
 *
 * @return  the pointer to the config manager
 */
DataInterfaceConfigMgr* DataInterfaceConfigMgr::get()
{
    static DataInterfaceConfigMgr *configMgr = NULL;
    if(configMgr == NULL)
        configMgr = new DataInterfaceConfigMgr();

    return configMgr;
}

bool DataInterfaceConfigMgr::initialize()
{
    isready = true;
    return true;
}


}}

