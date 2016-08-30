#ident "@(#) Protocol.h, Rev 2.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1991 NeXT, Inc.
//	All rights reserved.

#ifndef _OBJC_PROTOCOL_H_
#define _OBJC_PROTOCOL_H_

#import <objc/Object.h>

struct objc_method_description {
	SEL name;
	char *types;
};
struct objc_method_description_list {
        int count;
        struct objc_method_description list[1];
};

@interface Protocol : Object
{
@private
	char *protocol_name;
 	struct objc_protocol_list *protocol_list;
  	struct objc_method_description_list *instance_methods, *class_methods;
#ifdef __hpux
	unsigned long	risc_pad; 
#endif __hpux
}

/* Obtaining attributes intrinsic to the protocol */

- (const char *)name;

/* Testing protocol conformance */

- (BOOL) conformsTo: (Protocol *)aProtocolObject;

/* Looking up information specific to a protocol */

- (struct objc_method_description *) descriptionForInstanceMethod:(SEL)aSel;
- (struct objc_method_description *) descriptionForClassMethod:(SEL)aSel;

@end

#endif /* _OBJC_PROTOCOL_H_ */
