#ident "@(#) NSAutoreleasePool.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Autoreleasing

#import <Foundation/NSObject.h>

/***************	Autorelease pool		***************/

/*
	New pools are created and freed using the usual idioms (alloc/init
	and release).  When freed, the pool releases all the object in it
	(added with addObject:).  Autorelease pools are automatically
	associated with a thread.  Each newly created pool is 'stacked' in
	the current pool for that thread.  A pool that is in the middle of the
	stack that is freed causes every other pool higher in the stack to be
	released and diassociated with the stack.  This can happen if an
	execption breaks the normal allocation-release pairing without
	requiring explicit exception handler code for the release.
*/

@interface NSAutoreleasePool:NSObject {
    /* Should not be subclassed (because of optimized allocation) */
    @private
    unsigned			lastThread;
    NSAutoreleasePool	*parentPool;
    unsigned			countToBeReleased;
    unsigned			maxToBeReleased;
    id					*toBeFreed;
}

+ (void)addObject:(id)anObject;
	/* Notes that anObject should be released when the pool
	   at the current top of the stack is freed
	 */

- (void)addObject:(id)anObject;
	/* Notes that anObject must be released when pool is freed */


#ifndef STRICT_OPENSTEP

/***************	Debug helpers		***************/

+ (void)enableDoubleReleaseCheck:(BOOL)enable;
	/* When enabled, -release and -autorelease calls are checking whether
	   this object has been released too many times.  This is done by
	   searching all the pools, and makes programs run very slowly;
	   It is off by default
	 */
    
+ (void)enableRelease:(BOOL)enable;
	/* When disabled, nothing added to pools is really released;
	   This makes your VM grow ...
	   By default release is enabled
	 */

+ (void)setPoolCountThreshold:(unsigned)count;
	/* Useful to investigate why so many things are autoreleased;
	   When enabled and the pool reaches a multiple of trash it will
	   call a well-known method (indicated in the console).  Under
	   the debugger, break on that method if you want to investigate;
	   use 0 to disable;
	   By default release is disabled
	 */

+ (unsigned)totalAutoreleasedObjects;
	/* since the beginning of time, or since resetTotalAutoreleasedObjects */
    
+ (void)resetTotalAutoreleasedObjects;

+ (void)showPools;
	/* Shows all the pools */

+ (void)showPoolsWithObjectIdenticalTo:(id)object;
	/* Shows all the pools containing object, and the number of references */

#endif

@end

