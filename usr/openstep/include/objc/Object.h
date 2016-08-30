#ident "@(#) Object.h, Rev 2.10, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1988, 1989 NeXT, Inc.
//	All rights reserved.

#ifndef _OBJC_OBJECT_H_
#define _OBJC_OBJECT_H_

#import <objc/objc.h>
#import <objc/objc-class.h>
#import <objc/zone.h>

#define  SELECTOR(x)  @selector(x)

@class Protocol;

@interface Object
{
	Class isa;	/* A pointer to the instance's class structure */
}

/* Initializing classes and instances */

+ initialize;
- init;

/* Creating, copying, and freeing instances */

+ new;
+ free;
- free;
+ alloc;
- copy;
+ allocFromZone:(NXZone *)zone;
- copyFromZone:(NXZone *)zone;
- (NXZone *)zone;

/* Identifying classes */

+ class;
+ superclass;
+ (const char *) name;
- class;
- superclass;
- (const char *) name;

/* Identifying and comparing instances */

- self;
- (unsigned int) hash;
- (BOOL) isEqual:anObject;

/* Testing inheritance relationships */

- (BOOL) isKindOf: aClassObject;
- (BOOL) isMemberOf: aClassObject;
- (BOOL) isKindOfClassNamed: (const char *)aClassName;
- (BOOL) isMemberOfClassNamed: (const char *)aClassName;

/* Testing class functionality */

+ (BOOL) instancesRespondTo:(SEL)aSelector;
- (BOOL) respondsTo:(SEL)aSelector;

/* Testing protocol conformance */

- (BOOL) conformsTo: (Protocol *)aProtocolObject;
+ (BOOL) conformsTo: (Protocol *)aProtocolObject;

/* Obtaining method descriptors from protocols */

- (struct objc_method_description *) descriptionForMethod:(SEL)aSel;
+ (struct objc_method_description *) descriptionForInstanceMethod:(SEL)aSel;

/* Obtaining method handles */

- (IMP) methodFor:(SEL)aSelector;
+ (IMP) instanceMethodFor:(SEL)aSelector;

/* Sending messages determined at run time */

- perform:(SEL)aSelector;
- perform:(SEL)aSelector with:anObject;
- perform:(SEL)aSelector with:object1 with:object2;

/* Posing */

+ poseAs: aClassObject;

/* Enforcing intentions */
 
- subclassResponsibility:(SEL)aSelector;
- notImplemented:(SEL)aSelector;

/* Error handling */

- doesNotRecognize:(SEL)aSelector;
- error:(const char *)aString, ...;


/* Archiving */

- awake;
+ (int) version;
+ setVersion: (int) aVersion;

/* Forwarding */

- forward: (SEL)sel : (marg_list)args;
- performv: (SEL)sel : (marg_list)args;

@end

#ifdef __cplusplus
extern "C" {
#endif
extern id object_dispose(id anObject);
extern id object_copy(id anObject, unsigned nBytes);
extern id object_copyFromZone(id anObject, unsigned nBytes, NXZone *);
extern id object_realloc(id anObject, unsigned nBytes);
extern id object_reallocFromZone(id anObject, unsigned nBytes, NXZone *);

extern Ivar object_setInstanceVariable(id, const char *name, void *);
extern Ivar object_getInstanceVariable(id, const char *name, void **);
#ifdef __cplusplus
}
#endif

#endif /* _OBJC_OBJECT_H_ */
