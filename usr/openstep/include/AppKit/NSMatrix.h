#ident "@(#) NSMatrix.h, Rev 1.9, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSMatrix_h_
#define _NSMatrix_h_

#import <AppKit/NSControl.h>

@class NSColor <NSCopying, NSCoding>;

/* Matrix Constants */

typedef enum _NSMatrixMode {
    NSRadioModeMatrix			= 0,
    NSHighlightModeMatrix		= 1,
    NSListModeMatrix			= 2,
    NSTrackModeMatrix			= 3
} NSMatrixMode;

@interface NSMatrix : NSControl
{
    id                  _target;
    SEL                 _action;
    id                  _nextText;
    id                  _previousText;
    SEL                 _doubleAction;
    SEL                 _errorAction;
    id                  _delegate;
    id                  _selectedCell;
    int                 _selectedRow;
    int                 _selectedCol;
    int                 _numRows;
    int                 _numCols;
    NSSize              _cellSize;
    NSSize              _intercell;
    id                  _font;
    id                  _protoCell;
    id                  _cellClass;
    NSColor             *_backgroundColor;
    NSColor             *_cellBackgroundColor;
    NSMutableArray	*_cells;
    struct __mFlags {
	unsigned int	highlightMode:1;
	unsigned int	radioMode:1;
	unsigned int	listMode:1;
	unsigned int	allowEmptySel:1;
	unsigned int	autoscroll:1;
	unsigned int	selectionByRect:1;
	unsigned int	drawsCellBackground:1;
	unsigned int	drawsBackground:1;
	unsigned int	autosizeCells:1;
	unsigned int	drawingAncestor:1;
	unsigned int	RESERVED:21;
    } _mFlags;
}



- (id)initWithFrame:(NSRect)frameRect;
- (id)initWithFrame:(NSRect)frameRect mode:(int)aMode prototype:(NSCell *)aCell numberOfRows:(int)rowsHigh numberOfColumns:(int)colsWide;
- (id)initWithFrame:(NSRect)frameRect mode:(int)aMode cellClass:(Class)factoryId numberOfRows:(int)rowsHigh numberOfColumns:(int)colsWide;


- (void)setCellClass:(Class)factoryId;
- (Class)cellClass;
- (id)prototype;
- (void)setPrototype:(NSCell *)aCell;
- (NSCell *)makeCellAtRow:(int)row column:(int)col;
- (NSMatrixMode)mode;
- (void)setMode:(NSMatrixMode)aMode;
- (void)setAllowsEmptySelection:(BOOL)flag;
- (BOOL)allowsEmptySelection;
- (void)sendAction:(SEL)aSelector to:(id)anObject forAllCells:(BOOL)flag;
- (NSArray *)cells;
- (void)sortUsingSelector:(SEL)comparator;
- (void)sortUsingFunction:(int (*)(id, id, void *))compare context:(void *)context;
- (id)selectedCell;
- (NSArray *)selectedCells;
- (int)selectedRow;
- (int)selectedColumn;
- (void)setSelectionByRect:(BOOL)flag;
- (BOOL)isSelectionByRect;
- (void)setSelectionFrom:(int)startPos to:(int)endPos anchor:(int)anchorPos highlight:(BOOL)lit;
- (void)deselectSelectedCell;
- (void)deselectAllCells;
- (void)selectCellAtRow:(int)row column:(int)col;
- (void)selectAll:(id)sender;
- (BOOL)selectCellWithTag:(int)anInt;
- (NSSize)cellSize;
- (void)setCellSize:(NSSize)aSize;
- (NSSize)intercellSpacing;
- (void)setIntercellSpacing:(NSSize)aSize;
- (void)setScrollable:(BOOL)flag;
- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;
- (void)setCellBackgroundColor:(NSColor *)color;
- (NSColor *)cellBackgroundColor;
- (void)setDrawsCellBackground:(BOOL)flag;
- (BOOL)drawsCellBackground;
- (void)setDrawsBackground:(BOOL)flag;
- (BOOL)drawsBackground;
- (void)setState:(int)value atRow:(int)row column:(int)col;
- (void)getNumberOfRows:(int *)rowCount columns:(int *)colCount;
- (int)numberOfRows;
- (int)numberOfColumns;
- (id)cellAtRow:(int)row column:(int)col;
- (NSRect)cellFrameAtRow:(int)row column:(int)col;
- (BOOL)getRow:(int *)row column:(int *)col ofCell:(NSCell *)aCell;
- (BOOL)getRow:(int *)row column:(int *)col forPoint:(NSPoint)aPoint;
- (void)renewRows:(int)newRows columns:(int)newCols;
- (void)putCell:(NSCell *)newCell atRow:(int)row column:(int)col;
- (void)addRow;
- (void)addRowWithCells:(NSArray *)newCells;
- (void)insertRow:(int)row;
- (void)insertRow:(int)row withCells:(NSArray *)newCells;
- (void)removeRow:(int)row;
- (void)addColumn;
- (void)addColumnWithCells:(NSArray *)newCells;
- (void)insertColumn:(int)column;
- (void)insertColumn:(int)column withCells:(NSArray *)newCells;
- (void)removeColumn:(int)col;
- (id)cellWithTag:(int)anInt;
- (SEL)doubleAction;
- (void)setDoubleAction:(SEL)aSelector;
- (SEL)errorAction;
- (void)setErrorAction:(SEL)aSelector;
- (void)setAutosizesCells:(BOOL)flag;
- (BOOL)autosizesCells;
- (void)sizeToCells;
- (void)setValidateSize:(BOOL)flag;
- (void)drawCellAtRow:(int)row column:(int)col;
- (void)highlightCell:(BOOL)flag atRow:(int)row column:(int)col;

- (void)setAutoscroll:(BOOL)flag;
- (BOOL)isAutoscroll;
- (void)scrollCellToVisibleAtRow:(int)row column:(int)col;
- (int)mouseDownFlags;
- (void)mouseDown:(NSEvent *)theEvent;
- (BOOL)performKeyEquivalent:(NSEvent *)theEvent;
- (BOOL)sendAction;
- (void)sendDoubleAction;
- (id)delegate;
- (void)setDelegate:(id)anObject;
- (BOOL)textShouldBeginEditing:(NSText *)textObject;
- (BOOL)textShouldEndEditing:(NSText *)textObject;
- (void)textDidBeginEditing:(NSNotification *)notification;
- (void)textDidEndEditing:(NSNotification *)notification;
- (void)textDidChange:(NSNotification *)notification;
- (void)selectText:(id)sender;
- (id)selectTextAtRow:(int)row column:(int)col;
- (void)setPreviousText:(id)anObject;
- (void)setNextText:(id)anObject;
- (id)nextText;
- (id)previousText;
- (BOOL)acceptsFirstMouse:(NSEvent *)theEvent;
- (void)resetCursorRects;

@end

#endif // _NSMatrix_h_
