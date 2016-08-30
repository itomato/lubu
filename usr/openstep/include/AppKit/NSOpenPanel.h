#ident "@(#) NSOpenPanel.h, Rev 1.3, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSSavePanel.h"

/* Tags of views in the OpenPanel */

@interface NSOpenPanel : NSSavePanel
{
    NSArray	       *_filterTypes;
}

+ (NSOpenPanel *)openPanel;

- (void)setAllowsMultipleSelection:(BOOL)flag;
- (BOOL)allowsMultipleSelection;
- (void)setCanChooseDirectories:(BOOL)flag;
- (BOOL)canChooseDirectories;
- (void)setCanChooseFiles:(BOOL)flag;
- (BOOL)canChooseFiles;
- (NSArray *)filenames;
- (int)runModalForDirectory:(NSString *)path file:(NSString *)name types:(NSArray *)fileTypes;
- (int)runModalForTypes:(NSArray *)fileTypes;

@end
