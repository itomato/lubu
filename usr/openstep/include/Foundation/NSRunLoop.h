#ident "@(#) NSRunLoop.h, Rev 1.15, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	An input manager.
 

/* RunLoops manage input sources:
 * NSPorts, NSTimers, and POSIX file descriptors.
 *
 * The input sources are grouped by mode names; the RunLoop is told to
 * process input for the input sources associated with a particular mode.
 * The key constraint managed is the maximum amount of time that should be
 * spent blocked awaiting new input.  delegates and timers are polled
 * to determine this time limit. Polling also provides an opportunity to
 * service queued work.
 */

/* A runLoop is automatically provided (lazily) for each NSThread in a task. */

#import <Foundation/NSDate.h>
#import <Foundation/NSTimer.h>
#import <Foundation/NSPosixFileDescriptor.h>
#import <Foundation/NSMapTable.h>
#import <synch.h>

@class NSPort <NSCopying, NSCoding>;

/**************** 	Basic definitions	 **************************/

@interface NSRunLoop : NSObject {
@private
	NSMapTable	*_modes;
	id		_callout;
	void	*_callouts;
	id  _currentMode;
	void	*_timers;
	void	*_performers;

 	id pSet;
	id threadPort;
	mutex_t	portThreadLock;
	int SelectPipe[2];
	id pipePfdForThread; /* to wrap around the pipe*/

	/* This set of locks and condition vars it use to synchronize
	 * the starting and stopping of the thread that receives mach
	 * messages. We take the thread off its message receive every
	 * time we need to make a modification to its port set.
	 */
	cond_t inRunLoopCV;
	mutex_t inRunLoopLock;
	int inRunLoop;
	int runningWithPorts;
	int startedYet;
	mutex_t	stoppedLock;
	int portThreadStopped;
	cond_t stoppedCV;

	mutex_t msgBufLock;
	char **msgInfo;
	int slotMax;
}

+ (NSRunLoop *)currentRunLoop;
	// the runLoop for the executing thread

- (NSString *)currentMode;
	// current mode

/**************** 	Adding activity generators	 ******************/

#if !defined(STRICT_OPENSTEP)
- (void)addPosixFileDescriptor:(NSPosixFileDescriptor *)pfd
		forMode:(NSString *)mode;

- (void)removePosixFileDescriptor:(NSPosixFileDescriptor *)pfd
		forMode:(NSString *)mode;
#endif // STRICT_OPENSTEP

- (void)addRunLoopActivityMonitor:monitor;
	// monitor is added to the list of RunLoop activity monitors.

- (void)addTimer:(NSTimer *)timer
		forMode:(NSString *)mode;
	/* Timers are removed from modes if they supply nil as a fireDate */

/**************** 	Control primitives	 ******************/

- (NSDate *)limitDateForMode:(NSString *)mode;
	/* poll timers and port delegates for limitDate.
	 * timers will fire if appropriate.
	 * nil returned if no ports or timers for this mode (nothing to do!)
	 */

- (void)acceptInputForMode:(NSString *)mode
		beforeDate:(NSDate *)limitDate;
	/* actually running the run loop.
	 * pause no later than limitDate for input .
	 * input is processed via the Port delegates if it arrives
	 * NO timers will fire.
	 */

@end

/**************** 	Basic modes	 ******************/

extern NSString *NSDefaultRunLoopMode;
	// the common mode

/**************** 	Conveniences	 ******************/

@interface NSRunLoop (NSRunLoopConveniences)

- (void)run;
	// forever in NSDefaultRunLoopMode or nothing to do
 
- (void)runUntilDate:(NSDate *)limitDate;
	// run up to limitDate in mode NSDefaultRunLoopMode or nothing to do

- (BOOL)runMode:(NSString *)mode
		beforeDate:(NSDate *)limitDate;
	// run once before limitDate
	// returns NO if nothing to do

@end

/**************** 	Delayed perform	 ******************/

@interface NSObject (NSDelayedPerforming)
/*  These methods assume a run loop (hence their definition in this module)
 *	and are executed in NSDefaultRunLoopMode
 */

- (void)performSelector:(SEL)aSelector
		withObject:(id)anArgument
		afterDelay:(NSTimeInterval)delay;

	/* will send [self aSelector:anArgument] after delay;
	 * self and anArgument are retained until after the action is executed.
	 */

+ (void)cancelPreviousPerformRequestsWithTarget:(id)aTarget
		selector:(SEL)aSelector
		object:(id)anArgument;

	/* Cancels all the requests that had same (in the isEqual: sense)
	 * target and argument, and identical selector;
	 * Cancelling previous requests may be slow;
	 * Also note it only removes timers in the current run loop,
	 * not all run loops
	 */

@end

