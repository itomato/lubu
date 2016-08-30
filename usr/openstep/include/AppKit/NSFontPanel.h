#ident "@(#) NSFontPanel.h, Rev 1.3, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSPanel.h"
#import "NSFont.h"

@class NSMatrix;
@class NSButton;

/* Tags of views in the FontPanel */

enum {
    NSFPPreviewButton			= 131,
    NSFPRevertButton			= 130,
    NSFPSetButton			= 132,
    NSFPPreviewField			= 128,
    NSFPSizeField			= 129,
    NSFPSizeTitle			= 133,
    NSFPCurrentField			= 134
};

@interface NSFontPanel : NSPanel
{
    NSMatrix 		*_faces;
    NSMatrix 		*_families;
    id                  _preview;
    id                  _current;
    id                  _size;
    NSMatrix 		*_sizes;
    id                  _manager;
    id                  _selFont;
    struct _NSFontMetrics *_selMetrics;
    int                 _curTag;
    id                  _accessoryView;
    NSString		*_keyBuffer;
    NSButton		*_setButton;
    id                  _separator;
    id                  _sizeTitle;
    NSString		*_lastPreview;
    NSTimeInterval      _lastKeyTime;
    id		        _chooser;
    id		        _titles;
    id		        _previewBox;
    struct __fpFlags {
        unsigned int        multipleFont:1;
        unsigned int        dirty:1;
        unsigned int	    doingPreviewButton:1;
        unsigned int        amPreviewing:1;
        unsigned int        alwaysPreview:1;
        unsigned int        dontPreview:1;
        unsigned int        RESERVED:26;
    }                   _fpFlags;
}

+ (NSFontPanel *)sharedFontPanel;
- (NSView *)accessoryView;
- (void)setAccessoryView:(NSView *)aView;
- (void)orderWindow:(NSWindowOrderingMode)place relativeTo:(int)otherWin;
- (void)setPanelFont:(NSFont *)fontObj isMultiple:(BOOL)flag;
- (NSFont *)panelConvertFont:(NSFont *)fontObj;
- (BOOL)worksWhenModal;
- (BOOL)isEnabled;
- (void)setEnabled:(BOOL)flag;

@end
