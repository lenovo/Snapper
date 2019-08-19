//---------------------------------------------------------------------
// <copyright file="_pAuditEventMessage.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "SnapperMessage.h"

namespace snapper { namespace providers 
{

class _pAuditEventMessage : public SnapperRegistry
{
public:
    _pAuditEventMessage() : SnapperRegistry("AuditEventMessage", "AuditEvent.v1_1_0", "1.1.0", "AuditEvent.1.1.0.json")    
    {
    }

    virtual ~_pAuditEventMessage()    
    {}

    // MMO = Make Message Object
    static std::shared_ptr<bson::BSONObj> MMO_ResourceRead()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "AuditEvent.v1_1_0.ResourceRead"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "OK"
                << "Resolution" << "None"
                << "Message" << "Reading a resource."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ResourceAdded()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "AuditEvent.v1_1_0.ResourceAdded"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "None"
                << "Message" << "A resource is added."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ResourceUpdated()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "AuditEvent.v1_1_0.ResourceUpdated"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "None"
                << "Message" << "A resource is updated."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ResourceRemoved()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "AuditEvent.v1_1_0.ResourceRemoved"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "None"
                << "Message" << "A resource is removed."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_Authentication()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "AuditEvent.v1_1_0.Authentication"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "None"
                << "Message" << "An authentication attempt is occurred."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_UserLogin()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "AuditEvent.v1_1_0.UserLogin"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "OK"
                << "Resolution" << "None"
                << "Message" << "A user is logging in the server."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_UserLogout()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "AuditEvent.v1_1_0.UserLogout"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "OK"
                << "Resolution" << "None"
                << "Message" << "A user is logging out the server."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ServerShutdown()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "AuditEvent.v1_1_0.ServerShutdown"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "None"
                << "Message" << "Web Service is shutting down."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ServerStartup()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "AuditEvent.v1_1_0.ServerStartup"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "None"
                << "Message" << "Web Service is starting up."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ActionPerform(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "AuditEvent.v1_1_0.ActionPerform"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "None"
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("The action " + arg1 + " is performed.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_StatusChange()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "AuditEvent.v1_1_0.StatusChange"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "None"
                << "Message" << "The status of this resource has changed."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_Alert()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "AuditEvent.v1_1_0.Alert"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "None"
                << "Message" << "A condition exists which requires attention."));
    }

};

}}

