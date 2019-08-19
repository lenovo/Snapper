//---------------------------------------------------------------------
// <copyright file="_pStandardErrorMessage.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "SnapperMessage.h"

namespace snapper { namespace providers 
{

class _pStandardErrorMessage : public SnapperRegistry
{
public:
    _pStandardErrorMessage() : SnapperRegistry("StandardErrorMessage", "StandardError.v1_1_0", "1.1.0", "ExtendedError.1.1.0.json")    
    {
    }

    virtual ~_pStandardErrorMessage()    
    {}

    // MMO = Make Message Object
    static std::shared_ptr<bson::BSONObj> MMO_BadRequest()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.BadRequest"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Make sure your request respects the HTTP protocol completely."
                << "Message" << "The Web Server can not understand the request due to malformed syntax."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_Unauthorized()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.Unauthorized"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "You are required to log on Web Server with valid credentials first."
                << "Message" << "The request requires user authentication which has not yet been provided or invalid."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_MissingUsername()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.MissingUsername"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Please request again with a valid user name."
                << "Message" << "The user name is missing."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_MissingPassword()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.MissingPassword"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Please request again with a valid password."
                << "Message" << "The password is missing."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_InvalidCredentials()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.InvalidCredentials"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Please request again with correct credentials."
                << "Message" << "The login credentials is invalid."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_InvalidLoginBody(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.InvalidLoginBody"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Please request again with correct request body."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("The field " + arg1 + " of the request body is invalid.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_AccountLockout()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.AccountLockout"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Please contact the IT personnel for technical support."
                << "Message" << "The login account is blocked."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_InvalidBasicAuthorizationString()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.InvalidBasicAuthorizationString"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Please refer to RFC2617 to see the correct Basic authorization format."
                << "Message" << "The Basic authorization string is not a valid Base64 string."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_InvalidDigestAuthorizationString()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.InvalidDigestAuthorizationString"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Please refer to RFC2617 to see the correct Digest authorization format."
                << "Message" << "The format of the Digest authorization string is not correct."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_DigestURINotMatch()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.DigestURINotMatch"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "The URI field in the Digest token should match the actual requested URI."
                << "Message" << "The request URI does not match the URI filled in the Digest authorization string."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_MissingDigestNonceValue()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.MissingDigestNonceValue"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Please refer to RFC2617 to see the correct Digest authorization format."
                << "Message" << "The nonce value is missing and is required for the Digest Authorization."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_MissingDigestRealmValue()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.MissingDigestRealmValue"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Please refer to RFC2617 to see the correct Digest authorization format."
                << "Message" << "The realm value is missing and is required for the Digest Authorization."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_MissingDigestUriValue()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.MissingDigestUriValue"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Please refer to RFC2617 to see the correct Digest authorization format."
                << "Message" << "The URI value is missing and is required for the Digest Authorization."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_SessionNotExist()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.SessionNotExist"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Please try to login again to create a new session and get a new X-Auth-Token."
                << "Message" << "The login session does not exist or is expired."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_SessionFull()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.SessionFull"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Please try to login later."
                << "Message" << "The logged-in sessions reach the limit."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_EtagPreconditionalFailed()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.EtagPreconditionalFailed"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Please correct precondition fields in request header."
                << "Message" << "Server detects the precondition specification is not met."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_EtagPreconditionRequired()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.EtagPreconditionRequired"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Please add precondition fields in request header."
                << "Message" << "The origin server requires the request to be conditional."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_AcceptHeaderNotSatisfied()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.AcceptHeaderNotSatisfied"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Modify the Accept header to a value that is acceptable by the server."
                << "Message" << "Server cannot accept the media type specified in the Accept header."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_OdataVerHeaderNotSatisfied()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.OdataVerHeaderNotSatisfied"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Modify OData related header(s) that can be accepted by server."
                << "Message" << "The OData header(s) in request is not satisfied."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ContentTypeHeaderNotSatisfied()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.ContentTypeHeaderNotSatisfied"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Modify related header(s) that can be accepted by server."
                << "Message" << "Server cannot accept the media type specified in the Content-Type header."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_MethodNotAllowed(string arg1, string arg2)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.MethodNotAllowed"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Please specify a method that the resource supports."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2)
                << "Message" << ("The resource " + arg1  + " doesn't support " + arg2 + " method.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_BadActionRequestMethod(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.BadActionRequestMethod"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Trigger an action by a POST method."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("" + arg1 + " is an action and can only be triggered by a POST request.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_NotImplementedHttpMethod()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.NotImplementedHttpMethod"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Make sure your request respects the HTTP protocol completely."
                << "Message" << "The Web Server does not support the request method."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_QueryParameterUnknown(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.QueryParameterUnknown"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Remove the unknown query parameter and resubmit the request if the operation failed."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("The query parameter " + arg1 + " is not a valid query parameter for the resource.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_RequestUriNotFound()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.RequestUriNotFound"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Correct the URI and resubmit the request."
                << "Message" << "The request specified a URI of a resource that does not exist."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_Conflict()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.Conflict"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Eliminate the conflict and resubmit the request."
                << "Message" << "The request could not be completed due to a conflict with the current state of the resource."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_Gone()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.Gone"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Stop accessing the resource."
                << "Message" << "The requested resource is no longer available at the server."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_LengthRequired()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.LengthRequired"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Add a valid Content-Length header and resubmit the request."
                << "Message" << "The requested resource requires the Content-Length header."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_UnprocessableEntity()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.UnprocessableEntity"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Correct the value in the request body and resubmit the request if the operation failed."
                << "Message" << "The request was well-formed but was unable to be followed due to semantic errors."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_TooManyRequests()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.TooManyRequests"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Try again later."
                << "Message" << "The user has sent too many requests in a given amount of time."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_NotImplemented()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.NotImplemented"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "The request supplied cannot be resubmitted to the implementation.  The implementation documentation may be of assistance."
                << "Message" << "The server does not (currently) support the functionality required to fulfill the request."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ServiceUnavailable()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.ServiceUnavailable"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Resubmit the request later."
                << "Message" << "The server is currently unable to handle the request due to temporary overloading or maintenance of the server."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ServiceDisabled()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.ServiceDisabled"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Resubmit the request after the service is working and enabled."
                << "Message" << "The service is disabled or not working and cannot handle the request."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_RebootRequired()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.RebootRequired"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Reboot the computer system for the changes to take effect."
                << "Message" << "Changes completed successfully, but these changes will not take effect until next reboot."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_PhysicalPresenceError()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.PhysicalPresenceError"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Attempt asserting Physical Presence or Remote Physical Presence, and retry the operation."
                << "Message" << "The operation failed because of Remote Physical Presence security requirements."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ServiceTemporarilyUnavailable(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.ServiceTemporarilyUnavailable"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Wait for the indicated retry duration and retry the operation."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("The service is temporarily unavailable.  Retry in " + arg1 + " seconds.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_Processing()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.Processing"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "OK"
                << "Resolution" << "None"
                << "Message" << "Please check the request state later."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_NoContent()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.NoContent"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "OK"
                << "Resolution" << "None"
                << "Message" << "The Web Server does not return a response body."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_CancelAsyncTaskFailed()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.CancelAsyncTaskFailed"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "None"
                << "Message" << "The backend of the async task refused the cancellation."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_CancelAsyncTaskTimeout()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.CancelAsyncTaskTimeout"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Makes sure the resource backend either support the canceling of asynchronous tasks or is running correctly."
                << "Message" << "The request had been timed out."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_TaskCompleted()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.TaskCompleted"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "None"
                << "Message" << "The task is already completed and is not able to be canceled."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_TaskCreationLimitExceeded()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.TaskCreationLimitExceeded"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Cancel other task before trying to create the task or enlarge the max count of tasks."
                << "Message" << "The task creation failed due to the number of created tasks exceeding the limit of the implementation."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_SimpleUpdateTargetsConflict (int arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.SimpleUpdateTargetsConflict "
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Update one kind of firmware by one image. "
                << "MessageArgs" << BSON_ARRAY(to_string(arg1))
                << "Message" << ("These targets have different " + to_string(arg1) + " firmware type. They can not been togethere updated by the same image.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_PSUUpdatePreConditionFailed(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.PSUUpdatePreConditionFailed"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "The power supply must work without any error while system is powered-off;Or it must set to redundant mode and install more than one PSUs while system is running."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("The power supply firmware updating failed due pre-condication checking error.Details: " + arg1 + "")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_FirmwareUpdating(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.FirmwareUpdating"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Please contimuelly query the task to check the update progress."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("Firmware updating is in progress.Details: [" + arg1 + "]")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_FirmwareUpdateError(string arg1, string arg2)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "StandardError.v1_1_0.FirmwareUpdateError"
                << "@odata.type" << "#MessageRegistry.v1_1_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "According the message, check whether the request data is correct. And have a new retry."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2)
                << "Message" << ("Firmware updating for tagets:[ " + arg1  + " ] failed. Details: [" + arg2 + "]")));
    }

};

}}

