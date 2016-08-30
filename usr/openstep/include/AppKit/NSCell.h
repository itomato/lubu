#ident "@(#) NSCell.h, Rev 1.10, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSCell_h_
#define _NSCell_h_

#import <Foundation/NSObject.h>
#import <Foundation/NSFormatter.h>
#import <AppKit/NSGraphics.h>
#import <AppKit/NSText.h>

@class NSEvent <NSCopying, NSCoding>;
@class NSMenu;
@class NSControl;

enum {
    NSAnyType				= 0,
    NSIntType				= 1,
    NSPositiveIntType			= 2,
    NSFloatType				= 3,
    NSPositiveFloatType			= 4,
    NSDoubleType			= 5,
    NSPositiveDoubleType		= 6
};

typedef enum _NSCellType {
    NSNullCellType			= 0,
    NSTextCellType			= 1,
    NSImageCellType			= 2
} NSCellType;

typedef enum _NSCellAttribute {
    NSCellDisabled			= 0,
    NSCellState				= 1,
    NSPushInCell			= 2,
    NSCellEditable			= 3,
    NSChangeGrayCell			= 4,
    NSCellHighlighted			= 5,
    NSCellLightsByContents		= 6,
    NSCellLightsByGray			= 7,
    NSChangeBackgroundCell		= 8,
    NSCellLightsByBackground		= 9,
    NSCellIsBordered			= 10,
    NSCellHasOverlappingImage		= 11,
    NSCellHasImageHorizontal		= 12,
    NSCellHasImageOnLeftOrBottom	= 13,
    NSCellChangesContents		= 14,
    NSCellIsInsetButton			= 15
} NSCellAttribute;

typedef enum _NSCellImagePosition {
    NSNoImage				= 0,
    NSImageOnly				= 1,
    NSImageLeft				= 2,
    NSImageRight			= 3,
    NSImageBelow			= 4,
    NSImageAbove			= 5,
    NSImageOverlaps			= 6
} NSCellImagePosition;

/* ButtonCell highlightsBy and showsStateBy mask */

enum {
    NSNoCellMask			= 0,
    NSContentsCellMask			= 1,
    NSPushInCellMask			= 2,
    NSChangeGrayCellMask		= 4,
    NSChangeBackgroundCellMask		= 8
};


@interface NSCell : NSObject <NSCopying, NSCoding>
{
    NSString *_contents;
    struct __cFlags {
	unsigned int        state:1;
	unsigned int        highlighted:1;
	unsigned int        disabled:1;
	unsigned int        editable:1;
	NSCellType          type:2;
	NSTextAlignment     alignment:2;
	unsigned int        bordered:1;
	unsigned int        bezeled:1;
	unsigned int        selectable:1;
	unsigned int        scrollable:1;
	unsigned int        entryType:3;
	unsigned int        continuous:1;
	unsigned int        actOnMouseDown:1;
	unsigned int        isLeaf:1;
	unsigned int        floatLeft:4;
	unsigned int        floatRight:4;
	unsigned int        autoRange:1;
	unsigned int        actOnMouseDragged:1;
	unsigned int        isLoaded:1;
	unsigned int        noWrap:1;
	unsigned int        dontActOnMouseUp:1;
	unsigned int	    isWhite:1;
	unsigned int	    useUserKeyEquivalent:1;
	unsigned int	    center:1;
	unsigned int	    docEditing:1;
	unsigned int	    docSaved:1;
	unsigned int	    wasSelectable:1;
	unsigned int        hasInvalidObject:1;
	unsigned int        mnemonicLocation:8;
	unsigned int        RESERVED:18;
    } _cFlags;
@private
    // This variable should *only* be accessed through the following methods:
    // setImage:, image, setFont:, and font
    id _support;
}


+ (BOOL)prefersTrackingUntilMouseUp;


- (id)initTextCell:(NSString *)aString;
- (id)initImageCell:(NSImage *)image;

