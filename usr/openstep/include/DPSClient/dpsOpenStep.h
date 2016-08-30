#ident "@(#) dpsOpenStep.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//    	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//    	DPS routines specific to the OpenStep implementation of DPSClient.
//    	This API is part of OpenStep.

#ifndef DPSOPENSTEP_H
#define DPSOPENSTEP_H

#import <DPS/dpsclient.h>
#import <DPS/dpsXuserpath.h>

#import <Foundation/Foundation.h>

#ifdef __cplusplus
extern "C" {
#endif

/* === Exception names === */

extern NSString *DPSPostscriptErrorException;
extern NSString *DPSNameTooLongException;
extern NSString *DPSResultTagCheckException;
extern NSString *DPSResultTypeCheckException;
extern NSString *DPSInvalidContextException;

extern NSString *DPSCantConnectException;

#ifndef	STRICT_OPENSTEP

/*
 * these exceptions are not supported on Sun implementation
 */

extern NSString *DPSSelectException;
extern NSString *DPSConnectionClosedException;
extern NSString *DPSReadException;
extern NSString *DPSWriteException;
extern NSString *DPSInvalidFDException;
extern NSString *DPSInvalidTEException;
extern NSString *DPSInvalidPortException;
extern NSString *DPSOutOfMemoryException;
#endif

/*=== CONSTANTS ===*/


/* operation types for composite operators */
typedef enum _NSCompositingOperation {
    NSCompositeClear		= 0,
    NSCompositeCopy		= 1,
    NSCompositeSourceOver	= 2,
    NSCompositeSourceIn		= 3,
    NSCompositeSourceOut	= 4,
    NSCompositeSourceAtop	= 5,
    NSCompositeDestinationOver	= 6,
    NSCompositeDestinationIn	= 7,
    NSCompositeDestinationOut	= 8,
    NSCompositeDestinationAtop  = 9,
    NSCompositeXOR		= 10,
    NSCompositePlusDarker	= 11,
    NSCompositeHighlight	= 12,
    NSCompositePlusLighter	= 13
} NSCompositingOperation;

/* special values for alpha */
enum {
    NSAlphaEqualToData		= 1,
    NSAlphaAlwaysOne		= 2
};

/* types of window backing store */
typedef enum _NSBackingStoreType {
    NSBackingStoreRetained	 = 0,
    NSBackingStoreNonretained	 = 1,
    NSBackingStoreBuffered	 = 2
} NSBackingStoreType;

/* ways to order windows */
typedef enum _NSWindowOrderingMode {
    NSWindowAbove		 =  1,
    NSWindowBelow		 = -1,
    NSWindowOut			 =  0
} NSWindowOrderingMode;


/* a userobject that can be used to pass a PostScript "null" */
enum {
    DPSNullObject = 1
};

#ifdef __cplusplus
}
#endif

#endif DPSOPENSTEP_H
