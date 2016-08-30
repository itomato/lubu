#ident "@(#) NSConnection.h, Rev 1.10, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Encapsulates the state of a DO circuit

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSHashTable.h>
#import <Foundation/NSMapTable.h>

@class NSMutableData,
		NSDistantObject <NSCoding>,
		NSException <NSCopying,NSCoding>;


/*****************  NSConnection    **************************/

// When a connection dies, before it is deallocated,
// the event {name = NSConnectionDidDieNotification; sender = connection}
// is posted to let external clients back off the connection

// A connection object is a bookkeeper for objects vended or received over
// a particular port resource.  It may not be shared by multiple threads.

@interface NSConnection: NSObject {
    @private
    unsigned    isValid:1;
    unsigned	isDead:1;
    unsigned	isQueueing:1;
    unsigned	authGen:1;
    unsigned	authCheck:1;
    unsigned	encryptFlag:1;
    unsigned	decryptFlag:1;
    unsigned    doRequest:1;
    unsigned	refCount:24;
    id          delegate;
    id			receivePort;	// port that we decode from
    id			sendPort;	// port that we encode to
    void        *localProxies;
    void        *remoteProxies;
    id          coderClass;
    NSTimeInterval	requestLimit;
    NSTimeInterval	replyLimit;
    id			requestModes;	// mode in which we honor requests
    id          rootObject; // the "default" object for this connection
    id			registerName;
    id			statistics;
    NSHashTable	*classInfoExported;
    NSMapTable	*classInfoImported;
    NSMutableData	*releasedProxies;
    void		*reserved;
}

- (NSDictionary *)statistics;	// for this connection

+ (NSArray *)allConnections;   // return existing valid connections
  
  
// All connections register their receivePort for "server" activity
// in the default runLoop's default mode.  For activity to be honored in
// other modes,add the connection's receivePort for those modes.

+ (NSConnection *)defaultConnection;
  // (Establish and) provide a default per-thread connection

+ (NSConnection *)connectionWithRegisteredName:(NSString *)name
				host:(NSString *)hostName;
+ (NSDistantObject *)rootProxyForConnectionWithRegisteredName:(NSString *)name
				host:(NSString *)hostName;
  // use the MACH nmserver for name resolution. @"*" as a host implies a
  // broadcast lookup for any server registered with name.  nil as host
  // implies the local machine only
  
  // timeout values are inherited; infinite is the default
- (void)setRequestTimeout:(NSTimeInterval)ti;
- (NSTimeInterval)requestTimeout;
- (void)setReplyTimeout:(NSTimeInterval)ti;
- (NSTimeInterval)replyTimeout;

- (BOOL)registerName:(NSString *) name;
  // register the receivePort with name on the local system

- (void)setRootObject:(id)anObject;  // set or replace root object served
- (id)rootObject;

- (NSDistantObject *)rootProxy;
// return a NSDistantObject proxy to the root object served by this connection
  
- (void)setDelegate:(id)anObject;
- (id)delegate;
  // delegate methods are discussed below

- (void)setIndependentConversationQueueing:(BOOL)yorn;
- (BOOL)independentConversationQueueing;
  // default is NO
  // inherited by "child" connections
  // if yes, unrelated requests are queued for later processing
  // this can easily cause deadlocks among peers but will protect
  // state from simultaneous changes

- (BOOL)isValid;
- (void)invalidate;

- (void)addRequestMode:(NSString *)rmode;
- (void)removeRequestMode:(NSString *)rmode;


@end

extern NSString *NSConnectionReplyMode;
    // the runLoop mode that DO seeks replies; use
    // this to add timers or other activities that need to be processed
    // while awaiting DO replies

extern NSString *NSConnectionDidDieNotification;

@interface NSObject (NSConnectionDelegateMethods)

- (BOOL)connection:(NSConnection *)ancestor
		shouldMakeNewConnection:(NSConnection *)conn;
  // delegate should return YES to proceed.  conn is not yet entered into
  // the global table, so communication cannot occur on it yet.
  // conn's parameters may be reset.

- (BOOL)makeNewConnection:(NSConnection *)conn
		sender:(NSConnection *)ancestor;
  // synonym for the above.
  // Use the method -connection:shouldMakeNewConnection: in preference to
  // this one.  Note: the arguments are reversed!

#if !defined(STRICT_OPENSTEP)
- (NSData *)authenticationDataForComponents:(NSArray *)components;
    // If implemented, delegate should generate and return authentication data

- (BOOL)authenticateComponents:(NSArray *)components
		withData:(NSData *)signature;
    // If implemented, delegate should verify authentication data

extern NSString *NSFailedAuthenticationException;

#endif /* !STRICT_OPENSTEP */

@end

#if !defined(STRICT_OPENSTEP)

// Asynchronous request handling

@interface NSDistantObjectRequest : NSObject
- (NSInvocation *)invocation;
- (NSConnection *)connection;
- (void)replyWithException:(NSException *)exception;
    // the result from the doreq's invocation will be returned unless
    // the exception parameter is supplied (in which case the exception will
    // be delivered to the requesting party).
@end

@interface NSObject (NSDistantObjectRequestMethods)
- (BOOL)connection:(NSConnection *)connection
		handleRequest:(NSDistantObjectRequest *)doreq;
    // return NO if connection should disptach & return reply
    // return YES if delegate will dispatch & return reply
@end

#endif
