#ifndef __EVENTING_H__
#define __EVENTING_H__


#ifdef __cplusplus
extern "C" {
#endif

#define EVENT_SUBS_MAX         12

#define EVENT_TYPE_STATUS_STR     "StatusChange"
#define EVENT_TYPE_UPDATE_STR     "ResourceUpdated"
#define EVENT_TYPE_ADD_STR        "ResourceAdded"
#define EVENT_TYPE_REMOVE_STR     "ResourceRemoved"
#define EVENT_TYPE_ALERT_STR      "Alert"       

enum SnapperEventType
{
    EVENT_TYPE_ALERT         = 0x1,
    EVENT_TYPE_REMOVE        = 0x2,
    EVENT_TYPE_ADD           = 0x4,
    EVENT_TYPE_UPDATE        = 0x8,
    EVENT_TYPE_STATUS        = 0x10
};

#define EVENT_PROTOCOL_REDFISH    "Redfish"
#define EVENT_SUBSCRIPT_REDFISH   "RedfishEvent"
#define EVENT_SUBSCRIPT_SSE       "SSE"
#define SSE_INTERNEL_PROXY_URI    "http://localhost/redfish/v1/sseproxy"

#define SSE_EVENT_FIELD_FORMAT    "EventFormatType"
#define SSE_FORMAT_EVENT     "Event"
#define SSE_FORMAT_METRIC    "MetricReport"
#define SSE_FORMAT_COMMENT   "Comment"
#define SSE_EVENT_FIELD_DATA      "SSEData"

typedef struct _eventsubscription
{
    int tbd; //req
}eventsubscription;


/////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
};
#endif


#endif
