#ident "@(#) NSTableHeaderView.h, Rev 1.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1995, NeXT Computer, Inc.
//	All rights reserved.

#ifndef STRICT_OPENSTEP

#import <AppKit/NSView.h>

@class NSTableView;
@class NSColor <NSCopying, NSCoding>;
@class NSImage <NSCopying, NSCoding>;
@class NSCursor <NSCoding>;

@interface NSTableHeaderView : NSView
{
    NSTableView			*_tableView;
    int				_resizedColumn;
    int				_draggedColumn;
    int				_mayDragColumn;
    NSImage			*_headerDragImage;
    float			_draggedDistance;
    NSCursor			*_resizeCursor;
    BOOL			_drawingLastColumn;
    void			*_reserved;
}

- (void)setTableView:(NSTableView *)tableView;
- (NSTableView *)tableView;
- (int)draggedColumn;
- (float)draggedDistance;
- (int)resizedColumn;
- (NSRect)headerRectOfColumn:(int)column;
- (int)columnAtPoint:(NSPoint)point;

@end

#endif STRICT_OPENSTEP
