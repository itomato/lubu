#ident "@(#) NSTextFieldCell.h, Rev 1.4, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSActionCell.h"
#import "NSColor.h"

@interface NSTextFieldCell : NSActionCell  {
    NSColor *_backgroundColor;
    NSColor *_textColor;
    struct __tfFlags {
	unsigned int drawsBackground:1;
	unsigned int :31;
    } _tfFlags;
}


- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;
- (void)setDrawsBackground:(BOOL)flag;
- (BOOL)drawsBackground;
- (void)setTextColor:(NSColor *)color;
- (NSColor *)textColor;
- (NSText *)setUpFieldEditorAttributes:(NSText *)textObj;

@end
