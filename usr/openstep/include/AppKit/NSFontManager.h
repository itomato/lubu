#ident "@(#) NSFontManager.h, Rev 1.10, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSFontManager_h_
#define _NSFontManager_h_

#import <Foundation/NSObject.h>

@class NSArray;
@class NSFontPanel;
@class NSFont <NSCopying, NSCoding>;
@class NSMenu;

typedef unsigned int NSFontTraitMask;

/*
 * Font Traits
 *
 * This list should be kept small since the more traits that are assigned
 * to a given font, the harder it will be to map it to some other family.
 * Some traits are mutually exclusive such as NSExpanded and NSCondensed.
 */

enum {
    NSItalicFontMask			= 0x00000001,
    NSBoldFontMask			= 0x00000002,
    NSUnboldFontMask			= 0x00000004,
    NSNonStandardCharacterSetFontMask	= 0x00000008,
    NSNarrowFontMask			= 0x00000010,
    NSExpandedFontMask			= 0x00000020,
    NSCondensedFontMask			= 0x00000040,
    NSSmallCapsFontMask			= 0x00000080,
    NSPosterFontMask			= 0x00000100,
    NSCompressedFontMask		= 0x00000200,
    NSFixedPitchFontMask		= 0x00000400,
    NSUnitalicFontMask			= 0x01000000
};

typedef enum _NSFontAction {
    NSNoFontChangeAction		= 0,
    NSViaPanelFontAction		= 1,
    NSAddTraitFontAction		= 2,
    NSSizeUpFontAction			= 3,
    NSSizeDownFontAction		= 4,
    NSHeavierFontAction			= 5,
    NSLighterFontAction			= 6,
    NSRemoveTraitFontAction		= 7
} NSFontAction;

@interface NSFontManager : NSObject
{
@private
    id                  _panel;
    id                  _menu;
    SEL                 _action;
    int                 _whatToDo;
    NSFontTraitMask     _traitToChange;
    NSFont *            _selFont;
    struct _fmFlags {
	unsigned int        multipleFont:1;
	unsigned int        disabled:1;
	unsigned int        _RESERVED:14;
    }                   _fmFlags;
    unsigned short      _lastPos;
    id		        _delegate;
    unsigned int        _reservedFMint2;
    unsigned int        _reservedFMint3;
    unsigned int        _reservedFMint4;
}

+ (void)setFontPanelFactory:(Class)factoryId;
+ (void)setFontManagerFactory:(Class)factoryId;
+ (NSFontManager *)sharedFontManager;

- (BOOL)isMultiple;
- (NSFont *)selectedFont;
- (void)setSelectedFont:(NSFont *)fontObj isMultiple:(BOOL)flag;
- (void)setFontMenu:(NSMenu *)newMenu;
- (NSMenu *)fontMenu:(BOOL)create;
- (NSFontPanel *)fontPanel:(BOOL)create;
- (NSFont *)fontWithFamily:(NSString *)family traits:(NSFontTraitMask)traits weight:(int)weight size:(float)size;
- (NSFontTraitMask)traitsOfFont:(NSFont *)fontObj;
- (int)weightOfFont:(NSFont *)fontObj;
- (NSArray *)availableFonts;
- (NSFont *)convertFont:(NSFont *)fontObj;
- (NSFont *)convertFont:(NSFont *)fontObj toSize:(float)size;
- (NSFont *)convertFont:(NSFont *)fontObj toFace:(NSString *)typeface;
- (NSFont *)convertFont:(NSFont *)fontObj toFamily:(NSString *)family;
- (NSFont *)convertFont:(NSFont *)fontObj toHaveTrait:(NSFontTraitMask)trait;
- (NSFont *)convertFont:(NSFont *)fontObj toNotHaveTrait:(NSFontTraitMask)trait;
- (NSFont *)convertWeight:(BOOL)upFlag ofFont:(NSFont *)fontObj;
- (BOOL)isEnabled;
- (void)setEnabled:(BOOL)flag;
- (SEL)action;
- (void)setAction:(SEL)aSelector;
- (BOOL)sendAction;
- (void)setDelegate:(id)anObject;
- (id)delegate;

- (BOOL) fontNamed:(NSString *)fName hasTraits:(NSFontTraitMask)someTraits; 
- (NSArray *)availableFontNamesWithTraits:(NSFontTraitMask)someTraits; 

- (void)addFontTrait:(id)sender;
- (void)removeFontTrait:(id)sender;
- (void)modifyFont:(id)sender;
- (void)orderFrontFontPanel:(id)sender;
- (void)modifyFontViaPanel:(id)sender;


@end

@interface NSObject(NSFontManagerDelegate)
- (BOOL)fontManager:(id)sender willIncludeFont:(NSString *)fontName;
@end
 
#endif // _NSFontManager_h_
