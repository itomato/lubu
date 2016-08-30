#ident "@(#) NSCachedImageRep.h, Rev 1.3, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSImageRep.h"
@class NSWindow;

@interface NSCachedImageRep : NSImageRep {
    NSPoint _origin;
    NSWindow *_window;
    void *_cache;
}

/* References the specified rect within the window; the window is retained */
- (id)initWithWindow:(NSWindow *)win rect:(NSRect)rect;

/* Creates a location in some window. Will be freed when rep is freed */
- (id)initWithSize:(NSSize)size depth:(NSWindowDepth)depth separate:(BOOL)flag alpha:(BOOL)alpha;

- (NSWindow *)window;
- (NSRect)rect;

@end
