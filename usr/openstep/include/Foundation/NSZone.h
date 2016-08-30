#ident "@(#) NSZone.h, Rev 1.5, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Allocation of large regions

#import <objc/objc.h>

#ifdef __cplusplus 
extern "C" {
#endif

/***************	NSZone definition		***************/

typedef struct _NSZone NSZone;

/***************	Operations on zones		***************/

extern NSZone *NSDefaultMallocZone(void);
    /* Returns the default zone used by the malloc(3) calls. */

extern NSZone *NSCreateZone(unsigned startSize, unsigned granularity, BOOL canFree);
    /* Create a new zone with its own memory pool. If canfree is 0 the allocator will never free memory and mallocing will be fast */

extern void NSRecycleZone(NSZone *zone);
    /* Adds the pages still in use to the default zone */
	
/*
 * Note: Prototypes of zone functions returning NSStrings have been moved to 
 *  NSObject.h, to avoid problems with recursive includes and
 *  protocol warnings.
*/

/***************	Operations on pointers in zones		***********/

extern void *NSZoneMalloc(NSZone *zone, unsigned size);
    /* Allocates in zone; NULL zone => default zone is used */

extern void *NSZoneRealloc(NSZone *zone, void *ptr, unsigned size);
    /* Resizes in zone; ptr passed in may be NULL; NULL zone => default zone is used */

extern void NSZoneFree(NSZone *zone, void *ptr);
    /* Recycles the memory; NULL zone => default zone is used */

extern void *NSZoneCalloc(NSZone *zone, unsigned numElems, unsigned byteSize);
    /* Like NSZoneMalloc and then bzero; NULL zone => default zone is used */

extern NSZone *NSZoneFromPointer(void *ptr);
    /* Returns the zone for a malloced or realloced pointer, NULL if not in any zone. */

/***************	Low level VM primitives		***************/

/* IMPORTANT NOTE: NSZone and NSData use the following primitives to hide functionality like copy-on-write and large block allocation and should be preferred to calling directly these functions */

extern unsigned NSPageSize(void);
    /* Page size in bytes */

extern unsigned NSLogPageSize(void);
    /* Binary log of the page size in bytes */

extern unsigned NSRoundUpToMultipleOfPageSize(unsigned bytes);
    /* As name says; given 1 will return NSPageSize() */
    
extern unsigned NSRoundDownToMultipleOfPageSize(unsigned bytes);
    /* As name says; given NSPageSize()-1 will return 0 */

extern void *NSAllocateMemoryPages(unsigned bytes);
    /* Allocates an integral number of pages;
    pages are guranteed to be zero-filled */

extern void NSDeallocateMemoryPages(void *ptr, unsigned bytes);
    /* Deallocates memory allocated with NSAllocateMemoryPages() */

extern void NSCopyMemoryPages(const void *source, void *dest, unsigned bytes);
    /* Copies or copies-on-write; raises if error */

extern unsigned NSRealMemoryAvailable(void);
    /* Some DB algorithm require this hint */
#ifdef __cplusplus 
}
#endif
