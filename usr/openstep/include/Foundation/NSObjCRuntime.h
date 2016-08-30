#ident "@(#) NSObjCRuntime.h, Rev 1.9, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Language terminology

#import <objc/objc.h>
#import <Foundation/NSObject.h>
#ifdef __cplusplus
extern "C" {
#endif

@class NSString <NSCopying, NSMutableCopying, NSCoding>;

/***************	Types		***************/

/* We assume that id, Class, SEL, BOOL have been defined by the language */

/***************	Functions		***************/

extern NSString *NSStringFromSelector(SEL aSelector);

extern SEL NSSelectorFromString(NSString *aSelectorName);
    /* returns 0 if selector does not exist */

extern Class NSClassFromString(NSString *aClassName);
    /* Returns nil if no class with this name currently loaded */

extern NSString *NSStringFromClass(Class aClass);

extern const char *NSGetSizeAndAlignment(const char *typePtr, unsigned int *sizePtr, unsigned int *alignPtr);

/***************	Constants		***************/

#ifndef YES
#define YES		1
#endif YES
#ifndef NO
#define NO		0
#endif NO

#ifndef nil
#define nil		0
#endif nil

#ifdef __cplusplus
}
#endif
