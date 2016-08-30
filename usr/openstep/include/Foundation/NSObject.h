#ident "@(#) NSObject.h, Rev 1.15, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Definitions of very basic things

#import <Foundation/NSZone.h>
#import <objc/objc-class.h>
#import <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

@class NSCoder;

@class Protocol;	// part of ObjC language

/***************	Basic protocols		***************/

@protocol NSCopying

- (id)copyWithZone:(NSZone *)zone;
    /* expresses snapshots of objects.  
    Typical usage is for 'passing by value' value objects.  The only guarantee of the snapshot operation for classes that implement the NSCopying protocol is that: 
    	-copyWithZone: will yield a functional object as long as you don't change the returned value.  
    That snapshot operation does not preserve class mutability (for classes for which that makes sense).  Immutability of the returned value is not guaranteed in general either, although Property List classes (NSString, NSData, NSArray, NSDictionary) guarantee immutable returned values. 
    This method is an exception to the allocation rule: returned value is owned by caller who is responsible for releasing it;
    zone may be NULL */

@end

@protocol NSMutableCopying

- (id)mutableCopyWithZone:(NSZone *)zone;
    /* This should be implemented by cluster of classes that differentiate between mutable and immutable objects (such as the basic property list classes)
    It should yield a mutable copy, owned by the caller;
    zone may be NULL */

@end

@protocol NSCoding
    /* The NSCoding protocol is implemented by objects that wish to be persistent and/or distributed */

- (void)encodeWithCoder:(NSCoder *)aCoder;
    /* Object should store its state onto aCoder;
    First thing should be to call [super encodeWithCoder:];
    Default for NSObject is to encode nothing */

- (id)initWithCoder:(NSCoder *)aDecoder;
    /* Called with a freshly allocated object;
    should ask its super to reestablish its state, and then fill itself with data obtained from aDecoder;
    When the exact format of the parent classes serialization is known, the object can replace itself by another object.  In that case, -initWithCoder: must deallocate self, and take total responsability of the deserialization.  Also, there is a restriction that the original object must not appear more than once in the encoding graph;
    Default for NSObject is to do nothing */

@end

/*These are here so that the protocols are defined by now.*/

@class NSInvocation <NSCoding>;
@class NSMethodSignature;
@class NSString <NSCopying, NSMutableCopying, NSCoding>;
@class NSEnumerator;

/*
 * Extra NSZone functions
*/

extern void NSSetZoneName(NSZone *zone, NSString *name);
    /* Sets the zone name */

extern NSString *NSZoneName(NSZone *zone);
    /* Gets the name of a zone */
    

@protocol NSObject

- (BOOL)isEqual:(id)object;
    /* must accept any object as argument;
    Default for NSObject is pointer equality */

- (unsigned)hash;
    /* Must satisfy [x isEqual:y] => [x hash]==[y hash];
    Default for NSObject is to hash the pointer */
    
- (Class)superclass;
- (Class)class;
- (id)self;
- (NSZone *)zone;

- (id)performSelector:(SEL)aSelector;
    // method performed should return a 32-bit quantity
- (id)performSelector:(SEL)aSelector withObject:(id)object;
    // method performed should return a 32-bit quantity
- (id)performSelector:(SEL)aSelector withObject:(id)object1 withObject:(id)object2;
    // method performed should return a 32-bit quantity

- (BOOL)isProxy;

- (BOOL)isKindOfClass:(Class)aClass;
- (BOOL)isMemberOfClass:(Class)aClass;
- (BOOL)conformsToProtocol:(Protocol *)aProtocol;

- (BOOL)respondsToSelector:(SEL)aSelector;

- (id)retain;
    /* default for NSObject is to externally increment the ref count;
    subclasses may redefine if they have their own reference counting scheme, but should not call super;
    For convenience only, retain returns self; no other object should be returned than self */
    
- (void)release;
    /* default for NSObject is to externally decrement the reference count and to perform  dealloc if zero;
    subclasses may redefine if they have their own reference counting scheme, but should not call super */

- (id)autorelease;
    /* Inserts the object in the current delayed free pool, and returns the object itself for convenience;
    */

- (unsigned)retainCount;
    /* Method that should only be used for DEBUG or very unusual ref-counting strategies!
    default for NSObject is to return the externally maintained ref count;
    subclasses may should override this method if they implement their own refcounting scheme.
    This method is only used by foundation during debug, when "enableDoubleFreeCheck" (or the dwrite NSDisableDoubleFreeCheck) has been set to check for overfreeing, or over autoreleasing of objects. 
    For objects which never get released (i.e. their release method is a no-op), this method should return UINT_MAX. */

- (NSString*)description;
    /* Human-readable NSString */

@end

/***********	Base class		***********/

@interface NSObject <NSObject> {
    Class	isa;
}

