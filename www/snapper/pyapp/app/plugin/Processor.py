# -*- coding: utf-8 -*-

#---------------------------------------------------------------------------
#  Copyright (c) 2018-present, Lenovo. All rights reserved.
#  Licensed under BSD, see COPYING.BSD file for details.
#---------------------------------------------------------------------------

import os
import logging
import json
from flask import request, make_response, Flask
from flask_restful import reqparse, abort, Api, Resource
from flask_sse import sse

from extmod_c import _connector
from config import config


cfg = config[os.getenv('FLASK_CONFIG') or 'default']
logger = logging.getLogger(cfg.LOGGER_NAME)
internalerr = {"error": {"code": "Base.1.2.0.InternalError",  "message": "The request failed due to an internal service error.  The service is still operational." } }

def EnumReqHeaders():
    errorcode = 0
    cred = request.headers.get('Authorization', '')
    xtoken = request.headers.get('X-Auth-Token', '')
    remoteip = request.headers.get('X-Real-IP', 'unknown')
    reqhdrs = {'Authorization': cred, 'X-Real-IP': remoteip, 'X-Auth-Token': xtoken }

    accept = request.headers.get('Accept', '')
    if len(accept) > 0 :
        reqhdrs['Accept'] = accept

    accept_enc = request.headers.get('Accept-Encoding', '')
    if len(accept_enc) > 0 :
        reqhdrs['Accept-Encoding'] = accept_enc

    accept_lan = request.headers.get('Accept-Language', '')
    if len(accept_lan) > 0 :
        reqhdrs['Accept-Language'] = accept_lan

    content_type = request.headers.get('Content-Type', '')
    if len(content_type) > 0 :
        reqhdrs['Content-Type'] = content_type

    #content_len = request.headers.get('Content-Length', '')
    #if len(content_len) > 0 :
    #    reqhdrs['Content-Length'] = content_len

    odata_ver = request.headers.get('OData-Version', '')
    if len(odata_ver) > 0 :
        reqhdrs['OData-Version'] = odata_ver

    usr_agent = request.headers.get('User-Agent', '')
    if len(usr_agent) > 0 :
        reqhdrs['User-Agent'] = usr_agent

    host = request.headers.get('Host', '')
    if len(host) > 0 :
        reqhdrs['Host'] = host

    orig = request.headers.get('Origin', '')
    if len(orig) > 0 :
        reqhdrs['Origin'] = orig

    match = request.headers.get('If-Match', '')
    if len(match) > 0 :
        reqhdrs['If-Match'] = match

    nomatch = request.headers.get('If-None-Match', '')
    if len(nomatch) > 0 :
        reqhdrs['If-None-Match'] = nomatch

    reqhdrs['EC'] = errorcode
    return reqhdrs

class RedfishResource(Resource):
    def get(self, path):
        try:
            body = ''
            if request.get_json(silent=True) != False and request.get_json(silent=True) != None:
                body = json.dumps(request.get_json(silent=True))

            headers = EnumReqHeaders()
            if headers.get('EC') != 0 :
                return '', headers.get('EC')

            m = 0
            if request.method == 'HEAD' :
                m = 1
            result = _connector.connector_processor(request.url, m, json.dumps(headers), body)
            resp = result.get('response', '')
            request.resphdr = result.get('headers', '')
            status = result.get('http_status', 200)
        except Exception as e:
            logger.warn("RedfishResource: %s", str(e))
            return internalerr, 500

        if len(resp) == 0:
            return resp, status            
        else:
            return json.loads(resp), status


    def post(self, path):
        try:
            body = ''
            if request.get_json(silent=True) != False and request.get_json(silent=True) != None:
                body = json.dumps(request.get_json(silent=True))

            headers = EnumReqHeaders()
            if headers.get('EC') != 0 :
                return '', headers.get('EC')

            result = _connector.connector_processor(request.url, 2, json.dumps(headers), body)
            resp = result.get('response', '')
            request.resphdr = result.get('headers', '')
            status = result.get('http_status', 200)
        except Exception as e:
            logger.warn("RedfishResource: %s", str(e))
            return internalerr, 500

        if len(resp) == 0:
            return resp, status            
        else:
            return json.loads(resp), status


    def patch(self, path):
        try:
            body = ''
            if request.get_json(silent=True) != False and request.get_json(silent=True) != None:
                body = json.dumps(request.get_json(silent=True))

            headers = EnumReqHeaders()
            if headers.get('EC') != 0 :
                return '', headers.get('EC')

            result = _connector.connector_processor(request.url, 4, json.dumps(headers), body)
            resp = result.get('response', '')
            request.resphdr = result.get('headers', '')
            status = result.get('http_status', 200)
        except Exception as e:
            logger.warn("RedfishResource: %s", str(e))
            return internalerr, 500

        if len(resp) == 0:
            return resp, status            
        else:
            return json.loads(resp), status


    def delete(self, path):
        try:
            body = ''
            if request.get_json(silent=True) != False and request.get_json(silent=True) != None:
                body = json.dumps(request.get_json(silent=True))

            headers = EnumReqHeaders()
            if headers.get('EC') != 0 :
                return '', headers.get('EC')

            result = _connector.connector_processor(request.url, 5, json.dumps(headers), body)
            resp = result.get('response', '')
            request.resphdr = result.get('headers', '')
            status = result.get('http_status', 200)
        except Exception as e:
            logger.warn("RedfishResource: %s", str(e))
            return internalerr, 500

        if len(resp) == 0:
            return resp, status            
        else:
            return json.loads(resp), status


    def put(self, path):
        return 'put unsupported ...', 405

