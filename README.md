# snapper
A simulator of Redfish service on x86

A simulator for common Redfish service running on x86, with end 
to end solution for HTTP service, Redfish specification compliant
engine, custom implementation of standard/oem schema and utilities
serving Redfish schema upgrade and specification update.
==============================================================

Dependencies:
--------------------------------
The simulator depends on python 2.7, nginx as https server, gunicorn as 
application server. It also depends on following Python modules installed
in your system:
- certifi(2018.10.15)
- click(7.0)
- flask(1.0.2)
- flask_restful(0.3.6)
- gevent(1.3.6)
- jinja2(2.10)
- markupsafe(1.0)
- redis(2.10.6)
- requests(2.11.0)
- urllib3(1.24)
- werkzeug(0.14.1)
- ConcurrentLogHandler(0.9.1)
- itsdangerous(0.15)
- portalocker(0.3)
- six(1.11.0)
additionally it has dependency on and uses following source code
- odatacpp-server
- bson
- libjwt



Installation
--------------------------------
download nginx source code and install:
./configure --sbin-path=/usr/sbin/nginx --with-http_ssl_module
make
make install

install gunicorn:
pip install gunicorn

install gevent:
pip install gevent

install libraries:
yum install python-devel boost-devel pam-devel jansson-devel e2fsprogs-devel  libcurl-devel libuuid-devel libuuid
install other Python modules like
pip install flask
pip install requests
...

build Snapper code:
./bnp/makebmc pristine
./bnp/makebmc prep
./bnp/makebmc www allt

NOTE: the simulator wraps some Python modules under www/snapper/pyapp/openmodules/ like flask, requests. If you Python
environment already contains these modules, the simulator search Python path in your system first. 



Configuration and Custom Implementation
--------------------------------
configure nginx:
www/rootfs/etc/nginx/nginx.conf - general setting for http server with http service on port 8080
www/rootfs/etc/nginx/snapper_server.conf - snapper https service on port 8000

configure gunicorn:
www/rootfs/etc/snapper.conf.py - WSGI server settings. it can also be launched as lightweight http server

implement resource or use mockup data:
- you can create schema implementation file as samples under www/snapper/engine/providers/
each schema should implement GET/POST/PATCH/DELETE/PUT methods depending on the schema requirement
- you can also use mockup data and simulator provides API to read mockup data from files under 
www/snapper/pyapp/mockup/



Running Snapper
--------------------------------
cd pkgsrc-i686/rootfs/
sudo ./bin/appservice.sh start

the Snapper Redfish service is running with your implementation or mockup data over HTTPS (port 8000)

