#!/bin/ksh 
#####################################################################
###  File:              Xsession.os
###
###  Default Location:  /etc/dt/config/Xsession.os
###
###  Purpose:           OpenStep CDE session start script
###
###  Invoked by:        Solaris Desktop Login Manager (dtlogin)
###
###  Revision:          @(#)Xsession.os	1.6 OpenStep version 97/03/13
###
###  Based on:          @(#)Xsession.ow.src 1.4 95/08/10 
###
###  (c) Copyright 1993, 1994, 1995, 1996 Sun Microsystems, Inc.
###
#####################################################################


DTDSPMSG=/usr/dt/bin/dtdspmsg

if [ -z "$SESSIONTYPE" ]
then
	export SESSIONTYPE="altDt"
fi

if [ -z "$DTSTARTIMS" ]
then
	export DTSTARTIMS="False"
fi

if [ -z "$SDT_ALT_SESSION" ]
then
	export SDT_ALT_SESSION="/etc/dt/config/Xsession.os2"
fi

if [ -z "$SDT_ALT_HELLO" ]
then
     export SDT_ALT_HELLO="/usr/dt/bin/dthello -string 'Starting the Lighthouse Desktop' &"
fi

export SDT_NO_DSDM=""

/usr/dt/bin/Xsession
