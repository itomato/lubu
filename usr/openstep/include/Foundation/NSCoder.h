#ident "@(#) NSCoder.h, Rev 1.9, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Abstract class for serializing arbitrary objects

#import <Foundation/NSString.h>

/****************** Basic functionality **********************/

@interface NSCoder:NSObject

- (void)encodeValueOfObjCType:(const char *)type at:(const void *)addr;
    /* Serializes ObjC data; data must be passed by reference;
    Example:
 	[encoder encodeValueOfObjCType:@encode(typeof(item)) at:&item];
    */

- (void)encodeDataObject:(NSData *)data;
    /* Encodes an NSData.  Must be defined by subclasses.   */

- (void)decodeValueOfObjCType:(const char *)type at:(void *)data;
    /* Deserializes ObjC data; data is filled according to type;
    Contrary to normal conventions, decoded objects must be released by caller.
    Example:
	[decoder decodeValueOfObjCType:@encode(typeof(item)) at:&item];
    Decoded CStrings (char *)s must be free'd  
    */

- (NSData *)decodeDataObject;
    /* Returns an autoreleased NSData.  Must be defined by subclasses.   */

- (unsigned)versionForClassName:(NSString *)className;
    /* Returns the version stored in the encoding;
    May raise if class not encountered */

@end

/****************** Extended functionality **********************/

/* generic implementations are provided so that one can implement
   coding methods without needing to know the class of the coder */

@interface NSCoder (NSExtendedCoder)
    
- (void)encodeObject:(id)object;
    /* Shortcut for [self encodeValuesOfObjCTypes:@encode(typeof(object)) at:&object];
    object may be nil;
    Note however that some subclasses may have a more efficient encoding when using -encodeObject: and therefore that decoding must be done with -decodeObject  */

- (void)encodePropertyList:(id)aPropertyList;
    /* Encodes the property list serialized as an NSData.
    Note however that some subclasses may have a more efficient encoding when using -encodePropertyList: and therefore that decoding must be done with -decodePropertyList;
    Property List are constrained to be (and to contain) objects that are one of: NSDictionary, NSArray, NSString, NSData;
    Mutability and class are lost upon decoding; Other restrictions apply: no cycles, dags transformed to trees.
    */

- (void)encodeRootObject:(id)rootObject;
    /* calls encodeObject: */

- (void)encodeBycopyObject:(id)anObject;
    /* calls encodeObject: */

- (void)encodeConditionalObject:(id)object;
    /* calls encodeObject: */

- (void)encodeValuesOfObjCTypes:(const char *)types, ...;
    /* Last arguments specify addresses of values to be written.  It might seem surprising to specify values by address, but this is extremely convenient for copy-paste with -decodeValuesOfObjCTypes calls.  A more down-to-the-earth cause for this passing of addresses is that values of arbitrary size is not well supported in ANSI C for functions with variable number of arguments. */

- (id)decodeObject;
    /* object is autoreleased */

- (id)decodePropertyList;
  /* Returns an autoreleased property list: must retain if stored, as usual;
  Note that in -decodeValueOfObjCType:at: objects set are owned by caller*/

- (void)decodeValuesOfObjCTypes:(const char *)types, ...;
    /* Last arguments specify addresses of values to be read. */
    /* objects are NOT autoreleased: caller must release */

- (void)setObjectZone:(NSZone *)zone;
    /* zone may be NULL.  NSCoder's implementation ignores this.  Other coders might want to provide this functionality. */

- (NSZone *)objectZone;
    /* NSCoder's implementation just returns NSDefaultMallocZone(), but coders which honor setObjectZone: will want to override. */

- (unsigned)systemVersion;
    /* NSCoder's implementation just returns 1000, but coder's which care should override. */

- (void)encodeBytes:(void *)byteaddr length:(unsigned)length;
- (void *)decodeBytesWithReturnedLength:(unsigned *)lengthp;
	/* Note: result of decode is "autoreleased" */

- (void)encodeArrayOfObjCType:(const char *)type count:(unsigned)count at:(const void *)array;

- (void)decodeArrayOfObjCType:(const char *)itemType count:(unsigned)count at:(void *)array;

@end

