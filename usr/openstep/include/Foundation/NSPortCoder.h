#ident "@(#) NSPortCoder.h, Rev 1.9, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Sending Objective-C messages in Mach msgs

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSCoder.h>

@class NSConnection;

/* This provides buffering for an objective-C message to be sent or received across a connection */

@interface NSPortCoder : NSCoder

- (BOOL)isBycopy;
        // ask coder if this object (self) should go bycopy

- (BOOL)isByref;
        // ask coder if this object (self) should go byref

- (NSConnection *)connection;

- (void)encodePortObject:(id)aport;

- (id)decodePortObject;

@end


/* By default, NSObject provides an NSProxy based implementation for
distribution coding, enabling all objects to be distributed by proxy by
default.  If objects wish to copy themselves or substitute another
object, they must reimplement -replacementObjectForPortCoder: */

@interface NSObject (NSDistributedObjects)
- (Class)classForPortCoder;
    /* Allows substitution of the class used in distributed objects,
    thus providing very specialized behavior for this style of coding
    and general behavior for others.
    default is to call -classForCoder. */
    
- (id)replacementObjectForPortCoder:(NSPortCoder *)coder;
    /* asks [self replacementObjectForCoder:coder] which defaults to returning self;
       if not nil then provides [[coder connection] proxyForObject:new]
       This establishes a remote proxy for this object. */

@end

#endif /* !STRICT_OPENSTEP */
