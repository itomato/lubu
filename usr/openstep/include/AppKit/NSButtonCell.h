#ident "@(#) NSButtonCell.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSButtonCell_h_
#define _NSButtonCell_h_

#import <AppKit/NSActionCell.h>

@class NSImage <NSCopying, NSCoding>;
@class NSFont <NSCopying, NSCoding>;

typedef enum _NSButtonType {
    NSMomentaryPushButton		= 0,
    NSPushOnPushOffButton		= 1,
    NSToggleButton			= 2,
    NSSwitchButton			= 3,
    NSRadioButton			= 4,
    NSMomentaryChangeButton		= 5,
    NSOnOffButton			= 6,
    NSMomentaryLight			= 7
} NSButtonType;

@interface NSButtonCell : NSActionCell
{
    NSString		*_altContents;
    id			_sound;
    NSString		*_keyEquivalent;
    unsigned int	_keyEquivalentModifierMask;
    unsigned short	_periodicDelay;
    unsigned short	_periodicInterval;
    struct __bcFlags {
        unsigned int        pushIn:1;
        unsigned int        changeContents:1;
        unsigned int        changeBackground:1;
        unsigned int        changeGray:1;
        unsigned int        lightByContents:1;
        unsigned int        lightByBackground:1;
        unsigned int        lightByGray:1;
        unsigned int        hasAlpha:1;
        unsigned int        bordered:1;
        unsigned int        imageOverlaps:1;
        unsigned int        horizontal:1;
        unsigned int        bottomOrLeft:1;
        unsigned int        imageAndText:1;
        unsigned int        imageSizeDiff:1;
        unsigned int        hasKeyEquivalentInsteadOfImage:1;
        unsigned int        lastState:1;
        unsigned int        transparent:1;
        unsigned int        inset:2;
        unsigned int        momentarySound:1;
	unsigned int	    RESERVED:12;
    } _bcFlags;
@private
    // These variables should *only* be accessed through the following methods:
    // setImage:, image, setAlternateImage:, alternateImage,
    // setKeyEquivalentFont:, and keyEquivalentFont
    NSImage *_normalImage;
    id _alternateImageOrKeyEquivalentFont;
}


- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (NSString *)alternateTitle;
- (void)setAlternateTitle:(NSString *)aString;
- (NSImage *)alternateImage;
- (void)setAlternateImage:(NSImage *)image;
- (NSCellImagePosition)imagePosition;
- (void)setImagePosition:(NSCellImagePosition)aPosition;
- (int)highlightsBy;
- (void)setHighlightsBy:(int)aType;
- (int)showsStateBy;
- (void)setShowsStateBy:(int)aType;
- (void)setButtonType:(NSButtonType)aType;
- (NSButtonType)buttonType;
- (BOOL)isOpaque;
- (void)setFont:(NSFont *)fontObj;
- (BOOL)isTransparent;
- (void)setTransparent:(BOOL)flag;
- (void)setPeriodicDelay:(float)delay interval:(float)interval;
- (void)getPeriodicDelay:(float *)delay interval:(float *)interval;
- (NSString *)keyEquivalent;
- (void)setKeyEquivalent:(NSString *)aKeyEquivalent;
- (unsigned int)keyEquivalentModifierMask;
- (void)setKeyEquivalentModifierMask:(unsigned int)mask;
- (NSFont *)keyEquivalentFont;
- (void)setKeyEquivalentFont:(NSFont *)fontObj;
- (void)setKeyEquivalentFont:(NSString *)fontName size:(float)fontSize;
- (void)performClick:(id)sender;

@end


#ifndef STRICT_OPENSTEP

@class Sound;
@interface NSButtonCell(NSSound)
- (Sound *)sound;
- (void)setSound:(Sound *)aSound;
@end

#endif

#endif // _NSButtonCell_h_
