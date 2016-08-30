#! /bin/sh
# ident "@(#) LuBu OpenMagic 1.0, 06/03/10"; 
# cde_check.sh - Check if CDE is installed, else print error message.

if [ ! -d /usr/dt ]; then
 $OSLOC/bin/osalert -t "OpenMagic Alert System" \
 -i $OSLOC/Apps/WM.app/__ICON/app \
"CDE is not installed in /usr/dt. Cannot continue."
 exit 1
else
 exec /usr/dt/bin/$APP
fi

