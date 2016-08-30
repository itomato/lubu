#! /bin/sh
#
#  diagnostic script.
#

checkOSVersionAndPatches()
{
  retval="WARNING"

  #
  # We don't really know what versions of solaris this
  # might be run against, so we start by assuming we
  # can't id the specific OS version and issue a warning.
  # If we do have a test set for the version found, we
  # change the retval to indicate the test results.
  #

  vers=`/usr/bin/uname -r`
  /bin/echo Operating System: Solaris $vers

  if [ `/usr/bin/uname -r | /usr/bin/sed -e 's/^\(.\).*$/\1/'` -eq 5 ]
  then
    if [ `/usr/bin/uname -r | /usr/bin/sed -e 's/^..\(.\).*$/\1/'` -lt 4 ]
    then
      retval="FATAL"
    else
      #
      # Solaris 2.4 patch checks
      #
      if [ "$vers" = "5.4" ]
      then
        retval="OKAY"

        if [ "`/usr/bin/showrev -p | /bin/egrep 101242`" = "" ]
        then
          /bin/echo Patch ID #101242-10 is missing! (libC patch, mandatory!)
        fi

        if [ "`/usr/bin/showrev -p | /bin/egrep 101923`" = "" ]
        then
          /bin/echo Patch ID #101923-08 is missing! ( SS5 TCX patch )
        fi

        dpsstate=`/bin/echo "systemdict /composite known ==" | \
         $PRODUCTROOT"/bin/dpsexec" -root -noexec -nulldev`

        if [ "$dpsstate" != "true" ] 
        then
          
          /bin/echo "Can't find the DPS compositing operators. This either means"
          /bin/echo "you haven't installed the openwin 3.4 packages, or your X server"
          /bin/echo "isn't running now."
          
        fi
      fi
      
      #
      # Solaris 2.5 patch checks
      #
      if [ "$vers" = "5.5" ]
      then
        retval="OKAY"

        if [ "`/usr/bin/showrev -p | /bin/egrep 103073`" = "" ]
        then
          /bin/echo Patch 103073-01 is missing! \( SS5 TCX patch \)
        fi

        if [ "`/usr/bin/showrev -p | /bin/egrep 103246`" = "" ]
        then
          /bin/echo Patch 103246-03 is missing! \( OpenWindows Font Patch \)
        fi
      fi
      
      #
      # Solaris 2.5.1 patch checks
      #
      if [ "$vers" = "5.5.1" ]
      then
        retval="OKAY"

	# DPS 2.6 build 27 composite on 8bit patch
        #if [ "`/usr/bin/showrev -p | /bin/egrep 103246`" = "" ]
        #then
        #  /bin/echo Patch 103246-03 is missing! \( OpenWindows Font Patch \)
        #fi
      fi
      
      #
      # Solaris 2.6 patch checks
      #
      if [ "$vers" = "5.6" ]
      then
        retval="OKAY"
        #
        # Doesn't seem to be any 2.6 runtime patches yet.
        #
      fi
  
    fi
  else
    retval="FATAL"
  fi
  
  if [ "$retval" = "FATAL" ]
  then
    /bin/echo OpenStep does not work with the version of Solaris you have installed!
    return
  fi

  if [ "$retval" = "WARNING" ]
  then
    /bin/echo OpenStep has not been tested with the version of Solaris you are running.
    /bin/echo You may experience unusual behavior or bugs.
    return
  fi
  
}

