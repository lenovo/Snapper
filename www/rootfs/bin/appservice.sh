#!/bin/bash
CWD=`pwd`
NGINX_BIN="/usr/sbin/nginx"
NGINX_CONF="$CWD/etc/nginx/nginx.conf"

JSON_SCHM="$CWD/var/www/snapper/schema_json/ServiceRoot.json"
XML_SCHM="$CWD/var/www/snapper/schema_xml/ServiceRoot_v1.xml"

GUNICORN_BIN="/usr/local/bin/gunicorn"
GUNICORN_CONF="$CWD/etc/snapper.conf.py"
APP_MODULE="snapperapp"
#APP_MODULE="myapp"
APP_VAR="app"
CHDIR="$CWD/var/www/snapper/app"

is_running() {
	local r=`ps -aef | grep $1 | wc -l`
	if [ $r -gt 1 ]; then
		return 1
	fi
	return 0
}

stop_service(){
	is_running "nginx"
	if [ $? -gt 0 ]; then
		echo "Stop nginx ..."
		$NGINX_BIN -s stop
	fi

	is_running "gunicorn"
	if [ $? -gt 0 ]; then
		echo "Stop gunicorn ..."
		killall -s 2 gunicorn
	fi
}
start_service(){
	echo "start web service"
	$NGINX_BIN -c $NGINX_CONF
	echo "start app service"
	$GUNICORN_BIN -c $GUNICORN_CONF --chdir $CHDIR  $APP_MODULE:$APP_VAR

}

MYPYTHON=`python3 -c "import sys; print(':'.join(x for x in sys.path if x))"`
prepare() {
	LD_LIBRARY_PATH="$CWD/lib:$LD_LIBRARY_PATH"
	export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
	export PYTHONPATH="$MYPYTHON:$CWD/var/www/snapper/app:$CWD/var/www/snapper/openmodules"

	if [ ! -e "$NGINX_BIN" ]; then
		echo "can't find $NGINX_BIN"
		exit
	fi
	if [ ! -e "$GUNICORN_BIN" ]; then
		echo "can't find $GUNICORN_BIN"
		exit
	fi

	if [ ! -e "$JSON_SCHM" ]; then
		echo "can't find json schemas"
		exit
	fi
	if [ ! -e "$XML_SCHM" ]; then
		echo "can't find csdl schemas"
		exit
	fi

}

main() {
	prepare

	case "$1" in
		"stop" ) 
		    stop_service
		    ;;
		"start" ) 
		    stop_service
		    sleep 1
		    start_service
		    echo "abnormal $?" 
		    ;;
		* )
		    echo "invalid parameters"
		    echo "appservice.sh [start|stop]"
	esac
}

main $@
