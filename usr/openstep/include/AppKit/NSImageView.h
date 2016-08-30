#ident "@(#) NSImageView.h, Rev 1.4, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1996, NeXT Computer, Inc.
//	All rights reserved.

#ifndef STRICT_OPENSTEP

#import <AppKit/NSControl.h>
#import <AppKit/NSImageCell.h>

@interface NSImageView : NSControl
{
    BOOL _editable;
    id _target;                    // for action messages
    SEL _action;                   // call here after an image drag-drop
}


- (NSImage *)image;
- (void)setImage:(NSImage *)newImage;

- (NSImageAlignment)imageAlignment;
- (void)setImageAlignment:(NSImageAlignment)newAlign;
- (NSImageScaling)imageScaling;
- (void)setImageScaling:(NSImageScaling)newScaling;
- (NSImageFrameStyle)imageFrameStyle;
- (void)setImageFrameStyle:(NSImageFrameStyle)newStyle;
- (void)setEditable:(BOOL)yn;
- (BOOL)isEditable;


@end

#endif STRICT_OPENSTEP
