# -*- coding: utf-8 -*-

#---------------------------------------------------------------------------
#  Copyright (c) 2018-present, Lenovo. All rights reserved.
#  Licensed under BSD, see COPYING.BSD file for details.
#---------------------------------------------------------------------------

import os
import logging
import json
from logging import StreamHandler, DEBUG, Formatter
#from logging.handlers import SysLogHandler
from logging.handlers import RotatingFileHandler
from cloghandler import ConcurrentRotatingFileHandler
from datetime import datetime, timedelta
import thread
import time

from flask import Flask, request, current_app, abort, redirect
from flask_restful import Resource, Api
#from flask_jwt import JWT, jwt_required, current_identity
from werkzeug.security import safe_str_cmp
from flask_sse import sse

from extmod_c import _connector
from config import config

cfg = config[os.getenv('FLASK_CONFIG') or 'default']
logger = logging.getLogger(cfg.LOGGER_NAME)
#httplogger = logging.getLogger(cfg.LOGGER_HTTP_NAME)

def SessionTimerThread (name, timer):
    """ timer thread to recycle session resource: pam handle, session info
    """
    try:
        logger.debug("pid %d thread %s started" % (os.getpid(), name) )
        while True:
            #logger.debug("thread %d %s: %s" % (os.getpid(), name, time.ctime(time.time())) )
            _connector.scan_shm_session_expires()
            _connector.scan_shm_session_logoff()
            _connector.refresh_topology()
            time.sleep(timer)

    except Exception as e:
        logger.warn("exception(%s): session timer thread %s exit" % (str(e), name) )

def init_logger(config):
    # Remove exist handlers
    logger = logging.getLogger(config.LOGGER_NAME)
    del logger.handlers[:]
    Rthandler = ConcurrentRotatingFileHandler('/tmp/snapperapp.log', maxBytes=config.LOG_FILE_SIZE, backupCount=config.LOG_BKUP_FILES)
    Rthandler.setFormatter(Formatter(config.LOG_FORMAT))
    logger.addHandler(Rthandler)
    logger.setLevel(config.LOG_LEVEL)

    if config.LOG_CONSOLE == True:
        console = logging.StreamHandler()
        console.setFormatter(Formatter(config.LOG_FORMAT))
        logger.addHandler(console)
        logger.setLevel(config.LOG_CONSOLE_LEVEL)

# dump http data for debugging
def init_http_logger(config):
    logger = logging.getLogger(config.LOGGER_HTTP_NAME)
    del logger.handlers[:]
    Rthandler = ConcurrentRotatingFileHandler('/tmp/snapperhttp.log', maxBytes=(100*1024), backupCount=1)
    Rthandler.setFormatter(Formatter(config.LOG_FORMAT))
    logger.addHandler(Rthandler)
    logger.setLevel(logging.DEBUG)

def req_data():
    json_str = ''
    if request.get_json() != None:
        json_data = request.get_json()
        if type(json_data) == dict:
            json_str = json.dumps(json_data)
    elif request.form != None:
        json_data = {key:dict(request.form)[key][0] for key in dict(request.form)}
        json_str = json.dumps(json_data)
    return json_str

def CurrentUpTime():    
    f = open("/proc/uptime")
    result = f.read()
    tmp = result.split()      
    uptime = float(tmp[0])
    uptime  = int(uptime)
    #logger.warn("CurrentUpTime: %d ", uptime)
    return uptime

def SetRespHeaders(request, response):
    # fixed headers
    response.headers['OData-Version'] = "4.0"
    response.headers['Cache-Control'] = "no-cache, no-store, must-revalidate, private"

    # set in nginx config
    #response.headers['Server'] = "Lenovo-XCC Snapper/1.0"

    # provider returned headers
    if hasattr(request, 'resphdr') and request.resphdr != None and len(request.resphdr) > 0 :
        hdr_dict = json.loads(request.resphdr)
        token = hdr_dict.get('X-Auth-Token', '')
        if len(token) > 0:
            response.headers['X-Auth-Token'] = token
        loc = hdr_dict.get('Location', '')
        if len(loc) > 0:
            response.headers['Location'] = loc
        etag = hdr_dict.get('ETag', '')
        if len(etag) > 0:
            response.headers['ETag'] = etag
        allow = hdr_dict.get('Allow', '')
        if len(allow) > 0:
            response.headers['Allow'] = allow
        link = hdr_dict.get('Link', '')
        if len(link) > 0:
            response.headers['Link'] = link
        orig = hdr_dict.get('Access-Control-Allow-Origin', '')
        if len(orig) > 0:
            response.headers['Access-Control-Allow-Origin'] = orig
        type = hdr_dict.get('Content-Type', '')
        if len(type) > 0:
            response.headers['Content-Type'] = type
            
    # authentication headers
    if response.status_code == 401:                                                                                                           
        cred = request.headers.get('Authorization', '')
        if len(cred) == 0 or cred.find("Basic ") >= 0 :
            logger.warn("no credential or invalid basic credential in headers")
            response.headers['WWW-Authenticate'] = 'Basic realm="Lenovo Snapper"'


def SSEAuthen(request):
    if request.path.find('/redfish/v1/EventService/ServerSentEvent') == 0:
        cred = request.headers.get('Authorization', '')
        xtoken = request.headers.get('X-Auth-Token', '')
        remoteip = request.headers.get('X-Real-IP', 'unknown')
        result = _connector.connector_sse_auth(request.url, 0, cred, xtoken, remoteip)
        logger.info("sse auth (%s) %s " % (request.path, str(result)))
        if result.get('error', 1) != 0 :
            abort(result.get('http_status', 401))

def create_app(config):
    app = Flask(__name__)
    app.config.from_object(config)

    init_logger(config)
    init_http_logger(config)

    # init server side event
    app.register_blueprint(sse, url_prefix=config.EVENTSTREAM_URL)

    thread.start_new_thread( SessionTimerThread, ("snapper session timer",3) )

    # Restful api
    app.api = Api(app, serve_challenge_on_401=False)

    logger.info("==> snapper gunicorn worker(%d) started.", os.getpid() )

    # init engine. workdir var/www/snapper/app/
    schemapath=os.getcwd() + "/../schema_xml/"
    _connector.connector_init_engine(schemapath)

    @app.before_request
    def before_request():
        #httplogger.debug(">>>> %s from %s " % (request.path, request.headers.get('X-Real-IP', 'UNKNOWN')))
        #Debug.py_perf_trc_log(">> (%d) %s %s from %s" % (os.getpid(), request.path, request.method, request.headers.get('X-Real-IP', 'UNKNOWN')))

        SSEAuthen(request)
        request.req_time = CurrentUpTime()


    @app.after_request
    def after_request(response):
        #httplogger.debug("<<<< %s to %s " % (request.path, request.headers.get('X-Real-IP', 'UNKNOWN')))
        #Debug.py_perf_trc_log("<< (%d) %s [%d] to %s" % (os.getpid(), request.path, response.status_code, request.headers.get('X-Real-IP', 'UNKNOWN')))

        SetRespHeaders(request, response)

        #logging time consuming request and status code
        cur_time = CurrentUpTime()
        delta_time = cur_time - getattr(request, 'req_time', cur_time)
        if delta_time > 5:
            logger.info("request %s from %s cost %.2f(s) (%.2f(s) ~ %.2f(s))" % (request.path, request.headers.get('X-Real-IP', 'UNKNOWN'), delta_time, getattr(request, 'req_time', cur_time), cur_time))
        if response.status_code != 200:
            logger.warn("%s , status code %d" % (request.path, response.status_code))
        
        return response

    return app

