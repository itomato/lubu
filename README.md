LuBu OpenMagic is an enhancement of the Solaris OpenStep 1.1-sparc desktop enviroment.

This repo is the expanded tar originally distributed by Luke Bullock at http://alge.anart.no.

It is not a rewrite, nor is it a re-release, but is a package that enhances and improves (and includes) Solaris OpenStep 1.1. 

LuBu OpenMagic is only available for the SPARC architecture. 

LuBu OpenMagic 1.0 is a heavily modified version of the Lighthouse OpenStep 1.1 release for the Sparc platform. It is not a theme, nor a reconfiguration, but an almost pure rewrite of non-binary files (runtime configurations, application definitions, enviroment variables, and many functions). In some parts entire functions have been replaced features have been added. This applies primarily to the Wrapper function which has been entirely rewritten to use the LuBu OpenMagic Alert System (aka: LOAS). This is a completely new feature which among many other things also produces error messages in human readable form, with the actual cause of the error. This makes taking countermeasures and avoiding future errors easier. The default application definitions provided with OpenStep 1.1 were the cause of countless bugs, and I have spendt a great amount of time optimizing the default defs. There are still a few bugs for which I have found no workaround, but non are critical. 

OpenMagic 1.0 will only run on Sparc CPU's since it is based on Solaris OpenStep 1.1 for Sparc. There is not, nor will there ever be, a release for any other CPU. Since LuBu OpenMagic 1.0 is based on the binary Solaris OpenStep release, it remains a Solaris Sparc product. There are no known binaries for other CPU's or operating systems. It does however fully integrate the Solaris Operating Enviroment, Common Desktop Enviroment, and any other enviroments that run on Solaris Sparc. This makes it alot easier to integrate applications into the OpenStep enviroment without the need of porting. 

LuBu OpenMagic 1.0 is packaged as a pure gzipped tar file, intended for unpacking from the root directory (ie: / ). This means that the default installation directory for OpenStep should be /usr/openstep - it is importent that this rule is followed, else the installation will fail and the distribution will not function at all. It is however possible to extract to a different directory and create a symlink to /usr/openstep. Just remember to copy the etc/dt/config files to their desired location (/etc/dt/config). This is needed as there are some additional files included in order for LuBu OpenMagic 1.0 to function correctly: 

1. A modified /etc/dt/config/Xservers file with -dpi 72

