#ident "@(#) NSSlider.h, Rev 1.5, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSControl.h"

@interface NSSlider : NSControl
{
}


- (double)minValue;
- (void)setMinValue:(double)aDouble;
- (double)maxValue;
- (void)setMaxValue:(double)aDouble;
- (void)setTitleCell:(NSCell *)aCell;
- (id)titleCell;
- (void)setTitleColor:(NSColor *)newColor;
- (NSColor *)titleColor;
- (void)setTitleFont:(NSFont *)fontObj;
- (NSFont *)titleFont;
- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (void)setKnobThickness:(float)aFloat;
- (float)knobThickness;
- (void)setImage:(NSImage *)backgroundImage;
- (NSImage *)image;
- (int)isVertical;
- (BOOL)acceptsFirstMouse:(NSEvent *)theEvent;

@end
