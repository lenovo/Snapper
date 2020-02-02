#import multiprocessing
import os


errorlog = "/tmp/gunicorn_snapper.log"
loglevel = "info"
pidfile  = "/tmp/gunicorn_snapper.pid"

timeout=60
worker_class="gevent"

#bind = "0.0.0.0:8080"
bind = "unix:/tmp/snapper.sock"
workers = 1

def pre_fork(server, worker):
    pass

def worker_int(worker):
    print(("** worker %d INT/QUIT signal" % ( os.getpid() )))

def worker_abort(worker):
    print(("** worker %d ABRT signal" % ( os.getpid() )))

def child_exit(server, worker):
    print(("** child worker %d exit" % ( worker.pid )))
