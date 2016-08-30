#ident "@(#) NSClipView.h, Rev 1.5, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSClipView_h_
#define _NSClipView_h_

#import <AppKit/NSView.h>

@class NSColor <NSCopying, NSCoding>;

@interface NSClipView : NSView
{
    NSColor             *_backgroundColor;
    NSView              *_docView;
    NSRect              _docRect;
    NSCursor            *_cursor;
    void                *_reserved1;
    struct __cvFlags {
	unsigned int        isFlipped:1;
	unsigned int        onlyUncovered:1;
	unsigned int        reflectScroll:1;
	unsigned int        usedByCell:1;
	unsigned int	    scrollClipTo:1;
	unsigned int	    noCopyOnScroll:1;
        unsigned int        RESERVED:26;
    } _cvFlags;
}

- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;
- (void)setDocumentView:(NSView *)aView;
- (id)documentView;
- (NSRect)documentRect;
- (void)setDocumentCursor:(NSCursor *)anObj;
- (NSCursor *)documentCursor;
- (NSRect)documentVisibleRect;
- (void)viewBoundsChanged:(NSNotification *)notification;
- (void)viewFrameChanged:(NSNotification *)notification;
- (void)setCopiesOnScroll:(BOOL)flag;
- (BOOL)copiesOnScroll;
- (BOOL)autoscroll:(NSEvent *)theEvent;
- (NSPoint)constrainScrollPoint:(NSPoint)newOrigin;
- (void)scrollToPoint:(NSPoint)newOrigin;

@end

@interface NSView(NSClipViewSuperview)
- (void)reflectScrolledClipView:(NSClipView *)aClipView;
- (void)scrollClipView:(NSClipView *)aClipView toPoint:(NSPoint)aPoint;
@end

#endif // _NSClipView_h_
