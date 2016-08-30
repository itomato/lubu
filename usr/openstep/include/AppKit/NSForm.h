#ident "@(#) NSForm.h, Rev 1.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSMatrix.h"

@class NSFormCell;

@interface  NSForm : NSMatrix
{
}


- (int)indexOfSelectedItem;
- (void)setEntryWidth:(float)width;
- (void)setInterlineSpacing:(float)spacing;
- (void)setBordered:(BOOL)flag;
- (void)setBezeled:(BOOL)flag;
- (void)setTitleAlignment:(NSTextAlignment)mode;
- (void)setTextAlignment:(NSTextAlignment)mode;
- (void)setTitleFont:(NSFont *)fontObj;
- (void)setTextFont:(NSFont *)fontObj;
- (id)cellAtIndex:(int)index;
- (void)drawCellAtIndex:(int)index;
- (NSFormCell *)addEntry:(NSString *)title;
- (NSFormCell *)insertEntry:(NSString *)title atIndex:(int)index;
- (void)removeEntryAtIndex:(int)index;
- (int)indexOfCellWithTag:(int)aTag;
- (void)selectTextAtIndex:(int)index;

@end
