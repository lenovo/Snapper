#ifndef __DATA_INTERFACE_H_
#define __DATA_INTERFACE_H_

#include <vector>
#include <string>
#include <map>
#include <boost/noncopyable.hpp>
#include "bson/bson.h"

#include "datainf_log.h"

using namespace std;

namespace snapper { namespace datamgr
{

class DataInterface
{
public:
    DataInterface();
    virtual ~DataInterface();

    virtual int getTable( bson::BSONObj& pParams, bson::BSONArrayBuilder* pRslt, bson::BSONObjBuilder* pErrRslt ) = 0;
    virtual int getValue( bson::BSONObj& pParams, bson::BSONObjBuilder* pRslt, bson::BSONObjBuilder* pErrRslt ) = 0;
    virtual int setValue( vector<bson::BSONObj>& pParams, bson::BSONObjBuilder* pRslt ) = 0;

    virtual void setLog( DataInterfaceLog& log );
	virtual void setLog( const char* context, DataInterfaceLog& log );

    void SetSessionInfo( unsigned int clientPrivBits, const char *clientUsername, const char* clientIpAddr )
    {
        m_clientPrivBits = clientPrivBits;
        m_clientUsername = clientUsername;
        m_clientIpAddr   = clientIpAddr;
    }

    unsigned int              m_clientPrivBits;
    const char*               m_clientUsername;
    const char*               m_clientIpAddr;

protected:

    DataInterfaceLog m_log;
};

}}

#endif // __DATA_INTERFACE_H_
