#include <www/engine/rf_engine_error.h>
#include <www/engine/BSONCache.h>
#include <www/engine/rf_debug.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "DataInterfaceMgr.h"

using namespace std;
using namespace ::bson;

namespace snapper { namespace datamgr
{





int  DataInterfaceMgr::clientPrivBits;
char DataInterfaceMgr::clientUsername[64];
char DataInterfaceMgr::clientIpAddr[64];

DataInterfaceMgr::DataInterfaceMgr()
{

}

DataInterfaceMgr::~DataInterfaceMgr()
{

}

void DataInterfaceMgr::DataMgrClientInfo(int priv, char *user, char *remoteip)
{

}

bool DataInterfaceMgr::initialize()
{
    return true;
}

/************************************************************
 * get data
 * urlKey - key name
 * args   - parameters for the key name
 *      for k:v (GET), should be empty object (no parameter)
 *      for functionality (GET), should be empty object (no parameter). **all function for getData in xml will be invoked**
 *      for sql/db (GET), could be {"sqlFuncName": ["param1","param2", ..]}  E.g {"pci_GetAdaptersConfiguration": ["1","2","3"], "psu_GetPSUVPD":["1","3"]}
 *                          ** only selected sql/db function in args will be invoked **
 * rslt   - BSON objects
 ***********************************************************/
int  DataInterfaceMgr::getData( string urlKey, const bson::BSONObj& args, bson::BSONObjBuilder& rslt )
{
    bson::BSONObjBuilder objectbuilder;
    bson::BSONObj object;
    int rc = RFRC_SUCCESS;

    rc = getData_nocache(urlKey, args, objectbuilder);

    return rc;
}

int  DataInterfaceMgr::getData_nocache( string urlKey, const bson::BSONObj& args, bson::BSONObjBuilder& rslt )
{
    DataInterfaceConfigMgr* pDICfgMgr = DataInterfaceConfigMgr::get();

    if (pDICfgMgr == NULL)
    {
        return RFRC_FAILURE;
    }

    return RFRC_SUCCESS;
}

/************************************************************
 * set data for fields or functions specified in parameters
 *  for k:v data: 
 *        args - dictionary data  format like
 *           {"IMM_Location": "XXXX", "IMM_Contact": "YYY"}. all values should be string type which would be converted by setData()
 *  for aim function and sqldb function: 
 *        args - dictionary data format like
 *           {"pci_SetAdapterSlot": ["3","1","2"], "raidlink_ClearForeignConf": ["18"]}
 * return - error code
 ***********************************************************/
int DataInterfaceMgr::setData( const bson::BSONObj& args, bson::BSONObjBuilder& rslt )
{
    return RFRC_SUCCESS;
}

#ifdef __SIM_X86__
#define DIR_MOCKUP "/../mockup/"

int DataInterfaceMgr::mockupMemberList( string containing_path, vector<string> & mids )
{
    char cwd[1024], *ptr;
	ptr = getcwd(cwd, sizeof(cwd)-1); //  vaw/www/snapper/app
    if(ptr == NULL)
        return false;
    string abs_path = string(cwd) + DIR_MOCKUP + containing_path.substr(0, containing_path.find(" "));
    RF_PRINT_DBG("current containing [%s]\n", abs_path.c_str());

    DIR *dirptr = NULL;
    struct dirent *entry;
	if((dirptr = opendir(abs_path.c_str())) == NULL)
	{
        RF_PRINT_ERR("Failed to open directory %s\n", abs_path.c_str());
        return RFRC_FAILURE;
	}

    while( (entry = readdir(dirptr)) != NULL)
    {
        string fpath = abs_path + "/" + entry->d_name;
        struct stat buf;
        if(lstat(fpath.c_str(), &buf) < 0)
            continue;
        int isdir = S_ISDIR(buf.st_mode);

        RF_PRINT_DBG("file %s, isdir %d\n", entry->d_name, isdir);
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, "Oem") == 0 || !isdir)
            continue;
        mids.push_back(entry->d_name);
    }
    closedir(dirptr);
    return RFRC_SUCCESS;
}
#define RESP_MOCKUP "/index.json"
int DataInterfaceMgr::mockupGetData( string rel_uri, bson::BSONObj& rslt )
{
   char cwd[1024], *ptr;
	ptr = getcwd(cwd, sizeof(cwd)-1); //  vaw/www/snapper/app
    if(ptr == NULL)
        return false;
    string abs_path = string(cwd) + DIR_MOCKUP + rel_uri + RESP_MOCKUP;
    RF_PRINT_DBG("current data dir [%s]\n", abs_path.c_str());

    struct stat buf;
    if(lstat(abs_path.c_str(), &buf) < 0)
        return RFRC_FAILURE;


    std::ifstream ifs;
    ifs.open (abs_path.c_str(), std::ifstream::in);
    if(!ifs.good())
    {
        RF_PRINT_ERR("failed to open response file %s\n", abs_path.c_str());
        return RFRC_FAILURE;
    }

    string text;
    char c = ifs.get();
    while (ifs.good()) {
        text.push_back(c);
        c = ifs.get();
    }
    rslt = ::bson::fromjson(text);

    ifs.close();
    return RFRC_SUCCESS;
}
#endif

}}

