/*---------------------------------------------------------------------------
//  Copyright (c) 2018-present, Lenovo. All rights reserved.
//  Licensed under BSD, see COPYING.BSD file for details.
//---------------------------------------------------------------------------
*/

#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>
#include <dirent.h>
#include <regex.h>

#include "bson/bson.h"
#include "bson/util/json.h"
#include "odata/core/odata_core.h"


#include "message_registeries_autogen.h"


#include <boost/noncopyable.hpp>

using namespace std;
using namespace ::odata::core;
using namespace ::odata::edm;
using namespace ::odata::utility;
using namespace ::bson;


void _gen_message_header_file(string file_name, string dest_dir)
{
#pragma GCC diagnostic ignored "-Wformat-security"		
    
        /////////////////////////////////////////////
    // define static text of header code
    /////////////////////////////////////////////
        const char *sHdr = 
    "//---------------------------------------------------------------------\n"
    "// <copyright file=\"_p%s.h\" company=\"Lenovo\">\n"
    "//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.\n"
    "// </copyright>\n"
    "//---------------------------------------------------------------------\n\n"
    "#pragma once \n\n"
    "#include \"SnapperMessage.h\"\n\n";
    
        const char *sNS_Class_Hdr = 
    "namespace snapper { namespace providers \n"
    "{\n\n"
    "class _p%s : public SnapperRegistry\n"
    "{\n"
    "public:\n";
        
         const char *sNS_Class_Tail = 
    "};\n\n"
    "}}\n\n"; 
    
         const char *sNS_Class_Func1 = 
    "    _p%s() : SnapperRegistry(\"%s\", \"%s\", \"%s\", \"%s\")    \n"
    "    {\n";
    
         const char *sNS_Class_Func1_end = 
    "    }\n\n"
    "    virtual ~_p%s()    \n"
    "    {}\n\n"
    "    // MMO = Make Message Object\n";
    
         
         const char *sNS_Class_msg_function_start = 
    "    static std::shared_ptr<bson::BSONObj> MMO_%s(%s)\n"
    "    {\n "
    "        return  std::make_shared<bson::BSONObj>(%s);\n";
         const char *sNS_Class_msg_function_end = 
    "    }\n\n";
    

    ifstream ifs(file_name);
    stringstream buffer;
    buffer << ifs.rdbuf();  
    string contents(buffer.str());

    string str = contents.substr(0, contents.find_last_of("}")+1);
    bson::BSONObj o = bson::fromjson(str);
    string name =  o.getStringField("RegistryPrefix"); // use prefix, not include the version
    string id =  o.getStringField("Id");
    string version =  o.getStringField("RegistryVersion");
    string type = o.getStringField("@odata.type");

    stringstream fname;
	FILE *fp = NULL;

	fname.str("");
    name += "Message"; //put a suffix "Message"
	fname << dest_dir << "/_p" << name << ".h"; // auto gen file _pXXXMessage.h

	fp = fopen(fname.str().c_str(), "w+");
	if(fp == NULL)
    {
		cout << "failed to generate message registery " << fname.str().c_str() << endl;
	}

    //file header
    fprintf(fp, sHdr, name.c_str());
    
    //class header
    fprintf(fp, sNS_Class_Hdr, name.c_str());

    //construct, init prop map
    string rel_file_name = file_name.substr(file_name.find_last_of("/") + 1);
	fprintf(fp, sNS_Class_Func1, name.c_str(), name.c_str(), id.c_str(), version.c_str(), rel_file_name.c_str());
	fprintf(fp, sNS_Class_Func1_end, name.c_str());

    bson::BSONObj messages_obj = o.getObjectField("Messages");
    vector<bson::BSONElement> elements;
    messages_obj.elems(elements);

    stringstream params, bson_ss; 
    
    std::stringstream padding;
    padding.fill(' ');
    padding.width(16);
    padding << "";
    for(unsigned char i = 0; i < elements.size(); i++)
    {
        params.str("");
        bson_ss.str("");
        
        string name(elements[i].fieldName());
        bson::BSONObj elem_obj = elements[i].Obj();
    
        string desc = elem_obj.getStringField("Description");
        string message = elem_obj.getStringField("Message");
        string severity = elem_obj.getStringField("Severity");
        int number_of_args = elem_obj.getIntField("NumberOfArgs");
        string resolution = elem_obj.getStringField("Resolution");
    
        bson_ss << "BSON(\"MessageId\" << \"" << (id + "." + name)<< "\"";
        bson_ss << "\n" << padding.str() << "<< \"@odata.type\" << \"" << type << "\"";
        bson_ss << "\n" << padding.str() << "<< \"Severity\" << \"" << severity << "\"";
        bson_ss << "\n" << padding.str() << "<< \"Resolution\" << \"" << resolution<< "\"";
    
        if (number_of_args)
        {
            bson::BSONElement param_type = elem_obj.getField("ParamTypes");
            vector<bson::BSONElement> types = param_type.Array();
            std::size_t pos = 0; // find the "%1" "%2" string and replace them with the argument
            stringstream message_ss; //message string that includes the arguments
            
            bson_ss << "\n" << padding.str() << "<< \"MessageArgs\" << BSON_ARRAY(";
            for (unsigned int j = 0; j < types.size(); j++)
            {
                if (j)
                {
                    params << ", ";
                    bson_ss << " << ";
                    message_ss << " + ";
                }

                pos = message.find_first_of("%");
                 
                if (types[j].String().compare("string") == 0)
                {
                    params << "string arg" << (j+1);
                    bson_ss << "arg" << (j+1);
                    message_ss << "\"" << message.substr(0, pos) << "\"" << " + arg" << (j+1) << " ";
                }
                else if (types[j].String().compare("number") == 0)
                {
                    params << "int arg" << (j+1);
                    bson_ss << "to_string(" << "arg" << (j+1) << ")";
                    message_ss << "\"" << message.substr(0, pos) << "\"" << " + to_string(arg" << (j+1) << ") ";
                }
                message = message.substr(pos+2);
            }
            bson_ss << ")"; // right parenthesis of BSON_ARRAY
            message_ss << "+ \"" << message << "\"";
            
             //std::cout << "NewMessage " << new_message.str() << std::endl;
                
             bson_ss << "\n" << padding.str() << "<< \"Message\" << (" << message_ss.str() << ")";
        }
        else
        {
            bson_ss << "\n" << padding.str() << "<< \"Message\" << \"" << message << "\"";
        }
        
        bson_ss << ")"; // right parenthesis of BSON

        // add the Make_Message_Obj_%s(%s) function
        fprintf(fp, sNS_Class_msg_function_start, name.c_str(), params.str().c_str(), bson_ss.str().c_str());
        fprintf(fp, sNS_Class_msg_function_end);
    }
    
    fprintf(fp, sNS_Class_Tail);
    fclose(fp);

#pragma GCC diagnostic warning "-Wformat-security"
   
}

