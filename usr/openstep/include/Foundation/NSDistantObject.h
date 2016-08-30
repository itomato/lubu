#ident "@(#) NSDistantObject.h, Rev 1.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//

#import <Foundation/NSCoder.h>
#import <Foundation/NSProxy.h>

@class Protocol;
@class NSConnection;
@class NSCoder;

/*****************  Distributed Objects     **************************/

/* we keep a NSDistantObject for each Object, whether remote or local,
 * that has been communicated over the wire.
 */

@interface NSDistantObject : NSProxy <NSCoding> {
    @private
    id				name;           /* object name */
    unsigned		wire:2;         /* is this a stub for a local object? */
    unsigned		unused:6;
    unsigned		refCount:24;
    NSConnection	*conn;          /* what conn are we registered on? */
    unsigned		wireCount;
    void			*knownSelectors;    /* cache */
    void			*_reserved;
}

+ (NSDistantObject *)proxyWithTarget:(id)target
		connection:(NSConnection *)connection;
- (id)initWithTarget:(id)target
		connection:(NSConnection *)connection;
  // designated initializer; may deallocate and return nil if this target
  // is already known on the connection.
  // builds a remote proxy.
  // target is an id on the other side of this connection
  // Suggested use: subclass NSDistantObject to provide a "smart" proxy
  // that can locally implement some methods.  Construct this smart
  // proxy in the decodeUsingCoder: method of the target.

+ (NSDistantObject *)proxyWithLocal:(id)target
		connection:(NSConnection *)connection;
- (id)initWithLocal:(id)target
		connection:(NSConnection *)connection;
  // builds and registers a local proxy for a local object; this object
  // will copy itself over the wire forming a remote proxy on the other
  // end.  DO NOT RETAIN OR OTHERWISE USE THIS PROXY

- (void)setProtocolForProxy:(Protocol *)proto;
  // a performance improving hint: provide method signatures to avoid
  // a round-trip to determine signatures

- (NSConnection *)connectionForProxy;

@end

