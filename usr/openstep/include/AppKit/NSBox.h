#ident "@(#) NSBox.h, Rev 1.4, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#ifndef _NSBox_h_
#define _NSBox_h_

#import <AppKit/NSView.h>

@class NSCell <NSCopying, NSCoding>;
@class NSFont <NSCopying, NSCoding>;

typedef enum _NSTitlePosition {
    NSNoTitle				= 0,
    NSAboveTop				= 1,
    NSAtTop				= 2,
    NSBelowTop				= 3,
    NSAboveBottom			= 4,
    NSAtBottom				= 5,
    NSBelowBottom			= 6
} NSTitlePosition;

@interface NSBox : NSView
{
    id                  _titleCell;
    id                  _contentView;
    NSSize              _offsets;
    NSRect              _borderRect;
    NSRect              _titleRect;
    struct __bFlags {
	NSBorderType	borderType:2;
	NSTitlePosition	titlePosition:3;
	unsigned int	transparent:1;
	unsigned int	_RESERVED:26;
    } _bFlags;
}

- (NSBorderType)borderType;
- (NSTitlePosition)titlePosition;
- (void)setBorderType:(NSBorderType)aType;
- (void)setTitlePosition:(NSTitlePosition)aPosition;
- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (NSFont *)titleFont;
- (void)setTitleFont:(NSFont *)fontObj;
- (NSRect)borderRect;
- (NSRect)titleRect;
- (id)titleCell;
- (void)sizeToFit;
- (NSSize)contentViewMargins;
- (void)setContentViewMargins:(NSSize)offsetSize;
- (void)setFrameFromContentFrame:(NSRect)contentFrame;
- (id)contentView;
- (void)setContentView:(NSView *)aView;


@end

#endif // _NSBox_h_
