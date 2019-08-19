//---------------------------------------------------------------------
// <copyright file="SnapperMessage.h" company="Lenovo">
//      Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details. 
// </copyright>
//---------------------------------------------------------------------

#pragma once

#include "bson/bson.h"
#include "bson/util/json.h"
#include "SnapperType.h"
#include "SnapperRegistry.h"
using namespace ::std;

namespace snapper { namespace providers
{
/*
class MessageRegistery
{
public:
    MessageRegistery(string name, string id, string version): m_name(name), m_id(id), m_version(version) 
    {
        SnapperRegistry::register_to_snapper(id);
    }
    
    virtual ~MessageRegistery() {};  
    
        
    
    const string& get_name() const 
    {
        return m_name;
    }  

    const string& get_id() const 
    {
        return m_id;
    }

    const string& get_version() const 
    {
        return m_version;
    }
    

protected:
    
    std::map<const std::string, std::shared_ptr<bson::BSONObj>> m_message_objs;

private:

    string m_name;
    string m_id;
    string m_version;

};
*/
/***************************************************************************************
       This class provides the functions to build the Message Objects related BSON objects 
       for the redfish request response.
       Building Message Object itself is addressed in BaseMessage.h, 
       AuditEventMessage.h and StandardErrorMessage.h

       Message Objects provide additional information about an object, property, or error response, 
       which can contain the following properties: MessageId (M), Message(M), 
       RelatedProperties(O), MessageArgs(O), Severity(O), Resolution(O)

        Example of Error Response Object:
        {
             "error": {
                  "code": "Base.1.0.GeneralError",
                  "message": "xxx"
                  "@Message.ExtendedInfo":[<message objects>, ...]       
              }
         }

         Example of Extended object:
         {
             ......
             "@Message.ExtendedInfo" : [<message objects>, ... ]
         }

         Example of Extended property information:
         {
             ......
             "PinOut": "Cyclades",
             "PinOut@Message.ExtendedInfo" : [
                                              {
                                              "MessageId": "Base.1.0.PropertyValueNotInList",
                                              "Message": "The value Contoso for the property PinOut is not in the list
                                              of acceptable values.",
                                              "Severity": "Warning",
                                              "Resolution": "Choose a value from the enumeration list that the
                                              implementation can support and resubmit the request if the operation failed."
                                              }
             ]
         }        
         
****************************************************************************************/
class SnapperMessage
{
public:
    SnapperMessage(std::shared_ptr<bson::BSONObj> err_obj = nullptr): err_msg_obj(err_obj) 
    {}
    
    virtual ~SnapperMessage() {};

    // Error Object example:
    // {
    //      "error": {
    //           "code": "Base.1.0.GeneralError",
    //           "message": "xxx"
    //           "@Message.ExtendedInfo":[]
    //
    //       }
    //  }  

    // the message obj passed in can be built by calling static function 
    // Make_Message_Obj_xxx 
    bool validate_message_obj(std::shared_ptr<bson::BSONObj> obj);

    // For building the Error Response Object
    // the messageId and message of the passed in obj will be used to fill "code" and "message"
    void add_error_message_obj(std::shared_ptr<bson::BSONObj> obj);

    // the obj will be appended to the array for "xx@Message.ExtendedInfo"
    void add_extended_message_obj(std::shared_ptr<bson::BSONObj> obj, vector<string>* related_props = nullptr);

    // return null if none of err_msg_obj and extended_msg_objs are specified
    // otherwise, return the Error Response Object
    std::shared_ptr<bson::BSONObj> get_err_obj();

    // return the serialized string for the Error Response Object, could be empty 
    // if the err_msg_obj is not specified when construct, or not added by calling 
    // add_error_message_obj()
    string serialize_err_obj();

    // return null if no message obj is added by calling add_extended_message_obj()
    // otherwise, return the "xx@Message.ExtendedInfo"object
    // the "prefix" is only needed for Extended property information
    std::shared_ptr<bson::BSONObj> get_extended_info_obj(string prefix = "");

    // get the bson array for exteded info
    void get_extended_info_arr(bson::BSONArrayBuilder* a);
    
    void reset_obj();
    

protected:    

private:
    std::shared_ptr<bson::BSONObj> err_msg_obj;
    vector<std::shared_ptr<bson::BSONObj>> extended_msg_objs;
    std::shared_ptr<bson::BSONObj> err_obj; // representing the final Error Response Object

};
}}
 
