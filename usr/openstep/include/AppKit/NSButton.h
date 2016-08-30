#ident "@(#) NSButton.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSControl.h"
#import "NSCell.h"
#import "NSButtonCell.h"

@interface NSButton : NSControl


- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (NSString *)alternateTitle;
- (void)setAlternateTitle:(NSString *)aString;
- (NSImage *)image;
- (void)setImage:(NSImage *)image;
- (NSImage *)alternateImage;
- (void)setAlternateImage:(NSImage *)image;
- (NSCellImagePosition)imagePosition;
- (void)setImagePosition:(NSCellImagePosition)aPosition;
- (void)setButtonType:(NSButtonType)aType;
- (int)state;
- (void)setState:(int)value;
- (BOOL)isBordered;
- (void)setBordered:(BOOL)flag;
- (BOOL)isTransparent;
- (void)setTransparent:(BOOL)flag;
- (void)setPeriodicDelay:(float)delay interval:(float)interval;
- (void)getPeriodicDelay:(float *)delay interval:(float *)interval;
- (NSString *)keyEquivalent;
- (void)setKeyEquivalent:(NSString *)charCode;
- (unsigned int)keyEquivalentModifierMask;
- (void)setKeyEquivalentModifierMask:(unsigned int)mask;
- (void)highlight:(BOOL)flag;
- (BOOL)performKeyEquivalent:(NSEvent *)key;
- (void)performClick:(id)sender;

@end


#ifndef STRICT_OPENSTEP

@class Sound;
@interface NSButton(NSSound)
- (Sound *)sound;
- (void)setSound:(Sound *)soundObj;
@end

#endif