class Version(Resource):
    def get(self):
        try:
            return {"v1" : "/redfish/v1/"}
        except Exception as e:
            logger.warn("Version: %s", str(e))
            return internalerr, 500

class ServiceRoot(Resource):
    def get(self):
        try:
            body = ''
            if request.get_json(silent=True) != False and request.get_json(silent=True) != None:
                body = json.dumps(request.get_json(silent=True))

            headers = EnumReqHeaders()
            if headers.get('EC') != 0 :
                return '', headers.get('EC')

            logger.warn("ServiceRoot: %s", request.url)

            m = 0
            if request.method == 'HEAD' :
                m = 1
            result = _connector.connector_processor_nonauth(request.url, m, json.dumps(headers), body)
            resp = result.get('response', '')
            request.resphdr = result.get('headers', '')
            status = result.get('http_status', 200)

            if len(resp) == 0:
                return resp, status            
            return json.loads(resp), status
        except Exception as e:
            logger.warn("ServiceRoot: %s", str(e))
            return internalerr, 500

class MetaDataDoc(Resource):
    def get(self):
        try:
            body = ''
            if request.get_json(silent=True) != False and request.get_json(silent=True) != None:
                body = json.dumps(request.get_json(silent=True))

            headers = EnumReqHeaders()
            if headers.get('EC') != 0 :
                return '', headers.get('EC')

            m = 0
            if request.method == 'HEAD' :
                m = 1
            result = _connector.connector_processor_schema(request.url, m, json.dumps(headers), body)
            status = result.get('http_status', 200)
            respstr = result.get('response', '')
            
            if status == 200 :                
                resp = make_response(respstr)
                request.resphdr = result.get('headers', '')
                return resp
                
            if len(respstr) == 0:
                return respstr, status            
            else:
                return json.loads(respstr), status
                
        except Exception as e:
            logger.warn("SchemaResource: %s", str(e))
            return internalerr, 500
            
class SchemaResource(Resource):
    def get(self, path):
        try:
            body = ''
            if request.get_json(silent=True) != False and request.get_json(silent=True) != None:
                body = json.dumps(request.get_json(silent=True))

            headers = EnumReqHeaders()
            if headers.get('EC') != 0 :
                return '', headers.get('EC')

            m = 0
            if request.method == 'HEAD' :
                m = 1
            result = _connector.connector_processor_schema(request.url, m, json.dumps(headers), body)
            status = result.get('http_status', 200)
            respstr = result.get('response', '')
            
            if status == 200 :                
                resp = make_response(respstr)
                request.resphdr = result.get('headers', '')
                return resp
                
            if len(respstr) == 0:
                return respstr, status            
            else:
                return json.loads(respstr), status
                
        except Exception as e:
            logger.warn("SchemaResource: %s", str(e))
            return internalerr, 500

class SSEProxy(Resource):
    def get(self):
        abort(405)

    def post(self):
        try:
            # todo: 1 reuse channel as event type (telemtry,alert)
            # post data from snapper_monitor: {"EventFormatType": "Event", "SSEData": evttobj}
            # post data from snapper_monitor: {"EventFormatType": "Comment", "SSEData": ""}
            jbody = request.get_json(silent=True)
            if jbody == False or jbody == None:
                return {"sse" : "failed"}
            eventtype = jbody.get('EventFormatType', 'Comment')
            ssedata = jbody.get('SSEData', '')

            #different event format should use separate channel. flask_sse always subscribes 'Comment' channel
            if eventtype == 'Comment' :
                sse.publish(str(ssedata), type=eventtype, channel=eventtype)
            elif eventtype == 'Event' and isinstance(ssedata,dict):
                body = json.dumps(ssedata, indent=1)
                sse.publish(body, id=ssedata.get('Id', 'unknown'), type=eventtype, channel=eventtype)

            return {"sse" : "success"}
        except Exception as e:
            logger.warn("SSEProxy: %s", str(e))
            return internalerr, 500