verifyRuntime()
{

  retval="OKAY"

  WHAT=`which what`
  if [ "$WHAT" != "" ]
  then
	/bin/echo "Installed OpenStep component versions:"
	what $OPENSTEPHOME/lib/libAppKit.so.1 | grep "OpenStep"
	what $OPENSTEPHOME/lib/libFoundation.so.1 | grep "OpenStep"
	what $OPENSTEPHOME/lib/libobjc.so.1 | grep "OpenStep"
	what $OPENSTEPHOME/lib/libidlRuntime.so.1 | grep "OpenStep"
	what $OPENSTEPHOME/Apps/WM.app/WM | grep "OpenStep"
  else
	/bin/echo "The 'what' command is not installed on your system; We can't determine"
	/bin/echo "the individual versions of the installed OpenStep libraries and applications."
  fi
  /bin/echo "Overall OpenStep version installed appears to be:"
  softVers=`cat $OPENSTEPHOME/etc/Resources/software_version`
  if [ "$softVers" = "" ]
  then
	/bin/echo "\t" "Solaris OpenStep 1.0"
  else
	/bin/echo "\t" $softVers
  fi
  /bin/echo

  #
  # First we check for missing packages that would make
  # OpenStep behave oddly or give strange errors
  #

  if [ "`pkginfo -q SUNWOosUe`" = 0 ] 
  then
    /bin/echo Runtime is missing pkg SUNWOosUe
    retval="WARNING"
  fi

  if [ "`pkginfo -q SUNWOosUh`" = 0 ] 
  then
    /bin/echo Runtime is missing pkg SUNWOosUh
    retval="WARNING"
  fi

  if [ "`pkginfo -q SUNWOosUt`" = 0 ] 
  then
    /bin/echo Runtime is missing pkg SUNWOosUt
    retval="WARNING"
  fi

  if [ "`pkginfo -q SUNWOosUx`" = 0 ] 
  then
    /bin/echo Runtime is missing pkg SUNWOosUx
    retval="WARNING"
  fi

  #
  # Now we check for missing packages that would stop
  # OpenStep from running at all
  #

  if [ "`pkginfo -q SUNWOosUc`" = 0 ] 
  then
    /bin/echo Runtime is missing pkg SUNWOosUc
    retval="FATAL"
  fi

  if [ "`pkginfo -q SUNWOosUd`" = 0 ] 
  then
    /bin/echo Runtime is missing pkg SUNWOosUd
    retval="FATAL"
  fi

  if [ "`pkginfo -q SUNWOosUs`" = 0 ] 
  then
    /bin/echo Runtime is missing pkg SUNWOosUs
    retval="FATAL"
  fi

  if [ "`pkginfo -q SUNWOosUw`" = 0 ] 
  then
    /bin/echo Runtime is missing pkg SUNWOosUw
    retval="FATAL"
  fi

  #
  # Check the final value
  #

  if [ "$retval" = "FATAL" ]
  then
    /bin/echo There are fatal problems in the runtime install!
    return
  fi

  if [ "$retval" = "WARNING" ]
  then
    /bin/echo There are packages missing in the runtime install!
    return
  fi

  if [ "$retval" = "OKAY" ]
  then
    /bin/echo The runtime packages are all installed.
  fi
}

verifyPrinter()
{
  if [ "`pkginfo -q SUNWOosUp`" = 0 ] 
  then
    /bin/echo The printing package is not installed.
  else
    /bin/echo The printing package is installed.
  fi
}

verifyCDE()
{
  if [ "`pkginfo -q SUNWOosUy`" = 0 ] 
  then
    /bin/echo The CDE login package is not installed.
  else
    /bin/echo The CDE login package is installed.

    if [ -r /usr/dt/config/Xservers ]
    then
      /bin/echo /usr/dt/config/Xservers exists. This file may conflict
      /bin/echo with the Xservers file that SUNWOosUy installs in
      /bin/echo "/etc/dt/config/Xservers. If your display isn't set"
      /bin/echo to 72 dpi, try renaming /usr/dt/config/Xservers to
      /bin/echo /usr/dt/config/Xservers.old
      
    fi

    if [ -r /etc/dt/config/Xsession.os2 ]
    then
      hack="foo"
    else
      /bin/echo Your system does not have an /etc/dt/config/Xsession.os2
      /bin/echo file. This means you have an out of date version of SUNWOosUy.
      /bin/echo "The old version of SUNWOosUy didn't source .dtprofile. The"
      /bin/echo most common symptom of this problem is ProjectBuilder can
      /bin/echo not find the compiler.
      
    fi

  fi
}

verifyRemovableMedia()
{
  if [ "`pkginfo -q SUNWOosUv`" = 0 ] 
  then
    /bin/echo The removable media package is not installed.
  else
    /bin/echo The removable media package is installed.
  fi
}