2. Configuration files for dtlogin (in /etc/dt/config/*.os|*.xpm)

3. Icons for /cdrom and /floppy (directories will be created if missing)

For an optimal installation:

    $ su -
    # cd /
    # gtar zxvf /path/to/lubu_openwb-1.0-sparc.tgz

Make sure that all the files are extracted, and that existing files ARE overwritten! This will NOT reduce system security or in any other way reduce system performance. 
Make sure all files in /usr/openstep are owned by bin:bin else you will loose alot of functionality! There is NO NEED for ANY of the files to be owned by root (other than possibly Preferences.app/set_password which is initially broken due to a missing library - see KNOWN_BUGS). 
If you must chown /usr/openstep, then it is a good idea to cd to /usr before running chown -R in case you are using a non-standard chown. Worst case scenario is that a chown -R from / chowns your entire system bin:bin! Better safe than sorry. 

    # cd /usr
    # chown -R bin:bin openstep/

If you extracted OpenStep to a different location, then cd to that location before running chown # cd /path/to/your/installation

    # chown -R bin:bin ../openstep (provided you actually are in the openstep directory)
    
Make sure the following line is present in /etc/dt/config/Xservers:

    :0 Local local_uid@console root /usr/openwin/bin/Xsun :0 -nobanner -dpi 72 (this is however included in the distribution files and should be installed upon extraction).
    
For optimal performance it is best to run your display at -depth 24 -dpi 72 This file (Xservers) should be -rwx-xr-x otherwise run

    # chmod 755 /etc/dt/config/Xservers
    
It is vital that dtlogin is restarted after installation. Exit your windowmanager, login as root to the system console, and run the following commands (as root):

    # sh /etc/init.d/dtlogin stop
    # sh /etc/init.d/dtlogin start
Now log out from the console and allow the dtlogin loginwindow to reappear. Select "LuBu OpenMagic 1.0" from the session menu. Log in and enjoy!

It is however possible to run LuBu OpenMagic 1.0 without CDE installed, or without running it through dtlogin by simply starting the file /usr/openstep/bin/openstep, though you might loose some valuable configurations using this method. It has not as of yet been tested thouroughly:

    $ sh /usr/openstep/bin/openstep
    
----
LuBu OpenMagic 1.0 for Solaris OpenStep 1.1-sparc
-------------------------------------------------

Copyrights:
LuBu OpenMagic 1.0 (C)2006 Luke Th. Bullock.
Lighthouse OpenStep 1.1: (C)1997 Lighthouse Design
Solaris OpenStep 1.0: (C)1996 Sun Microsystems, Inc.
Portions (C)1994 NeXT Computer, Inc.

LuBu OpenMagic 1.0 is an enhanced desktop based on the Lighthouse OpenStep
1.1 release. No binary files have been altered or reversed, as LuBu OpenMagic
1.0 consists of optimized configurations, 3rd party software based on either
free or open software, or original code written by and (C)Luke Th. Bullock.
All original software code that is used in LuBu OpenMagic 1.0 has been made public in it's original form at ftp://alge.anart.no/pub/openmagic/source.
The copyright holders to the underlying software Solaris OpenStep 1.1 (Sun, Apple/NeXT & Lighthouse Design) may at any time revoke your right to use this software. 

LuBu OpenMagic 1.0 is (C)2006 Luke Th. Bullock. I do however reserve the 
right to deny all copyright rights since LuBu OpenMagic 1.0 is: 

a) An enhancement and optimization of existing software within Solaris
   OpenStep 1.1, where it has been possible to alter software behaviour
   without violating Sun, Apple/NeXT or Lighthouse copyrights.
b) Rewrites of freeware and opensource software - included in LuBu
   OpenMagic 1.0 as additions to the Solaris OpenStep 1.1 release for 
   either productivity reasons or configuration reasons.
c) Partial rewrites of code now released to the public from Sun's 
   former desktop enviroment, XVIEW. Many of these applications are
   most welcome additions to LuBu OpenMagic 1.0.
d) LuBu OpenMagic 1.0 specific scripts and applications written from
   scratch in either shell or C for use with the OpenMagic Desktop.
   Even though these scripts and apps are written and (C) myself,
   I wave the wright to maintain this copyright, and grant unlimited
   and unrestricted permissions to use, modify, alter and in any other
   way abuse them, under the condition that they 1. are not sold for
   profit, 2. are not put under restrictions of any kind other than 
   stated here, 3. are not used in systems that promote, maintain, 
   encourage or in any other way support war, hatred, voilence, crime
   or discrimination of race, sex, religion or belief-system.
   
LuBu OpenMagic 1.0 is put into the public domain as an attempt to revive 
and enhance an outstanding API, Interface and desktop enviroment for the 
SPARC platform, namely the OpenStep API/Desktop. Unfortunatly no compiler
for NeXT/OpenStep applications is available for the Sparc platform (ie: 
Solaris OpenStep-sparc), neither do I beleive Sun ever will release one, therefore I was forced to either write additions myself, or use 3rd party solutions and applications based on opensource and freeware and Public
Domain source code.

Please read the included LICENSE.SunSoft file, which is the original
Solaris OpenStep 1.0 license from Sun/Sunsoft. Also read the file(s) Copyright.Sun, KNOWN_BUGS, HINTS and READ_ME_FIRST in the Information
folder included with this release.

Luke Th. Bullock
Oslo, 10/03/06

-------------------------------------------------------------------
YOU MUST OBSERVE ANY AUTHORS' CONDITIONS WITH RESPECT TO
INDIVIDUAL COMPONENTS PROVIDED WITHIN THIS CODE.  SUPPORT
FOR THE TECHNOLOGIES AND DOCUMENTATION IS NOT PROVIDED
BY SUN MICROSYSTEMS, INC.

THE TECHNOLOGIES AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT TECHNICAL
SUPPORT OR WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.

