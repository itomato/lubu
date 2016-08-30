#ident "@(#) NSMenuCell.h, Rev 1.5, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSMenuItem.h"
#import "NSButtonCell.h"

@interface NSMenuCell : NSButtonCell <NSMenuItem>
{
}


+ (void)setUsesUserKeyEquivalents:(BOOL)flag;
+ (BOOL)usesUserKeyEquivalents;

- (NSString *)userKeyEquivalent;
- (BOOL)hasSubmenu;

@end
