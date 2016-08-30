#ident "@(#) NSHelpPanel.h, Rev 1.8, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSHelpPanel_h_
#define _NSHelpPanel_h_

#import <AppKit/NSApplication.h>
#import <AppKit/NSPanel.h>

@class NSEvent <NSCopying, NSCoding>;
@class NSSplitView;
@class NSCStringText;
@class NSSplitView;
@class NSHelpText;


@interface NSHelpPanel:NSPanel
{
    id		_textScrollView;
    id		_tocScrollView;
    id		_indexButton;
    id		_backtrackButton;
    id		_findButton;
    id		_findField;
    NSSplitView	*_splitView;
    id		_history;
    id		_tempText;
    NSHelpText	*_tocView;
    NSHelpText	*_indexView;
    NSCStringText *_textView;
    NSString	*_mainHelpDirectory;
    NSString	*_helpDirectory;
    NSString	*_indexDirectory;
    NSString	*_helpFile;
    int		_oldStartSel;
    int		_oldEndSel;
    float	_panelWidth;
    BOOL	_needToWriteSizes;
    id		_searchStorage;
}

+ (NSHelpPanel *)sharedHelpPanel;
+ (NSHelpPanel *)sharedHelpPanelWithDirectory:(NSString *)helpDirectory;

+ (void)attachHelpFile:(NSString *)filename markerName:(NSString *)markername to:(id)object;
+ (void)detachHelpFrom:(id)object;
+ (void)setHelpDirectory:(NSString *)helpDirectory;

- (void)addSupplement:(NSString *)helpDirectory inPath:(NSString *)supplementPath;

- (NSString *)helpDirectory;
- (NSString *)helpFile;
- (void)print:(id)sender;
- (void)showFile:(NSString *)filename atMarker:(NSString *)markername;
- (BOOL)showHelpAttachedTo:(id)object;

@end


@interface NSApplication(NSHelpPanel)
- (void)orderFrontHelpPanel:(id)sender;
@end

#endif // _NSHelpPanel_h_
