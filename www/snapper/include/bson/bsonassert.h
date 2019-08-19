/** @file bsonassert.h
    BSON classes
*/

/*
 *    Copyright 2009 10gen Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
   Main include file for C++ BSON module when using standalone (sans MongoDB client).

   "BSON" stands for "binary JSON" -- ie a binary way to represent objects that
   would be represented in JSON (plus a few extensions useful for databases &
   other languages).

   http://www.bsonspec.org/
*/

#pragma once

#include <cstdlib>
#include <memory>
#include <iostream>
#include <sstream>
#include <boost/utility.hpp>
#include <execinfo.h>
#include <cxxabi.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "stringdata.h"

namespace bson {

    using std::string;
    using std::stringstream;
#pragma GCC diagnostic ignored "-Wmissing-format-attribute"

    class assertion : public std::exception {
    public:
        assertion( unsigned u , const string& s )
            : id( u ) , msg( s ) {
            stringstream ss;
            ss << "BsonAssertion id: " << u << " " << s;
            full = ss.str();
            bson_backtrace(u, s);
        }

        virtual ~assertion() throw() {}

        virtual const char* what() const throw() { return full.c_str(); }

        void bson_log( const char *fmt, ... ) 
        { 
            va_list arg_list; 
            char buf[512]; 
            memset(buf, 0, sizeof(buf)); 
            va_start(arg_list, fmt); 
            vsnprintf(buf, sizeof(buf) - 1, fmt, arg_list); 
            va_end(arg_list); 

            int fd = open("/sys/kernel/tb_blk1/WEBAPP/push", O_WRONLY);//TODO rename region
            if(fd >=0 )
            {
                int rc = write(fd, buf, strlen(buf));
                if(rc);
                close(fd);
            }
            printf("%s", buf);
        }

        void bson_backtrace(unsigned msgid, string error)
        {
            bson_log("\n-----Exception [bson exception]-----\n");
            bson_log("Error: %d %s. Backtrace : \n", msgid, error.c_str());

            #define FR_NUM 10
            void * bt[FR_NUM];
            int entries = backtrace( (void **) &bt, FR_NUM );
            if ( entries )
            {
                char **data = backtrace_symbols( bt, entries );
                if ( data )
                {
                    for (int i = 0; i < entries; i++ )
                    {
                      bson_log( "    [%d] %s\n", i, data[i]);
                    }
                    free( data );
		        }
	        }
        }

        unsigned id;
        string msg;
        string full;
    };

#if !defined(assert)
    inline void assert(bool expr) {
        if(!expr) {
            throw bson::assertion( 0 , "assertion failure in bson library" );
        }
    }
#endif
#if !defined(uassert)
    inline void uasserted(unsigned msgid, std::string s) {
        throw bson::assertion( msgid , s );
    }

    inline void uassert(unsigned msgid, std::string msg, bool expr) {
        if( !expr )
            uasserted( msgid , msg );
    }
    inline void msgasserted(int msgid, const char *msg) {
        throw bson::assertion( msgid , msg );
    }
    inline void msgasserted(int msgid, const std::string &msg) { msgasserted(msgid, msg.c_str()); }
    inline void massert(unsigned msgid, std::string msg, bool expr) {
        if(!expr) {
            std::cout << "assertion failure in bson library: " << msgid << ' ' << msg << std::endl;
            throw bson::assertion( msgid , msg );
        }
    }
#endif

#pragma GCC diagnostic warning "-Wmissing-format-attribute"
}
