#ident "@(#) LockingApp.h, Rev 1.4, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	All rights reserved.


/*
  The LockingApp application subclass allows controlled access to the appkit.
  In general, the main thread's NSRunLoop will hold the lock, and if it's not
  running, other threads will not be able to acquire the lock.
  As long as the NSRunLoop is running, other threads can access the appkit safely
  by bracketing drawing code with calls to [NSApp lockAppkit] and [NSApp unlockAppkit].
  After drawing, the view may need to call display on its window to flush out
  the changes.
  
  To enable the locking features, simply replace the call [NSApplication sharedApplication]
  with a call to [LockingApp sharedApplication].
  */

#pragma ident "@(#)LockingApp.h	1.4 96/07/08 Sun Microsystems, Inc."

#import <AppKit/NSApplication.h>

@interface LockingApp:NSApplication
{
}

+ (LockingApp *)sharedApplication;
- (void) lockAppkit;
- (void) unlockAppkit;

@end

