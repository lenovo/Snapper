#---------------------------------------------------------------------------
#  Copyright (c) 2018-present, Lenovo. All rights reserved.
#  Licensed under BSD, see COPYING.BSD file for details.
#---------------------------------------------------------------------------

from flask import Flask, render_template
from flask_sse import sse
from flask import Flask, request, current_app, abort, redirect

def create_app():
    app = Flask(__name__)
    app.config["REDIS_URL"] = "unix:///tmp/redis.sock"
    app.register_blueprint(sse, url_prefix='/stream')
    return app

app = create_app()

@app.before_request
def before_request():
    print(">>>> %s  " % request.path)

@app.after_request
def after_request(response):
    print("<<<< %s  " % request.path)
    return response

@app.route('/')
def index():
    return render_template("index.html")

@app.route('/hello')
def publish_hello():
    print("hello msg")
    sse.publish({"message": "Hello!"}, type='greeting')
    return "Message sent!"

if __name__ == '__main__':
    app.run()
