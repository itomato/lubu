#ident "@(#) NSArray.h, Rev 1.9, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Basic dynamic array

#import <Foundation/NSString.h>

/* This module implement the 'array' concept.  Featuring:
    - arrays are always dynamic (resize themselves by doubling when they reach a certain maximum), so that callers never have to think about allocation;
    - support read only arrays;
    - embeds various conveniences and algorithms (e.g. sort);
    
   Generic coding behavior is supplied
    - it preserves class and calls initWithObjects:count:
    - immutable arrays are distributed bycopy with their elements also bycopy
    - mutable arrays are distributed by reference unless asked bycopy
*/

/***************	Read Only Abstract Class		***********/

@interface NSArray:NSObject <NSCopying, NSMutableCopying, NSCoding>
/* NOTES:
    -copyWithZone: and -copy guarantee an immutable returned value;
    	elements are recursively copied with -copyWithZone:
    -isEqual: checks that argument is an NSArray;
	If conforming, each item is compared using isEqual:;
    -hash is such that [x isEqual:y] => [x hash] == [y hash];    
     */

- (unsigned)count;
    /* Number of items in the array (NOT the maximum capacity of the array) */
    
- (id)objectAtIndex:(unsigned)index;
    /* Raises if index out of bounds;
    Clients can expect this method to be fast, in O(1) */
    
- (unsigned)indexOfObject:(id)anObject inRange:(NSRange)range;
- (unsigned)indexOfObjectIdenticalTo:(id)anObject inRange:(NSRange)range;
- (void)getObjects:(id *)buf;
- (void)getObjects:(id *)buf range:(NSRange)range;

@end

@interface NSArray (NSExtendedArray)

- (unsigned)indexOfObjectIdenticalTo:(id)anObject;
    /* Performs search on the array for candidate;
    pointer equality is used;
    Return NSNotFound iff not found */

- (unsigned)indexOfObject:(id)anObject;
    /* Performs search on the array for candidate;
    isEqual: equality is used;
    Return NSNotFound iff not found */

- (BOOL)containsObject:(id)anObject;
    /* short cut for indexOfObject: (isEqual: is used) */
    
- (BOOL)isEqualToArray:(NSArray *)otherArray;
    /* Compares 2 arrays for exact match;
    Uses isEqual: as the comparison predicate; */

- (id)lastObject;
    /* Returns nil if none */

- (void)makeObjectsPerform:(SEL)aSelector;
- (void)makeObjectsPerform:(SEL)aSelector withObject:(id)argument;
    
- (NSArray *)sortedArrayUsingSelector:(SEL)comparator;
    /* Returns a sorted array of references;
    Ascending sort.  Sort guarantees at most N*LOG(N) comparisons;
    (for N=2**P, at most (2**P)*(P-1)+1 comparisons)
    Performs comparator with 2 items to be compared ([item1 comparator:item2]);
    Comparison should return <0 if ascending >0 if descending 0 if same */
    
- (NSArray *)sortedArrayUsingFunction:(int (*)(id, id, void *))comparator context:(void *)context;
    /* Same except calls comparator with 3 arguments: 2 items to be compared and parameter */

- (NSString *)componentsJoinedByString:(NSString *)separator;
    /* The reverse of the componentsSeparatedByString: method in NSString.
    From the various parts, builds a complete string, with the separator
    in between each string. As a special case, if sent to an empty array, "" will be returned.
    It is an error for the array to contain any elements that aren't NSStrings. */

- (id)firstObjectCommonWithArray:(NSArray *)otherArray;
    /* Returns the first object in the receiver which occurs in the argument. */

- (NSArray *)subarrayWithRange:(NSRange)range;
    /* returns the restriction of self to range */

- (NSArray *)arrayByAddingObject:(id)object;
    /* Returns a new autoreleased array with one more object; slow - O(N) */
    
- (NSArray *)arrayByAddingObjectsFromArray:(NSArray *)otherArray;
    /* Returns a new autoreleased array; slow - O(N+P) */
    
- (NSEnumerator *)objectEnumerator;
    /* Returns an enumerator object to cycle through the contents,
    starting at the 0th element.
    Updates should not be done during enumeration
    To use:
    	NSEnumerator *enumerator = [collection objectEnumerator];
	id object;
	while (object = [enumerator nextObject]) {
	    ... 
	}
    */

- (NSEnumerator *)reverseObjectEnumerator;
    /* Returns an enumerator that enumerates objects starting at lastObject */

- (NSString *)description;
    /* Convert to a string, using the "PropertyList" format */

- (NSString *)descriptionWithLocale:(NSDictionary *)locale;
- (NSString *)descriptionWithLocale:(NSDictionary *)locale indent:(unsigned)level;
    /* Convert to a string, using the "PropertyList" format;
    locale specifies options for formatting, nil for none;
    indent is for human-readibility;
    level==0 means top level; level==1 => 4 spaces */

@end

/***************	Mutable Abstract Class		***************/

@interface NSMutableArray: NSArray

/* Note: Only the 3 first methods are necessary for the Array abstraction.  However, in order to enable subclasses to meaningfully implement certain functions (i.e. notification), all classes implementing the NSMutableArray should implement all 5 methods, and no method should call recursively any of the others */

