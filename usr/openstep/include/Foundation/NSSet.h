#ident "@(#) NSSet.h, Rev 1.5, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Hashed sets of objects

#import <Foundation/NSArray.h>

/* This module implement the 'set' concept.  Set elements are assumed to respond to -hash and isEqual: in order to ensure fast access.
Featuring:
    - hashed for efficiency;
    - sets are always dynamic (resize themselves by doubling when they reach a certain maximum), so that callers never have to think about allocation;
    - support for read only sets;
*/

/***************	Read only Abstract Class		***********/

@interface NSSet:NSObject <NSCopying, NSMutableCopying, NSCoding>

/* NOTES:
    -copyWithZone: and -copy guarantee an immutable returned value;
    	elements are recursively copied with -copyWithZone:
    -isEqual: checks that argument is an NSSet;
	If conforming, each item is compared using isEqual:;
    -hash is such that [x isEqual:y] => [x hash] == [y hash];  
    
    A generic coding implementation is provided.  For distribution, sets
    	go bycopy as do their elements.  Mutable sets go by reference,
	unless asked to go bycopy.
     */

- (unsigned)count;
    /* Number of items in set */

- (id)member:(id)object;
    /* Return the object in the set that is isEqual: to argument, nil if none;
    O(1) execution time */

- (NSEnumerator *)objectEnumerator;
    /* Returns an enumerator object to cycle through the contents
    Updates should not be done during enumeration
    To use:
    	NSEnumerator	*enumerator = [collection objectEnumerator];
	id	object;
	while (object = [enumerator nextObject]) {
	    ... 
	}
    */

@end

@interface NSSet (NSExtendedSet)

- (BOOL)isSubsetOfSet:(NSSet *)other;
    /* removes the ones not in other */

- (BOOL)intersectsSet:(NSSet *)other;
    /* returns YES if the sets share any elements */

- (void)makeObjectsPerform:(SEL)selector;
- (void)makeObjectsPerform:(SEL)selector withObject:(id)argument;

- (NSString *)description;
- (NSString *)descriptionWithLocale:(NSDictionary *)locale;

- (NSArray *)allObjects;
    /* returns an array containing all the objects;
    This snapshots the set */

- (id)anyObject;
    /* any member of the set.  nil if set is empty */
    
- (BOOL)containsObject:(id)anObject;
    /* short cut for [self member:anObject] != nil;
    Faster (in O(1)) than the NSArray version (in O(N)) */
    
- (BOOL)isEqualToSet:(NSSet *)otherSet;

@end

/***************	Mutable protocol		***********/

@interface NSMutableSet:NSSet

- (void)addObject:(id)object;
    /* Adds object to set if it was not already there; no effect otherwise;
    Performs -retain on object when added;
    O(1) execution time */

- (void)removeObject:(id)object;
    /* Removes object from set if it was there; no effect otherwise;
    Performs -release on object removed, if any;
    O(1) execution time */

@end

@interface NSMutableSet (NSExtendedMutableSet)

- (void)removeAllObjects;
    /* Empties the set;
    Applies -release to each removed object */

- (void)unionSet:(NSSet *)other;
    /* Multiple addObject: */

- (void)minusSet:(NSSet *)other;
    /* Multiple removeObject: */

- (void)intersectSet:(NSSet *)other;
    /* removes the ones not in other */

- (void)addObjectsFromArray:(NSArray *)array;
    /* multiple addObject: */

@end

/***************	Immutable Creation		***********/

@interface NSSet (NSSetCreation)

+ (id)allocWithZone:(NSZone *)zone;
    /* Create an uninitialized instance of a concrete class;
    substitutes a concrete class if called with NSSet;
    +alloc can also be used to that effect */
     
+ (id)set;
    /* convenience to create an autoreleased empty set */

+ (id)setWithObject:(id)object;
    /* convenience to create an autoreleased set with just 1 element */

+ (id)setWithObjects:(id)firstObj, ...;
    /* convenience to create an autoreleased set */

+ (id)setWithArray:(NSArray *)array;

- (id)initWithObjects:(id *)objects count:(unsigned)count;
    /* Designated initializer */

- (id)initWithSet:(NSSet *)set copyItems:(BOOL)flag;
    /* if flag makes immutable copies of each item in array */

- (id)initWithSet:(NSSet *)set;
    /* Performs -retain for each item in set */

- (id)initWithObjects:(id)firstObj, ...;
    /* Vararg list terminated with nil. */

- (id)initWithArray:(NSArray *)array;

@end

/***************	Mutable Creation		***********/

@interface NSMutableSet (NSMutableSetCreation)

+ (id)allocWithZone:(NSZone *)zone;
    /* Create an uninitialized instance of a concrete class;
    substitutes a concrete class if called with NSMutableSet;
    +alloc can also be used to that effect;
    -dealloc empties dictionary using -removeAllObjects before de-allocating */
     
+ (id)setWithCapacity:(unsigned)aNumItems;
    /* Creates an autoreleased mutable set */

- (id)initWithCapacity:(unsigned)aNumItems;
    
@end

/*******************   Counted Set    ***************************/

/* Counted set keeps track of the number of times objects are inserted
and requires that they are removed the same number of times.  This data
structure has been known elsewhere as a Bag.
- O(1) on insertion, removal, membership test
*/

@interface NSCountedSet:NSMutableSet {
    void	*impl;
}

+ (void)initialize;

- (id)initWithCapacity:(unsigned)numItems;

- (id)initWithArray:(NSArray *)array;
    /* Performs -retain for each item in array */

- (id)initWithSet:(NSSet *)set;
    /* Performs -retain for each item in set */

- (void)addObject:(id)object;
    /* Maintains a count of the number of times this (by isEqual:) object has been entered.  This count is available via countForObject:. */
    
- (void)removeObject:(id)object;
    /* decrements the count for the object. Removes the object when count reaches zero */

- (NSEnumerator *)objectEnumerator;
    /* An enumerator object is returned that will enumerate each object in the set once, independent of its count */

- (unsigned)countForObject:(id)object;

/*Needs to keep track of the count.*/

- (id)initWithCoder:(NSCoder *)decoder;
- (void)encodeWithCoder:(NSCoder *)encoder;

@end
