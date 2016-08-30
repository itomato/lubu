#ident "@(#) NSLock.h, Rev 1.5, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Support for locks

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

/***************	Locking protocol		***************/

    /* Locking protocol:
	    send "lock" message upon entering critical section
	    send "unlock" message to leave critical section
    
    There are four classes with different implementations and performance characteristics.  There are example usages preceeding each class definition.
	
    Use NSLock to protect regions of code that can consume long periods of time (disk I/O, heavy computation).
    Use NSConditionLock for those cases where you wish only certain threads to awaken based on some condition you define, or for those cases when you have both short and long critical sections.
    Use NSRecursiveLock to protect regions of code or data that may be accessed by the same thread.  The lock will not block if it is already held by the same thread.  This does not provide mutual exclusion with naive signal handlers...
	
    */
	
@protocol NSLocking

- (void)lock;
    // acquire lock (enter critical section)

- (void)unlock;
    // release lock (leave critical section)
    // In order to enable clients to only have locks when processes become multithreaded, it must be possible to unlock a lock freshly created (i.e. that has not been locked).  To see an example where this is assumed, check out the -retain method of NSArray
    
@end
 
/***************	NSLock		***************/

    /* NSLock:
    Ordinary, garden variety lock.  Use this if in doubt. 
    Best protection for critical sections that do system calls or heavy computation.  
    Threads will sleep if they cannot immediately acquire the lock
    
    NSLock  *glob = [NSLock new];       // done once!
    [glob lock];
    ... long time of fussing with global data
    [glob unlock];
    
    */
 
@interface NSLock:NSObject <NSLocking> {
    void    *_priv;
}

- (BOOL)tryLock;
    /* Returns YES iff lock acquired; returns immediately */

@end

/***************	NSConditionLock		***************/

    /* NSConditionLock:
    Used to selectively release threads upon conditions
    
    Usage (Producer):
    
    id condLock = [NSConditionLock new];
    [condLock lock];
    ...manipulate global data...
    [condLock unlockWithCondition:NEW_STATE];
    
    Usage (Consumer):
    
    ...The following sleeps until the producer does the unlockWithCondition: such
    that DESIRED_STATE == NEW_STATE.
    [condLock lockWhenCondition:DESIRED_STATE];
    ...manipulate global data if necessary...
    [condLock unlock];
    
    ...OR...
    
    [condLock lockWhenCondition:DESIRED_STATE];
    ...manipulate global data if necessary, then notify other lock users of change of state.
    [condLock unlockWithCondition:NEW_STATE];
    
    The value of 'condition' is user-dependent.
    
    All 4 combinations of {lock,lockWhenCondition} and {unlock,unlockWithCondition} are legal, i.e.,
    
    */

@interface NSConditionLock:NSObject <NSLocking> {
    void    *_priv;
}

- (id)initWithCondition:(int)condition;
    // init & set condition variable
    
- (int)condition;

- (void)lockWhenCondition:(int)condition;
    // acquire lock when conditionVar == condition
       
- (BOOL)tryLock;
    /* Returns YES iff lock acquired; returns immediately */

- (BOOL)tryLockWhenCondition:(int)condition;
    // acquire lock when conditionVar == condition
    
- (void)unlockWithCondition:(int)condition;
    // release lock and update conditionVar
    
@end

/***************	NSRecursiveLock		***************/

    /* NSRecursiveLock:
    used for locks that need to be reacquired by the same thread 
    
    NSRecursiveLock  *glob = [NSRecursiveLock new];       // done once!
    [glob lock];
    ... long time of fussing with global data
    
    [glob lock] from some interior routine
    [glob unlock] 
    
    [glob unlock];
    
    */
    
@interface NSRecursiveLock:NSObject <NSLocking> {
    void    *_priv;
}

- (BOOL)tryLock;
    /* Returns YES iff lock acquired; returns immediately */

@end
