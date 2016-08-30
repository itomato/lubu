#ident "@(#) NSDictionary.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Basic dictionary collection

#import <Foundation/NSArray.h>

/* This module implement the 'dictionary' concept.  Featuring:
    - dictionaries are always dynamic (resize themselves by doubling when they reach a certain maximum), so that callers never have to think about allocation;
    - support read only dictionaries;
    - embeds various conveniences;
    
   Generic coding behavior is supplied
    - it preserves class
    - immutable dictionaries are distributed bycopy with their elements also bycopy
    - mutable dictionaries are distributed by reference unless asked bycopy
*/

/***************	Read Only Abstract Class		***********/

@interface NSDictionary:NSObject <NSCopying, NSMutableCopying, NSCoding>
/* NOTES:
    -copyWithZone: and -copy guarantee an immutable returned value;
    	elements are recursively copied with -copyWithZone:
    -isEqual: checks that argument is an NSDictionary;
	If conforming, each item is compared using isEqual:;
    -hash is such that [x isEqual:y] => [x hash] == [y hash];    
     */

- (unsigned)count;
    /* Number of (key,associated object) pairs in the dictionary  */
    
- (id)objectForKey:(id)aKey;
    /* Get associated object given its key;
    may return nil */

- (NSEnumerator *)keyEnumerator;
    /* Returns an enumerator object to cycle through the keys.
    Note that an object enumerator is also available (see below).
    Updates should not be done during enumeration
    To use:
    	NSEnumerator	*enumerator = [collection keyEnumerator];
	id key;
	while (key = [enumerator nextObject]) {
	    ... 
	}
    */
  
@end

@interface NSDictionary (NSExtendedDictionary)

- (BOOL)isEqualToDictionary:(NSDictionary *)other;
    /* Compares 2 dictionaries for exact match;
    Uses isEqual: for comparison predicate; */

- (NSString *)description;
    /* Convert to a string, using the "PropertyList" format */

- (NSString *)descriptionWithLocale:(NSDictionary *)locale;
- (NSString *)descriptionWithLocale:(NSDictionary *)locale indent:(unsigned)level;
    /* Convert to a string, using the "PropertyList" format;
    locale specifies options for formatting, nil for none;
    indent is for human-readibility;
    level==0 means top level; level==1 => 4 spaces */

- (NSArray *)allKeys;
    /* returns an array containing all the keys;
    This snapshots the set of keys;
    Order is un-defined; */

- (NSArray *)allValues;
    /* returns an array containing all the associated objects;
    This snapshots the set of objects;
    Order is un-defined */

- (NSArray *)allKeysForObject:(id)anObject;
    /* Returns all keys for which corresponding object isEqual: given argument;
    Enumerates the dictionary (=> slow, O(N));
    Returns nil if none; otherwise an array of count >= 1 */
    
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
    /* writes a Property List string representation */

- (NSEnumerator *)objectEnumerator;
    /* Returns an enumerator object to cycle through the keys.
    Note that a key enumerator is available as the primitive.
    Updates should not be done during enumeration
    To use:
    	NSEnumerator	*enumerator = [collection objectEnumerator];
	id object;
	
	while (object = [enumerator nextObject])
	    ... 
    */

@end

/***************	Mutable Abstract Class		***********/

@interface NSMutableDictionary: NSDictionary

- (void)setObject:(id)anObject forKey:(id)aKey;
    /* Associate an object for a certain key; 
    If object is nil an exception is raised.
    -retain is applied to the object inserted in the array.
    and -release is applied to previous element, if any;
    The key is always copied using -copy by the dictionary */
    
- (void)removeObjectForKey:(id)aKey;
    /* Removes key and associated object from the dictionary;
    Performs -release on previous object if any. */
    
@end

@interface NSMutableDictionary (NSExtendedMutableDictionary)

- (void)removeAllObjects;
    /* Empties the dictionary; 
    Performs -release on each object removed */

- (void)removeObjectsForKeys:(NSArray *)keyArray;
    /* Removes keys and associated objects from the dictionary */
    
- (void)addEntriesFromDictionary:(NSDictionary *)otherDictionary;
    /* inserts all the pairs of other; 
    in case of pairs with same keys, other's pairs win */

- (void)setDictionary:(NSDictionary *)otherDictionary;
    /* replaces all pairs by pairs from otherDictionary; can be optimized by specific classes */

@end

/***************	Immutable Dictionary Creation		***********/

@interface NSDictionary (NSDictionaryCreation)

+ (id)allocWithZone:(NSZone *)zone;
    /* Create an uninitialized instance of a concrete dictionary;
    substitutes a concrete class if called with NSDictionary;
    +alloc can also be used to that effect */
     
+ (id)dictionary;
    /* Creates an autoreleased empty dictionary */
    
+ (id)dictionaryWithObjects:(id *)objects forKeys:(id *)keys count:(unsigned)count;
    /* Creates an autoreleased dictionary */

+ (id)dictionaryWithObjects:(NSArray *)objects forKeys:(NSArray *)keys;
    /* objects and keys must have the same number of items;
    All keys must be strings;
    Creates an autoreleased dictionary */

+ (id)dictionaryWithObjectsAndKeys:(id)firstObject, ...;
    /* Arguments should be an even number <object>1 <key>1 ... <object>n <key>n FOLLOWED BY nil */

+ (id)dictionaryWithContentsOfFile:(NSString *)path;
    /* reads a Property List string representation;
    returns nil on file error or if not a dictionary */

#ifndef STRICT_OPENSTEP
+ (id)dictionaryWithDictionary:(NSDictionary *)dict;
    /* Creates an autoreleased copy of dict */
+ (id)dictionaryWithObject:(id)anObject forKey:(id)aKey;
    /* creates an autoreleased dictionary with the given key and value */
#endif

- (id)initWithObjects:(id *)objects forKeys:(id *)keys count:(unsigned)count;
    /* Designated initializer for immutable dictionaries */

- (id)initWithObjects:(NSArray *)objects forKeys:(NSArray *)keys;
    /* objects and keys must have the same number of items;
    All keys must be strings */

- (id)initWithObjectsAndKeys:(id)firstObject, ...;
    /* Arguments should be an even number <object>1 <key>1 ... <object>n <key>n FOLLOWED BY nil */

- (id)initWithDictionary:(NSDictionary *)otherDictionary;
    /* Performs -retain for each item in otherDictionary */

- (id)initWithContentsOfFile:(NSString *)path;
    /* reads a Property List string representation;
    returns nil on file error or if not a dictionary */

@end

/***************	NSMutableDictionary creation		***********/

@interface NSMutableDictionary (NSMutableDictionaryCreation)

+ (id)allocWithZone:(NSZone *)zone;
    /* Create an uninitialized instance of a concrete dictionary;
    substitutes a concrete class if called with NSMutableDictionary;
    +alloc can also be used to that effect;
    -dealloc empties dictionary using -removeAllObjects before de-allocating */
     
+ (id)dictionaryWithCapacity:(unsigned)numItems;
    /* Creates an autoreleased mutable dictionary */

- (id)initWithCapacity:(unsigned)numItems;
    /* Designated initializer for mutable dictionaries */

@end



@interface NSDictionary (NSDictionaryOpenStepExtension)
 
- (NSArray *)objectsForKeys:(NSArray *)keys notFoundMarker:(id)marker;
    // Given an array of keys, fills the corresponding array of corresponding 
    // objects.  If the object is not present, marker is used instead.  Marker 
    // cannot be set to nil, because arrays can't contain nil.  Common 
    // marker: @"".
 
@end

