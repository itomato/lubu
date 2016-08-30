#ident "@(#) NSPageLayout.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSPageLayout_h_
#define _NSPageLayout_h_

#import <AppKit/NSApplication.h>
#import <AppKit/NSPanel.h>

@class NSButton;
@class NSPrintInfo <NSCopying, NSCoding>;
@class NSForm;

enum {
    NSPLImageButton			= 50,
    NSPLTitleField			= 51,
    NSPLPaperNameButton			= 52,
    NSPLUnitsButton			= 54,
    NSPLWidthForm			= 55,
    NSPLHeightForm			= 56,
    NSPLOrientationMatrix		= 57,
    NSPLCancelButton			= NSCancelButton,
    NSPLOKButton			= NSOKButton
};

@interface NSPageLayout : NSPanel
{
    id                  _appIcon;
    NSForm              *_height;
    NSForm              *_width;
    NSButton 		*_ok;
    id                  _cancel;
    id                  _orientation;
    id                  _paperNamePopUp;
    id                  _unitsPopUp;
    int                 _exitTag;
    id                  _paperView;
    id                  _paperViewShadow;
    id                  _accessoryView;
    NSPrintInfo		*_printInfo;
    unsigned char	_currUnits;
    BOOL                _otherPaper;
    BOOL		_recyclable;
}

+ (NSPageLayout *)pageLayout;

- (void)setAccessoryView:(NSView *)aView;
- (NSView *)accessoryView;
- (void)readPrintInfo;
- (void)writePrintInfo;
- (NSPrintInfo *)printInfo;
- (int)runModalWithPrintInfo:(NSPrintInfo *)pInfo;
- (int)runModal;

#ifndef STRICT_OPENSTEP
- (void)convertOldFactor:(float *)old newFactor:(float *)newx;
- (void)pickedButton:(id)sender;
- (void)pickedOrientation:(id)sender;
- (void)pickedPaperSize:(id)sender;
- (void)pickedUnits:(id)sender;
#endif

@end

@interface NSApplication(NSPageLayoutPanel)
- (void)runPageLayout:(id)sender;
@end
 
#endif // _NSPageLayout_h_