verifyDeveloper()
{
  retval="OKAY"

  #
  # First we check for missing packages that would stop
  # WorkShop OpenStep from working at all
  #
  if [ "`pkginfo -q SUNWOosDv`" = 0 ] 
  then
    /bin/echo Developer is missing pkg SUNWOosDv
    retval="FATAL"
  else
    #
    # Now we check for missing packages that would make
    # WorkShop OpenStep behave oddly or give strange errors
    #
    if [ "`pkginfo -q SUNWOosDw`" = 0 ] 
    then
      /bin/echo Runtime is missing pkg SUNWOosDw
      retval="WARNING"
    fi

    #
    # Check to make sure the compiler is available
    #
    CC=`which CC`
    if [ "$CC" = "" ]
    then
      
      /bin/echo No compiler was found in your PATH

      if [ -r /opt/SUNWspro/bin/CC ]
      then
        /bin/echo /opt/SUNWspro/bin/CC exists, it looks like you need to
        /bin/echo add /opt/SUNWspro/bin to your PATH.
        
      else
        /bin/echo "I can't find a compiler at /opt/SUNWspro/bin/CC. You"
        /bin/echo "need to install the devpro tools packages. For more"
        /bin/echo "information, see the WorkShop OpenStep install guide"
      fi
    else
      ccVers=`2>&1 CC -V | /bin/grep C++`
      ccNum=`CC -V 2>&1 | awk '{print $NF}' | sed -e 's/\.//g'`
      if [ "$ccNum" -lt 41 ]
      then
        /bin/echo "Your compiler version does not match the version shipped with"
        /bin/echo "WorkShop OpenStep. You must have a version of CC newer than:"
        /bin/echo "CC: SC4.0 04 Oct 1995 C++ 4.1"
        /bin/echo "The version I found was:"
        /bin/echo "$ccVers"
      else
        /bin/echo "Your compiler version appears to be"
       /bin/echo "$ccVers"
      fi
    fi

    if [ -r "$OPENSTEPHOME/include/AppKit/AppKit.p" ]
    then
      hack="foo"
    else
      /bin/echo "$OPENSTEPHOME/include/AppKit/AppKit.p does not exist!"
      /bin/echo "You should reinstall SUNWOosDv."
    fi

    if [ -r "$OPENSTEPHOME/include/DPSClient/DPSClient.p" ]
    then
      hack="foo"
    else
      /bin/echo "$OPENSTEPHOME/include/DPSClient/DPSClient.p does not exist!"
      /bin/echo "You should reinstall SUNWOosDv."
    fi

    if [ -r "$OPENSTEPHOME/include/Foundation/Foundation.p" ]
    then
      hack="foo"
    else
      /bin/echo "$OPENSTEPHOME/include/Foundation/Foundation.p does not exist!"
      /bin/echo "You should reinstall SUNWOosDv."
    fi

    if [ -r "$OPENSTEPHOME/include/soundkit/soundkit.p" ]
    then
      hack="foo"
    else
      /bin/echo "$OPENSTEPHOME/include/soundkit/soundkit.p does not exist!"
      /bin/echo "You should reinstall SUNWOosDv."
    fi
    
  fi

  if [ "$retval" = "FATAL" ]
  then
    /bin/echo There are fatal problems in the developer install!
    return
  fi

  if [ "$retval" = "WARNING" ]
  then
    /bin/echo There are packages missing in the developer install!
    return
  fi

  if [ "$retval" = "OKAY" ]
  then
    /bin/echo The developer packages are all installed.
  fi
}

checkDPI()
{
  /usr/openwin/bin/xdpyinfo | /usr/bin/awk '/resolution/ { if ( $2 == "72x72" ) exit 0; else exit 1; }'
    if [ $? -ne 0 ]
    then
      
      /bin/echo "The X-server resolution is not set to 72x72"
      /bin/echo "You need to add this option to your openwin startup:"
      /bin/echo " -dpi 72"
      /bin/echo "For more information, see the Solaris OpenStep install guide."
      
    fi
}

checkPATH()
{
  testPath=`printenv PATH | grep $PRODUCTROOT/bin`
  if [ "$testPath" = "" ]
  then
    
    /bin/echo "$PRODUCTROOT/bin is not in your PATH!"
    
  fi
}

if [ "$OPENSTEPHOME" = "" ]
then
  OPENSTEPHOME=/usr/openstep
  export OPENSTEPHOME
fi

/bin/echo "SYSTEM CONFIGURATION"
wai=`which whatami`
if [ "$wai" ]
then
	whatami
fi
checkOSVersionAndPatches
/bin/echo "\nSYSTEM DIAGNOSIS\n"
verifyRuntime
verifyPrinter
verifyCDE
verifyRemovableMedia
verifyDeveloper
checkDPI
checkPATH
