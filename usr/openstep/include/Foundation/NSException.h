#ident "@(#) NSException.h, Rev 1.21, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#ifndef _NSEXCEPTION_H
#define _NSEXCEPTION_H

#import <Foundation/NSDictionary.h>

// here starts the the file "error.h" previously in the 
// objc directory and defining old style exceptionbs on which the
// new style is based.

#include <setjmp.h>

#if defined(__SVR4)
#define _setjmp setjmp
#define _longjmp longjmp
#endif /* __SVR4 */


#define NSNewExceptionCode 100000       //  means called by an exception

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _NXHandler {	/* a node in the handler chain */
    jmp_buf jumpState;			/* place to longjmp to */
    struct _NXHandler *next;		/* ptr to next handler */
    int code;				/* error code of exception */
    const void *data1, *data2;		/* blind data for describing error */
} NXHandler;


/* Handles RAISE's with nowhere to longjmp to */
typedef void NXUncaughtExceptionHandler(int code, const void *data1,
						const void *data2);
extern NXUncaughtExceptionHandler *_NXUncaughtExceptionHandler;
#define NXGetUncaughtExceptionHandler() _NXUncaughtExceptionHandler
#define NXSetUncaughtExceptionHandler(proc) \
			(_NXUncaughtExceptionHandler = (proc))

/* NX_DURING, NX_HANDLER and NX_ENDHANDLER are always used like:

	NX_DURING
	    some code which might raise an error
	NX_HANDLER
	    code that will be jumped to if an error occurs
	NX_ENDHANDLER

   If any error is raised within the first block of code, the second block
   of code will be jumped to.  Typically, this code will clean up any
   resources allocated in the routine, possibly case on the error code
   and perform special processing, and default to RERAISE the error to
   the next handler.  Within the scope of the handler, a local variable
   called NXLocalHandler of type NXHandler holds information about the
   error raised.

   It is illegal to exit the first block of code by any other means than
   NX_VALRETURN, NX_VOIDRETURN, or just falling out the bottom.
 */

typedef void AltProc(void *context, int code, const void *data1, const void *data2);

/*  These nodes represent handlers that are called as normal procedures
    instead of longjmp'ed to.  When these procs return, the next handler
	in the chain is processed.
 */
typedef struct {                /* an alternative node in the handler chain */
	struct _NXHandler *next;            /* ptr to next handler */
	AltProc *proc;                      /* proc to call */
	void *context;                      /* blind data for client */
} AltHandler;

NXHandler *_NXAddAltHandler (AltProc *proc, void *context);
void _NXRemoveAltHandler (NXHandler *handler);

/* private support routines.  Do not call directly. */
void _NXAddHandler( NXHandler *handler );
void _NXRemoveHandler( NXHandler *handler );
#ifndef __cplusplus

extern _setjmp(jmp_buf env);

#define NX_DURING { NXHandler NXLocalHandler;			\
		    _NXAddHandler(&NXLocalHandler);		\
		    if( !_setjmp(NXLocalHandler.jumpState) ) {

#define NX_HANDLER _NXRemoveHandler(&NXLocalHandler); } else {

#define NX_ENDHANDLER }}

#define NX_VALRETURN(cast, val)  do { cast temp = (val);	\
			_NXRemoveHandler(&NXLocalHandler);	\
			return(temp); } while (0)

#define NX_VOIDRETURN	do { _NXRemoveHandler(&NXLocalHandler);	\
			return; } while (0)

/* RAISE and RERAISE are called to indicate an error condition.  They
   initiate the process of jumping up the chain of handlers.
 */

extern void 
_NXRaiseError(int code, const void *data1, const void *data2);


#define NX_RAISE( code, data1, data2 )	\
		_NXRaiseError( (code), (data1), (data2) )

#define NX_RERAISE() 	_NXRaiseError( NXLocalHandler.code,	\
				NXLocalHandler.data1, NXLocalHandler.data2 )
#else

