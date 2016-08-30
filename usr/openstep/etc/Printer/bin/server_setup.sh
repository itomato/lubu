#!/bin/sh -n
#
# @(#)server_setup.sh 1.4 95/12/13 Copyright Sun Microsystems, Inc.
#
dir_name()
{
    /usr/bin/expr \
	"${1:-.}/" : '\(/\)/*[^/]*//*$'  \| \
	"${1:-.}/" : '\(.*[^/]\)//*[^/][^/]*//*$' \| \
	.
}

status_check()
{
    if [ $1 -ne 0 ]; then
	echo "$2"
	echo "Exiting ...."
	rm -f /tmp/jds_inet
	exit $1
    fi
}

PrtAdm=
if [ "$1" = "-x" ]; then 
    PrtAdm=-x
fi 

RestartInet=0
SWARCH=`uname -r | grep '^5' >/dev/null && echo solaris2 || echo solaris1`
agent_dest=/usr/openstep/etc/Printer/bin/jdsagent

if [ "$SWARCH" = solaris2 ]; then

    installer=`id | grep uid=0`
    if [ -z "$installer" ]; then
        echo "You must be 'root' to run server_setup"
        echo "Exiting ..."
        exit 1
    fi

    PSCMD="/usr/bin/ps -ef"
    inet_entry="100410/1	tli	rpc/tcp	wait	root	/usr/openstep/etc/Printer/bin/jdsagent	jdsagent $PrtAdm
100410/1	dgram	rpc/udp	wait	root	/usr/openstep/etc/Printer/bin/jdsagent	jdsagent"
    inet_pid=`$PSCMD | grep inetd | awk '{ print $2 }'`
    INETDCMD="/usr/sbin/inetd -s"

else

    installer=`/usr/ucb/whoami`
    if [ "$installer" != "root" ]; then
        echo "You must be 'root' to run spa_setup"
        echo "Exiting ..."
        exit 1
    fi

    PSCMD="/usr/bin/ps -ax"
    inet_entry="100410/1	stream	rpc/tcp	wait	root	/usr/openstep/etc/Printer/bin/jdsagent	jdsagent $PrtAdm
100410/1	dgram	rpc/udp	wait	root	/usr/openstep/etc/Printer/bin/jdsagent	jdsagent"
    inet_pid=`$PSCMD | grep inetd | awk '{ print $1 }'`
    INETDCMD="/usr/etc/inetd"

fi

dir=`dir_name $0`
bintype=`$dir/binarytype`
agent=$dir/$bintype/jdsagent
if [ -x $agent_dest ]; then
    osum=`sum $agent_dest | awk '{ print $1, $2 }'`
    jsum=`sum $agent | awk '{ print $1, $2 }'`
    if [ "$osum" != "$jsum" ]; then
	/usr/bin/cp $agent $agent_dest
	status_check $? "Could not copy $agent to $agent_dest"
	chmod 555 $agent_dest
    fi
else
    /usr/bin/cp $agent $agent_dest
    status_check $? "Could not copy $agent to $agent_dest"
    chmod 555 $agent_dest
    RestartInet=1
fi

jdsentry=`grep '^100410' /etc/inetd.conf`
if [ -z "$jdsentry" ]; then
    echo "$inet_entry" >> /etc/inetd.conf
    RestartInet=1
elif [ "$jdsentry" != "$inet_entry" ]; then
    /usr/bin/sed -e '/^100410/d' /etc/inetd.conf > /tmp/jds_inet
    status_check $? "Could not edit /etc/inetd.conf: sed failed"
    echo "$inet_entry" >> /tmp/jds_inet
    /usr/bin/mv /etc/inetd.conf /etc/inetd.conf.$$
    /usr/bin/cp /tmp/jds_inet /etc/inetd.conf
    if [ $? -ne 0 ]; then
	/usr/bin/mv /etc/inetd.conf.$$ /etc/inetd.conf
	echo "$0: Not able to edit /etc/inetd.conf: copy failed."
	/usr/bin/rm -f /tmp/jds_inet
	exit 1
    fi
    /usr/bin/rm -f /tmp/jds_inet
    RestartInet=1
fi

if [ "$RestartInet" -eq 1 ]; then
# we get two pids from this command so blow off the error from
# trying to kill the pid for the grep

#
# kill -HUP doesn't seem to work consistently
#
#    /usr/bin/kill -9 $inet_pid 2>/dev/null
#    $INETDCMD

    /usr/bin/kill -HUP $inet_pid 2>/dev/null
    sleep 5
fi

exit 0