void gen_message_registry(string dest_dir, string src_dir)
{
     regex_t      reRes1, reRes2, reRes3;
     regmatch_t   subs[4];
     string regexRes1 = "(Base\\.)([0-9]{1,2}\\.[0-9]{1,2}\\.[0-9]{1,2}\\.)(json)";
     string regexRes2 = "(AuditEvent\\.)([0-9]{1,2}\\.[0-9]{1,2}\\.[0-9]{1,2}\\.)(json)";
     string regexRes3 = "(ExtendedError\\.)([0-9]{1,2}\\.[0-9]{1,2}\\.[0-9]{1,2}\\.)(json)";

     if( (regcomp(&reRes1, regexRes1.c_str(), REG_EXTENDED))
        || (regcomp(&reRes2, regexRes2.c_str(), REG_EXTENDED))
        || (regcomp(&reRes3, regexRes3.c_str(), REG_EXTENDED)))
     {
        std::cout << "regex compile error: " << std::endl;
        return ;
     }
    
    ::odata::utility::string_t reg_dir(src_dir);
    DIR *dp;
    struct dirent *dirp;
    if ((dp  = opendir(reg_dir.c_str())) == NULL) 
    {
        std::cout << "opendir " << src_dir  <<" error" << std::endl;
        return;
    }

    vector<::odata::utility::string_t> fileNameList;
    while ((dirp = readdir(dp)) != NULL) 
    {
        ::odata::utility::string_t filename = string(dirp->d_name);

        size_t found = filename.find_last_of(".");
        if (found != string::npos)
        {
            //std::cout << "file " << filename << std::endl;
                
            if (!regexec(&reRes1, filename.c_str(), sizeof(subs)/sizeof(regmatch_t), subs, 0)
                || !regexec(&reRes2, filename.c_str(), sizeof(subs)/sizeof(regmatch_t), subs, 0)
                || !regexec(&reRes3, filename.c_str(), sizeof(subs)/sizeof(regmatch_t), subs, 0))
            {
                ::odata::utility::string_t absFilename = src_dir + "/" + filename;
                //std::cout << "file " << absFilename << std::endl;
                _gen_message_header_file(absFilename, dest_dir);
            }
        }
    }
    std::cout << "message registry header files generated" << std::endl;
    closedir(dp);
}


