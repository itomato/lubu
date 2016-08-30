#ident "@(#) NSTableColumn.h, Rev 1.5, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1995, NeXT Computer, Inc.
//	All rights reserved.

#ifndef STRICT_OPENSTEP

#import <Foundation/Foundation.h>
#import <AppKit/NSCell.h>
#import <AppKit/NSTableView.h>

@interface NSTableColumn : NSObject
{
    id		_identifier;
    float	_width;
    float	_minWidth;
    float	_maxWidth;
    NSTableView *_tableView;
    NSCell	*_headerCell;
    NSCell	*_dataCell;
    struct __colFlags {
        unsigned int	isResizable:1;
        unsigned int	isEditable:1;
        unsigned int	resizedPostingDisableCount:8;
        unsigned int	RESERVED:22;
    } _cFlags;
    void	*_reserved;
}

- (id)initWithIdentifier:(id)identifier;

- (void)setIdentifier:(id)identifier;
- (id)identifier;
- (void)setTableView:(NSTableView *)tableView;
- (NSTableView *)tableView;
- (void)setWidth:(float)width;
- (float)width;
- (void)setMinWidth:(float)minWidth;
- (float)minWidth;
- (void)setMaxWidth:(float)maxWidth;
- (float)maxWidth;
- (void)setHeaderCell:(NSCell *)cell;
- (id)headerCell;
- (void)setDataCell:(NSCell *)cell;
- (id)dataCell;
- (void)setResizable:(BOOL)flag;
- (BOOL)isResizable;
- (void)setEditable:(BOOL)flag;
- (BOOL)isEditable;
- (void)sizeToFit;

@end

#endif STRICT_OPENSTEP
