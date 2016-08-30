#ident "@(#) NSText.h, Rev 1.11, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSText_h_
#define _NSText_h_

#import <AppKit/NSView.h>
#import <AppKit/NSSpellProtocol.h>

@class NSColor <NSCopying, NSCoding>;
@class NSFont <NSCopying, NSCoding>;

typedef enum _NSTextAlignment {
    NSLeftTextAlignment		= 0, /* Visually left aligned */
    NSRightTextAlignment	= 1, /* Visually right aligned */
    NSCenterTextAlignment	= 2,
    NSJustifiedTextAlignment	= 3,
    NSNaturalTextAlignment	= 4  /* Indicates the default alignment for script */
} NSTextAlignment;

/* movement codes for movement between fields; these codes are the intValue of the NSTextMovement key in NSTextDidEndEditing notifications
*/
enum {
    NSIllegalTextMovement		= 0,
    NSReturnTextMovement		= 0x10,
    NSTabTextMovement			= 0x11,
    NSBacktabTextMovement		= 0x12,
    NSLeftTextMovement			= 0x13,
    NSRightTextMovement			= 0x14,
    NSUpTextMovement			= 0x15,
    NSDownTextMovement			= 0x16
};

@interface NSText : NSView <NSChangeSpelling, NSIgnoreMisspelledWords> {
    @public
      void *_ivars;
}

- (NSString *)string;
- (void)setText:(NSString *)string;
- (void)setText:(NSString *)string range:(NSRange)range;
- (void)setString:(NSString *)string;
- (void)replaceCharactersInRange:(NSRange)range withString:(NSString *)string;

- (NSData *)RTFFromRange:(NSRange)range;
- (NSData *)RTFDFromRange:(NSRange)range;
- (void)replaceRange:(NSRange)range withRTF:(NSData *)rtfData;
- (void)replaceRange:(NSRange)range withRTFD:(NSData *)rtfdData;
- (void)replaceCharactersInRange:(NSRange)range withRTF:(NSData *)rtfData;
- (void)replaceCharactersInRange:(NSRange)range withRTFD:(NSData *)rtfdData;

- (BOOL)writeRTFDToFile:(NSString *)path atomically:(BOOL)flag;
- (BOOL)readRTFDFromFile:(NSString *)path;

- (BOOL)isEditable;
- (void)setEditable:(BOOL)flag;
- (BOOL)isSelectable;
- (void)setSelectable:(BOOL)flag;
- (BOOL)isRichText;
- (void)setRichText:(BOOL)flag;		/* If NO, also clears setImportsGraphics: */
- (BOOL)importsGraphics;
- (void)setImportsGraphics:(BOOL)flag;	/* If YES, also sets setRichText: */
- (id)delegate;
- (void)setDelegate:(id)anObject;

- (void)setFont:(NSFont *)obj;
- (NSFont *)font;
- (void)setTextColor:(NSColor *)color;
- (NSColor *)textColor;
- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;
- (void)setDrawsBackground:(BOOL)flag;
- (BOOL)drawsBackground;
- (NSTextAlignment)alignment;
- (void)setAlignment:(NSTextAlignment)mode;

- (void)setFieldEditor:(BOOL)flag; /* A BOOL to indicate whether to end on CR, TAB, etc */
- (BOOL)isFieldEditor;

- (void)setTextColor:(NSColor *)color range:(NSRange)range;
- (void)setFont:(NSFont *)font range:(NSRange)range;

- (BOOL)usesFontPanel;
- (void)setUsesFontPanel:(BOOL)flag;

- (NSSize)maxSize;
- (void)setMaxSize:(NSSize)newMaxSize;
- (NSSize)minSize;
- (void)setMinSize:(NSSize)newMinSize;

- (BOOL)isHorizontallyResizable;
- (void)setHorizontallyResizable:(BOOL)flag;
- (BOOL)isVerticallyResizable;
- (void)setVerticallyResizable:(BOOL)flag;

- (void)sizeToFit;

- (void)copy:(id)sender;
- (void)copyFont:(id)sender;
- (void)copyRuler:(id)sender;
- (void)cut:(id)sender;
- (void)delete:(id)sender;
- (void)paste:(id)sender;
- (void)pasteFont:(id)sender;
- (void)pasteRuler:(id)sender;
- (void)selectAll:(id)sender;
- (void)changeFont:(id)sender;
- (void)alignLeft:(id)sender;
- (void)alignRight:(id)sender;
- (void)alignCenter:(id)sender;
- (void)subscript:(id)sender;
- (void)superscript:(id)sender;
- (void)underline:(id)sender;
- (void)unscript:(id)sender;
- (void)showGuessPanel:(id)sender;
- (void)checkSpelling:(id)sender;
- (void)toggleRuler:(id)sender;

- (BOOL)isRulerVisible;

- (NSRange)selectedRange;
- (void)setSelectedRange:(NSRange)range;

- (void)scrollRangeToVisible:(NSRange)range;

@end

/* Delegate */
@interface NSObject(NSTextDelegate)
- (BOOL)textShouldBeginEditing:(NSText *)textObject; /* YES means do it */
- (BOOL)textShouldEndEditing:(NSText *)textObject; /* YES means do it */
@end

/* Notifications */
extern NSString *NSTextDidBeginEditingNotification;
extern NSString *NSTextDidEndEditingNotification;	// userInfo key:  @"NSTextMovement"
extern NSString *NSTextDidChangeNotification;

@interface NSObject(NSTextNotifications)
- (void)textDidBeginEditing:(NSNotification *)notification;
- (void)textDidEndEditing:(NSNotification *)notification;
- (void)textDidChange:(NSNotification *)notification; /* Any keyDown or paste which changes the contents causes this */
@end

#endif // _NSText_h_
