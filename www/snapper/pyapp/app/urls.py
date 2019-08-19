# -*- coding: utf-8 -*-

#---------------------------------------------------------------------------
#  Copyright (c) 2018-present, Lenovo. All rights reserved.
#  Licensed under BSD, see COPYING.BSD file for details.
#---------------------------------------------------------------------------

import plugin.ServiceInfo
import plugin.Processor

from flask import Flask
from werkzeug.routing import BaseConverter

class RegexConverter(BaseConverter):
    def __init__(self, url_map, *items):
        super(RegexConverter, self).__init__(url_map)
        self.regex = items[0]

def init_urls(app):
    api = app.api
    app.url_map.converters['regex'] = RegexConverter

    api.add_resource(plugin.Processor.Version,         '/redfish', '/redfish/')
    api.add_resource(plugin.Processor.ServiceRoot,     '/redfish/v1', '/redfish/v1/', '/redfish/v1/odata', '/redfish/v1/odata/')
    api.add_resource(plugin.Processor.SSEProxy,       '/redfish/v1/sseproxy')
    api.add_resource(plugin.Processor.MetaDataDoc,     '/redfish/v1/$metadata', '/redfish/v1/$metadata/')
    api.add_resource(plugin.Processor.SchemaResource,  '/redfish/v1/schemas/<regex(".+"):path>', '/redfish/v1/schemas/<regex(".+"):path>/')
    api.add_resource(plugin.Processor.RedfishResource, '/redfish/v1/<regex(".+"):path>')


