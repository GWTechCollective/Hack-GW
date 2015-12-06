#!/bin/bash
### BEGIN INIT INFO
# Provides: 		opto-audio 
# Required-Start: 	$all 
# Required-Stop:	 
# Default-Start: 	2 3 4 5 
# Default-Stop: 	0 1 6 
# Short-Description: Starts opto-audio service
### END INIT INFO

# Source function library.
. /lib/init/vars.sh
. /lib/lsb/init-functions

start() {
    python /home/pi/opto-audio/opto-audio.py &
}

stop() {
    ps aux | grep opto-audio | awk '{print $2}' | xargs kill
}

case "$1" in
    start)
       start
       ;;
    stop)
       stop
       ;;
    restart)
       stop
       start
       ;;
    status)
       # code to check status of app comes here example: status program_name
       ;;
    *)
	echo "Usage: $0 {start|stop|status|restart}" 
	esac
exit 0
