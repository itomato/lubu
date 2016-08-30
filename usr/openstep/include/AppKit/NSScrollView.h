#ident "@(#) NSScrollView.h, Rev 1.9, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSScrollView_h_
#define _NSScrollView_h_

#import <AppKit/NSView.h>

@class NSScroller;
@class NSClipView;
@class NSColor <NSCopying, NSCoding>;

@interface NSScrollView : NSView
{
    NSScroller	*_vScroller;
    NSScroller	*_hScroller;
    NSClipView	*_contentView;
    float	_pageContext;
    float	_lineAmount;
    id		_ruler;
    struct __sFlags {
	unsigned int        vScrollerRequired:1;
	unsigned int        hScrollerRequired:1;
	unsigned int        vScrollerStatus:1;
	unsigned int        hScrollerStatus:1;
	unsigned int        noDynamicScrolling:1;
	NSBorderType        borderType:2;
	unsigned int        oldRulerInstalled:1;
	unsigned int        RESERVED:24;
    } _sFlags;
    void       *_reserved1;
}

+ (NSSize)frameSizeForContentSize:(NSSize)cSize hasHorizontalScroller:(BOOL)hFlag hasVerticalScroller:(BOOL)vFlag borderType:(NSBorderType)aType;
+ (NSSize)contentSizeForFrameSize:(NSSize)fSize hasHorizontalScroller:(BOOL)hFlag hasVerticalScroller:(BOOL)vFlag borderType:(NSBorderType)aType;

- (NSRect)documentVisibleRect;
- (NSSize)contentSize;

- (void)setDocumentView:(NSView *)aView;
- (id)documentView;
- (void)setContentView:(NSClipView *)contentView;
- (NSClipView *)contentView;
- (void)setDocumentCursor:(NSCursor *)anObj;
- (NSCursor *)documentCursor;
- (void)setBorderType:(NSBorderType)aType;
- (NSBorderType)borderType;
- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;
- (void)setHasVerticalScroller:(BOOL)flag;
- (BOOL)hasVerticalScroller;
- (void)setHasHorizontalScroller:(BOOL)flag;
- (BOOL)hasHorizontalScroller;
- (void)setVerticalScroller:(NSScroller *)anObject;
- (NSScroller *)verticalScroller;
- (void)setHorizontalScroller:(NSScroller *)anObject;
- (NSScroller *)horizontalScroller;
- (void)setLineScroll:(float)value;
- (float)lineScroll;
- (void)setPageScroll:(float)value;
- (float)pageScroll;
- (void)setScrollsDynamically:(BOOL)flag;
- (BOOL)scrollsDynamically;
- (void)tile;
- (void)reflectScrolledClipView:(NSClipView *)cView;

@end

@interface NSScrollView(NSRuler)
- (void)toggleRuler:(id)sender;
- (BOOL)isRulerVisible;
@end

#endif // _NSScrollView_h_
