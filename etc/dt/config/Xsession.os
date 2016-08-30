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
###  Revision:          @(#)Xsession.os	1.4 OpenStep version 96/07/01
###
###  Based on:          @(#)Xsession.ow.src 1.4 95/08/10 
###
###  (c) Copyright 1993, 1994, 1995, 1996 Sun Microsystems, Inc.
###
#####################################################################

# /usr/dt/bin/Xsession ### not needed.

# At this point, the users .dtprofile and .login have been run
if [ -z "$OPENSTEPHOME" ]
then
     if [ -d /usr/openstep/etc ]
     then
          OPENSTEPHOME=/usr/openstep
          export OPENSTEPHOME
     fi
     if [ ! -d /usr/openstep/etc ]
     then
          # look for it in /usr/dist
          DHOME=${DIST_HOME:-/usr/dist}
          if [ ! -f $DHOME/exe/openstep ]
          then
               echo "--- Cannot locate /usr/openstep" >> ~/.dt/startlog
               echo "--- nor $DHOME/exe/openstep" >> ~/.dt/startlog
               DHOME=
          fi
          export OPENSTEPHOME=$DHOME/pkgs/openstep/5bin.`/usr/bin/arch`
          export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$OPENSTEPHOME/lib
     fi
fi

#
# If OpenStep's Xinitrc does not exist then
# fallback to the standard openwin version.
#
OPENSTEP_XINITRC=${OPENSTEPHOME:-/usr/openstep}/etc/Xinitrc

if [ -f $OPENSTEP_XINITRC ]; then
        /bin/ksh $OPENSTEP_XINITRC
else
	/bin/ksh ${OPENWINHOME:-/usr/openwin}/lib/Xinitrc
fi
