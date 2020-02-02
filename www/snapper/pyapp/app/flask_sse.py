# coding=utf-8


import flask
import os
import logging
from collections import OrderedDict
from flask import Blueprint, request, current_app, json, stream_with_context, Response, Flask, abort
from redis import StrictRedis
import six
import time
from extmod_c import _connector
from config import config

__version__ = '0.2.1'

cfg = config[os.getenv('FLASK_CONFIG') or 'default']
logger = logging.getLogger(cfg.LOGGER_NAME)

@six.python_2_unicode_compatible
class Message(object):
    """
    Data that is published as a server-sent event.
    """
    def __init__(self, data, type=None, id=None, retry=None):
        """
        Create a server-sent event.

        :param data: The event data. If it is not a string, it will be
            serialized to JSON using the Flask application's
            :class:`~flask.json.JSONEncoder`.
        :param type: An optional event type.
        :param id: An optional event ID.
        :param retry: An optional integer, to specify the reconnect time for
            disconnected clients of this stream.
        """
        self.data = data
        self.type = type
        self.id = id
        self.retry = retry

    def to_dict(self):
        """
        Serialize this object to a minimal dictionary, for storing in Redis.
        """
        # data is required, all others are optional
        d = {"data": self.data}
        if self.type:
            d["type"] = self.type
        if self.id:
            d["id"] = self.id
        if self.retry:
            d["retry"] = self.retry
        return d

    def __str__(self):
        """
        Serialize this object to a string, according to the `server-sent events
        specification <https://www.w3.org/TR/eventsource/>`_.
        """
        if isinstance(self.data, six.string_types):
            data = self.data
        else:
            data = json.dumps(self.data)
        if self.type and self.type == "Comment":
            lines = [":{value}".format(value=line) for line in data.splitlines()]
            return "\n".join(lines) + "\n\n"
        lines = ["data:{value}".format(value=line) for line in data.splitlines()]
        if self.type:
            lines.insert(0, "event:{value}".format(value=self.type))
        if self.id:
            lines.append("id:{value}".format(value=self.id))
        if self.retry:
            lines.append("retry:{value}".format(value=self.retry))
        return "\n".join(lines) + "\n\n"

    def __repr__(self):
        kwargs = OrderedDict()
        if self.type:
            kwargs["type"] = self.type
        if self.id:
            kwargs["id"] = self.id
        if self.retry:
            kwargs["retry"] = self.retry
        kwargs_repr = "".join(
            ", {key}={value!r}".format(key=key, value=value)
            for key, value in list(kwargs.items())
        )
        return "{classname}({data!r}{kwargs})".format(
            classname=self.__class__.__name__,
            data=self.data,
            kwargs=kwargs_repr,
        )

    def __eq__(self, other):
        return (
            isinstance(other, self.__class__) and
            self.data == other.data and
            self.type == other.type and
            self.id == other.id and
            self.retry == other.retry
        )

class SSEResponse(Response):
    """
    """
    def __init__(self, response=None, mimetype=None, _id=0):
        self.DestID = _id
        logger.info(">>new SSE connection to respond. destination id: %s" % str(self.DestID))
        return super(SSEResponse, self).__init__(response, mimetype=mimetype)

    def __del__(self):
        logger.info("<<SSE response obj to destruct. remove destination id: %s" % str(self.DestID))
        _connector.connector_sse_del_dest(self.DestID)

class ServerSentEventsBlueprint(Blueprint):
    """
    A :class:`flask.Blueprint` subclass that knows how to publish, subscribe to,
    and stream server-sent events.
    """
    @property
    def redis(self):
        """
        A :class:`redis.StrictRedis` instance, configured to connect to the
        current application's Redis server.
        """
        redis_url = current_app.config.get("SSE_REDIS_URL")
        if not redis_url:
            redis_url = current_app.config.get("REDIS_URL")
        if not redis_url:
            raise KeyError("Must set a redis connection URL in app config.")
        return StrictRedis.from_url(redis_url)

    def publish(self, data, type=None, id=None, retry=None, channel='Event'):
        """
        Publish data as a server-sent event.

        :param data: The event data. If it is not a string, it will be
            serialized to JSON using the Flask application's
            :class:`~flask.json.JSONEncoder`.
        :param type: An optional event type.
        :param id: An optional event ID.
        :param retry: An optional integer, to specify the reconnect time for
            disconnected clients of this stream.
        :param channel: If you want to direct different events to different
            clients, you may specify a channel for this event to go to.
            Only clients listening to the same channel will receive this event.
            Defaults to "Event".
        """
        message = Message(data, type=type, id=id, retry=retry)
        msg_json = json.dumps(message.to_dict())
        return self.redis.publish(channel=channel, message=msg_json)

    def messages(self, channel='Event'):
        """
        A generator of :class:`~flask_sse.Message` objects from the given channel.
        pubsub_message format: {'pattern': None, 'type': 'message', 'channel': 'Comment', 'data': 
                '{"data": "{\\"SSEData\\": \\": keep alive\\", \\"EventFormatType\\": \\"Comment\\"}", 
                  "id": 1, 
                  "type": "greeting"}'
               }
        """
        pubsub = self.redis.pubsub()
        pubsub.subscribe(channel)
        pubsub.subscribe('Comment') #all should subscribe comment channel

        logger.info("  SSE client info: %s" % str(request.sseconfig))
        _id = request.sseconfig['id']

        for pubsub_message in pubsub.listen():
            ret = _connector.connector_sse_query_dest(_id)
            if ret != 0 :
                logger.info("SSE destation %d removed from db, terminate stream" % _id)
                break
            if pubsub_message['type'] == 'message':
                msg_dict = json.loads(pubsub_message['data'])
                yield Message(**msg_dict)

    def stream(self):
        """
        A view function that streams server-sent events. Ignores any
        :mailheader:`Last-Event-ID` headers in the HTTP request.
        Use a "channel" query parameter to stream events from a different
        channel than the default channel (which is "Event").
        to add destination:
            unsigned int types(SnapperEventType), char *desturl, char *ctx, char *prot, char *subtype, char *hdrs, char *msgids, char *res
        """
        channel = request.args.get('channel') or 'Event'
        sseclient = {}
        sseclient['remoteip'] = request.headers.get('X-Real-IP', 'unknown')
        sseclient['id'] =  _connector.connector_sse_add_dest(1, sseclient['remoteip'], str(time.time()), 'Redfish', 'SSE', '', '', '')
        request.sseconfig = sseclient

        @stream_with_context
        def generator():
            for message in self.messages(channel=channel):
                yield str(message)

        #return current_app.response_class(
        return SSEResponse(
            generator(),
            mimetype='text/event-stream',
            _id=sseclient['id'],
        )


sse = ServerSentEventsBlueprint('Event', __name__)
"""
An instance of :class:`~flask_sse.ServerSentEventsBlueprint`
that hooks up the :meth:`~flask_sse.ServerSentEventsBlueprint.stream`
method as a view function at the root of the blueprint. If you don't
want to customize this blueprint at all, you can simply import and
use this instance in your application.
"""
sse.add_url_rule(rule="", endpoint="stream", view_func=sse.stream)
