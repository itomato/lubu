#ident "@(#) NSTableView.h, Rev 1.5, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1995, NeXT Computer, Inc.
//	All rights reserved.

#ifndef STRICT_OPENSTEP

#import <AppKit/NSControl.h>
@class _NSSparseArray <NSCopying>;
@class NSTableHeaderView;
@class NSTableColumn;

typedef struct __TvFlags {
#ifdef __BIG_ENDIAN__
    unsigned int	allowsColumnReordering:1;
    unsigned int	allowsColumnResizing:1;
    unsigned int	drawsGrid:1;
    unsigned int	allowsEmptySelection:1;
    unsigned int	allowsMultipleSelection:1;
    unsigned int	allowsColumnSelection:1;
    unsigned int	selectionType:2;
    unsigned int	changingLayout:1;
    unsigned int	compareWidthWithSuperview:2;
    unsigned int	delegateWillDisplayCell:1;
    unsigned int	delegateShouldEditTableColumn:1;
    unsigned int	delegateShouldSelectRow:1;
    unsigned int	delegateShouldSelectTableColumn:1;
    unsigned int	delegateSelectionShouldChangeInTableView:1;
    unsigned int	autoresizesAllColumnsToFit:1;
    unsigned int	dataSourceSetObjectValue:1;
    unsigned int	selectionPostingDisableCount:7;
    unsigned int	movedPostingDisableCount:7;
#else
    unsigned int	movedPostingDisableCount:7;
    unsigned int	selectionPostingDisableCount:7;
    unsigned int	dataSourceSetObjectValue:1;
    unsigned int	autoresizesAllColumnsToFit:1;
    unsigned int	delegateSelectionShouldChangeInTableView:1;
    unsigned int	delegateShouldSelectTableColumn:1;
    unsigned int	delegateShouldSelectRow:1;
    unsigned int	delegateShouldEditTableColumn:1;
    unsigned int	delegateWillDisplayCell:1;
    unsigned int	compareWidthWithSuperview:2;
    unsigned int	changingLayout:1;
    unsigned int	selectionType:2;
    unsigned int	allowsColumnSelection:1;
    unsigned int	allowsMultipleSelection:1;
    unsigned int	allowsEmptySelection:1;
    unsigned int	drawsGrid:1;
    unsigned int	allowsColumnResizing:1;
    unsigned int	allowsColumnReordering:1;
#endif
} _TvFlags;

@interface NSTableView : NSControl
{
    NSTableHeaderView	*_headerView;
    NSView		*_cornerView;
    NSMutableArray     	*_tableColumns;
    NSCell		*_editingCell;
    id			_delegate;
    id			_dataSource;
    NSSize		_intercellSpacing;
    float		_rowHeight;
    int			_lastSelectedColumn;
    int			_lastSelectedRow;
    int			_editingRow;
    int			_editingColumn;
    _NSSparseArray	*_selectedColumns;
    _NSSparseArray	*_selectedRows;
    NSImage		*_bodyDragImage;
    NSColor		*_backgroundColor;
    NSColor		*_gridColor;
    float		_dragYPos;
    id			_target;
    SEL                 _action;
    SEL                 _doubleAction;
    NSRect		_rectOfLastColumn;
    int			_lastCachedRectColumn;
    NSRect		_rectOfLastRow;
    int			_lastCachedRectRow;
    _TvFlags            _tvFlags;
    void		*_reserved;
}

- (void)setDataSource:(id)aSource;
- (id)dataSource;
- (void)setDelegate:(id)delegate;
- (id)delegate;
- (void)setHeaderView:(NSTableHeaderView *)headerView;
- (NSTableHeaderView *)headerView;
- (void)setCornerView:(NSView *)cornerView;
- (NSView *)cornerView;
- (void)setAllowsColumnReordering:(BOOL)flag;
- (BOOL)allowsColumnReordering;
- (void)setAllowsColumnResizing:(BOOL)flag;
- (BOOL)allowsColumnResizing;
- (void)setAutoresizesAllColumnsToFit:(BOOL)flag;
- (BOOL)autoresizesAllColumnsToFit;
- (void)setDrawsGrid:(BOOL)flag;
- (BOOL)drawsGrid;
- (void)setIntercellSpacing:(NSSize)aSize;
- (NSSize)intercellSpacing;
- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;
- (void)setGridColor:(NSColor *)color;
- (NSColor *)gridColor;
- (void)setRowHeight:(float)rowHeight;
- (float)rowHeight;

