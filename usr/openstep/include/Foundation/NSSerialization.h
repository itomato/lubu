#ident "@(#) NSSerialization.h, Rev 1.5, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Standard Serialization of Property Lists

#import <Foundation/NSData.h>
#import <Foundation/NSProxy.h>

/***************	Serialization of very basic types	***********/

@interface NSMutableData (NSMutableDataSerialization)

- (void)serializeInt:(int)value;
    /* 32-bit, machine independent integer coding */

- (void)serializeInts:(int *)intBuffer count:(unsigned)numInts;
    /* multiple appending */

- (void)serializeInt:(int)value atIndex:(unsigned)index;
    /* for rewriting an int somewhere in the buffer */
    
- (void)serializeInts:(int *)intBuffer count:(unsigned)numInts atIndex:(unsigned)index;
    /* for rewriting an int somewhere in the buffer */
        
- (void)serializeAlignedBytesLength:(unsigned)length;
    /* precedes a appendBytes:length:;
    implementation may decide if data length is big to create a hole to page align data */

@end

@interface NSData (NSDataDeserialization)

/* all read methods may raise */

- (int)deserializeIntAtIndex:(unsigned)index;
    /* 32-bit, machine independent integer decoding */

- (void)deserializeInts:(int *)intBuffer count:(unsigned)numInts atIndex:(unsigned)index;
    /* multiple deserializeIntAtIndex: */

- (int)deserializeIntAtCursor:(unsigned *)cursor;
    /* same as deserializeIntAtIndex: but advances cursor */
    
- (void)deserializeInts:(int *)intBuffer count:(unsigned)numInts atCursor:(unsigned *)cursor;
    /* multiple readInts */
    
- (unsigned)deserializeAlignedBytesLengthAtCursor:(unsigned *)cursor;
    /* must correspond to an serializeAlignedBytesLength: */
    
- (void)deserializeBytes:(void *)buffer length:(unsigned)bytes atCursor:(unsigned *)cursor;
    /* bytes must have been previously allocated;
    cursor is advanced */

@end

/********* 	Objective-C Type Serialization ************************/

/* We encode nearly all Objective-C primitive types. 
    Objects are handled by calling the context object.
    Usage:
	id <NSMutableData> d; 
	foobar x; // int, char, or a struct or whatever ...
	[d serializeDataAt:&x ofObjCType:@encode(typeof(x)) context:nil];
*/

@protocol NSObjCTypeSerializationCallBack
- (void)serializeObjectAt:(id *)object ofObjCType:(const char *)type intoData:(NSMutableData *)data;
	// tell caller to encode an object (potentially) bycopy
- (void)deserializeObjectAt:(id *)object ofObjCType:(const char *)type fromData:(NSData *)data atCursor:(unsigned *)cursor;
    // ask caller to decode an object
    // returned object is NOT auto-released
@end

@interface NSMutableData (NSMutableDataObjcTypeSerialization)

- (void)serializeDataAt:(const void *)data ofObjCType:(const char *)type context:(id <NSObjCTypeSerializationCallBack>)callback;
    /* most objc types supported: no unions, void *, or (yet) long long */
    /* objects supported via callback context */
@end

@interface NSData (NSDataObjCTypeDeserialization)

- (void)deserializeDataAt:(void *)data ofObjCType:(const char *)type atCursor:(unsigned *)cursor context:(id <NSObjCTypeSerializationCallBack>)callback;
    /* cursor is advanced */
    /* objects supported via callback context */
@end

/***************	Property List Serialization	***************/

@interface NSSerializer:NSObject

+ (void)serializePropertyList:(id)aPropertyList intoData:(NSMutableData *)mdata;
    /* It is legal to serialize nil;
    understands the NSSerializedPropertyList class, and any class that conforms to <NSData>, <NSString>, <NSArray> and <NSDictionary>;
    We can't really use a protocol here because proxies don't conform to protocols they implement */
    
+ (NSData *)serializePropertyList:(id)aPropertyList;
    /* Convenience only; Returns an autoreleased NSData */

@end

@interface NSDeserializer:NSObject

    
+ (id)deserializePropertyListFromData:(NSData *)data atCursor:(unsigned *)cursor mutableContainers:(BOOL)mutable;
    /* returns an evanescent, immutable property list;
    If mutableContainers is YES, then all arrays and dictionaries are mutable */

+ (id)deserializePropertyListLazilyFromData:(NSData *)data atCursor:(unsigned *)cursor length:(unsigned)length mutableContainers:(BOOL)mutable;

+ (id)deserializePropertyListFromData:(NSData *)serialization mutableContainers:(BOOL)mutable;
    /* Convenience only; Returns an evanescent property list */

@end
