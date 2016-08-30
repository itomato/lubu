#ident "@(#) NSThread.h, Rev 1.11, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Support for initiating and controlling threads

#import <Foundation/NSDictionary.h>
#import <Foundation/NSDate.h>
#import <thread.h>

@interface NSThread : NSObject  {
@public
    thread_t			thread;
    NSMutableDictionary 	*threadDictionary;
    id				runLoop;
    id				doStack;
    id				doQueue;
    id				noteQueue;
    id				autoreleasePool;
    void		*reserved;
}

+ (NSThread *)currentThread;
    /* the thread we are executing in */

+ (void)detachNewThreadSelector:(SEL)selector
		toTarget:(id)target
		withObject:(id)argument;
	/* creates and starts a new thread, sending the action to the target;
	   Actions should take one argument and yield none;
	   Target and argument are retained during the execution of the
	   detached thread, then released;
	   If this is the first time a new thread is created (by this method),
	   an anonymous notification NSWillBecomeMultiThreadedNotification is 
	   sent, to let modules protect access with locks.
	 */

+ (BOOL)isMultiThreaded;
    /* Returns YES if a thread was ever detached
	   (that thread may have died since!)
	 */

- (NSMutableDictionary *)threadDictionary;
	/* data specific to the receiving thread.  May only be accessed
	   outside that thread before the thread is forked.
	 */

+ (void)sleepUntilDate:(NSDate *)date;
    /* the current thread blocks until the designated date.
	   No run loop processing occurs.
	 */

+ (void)exit;
	/* Terminates the calling thread.
	   Same effect as returning from the initial message.
	   Before exiting that thread, posts the notification
	   {name = NSBecomingMultiThreaded, object = thread}
	 */

@end

extern NSString *NSWillBecomeMultiThreadedNotification;
extern NSString *NSThreadDidExitNotification;
