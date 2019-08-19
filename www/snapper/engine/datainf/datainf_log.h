#ifndef _DATAINF_LOG_H_
#define _DATAINF_LOG_H_

#include <string>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#ifdef __GNUC__
#define ATTRIBUTE_FORMAT(stridx, varargidx) __attribute__ ((format (printf, stridx, varargidx)))
#else
#define ATTRIBUTE_FORMAT(a,b)
#endif


using namespace std;
class DataInterfaceLog
{
protected:
    string context;
	int level;

public:
    static int TRACE;
    static int INFO;
    static int WARNING;
    static int ERROR;
    
    DataInterfaceLog();
    DataInterfaceLog(const char* ctxt);
    virtual ~DataInterfaceLog();
    void setBaseLog( DataInterfaceLog& l );
	void setBaseLog( const char* ctxt, DataInterfaceLog& l );
	void setLogLevel(int l);
    
    void logInfo( const char* msg, ... );
    void logWarning( const char* msg, ... );
    void logError( const char* msg, ... );
    void logTrace( const char* msg, ... );
private:
	void tprint(int l, const char* msg, va_list ap);
};

#endif