+ (void)initialize;
- (id)init;
- (void)dealloc;
    /* deallocates self; 
    subclasses should release their instance variables and call [super dealloc] */
- (id)self;
+ (void)load;
+ (id)new;
+ (id)allocWithZone:(NSZone *)zone;
    /* zone passed may be NULL */
+ (id)alloc;
+ (id)copyWithZone:(NSZone *)zone;
    /* convenience method - returns self */
+ (id)mutableCopyWithZone:(NSZone *)zone;
    /* convenience method - returns self */
- (id)copy;
    /* Convenience for implementors of <NSCopying>: just calls copyWithZone:, which raises (unless defined by a subclass) */

- (id)mutableCopy;
    /* Convenience for implementors of <NSMutableCopying>: just calls mutableCopyWithZone:, which raises (unless defined by a subclass) */

+ (Class)superclass;
+ (Class)class;
+ (void)poseAsClass:(Class)aClass;
+ (BOOL)instancesRespondToSelector:(SEL)aSelector;
+ (BOOL)conformsToProtocol:(Protocol *)protocol;
- (IMP)methodForSelector:(SEL)aSelector;
+ (IMP)instanceMethodForSelector:(SEL)aSelector;
+ (int)version;
+ (void)setVersion:(int)aVersion;
- (void)doesNotRecognizeSelector:(SEL)aSelector;
- (void)forwardInvocation:(NSInvocation *)anInvocation;
- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector;

+ (NSString *)description;
    /* returns the class name */

- (Class)classForCoder;
    /* Provide the class name used for coding.
    Default is -class */

- (id)replacementObjectForCoder:(NSCoder *)aCoder;
    /* Allows argument to propose another object at its place when encoding;
    nil means to encode nothing;
    default is to return self */

- (id)awakeAfterUsingCoder:(NSCoder *)aDecoder;
    /* Gives a last change for the object to propose another at its place;
    This is necessary because an object (say an instance of a subclass Font) may decide to replace itself once all the -initWithCoder have been done, and the method deciding to replace maybe in the middle of the inheritance hierarchy (say Font).
    Default is simply to return self;
    If a replacement takes place, the implementation of -awakeAfterUsingCoder is responsible for releasing the old self */

+ (void)enableZombieLogging:(BOOL)enable;
    /*Debugging memory management support*/

@end

/***********	Object Allocation / Deallocation		*******/
    
extern NSObject *NSAllocateObject(Class aClass, unsigned extraBytes, NSZone *zone);
    /* All allocations of NSObjects should go through this routine for the benefit of debug tools;
    If zone is NULL NSDefaultMallocZone() is used. extraBytes is typically 0. */

extern void NSDeallocateObject(NSObject *object);
    /* Must have been allocated with NSAllocateObject() */

extern NSObject *NSCopyObject(NSObject *object, unsigned extraBytes, NSZone *zone);
    /* Bit-by-bit copy of the object */

extern BOOL NSShouldRetainWithZone(NSObject *anObject, NSZone *requestedZone);
    /* This method encapsulates the little bit of logic to decide whether to honor the zone in a copyWithZone: or just do a -retain;
    This of course is only applicable for certain classes;
    The logic is as following:
    - if the default zone (or NULL) is requested just retain;
    - if the zone is the same as the object zone, retain;
    - otherwise, make a true copy */

/***********	Reference counting utilities		*******/

extern unsigned int NSExtraRefCount(id object);

extern void NSIncrementExtraRefCount(id object);
    /* Increments an externally maintained 'extra reference count' for object;
    The first reference (typically done in the +alloc method) is NOT maintained externally (=> no need to call NSIncrementExtraRefCount for that first allocation) */

extern BOOL NSDecrementExtraRefCountWasZero(id object);
    /* Decrements the externally maintained reference count if there is one (and returns NO) else returns YES;
    Typical idiom in the -release method is:
    	if (NSDecrementExtraRefCountWasZero(self)) [self dealloc];
    */

/***********		Misc		*******/

/* NSComparisonResult is used for ordered comparision results. If the first argument to the comparision (the receiving object in a message call or the left argument in a function call) is greater than the second, NSOrderedDescending is returned.  If it is smaller, NSOrderedAscending is returned. Examples:
  [@"Zebra" compare:@"Aardvark"] returns NSOrderedDescending
  compareInts (1, 7) returns NSOrderedAscending
*/
typedef enum _NSComparisonResult {NSOrderedAscending = -1, NSOrderedSame, NSOrderedDescending} NSComparisonResult;

enum {NSNotFound = 0x7fffffff};

#define obsolete	// In order to mark obsolete constructs and to be able to apply tops scripts

@interface NSObject(Sizeof)
+ (unsigned int) Sizeof;
- (unsigned int) Sizeof;
@end

#ifdef __cplusplus
}
#endif
