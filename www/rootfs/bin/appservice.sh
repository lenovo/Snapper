#!/bin/bash
CWD=`pwd`
NGINX_BIN="nginx"
NGINX_CONF="$CWD/etc/nginx/nginx.conf"

GUNICORN_BIN="gunicorn"
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
	echo "start app service"
	$NGINX_BIN -c $NGINX_CONF
	$GUNICORN_BIN -c $GUNICORN_CONF --chdir $CHDIR  $APP_MODULE:$APP_VAR

}

MYPYTHON=`python -c "import sys; print(':'.join(x for x in sys.path if x))"`
main() {
    LD_LIBRARY_PATH="$CWD/lib:$LD_LIBRARY_PATH"
	export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
	export PYTHONPATH="$MYPYTHON:$CWD/var/www/snapper/app:$CWD/var/www/snapper/openmodules"
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
