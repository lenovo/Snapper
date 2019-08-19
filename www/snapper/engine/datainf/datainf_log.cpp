#include <algorithm>
#include <iostream>
#include <string>
#include <stdarg.h>
#include "datainf_log.h"

int DataInterfaceLog::TRACE   = 3;
int DataInterfaceLog::INFO    = 2;
int DataInterfaceLog::WARNING = 1;
int DataInterfaceLog::ERROR   = 0;

using namespace std;    
DataInterfaceLog::DataInterfaceLog()
{
    context = "";
    level = 0; 
}
DataInterfaceLog::DataInterfaceLog( const char* ctxt ) : context(ctxt)
{
    level = 0; 
}

DataInterfaceLog::~DataInterfaceLog()
{
}

void DataInterfaceLog::setLogLevel( int l )
{
    level = l;
}

void DataInterfaceLog::setBaseLog( DataInterfaceLog& l )
{
    level = l.level;
    context = l.context;
}

void DataInterfaceLog::setBaseLog( const char* ctx, DataInterfaceLog& l )
{
    level = l.level;
    context = ctx;
}

#pragma GCC diagnostic ignored "-Wmissing-format-attribute"
void DataInterfaceLog::tprint(int l, const char* msg, va_list ap)
{
    char buf[2048];
    vsnprintf( buf, sizeof(buf)-1, msg, ap );
    if(l <= level)
        printf(buf);
}

void DataInterfaceLog::logInfo( const char* msg, ... )
{
    int l = INFO;
    va_list ap;
    va_start( ap, msg );
    tprint( l, msg, ap );
    va_end( ap );

}

void DataInterfaceLog::logWarning( const char* msg, ... )
{
    int l = WARNING;
    va_list ap;
    va_start( ap, msg );
    tprint( l, msg, ap );
    va_end( ap );
}

void DataInterfaceLog::logError( const char* msg, ... )
{
    int l = ERROR;
    va_list ap;
    va_start( ap, msg );
    tprint( l, msg, ap );
    va_end( ap );
}
void DataInterfaceLog::logTrace( const char* msg, ... )
{
    int l = TRACE;
    va_list ap;
    va_start( ap, msg );
    tprint( l, msg, ap );
    va_end( ap );
}
#pragma GCC diagnostic warning "-Wmissing-format-attribute"

