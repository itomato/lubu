#ident "@(#) NSColorPicker.h, Rev 1.3, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSColorPicking.h"
#import "NSColorPanel.h"

@class NSButtonCell;

@interface NSColorPicker : NSObject <NSColorPickingDefault>
{
    id _imageObject;
    NSColorPanel *_colorPanel;
}
- (id)initWithPickerMask:(int)mask colorPanel:(NSColorPanel *)owningColorPanel;
- (NSColorPanel *)colorPanel;
- (NSImage *)provideNewButtonImage;
- (void)insertNewButtonImage:(NSImage *)newButtonImage in:(NSButtonCell *)buttonCell;
- (void)viewSizeChanged:(id)sender;
- (void)attachColorList:(NSColorList *)colorList;
- (void)detachColorList:(NSColorList *)colorList;
- (void)setMode:(int)mode;

@end
