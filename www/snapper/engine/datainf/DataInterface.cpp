#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include "DataInterface.h"

using namespace std;

namespace snapper { namespace datamgr
{

DataInterface::DataInterface()
    :   m_log("DataIface")
{
}


DataInterface::~DataInterface()
{
}

void DataInterface::setLog( DataInterfaceLog& log ) 
{
    m_log.setBaseLog( log );
}

void DataInterface::setLog( const char * context, DataInterfaceLog& log ) 
{
    m_log.setBaseLog( context, log );
}

}}
