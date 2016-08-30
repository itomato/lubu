#ident "@(#) NSImageCell.h, Rev 1.4, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1996, NeXT Computer, Inc.
//	All rights reserved.

#ifndef STRICT_OPENSTEP

#import <AppKit/NSCell.h>

@class NSImage;

typedef enum {
    NSScaleProportionally = 0,   // Fit propoRtionally
    NSScaleToFit,                // Forced fit (distort if necessary)
    NSScaleNone                  // Don't scale (clip)
} NSImageScaling;

typedef enum {
    NSImageAlignCenter = 0,
    NSImageAlignTop,
    NSImageAlignTopLeft,
    NSImageAlignTopRight,
    NSImageAlignLeft,
    NSImageAlignBottom,
    NSImageAlignBottomLeft,
    NSImageAlignBottomRight,
    NSImageAlignRight
} NSImageAlignment;

typedef enum {
    NSImageFrameNone = 0,
    NSImageFramePhoto,
    NSImageFrameGrayBezel,
    NSImageFrameGroove,
    NSImageFrameButton
} NSImageFrameStyle;


@interface NSImageCell : NSCell <NSCopying, NSCoding>
{
    NSImageAlignment _align;
    NSImageScaling _scale;
    NSImageFrameStyle _style;
    NSImage *_scaledImage;
}

- (NSImageAlignment)imageAlignment;
- (void)setImageAlignment:(NSImageAlignment)newAlign;
- (NSImageScaling)imageScaling;
- (void)setImageScaling:(NSImageScaling)newScaling;
- (NSImageFrameStyle)imageFrameStyle;
- (void)setImageFrameStyle:(NSImageFrameStyle)newStyle;

@end

#endif STRICT_OPENSTEP
