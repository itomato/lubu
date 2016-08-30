#ident "@(#) NSCustomImageRep.h, Rev 1.3, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSImageRep.h"

@interface NSCustomImageRep : NSImageRep {
    SEL _drawMethod;
    id _drawObject;
    int _reservedInt;
}

- (id)initWithDrawSelector:(SEL)aMethod delegate:(id)anObject;
- (SEL)drawSelector;
- (id)delegate;

@end

