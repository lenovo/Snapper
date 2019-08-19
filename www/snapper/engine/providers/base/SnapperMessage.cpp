/*---------------------------------------------------------------------------
//  Copyright (c) 2018-present, Lenovo. All rights reserved.
//  Licensed under BSD, see COPYING.BSD file for details.
//---------------------------------------------------------------------------
*/

#include <www/engine/rf_debug.h>
#include "class/SnapperMessage.h"
#include <algorithm>

namespace snapper { namespace providers
{

bool SnapperMessage::validate_message_obj(std::shared_ptr<bson::BSONObj> obj)
{
    // currently only check for "MessageID", "Message", "Severity"
    // the obj includes these theree fields is considered as a valid message obj
    if (obj->hasField("MessageId") && obj->hasField("Message") && obj->hasField("Severity"))
        return true;
    else
        return false;
}

void SnapperMessage::add_error_message_obj(std::shared_ptr<bson::BSONObj> obj)
{
    // don't overwrite the existing error obj
    if (err_msg_obj == nullptr && validate_message_obj(obj))
    {
        err_msg_obj = obj;
    }
    else
    {
        RF_PRINT_ERR("add_error_message_obj::invalid message obj or err_msg_obj is already specified");
    }
    return;
}

void SnapperMessage::add_extended_message_obj(std::shared_ptr<bson::BSONObj> obj, vector<string>* related_props)
{    
    if (validate_message_obj(obj))
    {
        if(related_props && related_props->size())
        {
            bson::BSONArrayBuilder a;
            string prop("#/");
            for(auto it = related_props->begin(); it != related_props->end(); it++)
            {
                a.append(prop + *it);
            }

            bson::BSONObjBuilder o;
            o.appendElements(*obj);
            o.append(RESOURCE_RELATED_ITEM, a.arr());
            bson::BSONObj ext_obj = o.obj();
            extended_msg_objs.push_back(std::make_shared<bson::BSONObj>(ext_obj));
        }
        else
        {
            extended_msg_objs.push_back(obj);
        }
    }
    else
    {
        RF_PRINT_ERR("add_extended_message_obj::invalid message obj");
    }
}

std::shared_ptr<bson::BSONObj> SnapperMessage::get_err_obj()
{
    // at least one message object needs to be present
    if (!err_msg_obj && !extended_msg_objs.size())
    {
        RF_PRINT_ERR("build_error_obj::no valid message obj"); 
        return nullptr;
    }

    // if the err_msg_obj is not specified explicitly, use the first extended msg obj by default
    if (!err_msg_obj && extended_msg_objs.size())
    {
        add_error_message_obj(extended_msg_objs[0]);
    }

    bson::BSONArrayBuilder a;
    if (extended_msg_objs.size())
    {
        // build array for "@Message.ExtendedInfo"
        for (unsigned char i = 0; i < extended_msg_objs.size(); i++)
        {
            a.append(*(extended_msg_objs[i]));
        }
    }
    else
    {
        // if no extended msg objs added, use the error message obj in the extended by default
        a.append(*err_msg_obj);        
    }

    string code = err_msg_obj->getStringField("MessageId");
    string message = err_msg_obj->getStringField("Message");
    
    err_obj = MAKE_BSON_OBJ("error", BSON("code" << code
                                    << "message" << message
                                    << MESSAGE_EXTENDED << a.arr()));

    return err_obj;
}

std::shared_ptr<bson::BSONObj> SnapperMessage::get_extended_info_obj(string prefix)
{
    if (!extended_msg_objs.size())
    {
        //RF_PRINT_ERR("get_extended_obj::no valid message objects"); 
        return nullptr;
    }

    bson::BSONArrayBuilder a;
    // build array for "xx@Message.ExtendedInfo"
    for (unsigned char i = 0; i < extended_msg_objs.size(); i++)
    {
        a.append(*(extended_msg_objs[i]));
    }

    //string code = err_msg_obj->getStringField("MessageId");
    //string message = err_msg_obj->getStringField("Message");
    return MAKE_BSON_OBJ((prefix + MESSAGE_EXTENDED), a.arr());
}

void SnapperMessage::get_extended_info_arr(bson::BSONArrayBuilder* a)
{
    if (!extended_msg_objs.size())
    {
        RF_PRINT_ERR("get_extended_obj::no valid message objects"); 
        return;
    }

    for (unsigned char i = 0; i < extended_msg_objs.size(); i++)
    {
        a->append(*(extended_msg_objs[i]));
    }
}

string SnapperMessage::serialize_err_obj()
{
    get_err_obj();
    if (err_obj)
    {
        return err_obj->jsonString();
    }
    else
        return "";
}

void SnapperMessage::reset_obj()
{
    err_msg_obj = nullptr;
    extended_msg_objs.clear();
    err_obj = nullptr;
}


}}
