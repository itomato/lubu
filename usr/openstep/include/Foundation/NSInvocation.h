#ident "@(#) NSInvocation.h, Rev 1.16, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//

//	An Objective C message object

#import <Foundation/NSObject.h>

@class NSMutableArray, NSMethodSignature;

#if !defined(STRICT_OPENSTEP)
#ifndef _NSObjCValue_DEFINED
typedef enum {
 		NSObjCNoType = 0,
		NSObjCVoidType = 'v',
		NSObjCCharType = 'c',
		NSObjCShortType = 's',
		NSObjCLongType = 'l',
		NSObjCLonglongType = 'q',
		NSObjCFloatType = 'f',
		NSObjCDoubleType = 'd',
		NSObjCSelectorType = ':',
		NSObjCObjectType = '@',
		NSObjCStructType = '{',
		NSObjCPointerType = '^',
		NSObjCStringType = '*',
		NSObjCArrayType = '[', // not used in return values
		NSObjCUnionType = '(', // not used in return values
		NSObjCBitfield = 'b' // not used in return values
} NSObjCtypeValues;

typedef struct {
    NSObjCtypeValues type;
    union {
		char charValue;
		short shortValue;
		long longValue;
		long long longlongValue;
		float floatValue;
		double doubleValue;
		SEL selectorValue;
		id objectValue;
		void *pointerValue;
		void *structLocation;
		char *cStringLocation;
    } value;
}
    	NSObjCValue;
#define _NSObjCValue_DEFINED
#endif

#else /* STRICT_OPENSTEP */

#ifndef _NSObjCValue_DEFINED

typedef struct {
    int		type;
    long long	value;
} NSObjCValue;
#define _NSObjCValue_DEFINED
#endif
#endif /* !STRICT_OPENSTEP */
    
@interface NSInvocation : NSObject <NSCoding> {
    @private
    NSObjCValue	returnValue;	// first since it has largest alignment
    void	*argumentFrame;
    NSMethodSignature	*signature;
    NSMutableArray	*container;
    unsigned 	retainedArgs:1;
    unsigned	isInvalid:1;
    unsigned	unused:6;
    unsigned	refCount:24;
    void	*reserved;
}

+ (NSInvocation *)invocationWithMethodSignature:(NSMethodSignature *)sig;
- (SEL)selector;
- (void)setSelector:(SEL)selector;
- (id)target;
- (void)setTarget:(id)target;
- (void)retainArguments; // retain objects; copy char * strings
- (BOOL)argumentsRetained;
- (void)getReturnValue:(void *)retLoc;
- (void)setReturnValue:(void *)retLoc;
- (void)getArgument:(void *)argumentLocation atIndex:(int)index;
	//  0 target; 1 selector; ...
- (void)setArgument:(void *)argumentLocation atIndex:(int)index;

- (NSMethodSignature *)methodSignature;

- (void)invoke;
- (void)invokeWithTarget:(id)target;
	// dispatch the message and collect the result
@end
