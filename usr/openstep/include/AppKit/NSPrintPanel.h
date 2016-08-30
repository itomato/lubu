#ident "@(#) NSPrintPanel.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSPanel.h"


@class NSPopUpButton;
@class NSButtonCell;
@class NSMatrix;

enum {
    NSPPSaveButton			= 3,
    NSPPPreviewButton			= 4,
    NSFaxButton				= 5,
    NSPPTitleField			= 40,
    NSPPImageButton			= 41,
    NSPPNameTitle			= 42,
    NSPPNameField			= 43,
    NSPPNoteTitle			= 44,
    NSPPNoteField			= 45,
    NSPPStatusTitle			= 46,
    NSPPStatusField			= 47,
    NSPPCopiesField			= 49,
    NSPPPageChoiceMatrix		= 50,
    NSPPPageRangeFrom			= 51,
    NSPPPageRangeTo			= 52,
    NSPPScaleField			= 53,
    NSPPOptionsButton			= 54,
    NSPPPaperFeedButton			= 55,
    NSPPLayoutButton			= 56
};

@interface NSPrintPanel : NSPanel
{
    id                  _appIcon;
    id			_buttons;
    id                  _cancel;
    id                  _copies;
    id                  _feed;
    id			_feedBox;
    id                  _firstPage;
    id                  _lastPage;
    id                  _name;
    id                  _note;
    NSButtonCell	*_ok;
    id			_optionsButton;
    id                  _pageMode;
    id                  _preview;
    id			_printerListBox;
    NSPopUpButton       *resolutionList;
    id                  _save;
    id                  _status;
    id			_deviceButtonsBox;
    id			_ppdMessage;
    id                  _accessoryView;
    NSMatrix		*_printers;
    int                 _exitTag;
    BOOL		_isPPDFileOK;
    BOOL		_recyclable;
    id			_controlBox;
    id			_printerFeatures;
    NSPopUpButton	*_printServicesPopUp;
    BOOL		_checkedForPrintServicesPopUp;
}

+ (NSPrintPanel *)printPanel;

- (void)setAccessoryView:(NSView *)aView;
- (NSView *)accessoryView;
- (void)pickedButton:(id)sender;
- (void)pickedLayoutList:(id)sender;
- (void)pickedAllPages:(id)sender;
- (void)updateFromPrintInfo;
- (void)finalWritePrintInfo;
- (int)runModal;

@end
