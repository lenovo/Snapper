#ifndef __DATA_INTERFACE_MGR_H_
#define __DATA_INTERFACE_MGR_H_

#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include "bson/bson.h"

#include "DataInterfaceConfigMgr.h"
#include "datainf_log.h"

using namespace std;

namespace snapper { namespace datamgr
{

class DataInterfaceMgr
{
public:
    DataInterfaceMgr();
    ~DataInterfaceMgr();
    static bool initialize();

    static int getData( string urlKey, const bson::BSONObj& args, bson::BSONObjBuilder& err_rslt );
    static int getData_nocache( string urlKey, const bson::BSONObj& args, bson::BSONObjBuilder& err_rslt );

    static int setData( const bson::BSONObj& args, bson::BSONObjBuilder& rslt );

    static void DataMgrClientInfo(int priv, char *user, char *remoteip);
#ifdef __SIM_X86__
    static int mockupMemberList( string containing_path, vector<string> & mids );
    static int mockupGetData( string rel_uri, bson::BSONObj& rslt );
#endif

private:
    static int  clientPrivBits;
    static char clientUsername[64];
    static char clientIpAddr[64];

};


}}

#endif // __DATA_INTERFACE_MGR_H_
