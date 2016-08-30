#ident "@(#) NSBrowserCell.h, Rev 1.4, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSBrowserCell_h_
#define _NSBrowserCell_h_

#import <AppKit/NSCell.h>

@class NSImage <NSCopying, NSCoding>;

@interface NSBrowserCell : NSCell

+ (NSImage *)branchImage;
+ (NSImage *)highlightedBranchImage;

- (BOOL)isLeaf;
- (void)setLeaf:(BOOL)flag;
- (BOOL)isLoaded;
- (void)setLoaded:(BOOL)flag;
- (void)reset;
- (void)set;
- (void)setAlternateImage:(NSImage *)newAltImage;
- (NSImage *)alternateImage;

@end

#endif // _NSBrowserCell_h_
