#ident "@(#) NSColorPicking.h, Rev 1.5, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.


#ifndef _NSColorPicking_h_
#define _NSColorPicking_h_

#import <Foundation/NSObject.h>

@class NSColorList <NSCoding>;
@class NSColor <NSCopying, NSCoding>;
@class NSButtonCell;
@class NSColorPanel;
@class NSImage <NSCopying, NSCoding>;
@class NSView;

@protocol NSColorPickingDefault

// The following methods are implemented by the generic base class:
// NXColorPicker, and only need be implemented (overridden) by the CustomPicker
// developer if there is a need.

// "mask" is the mask (if any) passed to the ColorPanel by the
// + setPickerMask: method.  If your picker supports any of the bits in
// the mask, return "self", otherwise, return "nil" (default is "self" if not
// overridden, since if the "setPickerMask" method is never called, the
// ColorPanel will just start off with the normal picker modes, of which
// your custom mode will not be a part). This method can be used to turn
// off some (or all) of your subpickers, if you have any (like sliders).
// If this method returns "nil", the object will be freed.
// 
// "owningColorPanel" is the id of the instantiating ColorPanel.  
// if this method is overridden, the base class' (NXColorPicker's) 
// initFromPickerMask method should be called before any subclass processing.
// The instance variable "colorPanel" is set in this method.
// FOR PERFORMANCE, DO NOT LOAD .NIBS, ETC. HERE!!  WAIT 'TILL PROVIDENEWVIEW!
- (id)initWithPickerMask:(int)mask colorPanel:(NSColorPanel *)owningColorPanel;
- (NSImage *)provideNewButtonImage;
- (void)insertNewButtonImage:(NSImage *)newButtonImage in:(NSButtonCell *)buttonCell;
- (void)viewSizeChanged:(id)sender;
- (void)alphaControlAddedOrRemoved:(id)sender;
- (void)attachColorList:(NSColorList *)colorList;
- (void)detachColorList:(NSColorList *)colorList;
- (void)setMode:(int)mode;   

@end



@protocol NSColorPickingCustom

// These methods *MUST* be implemented by the CustomPicker, or an error
// will occur!

// Return No if "mode" not supported.
- (BOOL)supportsMode:(int)mode;   
- (int)currentMode;
// "Yes" on very first call (load your .nibs etc when "YES").
- (NSView *)provideNewView:(BOOL)initialRequest;  // "Yes" on very first call.
- (void)setColor:(NSColor *)newColor;

@end
// FIX ME NOW!  THIS DOES NOT END WITH @end IN APPKIT-160

#endif // _NSColorPicking_h_
