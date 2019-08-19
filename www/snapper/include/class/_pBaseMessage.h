//---------------------------------------------------------------------
// <copyright file="_pBaseMessage.h" company="Lenovo">
//        Copyright (c) 2018-present, Lenovo. All rights reserved. Licensed under BSD, see COPYING.BSD file for details.
// </copyright>
//---------------------------------------------------------------------

#pragma once 

#include "SnapperMessage.h"

namespace snapper { namespace providers 
{

class _pBaseMessage : public SnapperRegistry
{
public:
    _pBaseMessage() : SnapperRegistry("BaseMessage", "Base.1.2.0", "1.2.0", "Base.1.2.0.json")    
    {
    }

    virtual ~_pBaseMessage()    
    {}

    // MMO = Make Message Object
    static std::shared_ptr<bson::BSONObj> MMO_Success()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.Success"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "OK"
                << "Resolution" << "None"
                << "Message" << "Successfully Completed Request"));
    }

    static std::shared_ptr<bson::BSONObj> MMO_GeneralError()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.GeneralError"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "See ExtendedInfo for more information."
                << "Message" << "A general error has occurred. See ExtendedInfo for more information."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_Created()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.Created"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "OK"
                << "Resolution" << "None"
                << "Message" << "The resource has been created successfully"));
    }

    static std::shared_ptr<bson::BSONObj> MMO_PropertyDuplicate(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.PropertyDuplicate"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Remove the duplicate property from the request body and resubmit the request if the operation failed."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("The property " + arg1 + " was duplicated in the request.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_PropertyUnknown(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.PropertyUnknown"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Remove the unknown property from the request body and resubmit the request if the operation failed."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("The property " + arg1 + " is not in the list of valid properties for the resource.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_PropertyValueTypeError(string arg1, string arg2)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.PropertyValueTypeError"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Correct the value for the property in the request body and resubmit the request if the operation failed."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2)
                << "Message" << ("The value " + arg1  + " for the property " + arg2 + " is of a different type than the property can accept.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_PropertyValueFormatError(string arg1, string arg2)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.PropertyValueFormatError"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Correct the value for the property in the request body and resubmit the request if the operation failed."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2)
                << "Message" << ("The value " + arg1  + " for the property " + arg2 + " is of a different format than the property can accept.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_PropertyValueNotInList(string arg1, string arg2)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.PropertyValueNotInList"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Choose a value from the enumeration list that the implementation can support and resubmit the request if the operation failed."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2)
                << "Message" << ("The value " + arg1  + " for the property " + arg2 + " is not in the list of acceptable values.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_PropertyNotWritable(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.PropertyNotWritable"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Remove the property from the request body and resubmit the request if the operation failed."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("The property " + arg1 + " is a read only property and cannot be assigned a value.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_PropertyMissing(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.PropertyMissing"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Ensure that the property is in the request body and has a valid value and resubmit the request if the operation failed."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("The property " + arg1 + " is a required property and must be included in the request.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_MalformedJSON()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.MalformedJSON"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Ensure that the request body is valid JSON and resubmit the request."
                << "Message" << "The request body submitted was malformed JSON and could not be parsed by the receiving service."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_EmptyJSON()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.EmptyJSON"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Add properties in the JSON object and resubmit the request."
                << "Message" << "The request body submitted contained an empty JSON object and the service is unable to process it."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ActionNotSupported(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ActionNotSupported"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "The action supplied cannot be resubmitted to the implementation.  Perhaps the action was invalid, the wrong resource was the target or the implementation documentation may be of assistance."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("The action " + arg1 + " is not supported by the resource.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ActionParameterMissing(string arg1, string arg2)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ActionParameterMissing"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Supply the action with the required parameter in the request body when the request is resubmitted."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2)
                << "Message" << ("The action " + arg1  + " requires the parameter " + arg2 + " to be present in the request body.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ActionParameterDuplicate(string arg1, string arg2)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ActionParameterDuplicate"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Resubmit the action with only one instance of the parameter in the request body if the operation failed."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2)
                << "Message" << ("The action " + arg1  + " was submitted with more than one value for the parameter " + arg2 + ".")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ActionParameterUnknown(string arg1, string arg2)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ActionParameterUnknown"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Correct the invalid parameter and resubmit the request if the operation failed."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2)
                << "Message" << ("The action " + arg1  + " was submitted with the invalid parameter " + arg2 + ".")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ActionParameterValueTypeError(string arg1, string arg2, string arg3)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ActionParameterValueTypeError"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Correct the value for the parameter in the request body and resubmit the request if the operation failed."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2 << arg3)
                << "Message" << ("The value " + arg1  + " for the parameter " + arg2  + " in the action " + arg3 + " is of a different type than the parameter can accept.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ActionParameterValueFormatError(string arg1, string arg2, string arg3)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ActionParameterValueFormatError"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Correct the value for the parameter in the request body and resubmit the request if the operation failed."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2 << arg3)
                << "Message" << ("The value " + arg1  + " for the parameter " + arg2  + " in the action " + arg3 + " is of a different format than the parameter can accept.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ActionParameterNotSupported(string arg1, string arg2)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ActionParameterNotSupported"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Remove the parameter supplied and resubmit the request if the operation failed."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2)
                << "Message" << ("The parameter " + arg1  + " for the action " + arg2 + " is not supported on the target resource.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_QueryParameterValueTypeError(string arg1, string arg2)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.QueryParameterValueTypeError"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Correct the value for the query parameter in the request and resubmit the request if the operation failed."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2)
                << "Message" << ("The value " + arg1  + " for the query parameter " + arg2 + " is of a different type than the parameter can accept.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_QueryParameterValueFormatError(string arg1, string arg2)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.QueryParameterValueFormatError"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Correct the value for the query parameter in the request and resubmit the request if the operation failed."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2)
                << "Message" << ("The value " + arg1  + " for the parameter " + arg2 + " is of a different format than the parameter can accept.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_QueryParameterOutOfRange(string arg1, string arg2, string arg3)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.QueryParameterOutOfRange"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Reduce the value for the query parameter to a value that is within range, such as a start or count value that is within bounds of the number of resources in a collection or a page that is within the range of valid pages."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2 << arg3)
                << "Message" << ("The value " + arg1  + " for the query parameter " + arg2  + " is out of range " + arg3 + ".")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_QueryNotSupportedOnResource()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.QueryNotSupportedOnResource"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Remove the query parameters and resubmit the request if the operation failed."
                << "Message" << "Querying is not supported on the requested resource."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_QueryNotSupported()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.QueryNotSupported"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Remove the query parameters and resubmit the request if the operation failed."
                << "Message" << "Querying is not supported by the implementation."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_SessionLimitExceeded()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.SessionLimitExceeded"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Reduce the number of other sessions before trying to establish the session or increase the limit of simultaneous sessions (if supported)."
                << "Message" << "The session establishment failed due to the number of simultaneous sessions exceeding the limit of the implementation."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_EventSubscriptionLimitExceeded()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.EventSubscriptionLimitExceeded"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Reduce the number of other subscriptions before trying to establish the event subscription or increase the limit of simultaneous subscriptions (if supported)."
                << "Message" << "The event subscription failed due to the number of simultaneous subscriptions exceeding the limit of the implementation."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ResourceCannotBeDeleted()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ResourceCannotBeDeleted"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Do not attempt to delete a non-deletable resource."
                << "Message" << "The delete request failed because the resource requested cannot be deleted."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ResourceInUse()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ResourceInUse"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Remove the condition and resubmit the request if the operation failed."
                << "Message" << "The change to the requested resource failed because the resource is in use or in transition."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ResourceAlreadyExists(string arg1, string arg2, string arg3)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ResourceAlreadyExists"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Do not repeat the create operation as the resource has already been created."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2 << arg3)
                << "Message" << ("The requested resource of type " + arg1  + " with the property " + arg2  + " with the value " + arg3 + " already exists.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ResourceNotFound(string arg1, string arg2)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ResourceNotFound"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Provide a valid resource identifier and resubmit the request."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2)
                << "Message" << ("The requested resource of type " + arg1  + " named " + arg2 + " was not found.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_CreateFailedMissingReqProperties(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.CreateFailedMissingReqProperties"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Correct the body to include the required property with a valid value and resubmit the request if the operation failed."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("The create operation failed because the required property " + arg1 + " was missing from the request.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_CreateLimitReachedForResource()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.CreateLimitReachedForResource"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Either delete resources and resubmit the request if the operation failed or do not resubmit the request."
                << "Message" << "The create operation failed because the resource has reached the limit of possible resources."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ServiceShuttingDown()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ServiceShuttingDown"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "When the service becomes available, resubmit the request if the operation failed."
                << "Message" << "The operation failed because the service is shutting down and can no longer take incoming requests."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ServiceInUnknownState()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ServiceInUnknownState"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Restart the service and resubmit the request if the operation failed."
                << "Message" << "The operation failed because the service is in an unknown state and can no longer take incoming requests."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_NoValidSession()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.NoValidSession"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Establish as session before attempting any operations."
                << "Message" << "There is no valid session established with the implementation."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_InsufficientPrivilege()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.InsufficientPrivilege"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Either abandon the operation or change the associated access rights and resubmit the request if the operation failed."
                << "Message" << "There are insufficient privileges for the account or credentials associated with the current session to perform the requested operation."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_AccountModified()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.AccountModified"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "OK"
                << "Resolution" << "No resolution is required."
                << "Message" << "The account was successfully modified."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_AccountNotModified()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.AccountNotModified"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "The modification may have failed due to permission issues or issues with the request body."
                << "Message" << "The account modification request failed."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_AccountRemoved()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.AccountRemoved"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "OK"
                << "Resolution" << "No resolution is required."
                << "Message" << "The account was successfully removed."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_AccountForSessionNoLongerExists()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.AccountForSessionNoLongerExists"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "OK"
                << "Resolution" << "Attempt to connect with a valid account."
                << "Message" << "The account for the current session has been removed, thus the current session has been removed as well."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_InvalidObject(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.InvalidObject"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Either the object is malformed or the URI is not correct.  Correct the condition and resubmit the request if it failed."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("The object at " + arg1 + " is invalid.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_InternalError()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.InternalError"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Resubmit the request.  If the problem persists, consider resetting the service."
                << "Message" << "The request failed due to an internal service error.  The service is still operational."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_UnrecognizedRequestBody()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.UnrecognizedRequestBody"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Correct the request body and resubmit the request if it failed."
                << "Message" << "The service detected a malformed request body that it was unable to interpret."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ResourceMissingAtURI(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ResourceMissingAtURI"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Place a valid resource at the URI or correct the URI and resubmit the request."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("The resource at the URI " + arg1 + " was not found.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ResourceAtUriInUnknownFormat(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ResourceAtUriInUnknownFormat"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Place an image or resource or file that is recognized by the service at the URI."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("The resource at " + arg1 + " is in a format not recognized by the service.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ResourceAtUriUnauthorized(string arg1, string arg2)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ResourceAtUriUnauthorized"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Ensure that the appropriate access is provided for the service in order for it to access the URI."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2)
                << "Message" << ("While accessing the resource at " + arg1  + ", the service received an authorization error " + arg2 + ".")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_CouldNotEstablishConnection(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.CouldNotEstablishConnection"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Ensure that the URI contains a valid and reachable node name, protocol information and other URI components."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("The service failed to establish a connection with the URI " + arg1 + ".")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_SourceDoesNotSupportProtocol(string arg1, string arg2)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.SourceDoesNotSupportProtocol"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Change protocols or URIs. "
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2)
                << "Message" << ("The other end of the connection at " + arg1  + " does not support the specified protocol " + arg2 + ".")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_AccessDenied(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.AccessDenied"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Attempt to ensure that the URI is correct and that the service has the appropriate credentials."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("While attempting to establish a connection to " + arg1 + ", the service denied access.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ServiceTemporarilyUnavailable(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ServiceTemporarilyUnavailable"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Wait for the indicated retry duration and retry the operation."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("The service is temporarily unavailable.  Retry in " + arg1 + " seconds.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_InvalidIndex(int arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.InvalidIndex"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Verify the index value provided is within the bounds of the array."
                << "MessageArgs" << BSON_ARRAY(to_string(arg1))
                << "Message" << ("The Index " + to_string(arg1) + " is not a valid offset into the array.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_PropertyValueModified(string arg1, string arg2)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.PropertyValueModified"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "No resolution is required."
                << "MessageArgs" << BSON_ARRAY(arg1 << arg2)
                << "Message" << ("The property " + arg1  + " was assigned the value " + arg2 + " due to modification by the service.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ResourceInStandby()
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ResourceInStandby"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Ensure that the resource is in the correct power state and resubmit the request."
                << "Message" << "The request could not be performed because the resource is in standby."));
    }

    static std::shared_ptr<bson::BSONObj> MMO_ResourceExhaustion(string arg1)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.ResourceExhaustion"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Critical"
                << "Resolution" << "Ensure that the resources are available and resubmit the request."
                << "MessageArgs" << BSON_ARRAY(arg1)
                << "Message" << ("The resource " + arg1 + " was unable to satisfy the request due to unavailability of resources.")));
    }

    static std::shared_ptr<bson::BSONObj> MMO_StringValueTooLong(string arg1, int arg2)
    {
         return  std::make_shared<bson::BSONObj>(BSON("MessageId" << "Base.1.2.0.StringValueTooLong"
                << "@odata.type" << "#MessageRegistry.v1_0_0.MessageRegistry"
                << "Severity" << "Warning"
                << "Resolution" << "Resubmit the request with an appropriate string length."
                << "MessageArgs" << BSON_ARRAY(arg1 << to_string(arg2))
                << "Message" << ("The string " + arg1  + " exceeds the length limit " + to_string(arg2) + ".")));
    }

};

}}

