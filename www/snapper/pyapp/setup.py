# -*- coding: utf-8 -*-

import os
import sys
import sysconfig

from distutils.core import setup, Extension
from Cython.Build import cythonize
from Cython.Distutils import build_ext
#from distutils import ccompiler

#print(os.environ)
TGTROOT = os.environ.get('SDKTARGETSYSROOT')
INC_DIR = os.environ.get('INC_DIR')


snapper_core_lib=[
'xml2','boost_filesystem','boost_system','boost_locale',
'odata','snapper_engine','snapper_provider','snapper_datainterface','snapper_jwt','rfmon_clt','jansson','stub',
'uuid','pam','curl','boost_thread'
]


PY2 = sys.version_info[0] == 2
if not PY2:
    INC_PYTHON = "/usr/include/python3.6m/"
else:
    INC_PYTHON = "/usr/include/python2.7/"
    assert False, "Python2 is out of support!"



def get_ext_filename_without_platform_suffix(filename):
    name, ext = os.path.splitext(filename)
    ext_suffix = sysconfig.get_config_var('EXT_SUFFIX')
    #print("%s %s %s ------------p3 name" % (name, ext,ext_suffix))
    # like _connector.cpython-35m-x86_64-linux-gnu     .so      .cpython-35m-x86_64-linux-gnu.so

    if ext_suffix == ext:
        return filename

    ext_suffix = ext_suffix.replace(ext, '')
    idx = name.find(ext_suffix)

    if idx == -1:
        return filename
    else:
        return name[:idx] + ext

class BuildExtWithoutPlatformSuffix(build_ext):
    def get_ext_filename(self, ext_name):
        filename = super().get_ext_filename(ext_name)
        return get_ext_filename_without_platform_suffix(filename)

kw = {'name':"Snapper",
      'version':"1.0",
      'description':"XCC Redfish Data Provider",
      'author':"Lenovo",
      'author_email':"xxx@lenovo.com",
      #'url':"",
      'packages':['app','app.plugin','app.extmod_c'],
      'package_dir' : { "app": "./app" },
      'cmdclass':{'build_ext': BuildExtWithoutPlatformSuffix},
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
