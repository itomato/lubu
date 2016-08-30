# Simple Makefile for osxpm - no need for Imake 
# (C) Lubu OpenStep 1.1.1 - 01MAY2005

all::
	@echo "Making osxpm ... "
	gcc -o osxpm osxpm.c -O2 -I/usr/openwin/include -I. -L/usr/openwin/lib -lX11 -lXpm
	strip osxpm
	du -sh osxpm

clean::
	@echo "Cleaning up ... "
	rm -f osxpm
	rm -f *.BAK *.bak *.o core "#"*

install::
	@echo "Installing distribution files ... "
	/usr/ucb/install -c   osxpm /usr/openstep/bin/osxpm
	/usr/ucb/install -c -m 0444 osxpm.man /usr/openstep/man/man1/osxpm.1	

test::
	@echo "Making test ... "
	./osxpm hatch.xpm
	@echo "Test done."
	@echo "If you see a gray hatch on a black background, then it worked."
	@echo "Now you can set your background back to it's normal state ..."