- (void)addObject:(id)anObject;
    /* Appends element at end of array; Resizes if necessary;
    -retain is applied to the object inserted;
    If object is nil an exception is raised;
    Clients can expect this method to be fast, in O(1) */
    
- (void)replaceObjectAtIndex:(unsigned)index withObject:(id)anObject;
    /* Replaces any existing item;
    If object is nil an exception is raised.
    The object inserted in the array is the result of [object retain] 
    and -release is applied to previous element;
    Clients can expect this method to be fast, in O(1) */
    
- (void)removeLastObject;
    /* Removes from array; Raises if applied on an empty list.
    Applies -release to removed object;
    Clients can expect this method to be fast, in O(1) */    
    
- (void)insertObject:(id)anObject atIndex:(unsigned)index;
    /* Shifts the items after index to allow insertion;
    The object inserted in the array is the result of [object retain]
    Attention: this method is slow: only O(count) time is guaranteed */
    
- (void)removeObjectAtIndex:(unsigned)index;
    /* Recompacts the array after item has been removed;
    Applies -release to removed object;
    Attention: this method is slow: only O(count) time is guaranteed */
    
- (void)removeObjectsInRange:(NSRange)range;
- (void)removeObject:(id)anObject inRange:(NSRange)range;
- (void)removeObjectIdenticalTo:(id)anObject inRange:(NSRange)range;
- (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(NSArray *)otherArray;
- (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(NSArray *)otherArray range:(NSRange)otherRange;

@end

@interface NSMutableArray (NSExtendedMutableArray)
    
- (void)removeObjectIdenticalTo:(id)anObject;
    /* Removes all occurrences of candidate */

- (void)removeObject:(id)anObject;
    /* Removes all occurrences of candidate */

- (void)removeAllObjects;
    /* Removes all object froms the array; 
    Applies -release to each removed object */

- (void)addObjectsFromArray:(NSArray *)otherArray;
    /* adds each element in otherArray */

- (void)setArray:(NSArray *)otherArray;
    /* replaces all items by items from otherArray; can be optimized by specific classes */

- (void)removeObjectsFromIndices:(unsigned *)indices numIndices:(unsigned)count;
    /* Speed up of removeObjectAtIndex: for batches of indices;
    This method does not distribute and therefore should be used sparingly */

- (void)removeObjectsInArray:(NSArray *)otherArray;
    /* Assumes that all elements in otherArray respond to -hash and -isEqual:, 
    in order to very efficiently remove large sets of objects;
    This method does not distribute and therefore should be used sparingly */

- (void)sortUsingFunction:(int (*)(id, id, void *))compare context:(void *)context;
    /* In place sort; O(N * LOG(N)) */

- (void)sortUsingSelector:(SEL)comparator;
    /* In place sort; O(N * LOG(N)) */

@end

/***************	Array creation		***************/

@interface NSArray (NSArrayCreation)

+ (id)allocWithZone:(NSZone *)zone;
    /* Create an uninitialized instance of a concrete array;
    substitutes a concrete class if called with NSArray;
    +alloc can also be used to that effect */

+ (id)array;
    /* Creates an empty autoreleased array */

+ (id)arrayWithObject:(id)anObject;
    /* convenience to create an autoreleased array with just 1 element */

+ (id)arrayWithObjects:(id)firstObj, ...;
    /* convenience to create an autoreleased array */

+ (id)arrayWithObjects:(id *)objects count:(unsigned)count;
    /* convenience to create an autoreleased array */

- (id)initWithObjects:(id *)objects count:(unsigned)count;
    /* Objects are retained;
    Designated initializer for immutable arrays */

- (id)initWithObjects:(id)firstObj, ...;
    /* Vararg list terminated with nil. */

- (id)initWithArray:(NSArray *)array;
    /* Performs -retain: for each item in array */

@end

/***************	Mutable Array creation		***************/

@interface NSMutableArray (NSMutableArrayCreation)

+ (id)allocWithZone:(NSZone *)zone;
    /* Create an uninitialized instance of a concrete mutable array;
    substitutes a concrete class if called with NSMutableArray;
    +alloc can also be used to that effect;
    -dealloc empties array using -removeAllObjects before de-allocating */

+ (id)arrayWithCapacity:(unsigned)numItems;
    /* Creates an autoreleased mutable array */

- (id)initWithCapacity:(unsigned)numItems;
    /* Designated initializer for mutable arrays */

@end


@interface NSArray (NSArrayOpenStepExtension)
 
+ (id)arrayWithContentsOfFile:(NSString *)path;
    /* reads a Property List string representation;
    returns nil on file error or if not an array */
 
- (id)initWithContentsOfFile:(NSString *)path;
    /* reads a Property List string representation;
    returns nil on file error or if not an array */
 
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
    /* writes a Property List string representation */
 
@end

@interface NSArray (NSIncrementalSort)
 
- (NSArray *)sortedArrayUsingFunction:(int (*)(id, id, void *))compare context:(
void *)context hint:(NSData *)hint;
    // functionally same as the equivalent array method without hint;
    // Assumes objects respond to -hash
 
- (NSData *)sortedArrayHint;
    // should be called on a sorted array for later use in the above method
    // may return nil for un-interesting hints
 
@end


