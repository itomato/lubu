#ident "@(#) NSHashTable.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Scalable hash table

#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>

#ifdef __cplusplus
extern "C" {
#endif

/* This module implements sets of pointers - or arbitrary pointer-sized data. API is in terms of pure C Functions for the rare but important cases where maximum speed is key.  Use NSSet for representing non performance-critical sets of objects.  Specialization is done through allocation call-backs.  Hash tables double in size when they start becoming full, guaranteeing both average constant time access and linear size. */

/***************	Data structures		***********/

typedef struct _NSHashTable NSHashTable;

typedef struct {
    unsigned	(*hash)(NSHashTable *table, const void *);
    BOOL	(*isEqual)(NSHashTable *table, const void *, const void *);
    void	(*retain)(NSHashTable *table, const void *);
    void	(*release)(NSHashTable *table, void *);
    NSString 	*(*describe)(NSHashTable *table, const void *);
} NSHashTableCallBacks;
    
/* Invariants assumed by the implementation: 
	1 - hash(pointer) must remain invariant over time;
	e.g. if pointer designated a mutable string, the string must not be changed
	2- isEqual(pointer1, pointer2) => hash(pointer1) == hash(pointer2); */

typedef struct {unsigned _pi; unsigned _si; void *_bs;} NSHashEnumerator;
    /* callers should not rely on actual contents of the struct */

/***************	Global table manipulation		***********/

extern NSHashTable *NSCreateHashTableWithZone(NSHashTableCallBacks callBacks, unsigned capacity, NSZone *zone);
    /* if hash is NULL, pointer hash is assumed;
    if isEqual is NULL, pointer equality is assumed;
    if retain is NULL, no call back upon addition in table;
    if release is NULL, no call back upon removal in table;
    if describe is NULL, the hex value is used when describing;
    capacity is only a hint; 0 creates a small table;
    zone may be NULL, implying default zone */

extern NSHashTable *NSCreateHashTable(NSHashTableCallBacks callBacks, unsigned capacity);
    /* Same but in the default zone */

extern void NSFreeHashTable(NSHashTable *table);
    /* calls release for each item, and recovers table */
	
extern void NSResetHashTable(NSHashTable *table);
    /* calls release for each item; keeps current capacity */

extern BOOL NSCompareHashTables(NSHashTable *table1, NSHashTable *table2);
    /* Returns YES if the two sets are equal (each member of table1 in table2, and table have same size) */

extern NSHashTable *NSCopyHashTableWithZone(NSHashTable *table, NSZone *zone);
    /* makes a new table, and inserts each item in that new table;
    zone may be NULL, implying default zone  */
	
/***************	Accessing items in table		***********/

extern void *NSHashGet(NSHashTable *table, const void *pointer);
    /* return original table pointer or NULL.  */

extern void NSHashInsert(NSHashTable *table, const void *pointer);
    /* insert pointer in table; pointer cannot be NULL;
    previous pointer is released using call back. */
	
extern void NSHashInsertKnownAbsent(NSHashTable *table, const void *pointer);
    /* insert pointer in table; pointer cannot be NULL;
    Raises if there was already a matching item. */
	
extern void *NSHashInsertIfAbsent(NSHashTable *table, const void *pointer);
    /* If pointer not already in table adds pointer to table and returns NULL; else returns previous */

extern void NSHashRemove(NSHashTable *table, const void *pointer);
    /* previous pointer is released */

extern NSHashEnumerator NSEnumerateHashTable(NSHashTable *table);
    /* Returns an enumerator struct for all the table items; 
    Example of use:
	unsigned		count = 0;
	MyPointer		*pointer;
	NSHashEnumerator	enumerator = NSEnumerateHashTable(table);
	while (pointer = NSNextHashEnumeratorItem(&enumerator)) {
	    count++;
	}
    */

extern void *NSNextHashEnumeratorItem(NSHashEnumerator *enumerator);
    /* Returns the next item in table for enumerator, NULL if none left */
    
extern unsigned NSCountHashTable(NSHashTable *table);
    /* current number of items in table */

extern NSString *NSStringFromHashTable(NSHashTable *table);
    /* Applies the describe call-back to obtain a human readable description */

extern NSArray *NSAllHashTableObjects(NSHashTable *table);
    /* Returns an array of all objects in table;  
    Should only be called when table items are objects */

/***************	Common call backs		***********/

/* You can make your own call back by picking fields among the following call backs */

extern const NSHashTableCallBacks NSIntHashCallBacks;
    /* For sets of pointer-sized quantities or samller (i.e. ints, longs, unichar, ...);
    {NULL, NULL, NULL, NULL, NULL} */

extern const NSHashTableCallBacks NSNonOwnedPointerHashCallBacks;
    /* For sets of pointers, hashed by address;
    {NULL, NULL, NULL, NULL, NULL} */

extern const NSHashTableCallBacks NSOwnedPointerHashCallBacks;
    /* For sets of pointers, with transfer of ownership upon insertion;
    {NULL, NULL, NULL, free(), NULL} */

extern const NSHashTableCallBacks NSPointerToStructHashCallBacks;
    /* For sets of pointers to structs, when the first field of the struct is int-sized;
    {hash of (*pointer), identity of (*pointer), NULL, free(), NULL} */

extern const NSHashTableCallBacks NSObjectHashCallBacks;
    /* For sets of objects; Similar to NSSet;
    {-hash, -isEqual:, -retain, -release, -description} */

extern const NSHashTableCallBacks NSNonRetainedObjectHashCallBacks;
    /* For sets of objects, but without retaining/releasing;
    {-hash, -isEqual:, NULL, NULL, -description} */

extern const NSHashTableCallBacks NSOwnedObjectIdentityHashCallBacks;
    /*For a set that owns the objects but uses pointer comparison;
      {NULL,NULL,-retain,-release,-description} */

#ifdef __cplusplus
}
#endif
