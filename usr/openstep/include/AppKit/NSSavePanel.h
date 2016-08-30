#ident "@(#) NSSavePanel.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSPanel.h"

/* Tags of views in the SavePanel */

enum {
    NSFileHandlingPanelImageButton	= 150,
    NSFileHandlingPanelTitleField	= 151,
    NSFileHandlingPanelBrowser		= 152,
    NSFileHandlingPanelCancelButton	= NSCancelButton,
    NSFileHandlingPanelOKButton		= NSOKButton,
    NSFileHandlingPanelForm		= 155,
    NSFileHandlingPanelHomeButton	= 156,
    NSFileHandlingPanelDiskButton	= 157,
    NSFileHandlingPanelDiskEjectButton	= 158
};		

@class NSBrowser;

@interface NSSavePanel : NSPanel
{
    NSBrowser		*_browser;
    id                  _form;
    id                  _homeButton;
    id                  _okButton;
    id			_removableDeviceButton;
    id                  _separator;
    id                  _accessoryView;
    NSString		*_filename;
    NSString		*_directory;
    NSArray		*_filenames;
    NSString		*_requiredType;
    void		*_columns;
    NSSet		*_typeTable;
    int                 _cdcolumn;
    id                  _scroller;
    BOOL		_recyclable;
    struct __spFlags {
        unsigned int        opening:1;
        unsigned int        exitOk:1;
        unsigned int        allowMultiple:1;
        unsigned int        dirty:1;
        unsigned int        invalidateMatrices:1;
        unsigned int        filtered:1;
        unsigned int        canChooseFolders:1;
        unsigned int        treatsFilePackagesAsDirectories:1;
        unsigned int        largeFS:1;
        unsigned int	    delegateValidatesNew:1;
        unsigned int	    canChooseFiles:1;
        unsigned int        checkCase:1;
        unsigned int        cancd:1;
        unsigned int        UnixExpert:1;
        unsigned int        backwards:1;
        unsigned int        forwards:1;
        unsigned int        delegateCompares:1;
        unsigned int        delegateFilters:1;
        unsigned int	    RESERVED:14;
    }                   _spFlags;
}

+ (NSSavePanel *)savePanel;

- (void)ok:(id)sender;
- (void)cancel:(id)sender;
- (int)runModalForDirectory:(NSString *)path file:(NSString *)name;
- (int)runModal;
- (NSString *)filename;
- (void)setDirectory:(NSString *)path;
- (NSString *)directory;
- (void)setPrompt:(NSString *)prompt;
- (NSString *)prompt;
- (void)setTitle:(NSString *)title;
- (NSString *)title;
- (void)setRequiredFileType:(NSString *)type;
- (NSString *)requiredFileType;
- (void)setTreatsFilePackagesAsDirectories:(BOOL)flag;
- (BOOL)treatsFilePackagesAsDirectories;
- (void)setAccessoryView:(NSView *)aView;
- (NSView *)accessoryView;
- (void)selectText:(id)sender;
- (void)setDelegate:(id)anObject;
- (void)validateVisibleColumns;

@end

@interface NSObject(NSSavePanelDelegate)
- (BOOL)panel:(id)sender isValidFilename:(NSString *)filename;
- (BOOL)panel:(id)sender shouldShowFilename:(NSString *)filename;
- (NSComparisonResult)panel:(id)sender compareFilename:(NSString *)file1 with:(NSString *)file2 caseSensitive:(BOOL)caseSensitive;
@end