//These Objective-C macros use C++ exception handling rather than
//  setjmp/longjmp. 
//  additionally, using it with Objective-C allows C++ code
//  to execute properly in the face of Objective-C exceptions.
// the chnage is not complete in the implementaion because of
// the alternate handlers. these are grouped with the NEXT exceptions
// on their stack, and the only way for calling them is through
// the "Next" style exceptions

#define NX_DURING { NXHandler NXLocalHandler;			\
		    _NXAddHandler(&NXLocalHandler);		\
		    try {

#define NX_HANDLER _NXRemoveHandler(&NXLocalHandler); } 	\
			   catch (NSException* localException) {

#define NX_ENDHANDLER }}

#define NX_VALRETURN(cast, val)  do { cast temp = (val);	\
			_NXRemoveHandler(&NXLocalHandler);	\
			return(temp); } while (0)

#define NX_VOIDRETURN	do { _NXRemoveHandler(&NXLocalHandler);	\
			return; } while (0)

/* RAISE and RERAISE are called to indicate an error condition.  They
   initiate the process of jumping up the chain of handlers.
 */

void 
_NXRaiseError(int code, const void *data1, const void *data2);


#define NX_RAISE( code, data1, data2 )	\
		_NXRaiseError( (code), (data1), (data2) )

#define NX_RERAISE() 	_NXRaiseError( NXLocalHandler.code,	\
				NXLocalHandler.data1, NXLocalHandler.data2 )

#endif /* __cplusplus */

/* These routines set and return the procedure which is called when
   exceptions are raised.  This procedure must NEVER return.  It will
   usually either longjmp, or call the uncaught exception handler.
   The default exception raiser is also declared
 */
typedef void 
NXExceptionRaiser(int code, const void *data1, const void *data2);

void NXSetExceptionRaiser(NXExceptionRaiser *proc);
NXExceptionRaiser *NXGetExceptionRaiser(void);
extern NXExceptionRaiser NXDefaultExceptionRaiser;


/* The error buffer is used to allocate data which is passed up to other
   handlers.  Clients should clear the error buffer in their top level
   handler.  The Application Kit does this.
 */
void NXResetErrorData(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

// end of old include file "error.h"

/***************	Generic Exception names		***************/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern NSString *NSGenericException;
extern NSString *NSRangeException;
extern NSString *NSInvalidArgumentException;
extern NSString *NSInternalInconsistencyException;

extern NSString *NSMallocException;

extern NSString *NSCharacterConversionException;

/***************	Exception object	***************/

@interface NSException:NSObject <NSCopying, NSCoding> {
    @private
    /* Exceptions are immutable, although they may retain objects in a dictionary that may be mutable;
    Note that -description is used when an exception is reported and can be redefined */
    NSString		*name;		/* Exception name */
    NSString		*reason; 	/* Human readable reason for raising */
    NSDictionary	*userInfo;	/* Any arbitrary other data */
}

+ (NSException *)exceptionWithName:(NSString *)name reason:(NSString *)reason userInfo:(NSDictionary *)userInfo;
    /* Creates an autoreleased exception */

- (NSString *)name;

- (NSString *)reason;

- (NSDictionary *)userInfo;
    /* May return nil */

- (void)raise;
    /* Dispatches according to the appropriate catcher;
    Never returns */

- (id)initWithName:(NSString *)aName reason:(NSString *)aReason userInfo:(NSDictionary *)aUserInfo;
    /* Designated initializer */

@end

/***************	Conveniences for raising	***************/

@interface NSException (NSExceptionRaisingConveniences)

+ (void)raise:(NSString *)name format:(NSString *)format, ...;
    /* Create an exception then raise it; 
    format is used to create the exception 'reason' */

+ (void)raise:(NSString *)name format:(NSString *)format arguments:(va_list)argList;

@end

/***************	Raising and catching	***************/

// Private definition
typedef struct _NSHandler {	/* Private */
    jmp_buf		_jumpState;
    struct _NSHandler	*_next;
    int 		_code;
    const void		*_data1;
    const void		*_data2;
} NSHandler;

/* NS_DURING, NS_HANDLER and NS_ENDHANDLER are always used like:

	NS_DURING
	    some code which might raise an error
	NS_HANDLER
	    code that will be jumped to if an error occurs
	NS_ENDHANDLER

   If any error is raised within the first block of code, the second block of code will be jumped to.  Typically, this code will clean up any resources allocated in the routine, possibly case on the error code and perform special processing, and default to -raise again the exception to the next handler.  Within the scope of the handler, a local variable called 'localException' holds the raised exception.
   It is illegal to exit the first block of code by any other means than
   NS_VALRETURN, NS_VOIDRETURN, or just falling out the bottom.
 */

/* private support routines.  Do not call directly. */
void _NSAddHandler(NSHandler *handler);
void _NSRemoveHandler(NSHandler *handler);
void _NSRaiseError(int code, const void *data1, const void *data2);
extern _setjmp(jmp_buf env);
NSException *_NSExceptionObjectFromHandler(NSHandler *handler);

#ifndef __cplusplus

#define NS_DURING { NSHandler _localHandler;			\
		    _NSAddHandler(&_localHandler);		\
		    if( !_setjmp(_localHandler._jumpState) ) {

#define NS_HANDLER _NSRemoveHandler(&_localHandler); } else { \
		    NSException	*localException = _NSExceptionObjectFromHandler(&_localHandler);

#define NS_ENDHANDLER localException = nil; /* to avoid compiler warning */}}

#define NS_VALUERETURN(val,type)  do { type temp = (val);	\
			_NSRemoveHandler(&_localHandler);	\
			return(temp); } while (0)

#define NS_VOIDRETURN	do { _NSRemoveHandler(&_localHandler);	\
			return; } while (0)
