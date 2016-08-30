#ident "@(#) NSScreen.h, Rev 1.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import <Foundation/NSObject.h>
#import "NSGraphics.h"

@interface NSScreen : NSObject {
@private
    NSRect	  _frame;
    NSWindowDepth _depth;

    id		  _xScr;
}

+ (NSArray *)screens;		/* All screens; first one is "zero" screen */
+ (NSScreen *)mainScreen;	/* Screen with key window */
+ (NSScreen *)deepestScreen;

- (NSWindowDepth)depth;
- (NSRect)frame;
- (NSDictionary *)deviceDescription;

/* List of window depths supported on a particular screen. */

- (const NSWindowDepth *const) supportedWindowDepths; /* 0 terminated */
@end

