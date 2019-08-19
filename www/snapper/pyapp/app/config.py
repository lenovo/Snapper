# -*- coding: utf-8 -*-

#---------------------------------------------------------------------------
#  Copyright (c) 2018-present, Lenovo. All rights reserved.
#  Licensed under BSD, see COPYING.BSD file for details.
#---------------------------------------------------------------------------

import os
import logging
from datetime import datetime, timedelta

class Config:
    LOGGER_NAME = 'SnapperAPP'
    LOGGER_HTTP_NAME = 'SnapperHTTP'
    LOG_LEVEL = logging.DEBUG
    LOG_FORMAT = ('%(asctime)s  %(levelname)s  (%(funcName)s:%(lineno)d) %(message)s\n')
    LOG_BKUP_FILES = 2
    LOG_FILE_SIZE  = 50*1024
    LOG_CONSOLE    = False
    LOG_CONSOLE_LEVEL    = logging.ERROR
    #logging.WARNING, logging.INFO
    REDIS_URL = 'unix:///tmp/redis.sock'
    EVENTSTREAM_URL = '/redfish/v1/EventService/ServerSentEvent'

    @staticmethod
    def init_app(app):
        pass

class DevelopmentConfig(Config):
    DEBUG = True

class TestingConfig(Config):
    TESTING = True

class ProductionConfig(Config):
    DEBUG = True

config = {
    'development': DevelopmentConfig,
    'testing': TestingConfig,
    'production': ProductionConfig,

    'default': ProductionConfig
}
