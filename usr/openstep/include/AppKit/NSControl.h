#ident "@(#) NSControl.h, Rev 1.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSControl_h_
#define _NSControl_h_

#import <AppKit/NSView.h>
#import <AppKit/NSText.h>

@class NSFont <NSCopying, NSCoding>;
@class NSCell <NSCopying, NSCoding>;

@interface NSControl : NSView
{
    int	_tag;
    id	_cell;
    struct __conFlags {
	unsigned int        enabled:1;
	unsigned int        editingValid:1;
	unsigned int        ignoreMultiClick:1;
	unsigned int        calcSize:1;
	unsigned int        drawingAncestor:1;
	unsigned int        RESERVED:27;
    } _conFlags;
}

+ (void)setCellClass:(Class)factoryId;
+ (Class)cellClass;

- (id)initWithFrame:(NSRect)frameRect;
- (void)sizeToFit;
- (void)calcSize;
- (id)cell;
- (void)setCell:(NSCell *)aCell;
- (id)selectedCell;
- (id)target;
- (void)setTarget:(id)anObject;
- (SEL)action;
- (void)setAction:(SEL)aSelector;
- (int)tag;
- (void)setTag:(int)anInt;
- (int)selectedTag;
- (void)setIgnoresMultiClick:(BOOL)flag;
- (BOOL)ignoresMultiClick;
- (int)sendActionOn:(int)mask;
- (BOOL)isContinuous;
- (void)setContinuous:(BOOL)flag;
- (BOOL)isEnabled;
- (void)setEnabled:(BOOL)flag;
- (void)setFloatingPointFormat:(BOOL)autoRange left:(unsigned)leftDigits right:(unsigned)rightDigits;
- (NSTextAlignment)alignment;
- (void)setAlignment:(NSTextAlignment)mode;
- (NSFont *)font;
- (void)setFont:(NSFont *)fontObj;
- (void)setStringValue:(NSString *)aString;
- (void)setIntValue:(int)anInt;
- (void)setFloatValue:(float)aFloat;
- (void)setDoubleValue:(double)aDouble;
- (NSString *)stringValue;
- (int)intValue;
- (float)floatValue;
- (double)doubleValue;
- (void)setNeedsDisplay;
- (void)updateCell:(NSCell *)aCell;
- (void)updateCellInside:(NSCell *)aCell;
- (void)drawCellInside:(NSCell *)aCell;
- (void)drawCell:(NSCell *)aCell;
- (void)selectCell:(NSCell *)aCell;

- (BOOL)sendAction:(SEL)theAction to:(id)theTarget;
- (void)takeIntValueFrom:(id)sender;
- (void)takeFloatValueFrom:(id)sender;
- (void)takeDoubleValueFrom:(id)sender;
- (void)takeStringValueFrom:(id)sender;
- (NSText *)currentEditor;
- (BOOL)abortEditing;
- (void)validateEditing;
- (void)mouseDown:(NSEvent *)theEvent;

#ifndef STRICT_OPENSTEP
- (void)setObjectValue:(id)obj;
- (id)objectValue;
- (void)takeObjectValueFrom:(id)sender;
#endif STRICT_OPENSTEP

@end

@interface NSObject(NSControlSubclassNotifications)

- (void)controlTextDidBeginEditing:(NSNotification *)obj;
- (void)controlTextDidEndEditing:(NSNotification *)obj;
- (void)controlTextDidChange:(NSNotification *)obj;

@end

@interface NSObject(NSControlSubclassDelegate)

// These delegate and notification methods are sent from NSControl subclasses that allow text editing such as NSTextField and NSMatrix.  The classes that need to send these have delegates.  NSControl does not.

- (BOOL)control:(NSControl *)control textShouldBeginEditing:(NSText *)fieldEditor;
- (BOOL)control:(NSControl *)control textShouldEndEditing:(NSText *)fieldEditor;

#ifndef STRICT_OPENSTEP
- (BOOL)control:(NSControl *)control didFailToFormatString:(NSString *)string errorDescription:(NSString *)error;
- (void)control:(NSControl *)control didFailToValidatePartialString:(NSString *)string errorDescription:(NSString *)error;
- (BOOL)control:(NSControl *)control isValidObject:(id)obj;
#endif STRICT_OPENSTEP

@end

								// userInfo keys:
extern NSString *NSControlTextDidBeginEditingNotification;	//	@"NSFieldEditor"
extern NSString *NSControlTextDidEndEditingNotification;	//	@"NSFieldEditor"
extern NSString *NSControlTextDidChangeNotification;		//	@"NSFieldEditor"

#endif // _NSControl_h_
