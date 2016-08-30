#ident "@(#) NSActionCell.h, Rev 1.5, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSCell.h"

@interface NSActionCell : NSCell
{
    int	_tag;        
    id	_target;     
    SEL	_action;     
    id	_controlView;      
}

- (NSView *)controlView;
- (void)setFont:(NSFont *)fontObj;
- (void)setAlignment:(NSTextAlignment)mode;
- (void)setBordered:(BOOL)flag;
- (void)setBezeled:(BOOL)flag;
- (void)setEnabled:(BOOL)flag;
- (void)setFloatingPointFormat:(BOOL)autoRange left:(unsigned int)leftDigits right:(unsigned int)rightDigits;
- (void)setImage:(NSImage *)image;
- (id)target;
- (void)setTarget:(id)anObject;
- (SEL)action;
- (void)setAction:(SEL)aSelector;
- (int)tag;
- (void)setTag:(int)anInt;
- (NSString *)stringValue;
- (int)intValue;
- (float)floatValue;
- (double)doubleValue;
- (void)drawWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;

#ifndef STRICT_OPENSTEP
- (void)setObjectValue:(id)obj;
#endif STRICT_OPENSTEP

@end
