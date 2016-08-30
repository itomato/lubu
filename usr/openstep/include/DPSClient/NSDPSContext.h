#ident "@(#) NSDPSContext.h, Rev 1.18, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSDPSContext_h_
#define _NSDPSContext_h_

/*
 * WARNING
 * WARNING
 * WARNING
 *
 * The interfaces herein are implementation dependent and may not be portable
 * across all implementations.
 *
 * In particular on Solaris we do not have the ability to expose or change
 * API/implementation of libdps as with NeXT. Therefore the capabilities
 * of this class change drastically. In particular since we are unable to
 * modify the contexts of libdps on our platform the NSDPSContext class
 * must treat the implementation of DPSContexts as essentialy private.
 *
 */

#import <Foundation/Foundation.h>
#import <DPS/dpsclient.h>

/* NXRunLoop mode used when DPS is waiting for return vals or pings */

extern NSString *NSDPSRunLoopMode;

@class NSDPSContext;
struct NSGStateList;

// HV's precomp doesn't like items declared to be ptrs to the
// above type.  But, it accepts the following type.
typedef struct NSGStateList NSGStateList_HV;

@protocol NSDPSContextNotification
- (void) contextFinishedExecuting: (NSDPSContext *) context;
@end

@interface NSDPSContext : NSObject {
	DPSContext	ctxt;
@private
	DPSProcs	ctxtProcs;
	BOOL	   	syncMode;
	NSDPSContext*	traceCtxt;

	/*
	 * IMPLEMENTATION DEPENDENT/PRIVATE
	 */

	DPSErrorProc	_actualErrorProc;

	BOOL		_resyncPending;

	int		_pendingDPSExceptionCode;	// pending iff != 0
	char*		_pendingDPSExceptionMsg;
	NSException*	_nsException;			// pending iff != nil

	int		_nullUserObject;

	NSGStateList_HV	*_inUseGStates;
	NSGStateList_HV	*_freeGStates;

	struct {
		unsigned _isSynced:1;
		unsigned _callDidWrite:1;
	} _flags;

@protected
	BOOL		_autoResync;

	void*		_impl;				// reserved.
}

+ (void) setAllContextsSynchronized: (BOOL) flag;
+ (BOOL) areAllContextsSynchronized;
+ (void) setAllContextsOutputTraced: (BOOL) flag;
+ (BOOL) areAllContextsOutputTraced;

+ (NSDPSContext *) currentContext;

+ (NSDPSContext *) NSDPSContextForDPSContext: (DPSContext) ctxt;

#define DPSContextObject(ctxt) [NSDPSContext NSDPSContextForDPSContext:(ctxt)]

+ (void) setCurrentContext: (NSDPSContext *) context;

+ (NSString *) stringForDPSError: (const DPSBinObjSeqRec *) error;

#ifndef	STRICT_OPENSTEP
- (NSDPSContext*) initWithDPSContext: (DPSContext) ctxt; // designated init

- (void) initContextAutoResync;
#endif

- (id) initWithMutableData: (NSMutableData *)	 data
	      forDebugging: (BOOL)		 debug
	  languageEncoding: (DPSProgramEncoding) langEnc
	      nameEncoding: (DPSNameEncoding)    nameEnc
		  textProc: (DPSTextProc)	 tProc
		 errorProc: (DPSErrorProc)	 errorProc;

- (void) dealloc;

- (NSMutableData *) mutableData;

#ifndef	STRICT_OPENSTEP
- (int) nullUserObject;

- (BOOL) resyncPending; // only interesting if called from inside error procs.
#endif

/* returns the corresponding DPSContext */

- (DPSContext) DPSContext;


- (BOOL) isDrawingToScreen;	/* drawing status */

/* methods for the standard DPS API */

/* methods used by pswrap generated functions to emit binary PS */

- (void) writeBinaryObjectSequence: (const void *) data
			    length: (unsigned int) bytes;

- (void) writeBOSArray: (const void *)   data
		 count: (unsigned int)   items
		ofType: (DPSDefinedType) type;

- (void) writeBOSString: (const void *) data
		 length: (unsigned int) bytes;

- (void) writeBOSNumString: (const void *)   data
		    length: (unsigned int)   count
		    ofType: (DPSDefinedType) type
		     scale: (int)	     scale;

- (void) awaitReturnValues;
- (void) updateNameMap;

/* methods to send raw data */

- (void) writeData: (NSData *) buf;
- (void) writePostScriptWithLanguageEncodingConversion: (NSData *) buf;
- (void) printFormat: (NSString *) format, ...;
- (void) printFormat: (NSString *) format arguments: (va_list) argList;

/* methods to control the context */

- (void) flush;
- (void) resetCommunication;
- (void) interruptExecution;
- (void) wait;
- (void) notifyObjectWhenFinishedExecuting: (id <NSDPSContextNotification>) object;


/* methods to control text and error procs */

- (void) setTextProc: (DPSTextProc) proc;
- (DPSTextProc) textProc;

- (void)setErrorProc: (DPSErrorProc) proc;
- (DPSErrorProc) errorProc;

/* setting and getting the chained context */

- (void) chainChildContext: (NSDPSContext *) child;
- (void) unchainContext;

- (NSDPSContext *) childContext;
- (NSDPSContext *) parentContext;

/* debugging aids */

- (void) setSynchronized: (BOOL) flag;
- (BOOL) isSynchronized;

- (void) setOutputTraced: (BOOL) flag;
- (BOOL) isOutputTraced;

@end

#endif // _NSDPSContext_h_
