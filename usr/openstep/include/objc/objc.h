#ident "@(#) objc.h, Rev 2.13, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1988, NeXT, Inc.
//	All rights reserved.

#ifndef _OBJC_OBJC_H_
#define _OBJC_OBJC_H_

#if defined(sparc)
#if !defined(__BIG_ENDIAN__)
#define __BIG_ENDIAN__
#endif
#elif defined(i386)
#if !defined(__LITTLE_ENDIAN__)
#define __LITTLE_ENDIAN__
#endif
#else
#error "Architecture not supported"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct objc_class *Class;

typedef struct objc_object {
	Class isa;
} *id;

typedef struct objc_selector 	*SEL;    
typedef char *			STR_NS;
typedef id 			(*IMP)(id, SEL, ...); 
#ifndef	XMD_H
typedef unsigned char		BOOL;
#endif

extern BOOL sel_isMapped(SEL sel);
extern const char *sel_getName(SEL sel);
extern SEL sel_getUid(const char *str);
extern SEL sel_registerName(const char *str);
extern const char *object_getClassName(id obj);
extern void *object_getIndexedIvars(id obj);
extern int objc_build_selector_table(const char * path);
extern void _objc_print_selector_table();

#define YES             (BOOL)1
#define NO              (BOOL)0
#define ISSELECTOR(sel) sel_isMapped(sel)
#define SELNAME(sel)	sel_getName(sel)
#define SELUID(str)	sel_getUid(str)
#define NAMEOF(obj)     object_getClassName(obj)
#define IV(obj)         object_getIndexedIvars(obj)

#define SEL_EQUAL(S1,S2) ((S1) == (S2))

#define Nil (Class)0           /* id of Nil class */
#define nil (id)0              /* id of Nil instance */

#ifdef __cplusplus
}
#endif

#endif /* _OBJC_OBJC_H_ */
