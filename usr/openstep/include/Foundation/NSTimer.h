#ident "@(#) NSTimer.h, Rev 1.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
 
#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@interface NSTimer : NSObject

+ (NSTimer *)timerWithTimeInterval:(NSTimeInterval)ti
			invocation:(NSInvocation *)invocation
			repeats:(BOOL)yesOrNo;
  /*	return a timer that, if scheduled, will fire ti seconds from now. 
	If repeats is YES, the timer will reschedule itself at the next time interval ti from the original;
	invocation is retained */

+ (NSTimer *)scheduledTimerWithTimeInterval:(NSTimeInterval)ti
			invocation:(NSInvocation *)invocation
			repeats:(BOOL)yesOrNo;
    /* same as previous, but registers with the run loop in default mode */
    
+ (NSTimer *)timerWithTimeInterval:(NSTimeInterval)ti
		target:(id)aTarget
		selector:(SEL)aSelector
		userInfo:userInfo
		repeats:(BOOL)yesOrNo;
    /* send [aTarget aSelector:timer] on firing;
	userInfo available as [timer userInfo];
	aTarget is retained until invalidation */

+ (NSTimer *)scheduledTimerWithTimeInterval:(NSTimeInterval)ti
		target:(id)aTarget
		selector:(SEL)aSelector
		userInfo:userInfo
		repeats:(BOOL)yesOrNo;
    /* same as previous, but registers with the run loop in default mode */


- (void)fire;
    // fire timer

- (NSDate *)fireDate;
    // next date to fire;

#if !defined(STRICT_OPENSTEP)
- (NSTimeInterval)timeInterval;
#endif /* !STRICT_OPENSTEP */

- (void)invalidate;
    // stop timer from ever firing again

- (BOOL)isValid;

- userInfo;
    // any userInfo

@end


