#ident "@(#) NSProxy.h, Rev 1.4, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Class to subclass for easily defining proxies

#import <Foundation/NSObject.h>
#import <Foundation/NSZone.h>

/* Allows easy implementation of ref-counted proxies by subclassing */

@class NSMethodSignature;
@class NSInvocation <NSCoding>;

@interface NSProxy <NSObject> {
    Class	isa;
}

+ (id)allocWithZone:(NSZone *)zone;

+ (id)alloc;

+ (Class)class;

- (void)forwardInvocation:(NSInvocation *)invocation;
    /* RAISES: override for other behavior */

- (NSMethodSignature *)methodSignatureForSelector:(SEL)sel;
    /* RAISES: override and supply signature for subsequent forwardInvocation: */

- (void)dealloc;
    /* de-allocates proxy */

- (NSString *)description;

@end

