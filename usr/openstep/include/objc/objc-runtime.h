#ident "@(#) objc-runtime.h, Rev 2.17, 95/11/08"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1988, NeXT, Inc.
//	All rights reserved.

#ifndef _OBJC_RUNTIME_H_
#define _OBJC_RUNTIME_H_

#import <objc/objc.h>
#import <objc/objc-class.h>
#import <objc/hashtable.h>
#import <objc/Object.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void *_MT_SAFE_INIT_CODE;
extern void *_MT_SAFE_CODE;
extern void *_MT_UNSAFE_CODE;
extern void *_MT_SAFE_INIT_TRACE_CODE;
extern void *_MT_SAFE_TRACE_CODE;
extern void *_MT_UNSAFE_TRACE_CODE;
extern void *_MT_SAFE_INIT_PROFILE_CODE;
extern void *_MT_SAFE_PROFILE_CODE;
extern void *_MT_UNSAFE_PROFILE_CODE;


// this label contains the address of the 'unimp' instrcution
// inside objc_msgSendStructV() that must be uodated at each call
// with the size of the structure returned.
extern int * _UNIMP_LABEL;

/* globals for command line args */
extern int      NSArgc;
extern char   **NSArgv;

typedef struct objc_symtab *Symtab;

struct objc_symtab {
	Class 		*cls_inst;
	SEL 		*refs;		
	unsigned short 	cls_def_cnt;
	unsigned short 	cat_def_cnt;
#ifndef hpux
	int             obj_defs;
	int             proto_defs;
#endif
	void  		*defs[1];	/* variable size */
};

typedef struct objc_module *Module;

struct objc_module {
	unsigned long	version;
	unsigned long	size;
	const char	*name;
	Symtab 		symtab;	
};

struct objc_super {
	id receiver;
	Class cls;
};

/* kernel operations */

extern id objc_getClass(const char *name);
extern id objc_getMetaClass(const char *name);
extern id objc_msgSend(id self, SEL op, ...);
extern id objc_msgSendSuper(struct objc_super *super, SEL op, ...);

/* forwarding operations */

extern id objc_msgSendv(id self, SEL op, unsigned arg_size, marg_list arg_frame);
extern id objc_msgSendvStruct(id self, SEL op, unsigned arg_size, marg_list arg_frame);
extern id objc_msgSendStructV(id self, SEL op, unsigned arg_size, marg_list arg_frame);

/* 
   iterating over all the classes in the application...
  
   NXHashTable *class_hash = objc_getClasses();
   NXHashState state = NXInitHashState(class_hash);
   Class cls;
  
   while (NXNextHashState(class_hash, &state, &cls)
     ...;
 */
extern NXHashTable *objc_getClasses();
extern Module *objc_getModules();
extern id objc_lookUpClass(const char *name);

// defined in objc-errors.m
extern int _objc_enable_warnings(int enable);
extern int _objc_enable_consoleError(int enable);

/* customizing the error handling for objc_getClass/objc_getMetaClass */

extern void objc_setClassHandler(int (*)(const char *));

/* Making the Objective-C runtime thread safe. */
extern void 	objc_setMultithreaded (BOOL flag);

/* overriding the default object allocation and error handling routines */

extern id	(*_alloc)(Class, unsigned int);
extern id	(*_copy)(Object *, unsigned int);
extern id	(*_realloc)(Object *, unsigned int);
extern id	(*_dealloc)(Object *);
extern id	(*_zoneAlloc)(Class, unsigned int, NXZone *);
extern id	(*_zoneRealloc)(Object *, unsigned int, NXZone *);
extern id	(*_zoneCopy)(Object *, unsigned int, NXZone *);
extern void	(*_error)(Object *, const char *, va_list);

// Register callbacks invoked after _objcInit
int 		_objcPostInit(void (*initfunc)(int ismain));
// Clear callbacks
int 		_objcPostInitClear();

// form objc-load.h: merged here
// loading a shared object in an application

extern long objc_loadModule(
	char *modulePath, 				/* input */
	void (*loadCallback)(Class, Category),		/* input (optional) */
	char                ** errMsg 			/* output */ 
);

#ifdef __cplusplus
}
#endif

#endif /* _OBJC_RUNTIME_H_ */
