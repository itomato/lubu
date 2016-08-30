#ident "@(#) objc-class.h, Rev 2.15, 96/09/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1988, NeXT, Inc.
//	All rights reserved.

#ifndef _OBJC_CLASS_H_
#define _OBJC_CLASS_H_

#import <objc/objc.h>
#import <objc/zone.h>

#define SPARC_VERSION      	10
#define SPARC_VERSION_MT 	11

#define CLASS_VERSION SPARC_VERSION_MT

#ifdef __cplusplus
extern "C" {
#endif

/* Structure for method cache - allocated/sized at runtime */

typedef void *Cache;

/* 
 *	Class Template
 */
struct objc_class {			
	struct objc_class *isa;	
	struct objc_class *super_class;	
	const char *name;		
	long version;
	long info;		// 8 high order bits contain class lock
	long instance_size;
	struct objc_ivar_list *ivars;
	struct objc_method_list *methods;
	Cache *cache;    // This is the big change!
 	struct objc_protocol_list *protocols;
        int     thread_id;  // really contains thread_id during initialization
        void    *dispatch_code;
};

#define CLS_GETINFO(cls,infomask)	((cls)->info & infomask)
#define CLS_SETINFO(cls,infomask)	((cls)->info |= infomask)

#define CLS_CLASS		0x1L
#define CLS_META		0x2L
#define CLS_INITIALIZED		0x4L
#define CLS_POSING		0x8L
#define CLS_PRIVATE_CAT		0x10L
#define CLS_FLUSH_CACHE		0x20L
#define CLS_METHODS		0x40L
#define CLS_INITVTABLE		0x80L
/* 
 *	Category Template
 */
typedef struct objc_category *Category;

struct objc_category {
	char *category_name;
	char *class_name;
	struct objc_method_list *instance_methods;
	struct objc_method_list *class_methods;
 	struct objc_protocol_list *protocols;
};
/* 
 *	Instance Variable Template
 */
typedef struct objc_ivar {
	char	*ivar_name;
	char	*ivar_type;
	int	ivar_offset;
} *Ivar;

struct objc_ivar_list {
	int ivar_count;
	struct objc_ivar    ivar_list[1];	/* variable length structure */
};
/* 
 *	Method Template
 */
typedef struct objc_method {
	SEL	method_name;
	char	*method_types;
        IMP 	method_imp;
} *Method;

struct objc_method_list {
	struct objc_method_list *method_next;
	int 			method_count;
	struct objc_method	method_list[1];	/* variable length structure */
};

/* Protocol support */

@class Protocol;

struct objc_protocol_list {
	struct objc_protocol_list *next;
	int count;
	Protocol *list[1];
};

/* Definitions of filer types */

#define _C_ID		'@'
#define _C_CLASS	'#'
#define _C_SEL		':'
#define _C_CHR		'c'
#define _C_UCHR		'C'
#define _C_SHT		's'
#define _C_USHT		'S'
#define _C_INT		'i'
#define _C_UINT		'I'
#define _C_LNG		'l'
#define _C_ULNG		'L'
#define _C_FLT		'f'
#define _C_DBL		'd'
#define _C_BFLD		'b'
#define _C_VOID		'v'
#define _C_UNDEF	'?'
#define _C_PTR		'^'
#define _C_CHARPTR	'*'
#define _C_ARY_B	'['
#define _C_ARY_E	']'
#define _C_UNION_B	'('
#define _C_UNION_E	')'
#define _C_STRUCT_B	'{'
#define _C_STRUCT_E	'}'

/* operations */

extern id class_createInstance(Class, unsigned idxIvars);
extern id class_createInstanceFromZone(Class, unsigned idxIvars, NXZone *zone);

extern void class_setVersion(Class, int);
extern int class_getVersion(Class);

extern Ivar class_getInstanceVariable(Class, const char *);
extern Method class_getInstanceMethod(Class, SEL);
extern Method class_getClassMethod(Class, SEL);

extern void class_addMethods(Class, struct objc_method_list *);
extern void class_removeMethods(Class, struct objc_method_list *);

extern Class class_poseAs(Class imposter, Class original);
extern int create_selector_table();
extern Class objc_get_cls(void * cls_candidate);

extern unsigned struct_ret(Method);
extern unsigned method_getNumberOfArguments(Method);
extern unsigned method_getSizeOfArguments(Method);
extern unsigned method_getArgumentInfo(Method m, int arg, const char **type, int *offset);

typedef void *marg_list;

#define marg_getRef(margs, offset, type) \
	( (type *)((char *)margs + offset) )

#define marg_getValue(margs, offset, type) \
	( *marg_getRef(margs, offset, type) )

#define marg_setValue(margs, offset, type, value) \
	( marg_getValue(margs, offset, type) = (value) )

#ifdef __cplusplus
}
#endif

#endif /* _OBJC_CLASS_H_ */
