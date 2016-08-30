#ident "@(#) zone.h, Rev 2.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	All rights reserved.

#ifndef _OBJC_ZONE_H_
#define _OBJC_ZONE_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Interface to zone based malloc.
 */

typedef struct _NXZone {
    void *(*realloc)(struct _NXZone *zonep, void *ptr, size_t size);
    void *(*malloc)(struct _NXZone *zonep, size_t size);
    void (*free)(struct _NXZone *zonep, void *ptr);
    void (*destroy)(struct _NXZone *zonep);
      	/* Implementation specific entries */
      	/* Do not depend on the size of this structure */
} NXZone;

#define NX_NOZONE  ((NXZone *)0)

/*
 * Returns the default zone used by the malloc(3) calls.
 */
extern NXZone *NXDefaultMallocZone(void);

/* 
 * Create a new zone with its own memory pool.
 * If canfree is 0 the allocator will never free memory and mallocing will be fast
 */
extern NXZone *NXCreateZone(size_t startSize, size_t granularity, int canFree);

/*
 * Create a new zone who obtains memory from another zone.
 * Returns NX_NOZONE if the passed zone is already a child.
 */
extern NXZone  *NXCreateChildZone(NXZone *parentZone, size_t startSize, size_t granularity, int canFree);

/*
 * The zone is destroyed and all memory reclaimed.
 */
#define NXDestroyZone(zonep) \
	((*(zonep)->destroy)(zonep))
	
/*
 * Will merge zone with the parent zone. Malloced areas are still valid.
 * Must be an child zone.
 */
extern void NXMergeZone(NXZone *zonep);

/* jjh 7feb95
 * The following casts to _NXZone * solves the problem that objects based on
 * NSObject have a NSZone zone instance var.  This is passed as zonep
 * to the following macros.  But, The NSZone struct is not defined in
 * the .h file so the func ptrs it contains are hidden.
 * The following will work, but only because currently, the NSZone
 * struct  isn't actually used for anything.  All the NSZone mallocing
 * is done by calling the old NXZone routines.
 */


#define NXZoneMalloc(zonep, size) \
	((*( (struct _NXZone *)zonep )->malloc)(zonep, size))

#define NXZoneRealloc(zonep, ptr, size) \
	((*( (struct _NXZone *)zonep )->realloc)(zonep, ptr, size))
	
#define NXZoneFree(zonep, ptr) \
	((*( (struct _NXZone *)zonep )->free)(zonep, ptr))

/*
 * Calls NXZoneMalloc and then bzero.
 */
extern void *NXZoneCalloc(NXZone *zonep, size_t numElems, size_t byteSize);

/*
 * Returns the zone for a pointer.
 * NX_NOZONE if not in any zone.
 * The ptr must have been returned from a malloc or realloc call.
 */
extern NXZone *NXZoneFromPtr(void *ptr);

/*
 * Debugging Helpers.
 */
 
 /*  
  * Will print to stdout if this pointer is in the malloc heap, free status, and size.
  */
extern void NXZonePtrInfo(void *ptr);

/*
 * Will verify all internal malloc information.
 * This is what malloc_debug calls.
 */
extern int NXMallocCheck(void);

/*
 * Give a zone a name.
 *
 * The string will be copied.
 */
extern void NXNameZone(NXZone *z, const char *name);

/*
 * Internal functions
 */
extern size_t malloc_size(void *);
extern int    malloc_debug(int level);

#ifdef __cplusplus
}
#endif

#endif 	/* _OBJC_ZONE_H_ */
