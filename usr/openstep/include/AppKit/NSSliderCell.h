#ident "@(#) NSSliderCell.h, Rev 1.4, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSActionCell.h"

@interface NSSliderCell : NSActionCell
{
    NSImage            *_knobImage;
    int                 _weAreVertical;
    float               _knobThickness;
    NSImage            *_backImage;
    id                  _textCell;
    double              _altIncValue;
    BOOL		_copyImageBeforeModifying;
    double              _value;
    double              _maxValue;
    double              _minValue;
    NSRect              _trackRect;
}


+ (BOOL)prefersTrackingUntilMouseUp;


- (double)minValue;
- (void)setMinValue:(double)aDouble;
- (double)maxValue;
- (void)setMaxValue:(double)aDouble;
- (void)setAltIncrementValue:(double)incValue;
- (double)altIncrementValue;
- (int)isVertical;
- (NSSize)cellSizeForBounds:(NSRect)aRect;
- (void)setTitleColor:(NSColor *)newColor;
- (NSColor *)titleColor;
- (void)setTitleFont:(NSFont *)fontObj;
- (NSFont *)titleFont;
- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (void)setTitleCell:(NSCell *)aCell;
- (id)titleCell;
- (void)setKnobThickness:(float)aFloat;
- (float)knobThickness;
- (NSRect)knobRectFlipped:(BOOL)flipped;
- (void)drawKnob:(NSRect)knobRect;
- (void)drawKnob;
- (void)drawBarInside:(NSRect)aRect flipped:(BOOL)flipped;
- (NSRect)trackRect;	// Only valid while tracking the mouse!

@end
