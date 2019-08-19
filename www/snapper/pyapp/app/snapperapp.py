# -*- coding: utf-8 -*-

#---------------------------------------------------------------------------
#  Copyright (c) 2018-present, Lenovo. All rights reserved.
#  Licensed under BSD, see COPYING.BSD file for details.
#---------------------------------------------------------------------------

import os
import logging
from config import config
from create_app import create_app
from urls import init_urls
import fcntl
import time

cfg = config[os.getenv('FLASK_CONFIG') or 'default']
app = create_app(cfg)
init_urls(app)

if __name__ == '__main__':
    app.run()
