#ident "@(#) NSFormCell.h, Rev 1.3, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSActionCell.h"

@interface NSFormCell : NSActionCell
{
    float	_titleWidth;
    id		_titleCell;
    float	_titleEndPoint;
}


- (id)initTextCell:(NSString *)aString;

- (float)titleWidth:(NSSize)aSize;
- (float)titleWidth;
- (void)setTitleWidth:(float)width;
- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (NSFont *)titleFont;
- (void)setTitleFont:(NSFont *)fontObj;
- (NSTextAlignment)titleAlignment;
- (void)setTitleAlignment:(NSTextAlignment)mode;
- (BOOL)isOpaque;
- (NSSize)cellSizeForBounds:(NSRect)aRect;
- (void)drawInteriorWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;

@end
