# -*- coding: utf-8 -*-

#---------------------------------------------------------------------------
#  Copyright (c) 2018-present, Lenovo. All rights reserved.
#  Licensed under BSD, see COPYING.BSD file for details.
#---------------------------------------------------------------------------

import os
import logging
import json
from flask import request, Flask
from flask_restful import reqparse, abort, Api, Resource
from config import config


cfg = config[os.getenv('FLASK_CONFIG') or 'default']
logger = logging.getLogger(cfg.LOGGER_NAME)


class ServiceRoot(Resource):
    def get(self):
        try:
            return {'return': 0}
        except Exception as e:
            logger.warn("ServiceRoot: %s", str(e))
            return {'return':1}



