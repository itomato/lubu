#ident "@(#) NSMapTable.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Scalable hash table for mapping keys to values

#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>

#ifdef __cplusplus
extern "C" {
#endif

/* This module implements hashing of arbitrary associations [key -> value].  Keys and values must be pointers - or arbitrary pointer-sized data. API is in terms of pure C Functions for the rare but important cases where maximum speed is key.  Use NSDictionary for representing non performance-critical associations of objects.  Specialization is done through allocation call-backs.  A special marker is necessary for efficient implementation, and can be set.  Map tables double in size when they start becoming full, guaranteeing both average constant time access and linear size. */

#define NSNotAnIntMapKey	((const void *)0x80000000)
#define NSNotAPointerMapKey	((const void *)0xffffffff)

/***************	Data structures		***********/

typedef struct _NSMapTable NSMapTable;

typedef unsigned  (*NSMapTableKeyCallbackHash_t)(NSMapTable *table, const void *);
typedef BOOL	  (*NSMapTableKeyCallbackIsEqual_t)(NSMapTable *table, const void *, const void *);
typedef void	  (*NSMapTableKeyCallbackRetain_t)(NSMapTable *table, const void *);
typedef void	  (*NSMapTableKeyCallbackRelease_t)(NSMapTable *table, void *);
typedef NSString  *(*NSMapTableKeyCallbackDescribe_t)(NSMapTable *table, const void *);

typedef struct {
    NSMapTableKeyCallbackHash_t		hash;
    NSMapTableKeyCallbackIsEqual_t	isEqual;
    NSMapTableKeyCallbackRetain_t	retain;
    NSMapTableKeyCallbackRelease_t	release;
    NSMapTableKeyCallbackDescribe_t	describe;
    const void	*notAKeyMarker; // not a call back; just something that can't be a key; necessary for efficient implementation
} NSMapTableKeyCallBacks;
    
/* Invariants assumed by the implementation: 
	1 - hash(pointer) must remain invariant over time;
	e.g. if pointer designated a mutable string, the string must not be changed
	2- isEqual(pointer1, pointer2) => hash(pointer1) == hash(pointer2); */

typedef    void	     (*NSMapTableValueCallbackRetain_t)(NSMapTable *table, const void *);
typedef    void	     (*NSMapTableValueCallbackRelease_t)(NSMapTable *table, void *);
typedef    NSString *(*NSMapTableValueCallbackDescribe_t)(NSMapTable *table, const void *);

typedef struct {
    NSMapTableValueCallbackRetain_t	retain;
    NSMapTableValueCallbackRelease_t	release;
    NSMapTableValueCallbackDescribe_t	describe;
} NSMapTableValueCallBacks;
    
typedef struct {unsigned _pi; void *_nk; void *_bs;} NSMapEnumerator;
    /* callers should not rely on actual contents of the struct */

/***************	Global table manipulation		***********/

extern NSMapTable *NSCreateMapTableWithZone(NSMapTableKeyCallBacks keyCallBacks, NSMapTableValueCallBacks valueCallBacks, unsigned capacity, NSZone *zone);
    /* if hash is NULL, pointer hash is assumed;
    if isEqual is NULL, pointer equality is assumed;
    if retainKey is NULL, no call back upon addition in table;
    if releaseKey is NULL, no call back upon removal in table;
    if describeKey is NULL, the hex value is used when describing;
    notAKeyMarker should be never be the same as a possible key.  Good values are 0 when 0 is not expected to be a key, or NSNotAPointerMapKey that can never be the address of a pointer.
    if retainValue is NULL, no call back upon addition in table;
    if releaseValue is NULL, no call back upon removal in table;
    if describeValue is NULL, the hex value is used when describing;
    capacity is only a hint; 0 creates a small table;
    zone may be NULL, implying default zone */

extern NSMapTable *NSCreateMapTable(NSMapTableKeyCallBacks keyCallBacks, NSMapTableValueCallBacks valueCallBacks, unsigned capacity);
    /* Same but in the default zone */

extern void NSFreeMapTable(NSMapTable *table);
    /* calls release for each key and value, and recovers table */
	
extern void NSResetMapTable(NSMapTable *table);
    /* calls release for each key and value; keeps current capacity */

extern BOOL NSCompareMapTables(NSMapTable *table1, NSMapTable *table2);
    /* Returns YES if the two tables are equal (each member of table1 in table2, and table have same size); Attention: does not compare values! */

extern NSMapTable *NSCopyMapTableWithZone(NSMapTable *table, NSZone *zone);
    /* makes a new table, and inserts each item in that new table;
    zone may be NULL, implying default zone  */

/***************	Accessing items in table		***********/

extern BOOL NSMapMember(NSMapTable *table, const void *key, void **originalKey, void **value);
    /* return whether an equal key is found;.  
    If key is found, originalKey and value are set */

extern void *NSMapGet(NSMapTable *table, const void *key);
    /* return table value or NULL.  */

extern void NSMapInsert(NSMapTable *table, const void *key, const void *value);
    /* insert key in table; key cannot be notAKeyMarker;
    previous key and value are released using call back. */
	
extern void NSMapInsertKnownAbsent(NSMapTable *table, const void *key, const void *value);
    /* insert key in table; key cannot be notAKeyMarker;
    Raises if there was already a matching key. */
	
extern void *NSMapInsertIfAbsent(NSMapTable *table, const void *key, const void *value);
    /* If key not already in table adds key value to table and returns NULL, else returns original key. */

extern void NSMapRemove(NSMapTable *table, const void *key);
    /* previous key and value are released */

extern NSMapEnumerator NSEnumerateMapTable(NSMapTable *table);
    /* Returns an enumerator struct for all the table items; 
    Example of use:
	unsigned	count = 0;
	MyKey		*key;
	MyValue		*value;
	NSMapEnumerator	enumerator = NSEnumerateMapTable(table);
	while (NSNextMapEnumeratorPair(&enumerator, &key, &value)) {
	    count++;
	}
    */

extern BOOL NSNextMapEnumeratorPair(NSMapEnumerator *enumerator, void **key, void **value);
    /* Returns YES if next key value pair set; */
    
extern unsigned NSCountMapTable(NSMapTable *table);
    /* current number of items in table */

extern NSString *NSStringFromMapTable(NSMapTable *table);
    /* Applies the describe call-backs to obtain a human readable description */

extern NSArray *NSAllMapTableKeys(NSMapTable *table);
    /* Returns an array of all objects in table;  
    Should only be called when table keys are objects */

extern NSArray *NSAllMapTableValues(NSMapTable *table);
    /* Returns an array of all objects in table;  
    Should only be called when table values are objects */

/***************	Common key call backs		***********/

/* You can make your own call back by picking fields among the following call backs */

extern const NSMapTableKeyCallBacks NSIntMapKeyCallBacks;
    /* For keys that are pointer-sized quantities or samller (i.e. ints, longs, unichar, ...);
    0 permissible in table (but not NSNotAnIntMapKey);
    {NULL, NULL, NULL, NULL, NULL, NSNotAnIntMapKey} */

extern const NSMapTableKeyCallBacks NSNonOwnedPointerMapKeyCallBacks;
    /* For keys that are pointers not freed;
    {NULL, NULL, NULL, NULL, NULL, 0} */

extern const NSMapTableKeyCallBacks NSNonOwnedPointerOrNullMapKeyCallBacks;
    /* For keys that are pointers not freed, or NULL;
    {NULL, NULL, NULL, NULL, NULL, NSNotAPointerMapKey} */

extern const NSMapTableKeyCallBacks NSOwnedPointerMapKeyCallBacks;
    /* For keys that are pointers, with transfer of ownership upon insertion;
    {NULL, NULL, NULL, free(), NULL, 0} */

extern const NSMapTableKeyCallBacks NSObjectMapKeyCallBacks;
    /* For keys that are objects;
    {-hash, -isEqual:, -retain, -release, -description, 0} */

extern const NSMapTableKeyCallBacks NSNonRetainedObjectMapKeyCallBacks;
    /* For sets of objects, but without retaining/releasing;
    {-hash, -isEqual:, NULL, NULL, -description, 0} */

/***************	Common value call backs		***********/

extern const NSMapTableValueCallBacks NSIntMapValueCallBacks;
    /* For values that are pointer-sized quantities (i.e. ints);
    {NULL, NULL, NULL} */

extern const NSMapTableValueCallBacks NSNonOwnedPointerMapValueCallBacks;
    /* For values that are not owned pointers;
    {NULL, NULL, NULL} */

extern const NSMapTableValueCallBacks NSOwnedPointerMapValueCallBacks;
    /* For values that are owned pointers;
    {NULL, free(), NULL} */

extern const NSMapTableValueCallBacks NSObjectMapValueCallBacks;
    /* For values that are objects;
    {-retain, -release, -description} */

extern const NSMapTableValueCallBacks NSNonRetainedObjectMapValueCallBacks;
    /* For values that are objects, which should be ratained;
    {NULL, NULL, -description} */

#ifdef __cplusplus
}
#endif