- (NSView *)controlView;
- (NSCellType)type;
- (void)setType:(NSCellType)aType;
- (int)state;
- (void)setState:(int)value;
- (id)target;
- (void)setTarget:(id)anObject;
- (SEL)action;
- (void)setAction:(SEL)aSelector;
- (int)tag;
- (void)setTag:(int)anInt;
- (BOOL)isOpaque;
- (BOOL)isEnabled;
- (void)setEnabled:(BOOL)flag;
- (int)sendActionOn:(int)mask;
- (BOOL)isContinuous;
- (void)setContinuous:(BOOL)flag;
- (BOOL)isEditable;
- (void)setEditable:(BOOL)flag;
- (BOOL)isSelectable;
- (void)setSelectable:(BOOL)flag;
- (BOOL)isBordered;
- (void)setBordered:(BOOL)flag;
- (BOOL)isBezeled;
- (void)setBezeled:(BOOL)flag;
- (BOOL)isScrollable;
- (void)setScrollable:(BOOL)flag;
- (BOOL)isHighlighted;
- (NSTextAlignment)alignment;
- (void)setAlignment:(NSTextAlignment)mode;
- (BOOL)wraps;
- (void)setWraps:(BOOL)flag;
- (NSFont *)font;
- (void)setFont:(NSFont *)fontObj;
- (int)entryType;
- (void)setEntryType:(int)aType;
- (BOOL)isEntryAcceptable:(NSString *)aString;
- (void)setFloatingPointFormat:(BOOL)autoRange left:(unsigned)leftDigits right:(unsigned)rightDigits;
- (NSString *)keyEquivalent;
- (NSString *)stringValue;
- (void)setStringValue:(NSString *)aString;
- (NSComparisonResult)compare:(id)otherCell;
- (int)intValue;
- (void)setIntValue:(int)anInt;
- (float)floatValue;
- (void)setFloatValue:(float)aFloat;
- (double)doubleValue;
- (void)setDoubleValue:(double)aDouble;
- (void)takeIntValueFrom:(id)sender;
- (void)takeFloatValueFrom:(id)sender;
- (void)takeDoubleValueFrom:(id)sender;
- (void)takeStringValueFrom:(id)sender;
- (NSImage *)image;
- (void)setImage:(NSImage *)image;
- (id)representedObject;
- (void)setRepresentedObject:(id)anObject;
- (int)cellAttribute:(NSCellAttribute)aParameter;
- (void)setCellAttribute:(NSCellAttribute)aParameter to:(int)value;
- (NSRect)imageRectForBounds:(NSRect)theRect;
- (NSRect)titleRectForBounds:(NSRect)theRect;
- (NSRect)drawingRectForBounds:(NSRect)theRect;
- (NSSize)cellSize;
- (NSSize)cellSizeForBounds:(NSRect)aRect;
- (void)calcDrawInfo:(NSRect)aRect;
- (NSText *)setUpFieldEditorAttributes:(NSText *)textObj;
- (void)drawInteriorWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)drawWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)highlight:(BOOL)flag withFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (int)mouseDownFlags;
- (void)getPeriodicDelay:(float *)delay interval:(float *)interval;
- (BOOL)startTrackingAt:(NSPoint)startPoint inView:(NSView *)controlView;
- (BOOL)continueTracking:(NSPoint)lastPoint at:(NSPoint)currentPoint inView:(NSView *)controlView;
- (void)stopTracking:(NSPoint)lastPoint at:(NSPoint)stopPoint inView:(NSView *)controlView mouseIsUp:(BOOL)flag;
- (BOOL)trackMouse:(NSEvent *)theEvent inRect:(NSRect)cellFrame ofView:(NSView *)controlView untilMouseUp:(BOOL)flag;
- (void)editWithFrame:(NSRect)aRect inView:(NSView *)controlView editor:(NSText *)textObj delegate:(id)anObject event:(NSEvent *)theEvent;
- (void)selectWithFrame:(NSRect)aRect inView:(NSView *)controlView editor:(NSText *)textObj delegate:(id)anObject start:(int)selStart length:(int)selLength;
- (void)endEditing:(NSText *)textObj;
- (void)resetCursorRect:(NSRect)cellFrame inView:(NSView *)controlView;
#ifndef STRICT_OPENSTEP
- (void)setFormatter:(NSFormatter *)newFormatter;
- (id)formatter;
- (id <NSCopying>)objectValue;
- (void)setObjectValue:(id <NSCopying>)obj;
- (BOOL)hasValidObjectValue;
- (void)takeObjectValueFrom:(id)sender;
#endif //STRICT_OPENSTEP

@end

#endif // _NSCell_h_
