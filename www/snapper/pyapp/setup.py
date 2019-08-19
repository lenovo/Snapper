# -*- coding: utf-8 -*-

import os
import sys

from distutils.core import setup, Extension
from distutils import ccompiler

#print(os.environ)
TGTROOT = os.environ.get('SDKTARGETSYSROOT')
INC_DIR = os.environ.get('INC_DIR')


snapper_core_lib=[
'xml2','boost_filesystem','boost_system','boost_locale',
'odata','snapper_engine','snapper_provider','snapper_datainterface','snapper_jwt','rfmon_clt','jansson','stub',
'uuid','pam','curl','boost_thread','boost_thread-mt'
]


PY2 = sys.version_info[0] == 2
if not PY2:
    INC_PYTHON = "/usr/include/python3.4m/"
else:
    INC_PYTHON = "/usr/include/python2.7/"

kw = {'name':"Snapper",
      'version':"1.0",
      'description':"XCC Redfish Data Provider",
      'author':"Lenovo",
      'author_email':"xxx@lenovo.com",
      #'url':"",
      'packages':['app','app.plugin','app.extmod_c'],
      'package_dir' : { "app": "./app" },
      'ext_modules': [
            Extension("app.extmod_c._connector",
                      include_dirs=['extmod_c/', TGTROOT+INC_PYTHON, INC_DIR],
                      libraries=snapper_core_lib[:],
                      sources=["app/extmod_c/connector.c"]),
#            Extension("app.dataprovider._prop",
#                      include_dirs=['providers/', TGTROOT+INC_PYTHON, INC_DIR],
#                      libraries=['ipmiraw', 'tb'],
#                      sources=["providers/prop.c"]),
      ],
}

setup(**kw)