#else

//These Objective-C macros use C++ exception handling rather than
//  setjmp/longjmp.
//  additionally, using it with Objective-C allows C++ code
//  to execute properly in the face of Objective-C exceptions.
// the chnage is not complete in the implementaion because of 
// the alternate handlers. these are grouped with the NEXT exceptions
// on their stack, and the only way for calling them is through
// the "Next" style exceptions

#define NS_DURING { NSHandler _localHandler;			\
		    _NSAddHandler(&_localHandler);		\
		    try {

#define NS_HANDLER  _NSRemoveHandler(&_localHandler); }		\
			catch (NSException* localException) {   

#define NS_ENDHANDLER } }

#define NS_RERAISE()    ( [ localException raise ] )

#define NS_VALUERETURN(val,type)  do { type temp = (val);	\
			_NSRemoveHandler(&_localHandler);	\
			return(temp); } while (0)

#define NS_VOIDRETURN	do { _NSRemoveHandler(&_localHandler);	\
			return; } while (0)

#endif /* __cplusplus */

/***************	Changing the top level error catcher	***********/

/* The top level error catcher can be set to look for certain exceptions, do some work, and then either abort or call the previous top level error catcher */

typedef void NSUncaughtExceptionHandler(NSException *exception);

NSUncaughtExceptionHandler *NSGetUncaughtExceptionHandler(void);
void NSSetUncaughtExceptionHandler(NSUncaughtExceptionHandler *);

/***********	Assertion of program consistency		***********/

/* Assertions evaluate a condition, and if it is false, they call the NSAssertionHandler for the current thread to report that fact.  The assertion macros also take a "description" argument, which should describe the failure that is being tested for.  The description is a printf-style format NSString.  N args may be passed using the NSAssertN() variations.  When calling from within a method, the object's class and method name need not be included in the description, since those args are passed separately.

Assertions are compiled into code if the cpp macro NS_BLOCK_ASSERTIONS is defined.  Runtime control is achieved by substituting a different assertion handler.

Since these macros pass the variables "self" and "_cmd" automatically, they assume that they are being called from within a method context. There is a parallel set of macros for use within C functions. 
*/


@class NSAssertionHandler;

// jjh 12/23/94:  In the following, __PRETTY_FUNCTION__ was changed
// to "some_function"

