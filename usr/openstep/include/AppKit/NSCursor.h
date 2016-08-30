#ident "@(#) NSCursor.h, Rev 1.13, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSCursor_h_
#define _NSCursor_h_

#import <Foundation/NSObject.h>
#import <AppKit/NSColor.h>

@class NSImage <NSCopying, NSCoding>;
@class NSEvent <NSCopying, NSCoding>;

@interface NSCursor : NSObject <NSCoding> 
{
    NSPoint 		 _hotSpot;

    struct _cursorFlags {
	unsigned int 	 onMouseExited:1;
	unsigned int 	 onMouseEntered:1;
	unsigned int :30;

    } 			 _flags;
    id 			 _image;
@private
    id			 _xCursor;
    NSColor              *foreground;
    NSColor              *background;
}

+ (void)pop;
+ (NSCursor *)currentCursor;
+ (NSCursor *)arrowCursor;
+ (NSCursor *)IBeamCursor;
+ (NSCursor *)copyCursor;
+ (NSCursor *)linkCursor;
+ (NSCursor *)genericCursor;

+ (void)hide;
+ (void)unhide;
+ (void)setHiddenUntilMouseMoves:(BOOL)flag;

- (id)initWithImage:(NSImage *)newImage hotSpot:(NSPoint)hotSpot;

- (id)initWithImage:(NSImage *)newImage
    foregroundColorHint:(NSColor *)fg
    backgroundColorHint:(NSColor *)bg
    hotSpot:        (NSPoint) hotSpot;

- (NSImage *)image;
- (void)setImage:(NSImage *)newImage;
- (void)setImage:    (NSImage *)newImage 
    foregroundColor: (NSColor *)fg
    backgroundColor: (NSColor *)bg;
- (void)setForeground: (NSColor *)fg background: (NSColor *)bg;
- (void)getForeground: (NSColor *)fg background: (NSColor *)bg;
- (NSPoint)hotSpot;
- (void)push;
- (void)pop;
- (void)set;
- (void)setOnMouseExited:(BOOL)flag;
- (void)setOnMouseEntered:(BOOL)flag;
- (BOOL)isSetOnMouseExited;
- (BOOL)isSetOnMouseEntered;
- (void)mouseEntered:(NSEvent *)theEvent;
- (void)mouseExited:(NSEvent *)theEvent;
- (void)_setCurrentCursor:(BOOL)entered;

@end

#endif // _NSCursor_h_
