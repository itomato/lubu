#ident "@(#) NSNotificationQueue.h, Rev 1.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Queues up notifications and posts them to the attached notificationCenter when needed.

#import <Foundation/NSObject.h>

@class NSNotification, NSNotificationCenter, NSArray;

typedef enum {
    NSPostWhenIdle = 1,
    NSPostASAP = 2,
    NSPostNow = 3
} NSPostingStyle;

typedef enum {
    NSNotificationNoCoalescing = 0,
    NSNotificationCoalescingOnName = 1,
    NSNotificationCoalescingOnSender = 2
} NSNotificationCoalescing;

@interface NSNotificationQueue:NSObject {
    NSNotificationCenter	*_notificationCenter;
    id		_asapQueue;
    id		_idleQueue;
    BOOL	_attached;
    void	*_reserved;
}

+ (NSNotificationQueue *)defaultQueue;
    /* a per-task notification queue,
    that uses the default notification center */

- (id)initWithNotificationCenter:(NSNotificationCenter *)notificationCenter;
    /* uses the specified notificationCenter to post the notifications */

- (id)init;
    /* uses the default notificationCenter */

- (void)enqueueNotification:(NSNotification *)notification
		postingStyle:(NSPostingStyle)postingStyle
		coalesceMask:(unsigned)coalesceMask
		forModes:(NSArray *)modes;
    /* Will post the notifications later, according to the postingStyle:
    NSPostWhenIdle	: when the runloop has nothing else to do
    NSPostASAP		: at the end of the current notification,
    			  callout or timer
    NSPostNow		: now, but after cloalescing

    Coalescing first adds the new notification to the queue, and then sweeps
    the queue, removing all notifications matching the new one, except the
    one with the highest position in the queue (closest to being posted).
    Matching is done on notification name NSNotificationCoalescingOnName, and/or on the
    sender if NSNotificationCoalescingOnSender.

    The notifications are posted only if the runloop is in a mode contained
    in the modes array. A nil value for modes means 'all modes'.
    */

- (void)enqueueNotification:(NSNotification *)notification postingStyle:(NSPostingStyle)postingStyle;
    /* shortcut for coalescing on name and sender, and posting in all modes */

- (void)dequeueNotificationsMatching:(NSNotification *)notification coalesceMask:(unsigned)coalesceMask;
    /* removes from the queue all the notifications matching the notification, according to the mask */

@end