- (NSArray *)tableColumns;
- (int)numberOfColumns;
- (int)numberOfRows;

- (void)addTableColumn:(NSTableColumn *)column;
- (void)removeTableColumn:(NSTableColumn *)column;
- (int)columnWithIdentifier:(id)identifier;
- (NSTableColumn *)tableColumnWithIdentifier:(id)identifier;

- (void)tile;
- (void)sizeLastColumnToFit;
- (void)scrollRowToVisible:(int)row;
- (void)scrollColumnToVisible:(int)column;
- (void)moveColumn:(int)column toColumn:(int)newIndex;

- (void)reloadData;
- (void)noteNumberOfRowsChanged;

- (int)editedColumn;
- (int)editedRow;
- (int)clickedColumn;
- (int)clickedRow;

- (void)setDoubleAction:(SEL)aSelector;
- (SEL)doubleAction;

/*
 * Selection
 */
- (void)setAllowsMultipleSelection:(BOOL)flag;
- (BOOL)allowsMultipleSelection;
- (void)setAllowsEmptySelection:(BOOL)flag;
- (BOOL)allowsEmptySelection;
- (void)setAllowsColumnSelection:(BOOL)flag;
- (BOOL)allowsColumnSelection;
- (void)selectAll:(id)sender;
- (void)deselectAll:(id)sender;
- (void)selectColumn:(int)column byExtendingSelection:(BOOL)extend;
- (void)selectRow:(int)row byExtendingSelection:(BOOL)extend;
- (void)deselectColumn:(int)column;
- (void)deselectRow:(int)row;
- (int)selectedColumn;
- (int)selectedRow;
- (BOOL)isColumnSelected:(int)row;
- (BOOL)isRowSelected:(int)row;
- (int)numberOfSelectedColumns;
- (int)numberOfSelectedRows;
- (NSEnumerator *)selectedColumnEnumerator;
- (NSEnumerator *)selectedRowEnumerator;


/*
 * Layout support
 */
- (NSRect)rectOfColumn:(int)column;
- (NSRect)rectOfRow:(int)row;
- (NSRange)columnsInRect:(NSRect)rect;
- (NSRange)rowsInRect:(NSRect)rect;
- (int)columnAtPoint:(NSPoint)point;
- (int)rowAtPoint:(NSPoint)point;
- (NSRect)frameOfCellAtColumn:(int)column row:(int)row;


/*
 * Text delegate methods
 */
- (BOOL)textShouldBeginEditing:(NSText *)textObject;
- (BOOL)textShouldEndEditing:(NSText *)textObject;
- (void)textDidBeginEditing:(NSNotification *)notification;
- (void)textDidEndEditing:(NSNotification *)notification;
- (void)textDidChange:(NSNotification *)notification;

/*
 * For subclassers
 */
- (void)editColumn:(int)column row:(int)row withEvent:(NSEvent *)theEvent select:(BOOL)select;
- (void)drawRow:(int)row clipRect:(NSRect)rect;
- (void)highlightSelectionInClipRect:(NSRect)rect;
- (void)drawGridInClipRect:(NSRect)rect;

@end

@interface NSObject(NSTableViewDelegate)

- (void)tableView:(NSTableView *)tableView willDisplayCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn row:(int)row;
- (BOOL)tableView:(NSTableView *)tableView shouldEditTableColumn:(NSTableColumn *)tableColumn row:(int)row;
- (BOOL)selectionShouldChangeInTableView:(NSTableView *)aTableView;
- (BOOL)tableView:(NSTableView *)tableView shouldSelectRow:(int)row;
- (BOOL)tableView:(NSTableView *)tableView shouldSelectTableColumn:(NSTableColumn *)tableColumn;

@end

/*
 * Notifications
 */

extern NSString *NSTableViewSelectionDidChangeNotification;
extern NSString *NSTableViewColumnDidMoveNotification;		// @"NSOldColumn", @"NSNewColumn"
extern NSString *NSTableViewColumnDidResizeNotification;	// @"NSTableColumn", @"NSOldWidth"


@interface NSObject(NSTableDataSource)
- (int)numberOfRowsInTableView:(NSTableView *)tableView;
- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(int)row;
- (void)tableView:(NSTableView *)tableView setObjectValue:(id)object forTableColumn:(NSTableColumn *)tableColumn row:(int)row;
@end

#endif STRICT_OPENSTEP
