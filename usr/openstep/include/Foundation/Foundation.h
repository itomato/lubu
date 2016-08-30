#ident "@(#) Foundation.h, Rev 1.14, 97/02/10"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.


/***************	Assumptions			***************/
#import <stdio.h>
#import <stdlib.h>
#import <unistd.h>

/***************	Language			***************/

#import <Foundation/NSException.h>
#import <Foundation/NSInvocation.h>
#import <Foundation/NSMethodSignature.h>
#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSObject.h>

/***************	Basics			***************/

#import <Foundation/NSAutoreleasePool.h>
#import <Foundation/NSProxy.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSUtilities.h>
#import <Foundation/NSZone.h>

/***************	String, Data, Value	***************/

#import <Foundation/NSCharacterSet.h>
#import <Foundation/NSData.h>
#import <Foundation/NSString.h>
#import <Foundation/NSValue.h>

/***************	Collections		***************/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSHashTable.h>
#import <Foundation/NSMapTable.h>

/***************	Persistency		***************/

#import <Foundation/NSArchiver.h>
#import <Foundation/NSCoder.h>
#import <Foundation/NSSerialization.h>

/***************	Distribution		***************/

#import <Foundation/NSConnection.h>
#import <Foundation/NSDistantObject.h>

/***************	Misc			***************/

#import <Foundation/NSBundle.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSNotification.h>
#import <Foundation/NSNotificationQueue.h>
#import <Foundation/NSLock.h>
#import <Foundation/NSPathUtilities.h>
#import <Foundation/NSScanner.h>
#import <Foundation/NSTimer.h>
#import <Foundation/NSRunLoop.h>
#import <Foundation/NSThread.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSProcessInfo.h>
#import <Foundation/NSUserDefaults.h>

/***************	Non OPENSTEP additions		*******/

#if !defined(STRICT_OPENSTEP)
#import <Foundation/NSByteOrder.h>
#import <Foundation/NSDecimal.h>
#import <Foundation/NSDecimalNumber.h>
#import <Foundation/NSDateFormatter.h>
#import <Foundation/NSFormatter.h>
#import <Foundation/NSNumberFormatter.h>
#import <Foundation/NSPortCoder.h>
#import <Foundation/NSPosixFileDescriptor.h>
#endif /* !STRICT_OPENSTEP */