/* Implementation of asserts (ignore) */
#ifndef NS_BLOCK_ASSERTIONS
#define _NSAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
    do {						\
	if (!(condition)) {				\
	    [[NSAssertionHandler currentHandler] handleFailureInMethod:_cmd object:self file:[NSString stringWithCString:__FILE__] lineNumber:__LINE__ description:(desc), (arg1), (arg2), (arg3), (arg4), (arg5)];	\
	}						\
    } while(0)
#define _NSCAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
    do {						\
	if (!(condition)) {				\
	    [[NSAssertionHandler currentHandler] handleFailureInFunction:[NSString stringWithCString:"some_function"] file:[NSString stringWithCString:__FILE__] lineNumber:__LINE__ description:(desc), (arg1), (arg2), (arg3), (arg4), (arg5)];	\
	}						\
    } while(0)
#else
#define _NSAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)
#define _NSCAssertBody(condition, desc, arg1, arg2, arg3, arg4, arg5)
#endif NS_BLOCK_ASSERTIONS


/*
 * Asserts to use in Objective-C method bodies
 */
 
#define NSAssert5(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
    _NSAssertBody((condition), (desc), (arg1), (arg2), (arg3), (arg4), (arg5))

#define NSAssert4(condition, desc, arg1, arg2, arg3, arg4)	\
    _NSAssertBody((condition), (desc), (arg1), (arg2), (arg3), (arg4), 0)

#define NSAssert3(condition, desc, arg1, arg2, arg3)	\
    _NSAssertBody((condition), (desc), (arg1), (arg2), (arg3), 0, 0)

#define NSAssert2(condition, desc, arg1, arg2)		\
    _NSAssertBody((condition), (desc), (arg1), (arg2), 0, 0, 0)

#define NSAssert1(condition, desc, arg1)		\
    _NSAssertBody((condition), (desc), (arg1), 0, 0, 0, 0)

#define NSAssert(condition, desc)			\
    _NSAssertBody((condition), (desc), 0, 0, 0, 0, 0)

/* convenience for validating parameters.  The text of the condition that fails is passed to the handler. */
#define NSParameterAssert(condition)			\
    _NSAssertBody((condition), @"Invalid parameter not satisfying: %s", #condition, 0, 0, 0, 0)

/*
 * Asserts to use in C function bodies
 */
 
#define NSCAssert5(condition, desc, arg1, arg2, arg3, arg4, arg5)	\
    _NSCAssertBody((condition), (desc), (arg1), (arg2), (arg3), (arg4), (arg5))

#define NSCAssert4(condition, desc, arg1, arg2, arg3, arg4)	\
    _NSCAssertBody((condition), (desc), (arg1), (arg2), (arg3), (arg4), 0)

#define NSCAssert3(condition, desc, arg1, arg2, arg3)	\
    _NSCAssertBody((condition), (desc), (arg1), (arg2), arg3, 0, 0)

#define NSCAssert2(condition, desc, arg1, arg2)	\
    _NSCAssertBody((condition), (desc), (arg1), (arg2), 0, 0, 0)

#define NSCAssert1(condition, desc, arg1)		\
    _NSCAssertBody((condition), (desc), (arg1), 0, 0, 0, 0)

#define NSCAssert(condition, desc)			\
    _NSCAssertBody((condition), (desc), 0, 0, 0, 0, 0)

/* convenience for validating parameters.  The text of the condition that fails is passed to the handler. */
#define NSCParameterAssert(condition)			\
    _NSCAssertBody((condition), @"Invalid parameter not satisfying: %s", #condition, 0, 0, 0, 0)


@interface NSAssertionHandler : NSObject

+ (NSAssertionHandler *)currentHandler;

- (void)handleFailureInMethod:(SEL)selector object:(id)object file:(NSString *)fileName lineNumber:(int)line description:(NSString *)format,...;
    // raises NSInternalInconsistencyException 

- (void)handleFailureInFunction:(NSString *)functionName file:(NSString *)fileName lineNumber:(int)line description:(NSString *)format,...;
    // raises NSInternalInconsistencyException 

@end

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NSEXCEPTION_H */

