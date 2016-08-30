#ident "@(#) NSMethodSignature.h, Rev 1.10, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//

#import <Foundation/NSObject.h>

@class Protocol;

/*************		NSMethodSignature 		******************
 * ObjC does not keep type information with the selectors, so remote
 * objects need to acquire and keep this info as appropriate.
 *
 **********************************************************************/

@interface NSMethodSignature: NSObject {
    @private
    const char	*_types;
    int		_nargs;
    unsigned	_sizeofParams;
    unsigned	_returnValueLength;
    void	*_parmInfoP;
    int		*_fixup;
    void	*_reserved;
}



- (const char *)getArgumentTypeAtIndex:(unsigned)idx;

- (unsigned)frameLength;

- (unsigned)numberOfArguments; // self and _cmd counted

- (BOOL)isOneway;
	/* is this method asynchronous? */

- (const char *)methodReturnType;
- (unsigned)methodReturnLength;

@end
