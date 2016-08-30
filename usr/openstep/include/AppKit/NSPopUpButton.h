#ident "@(#) NSPopUpButton.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSPopUpButton_h_
#define _NSPopUpButton_h_

#import <Foundation/Foundation.h>
#import <AppKit/NSButton.h>
#import "NSMenuItem.h"

@class NSString <NSCopying, NSMutableCopying, NSCoding>;
@class NSFont <NSCopying, NSCoding>;
@class NSMatrix;
@class NSMenuCell<NSMenuItem>;

@interface NSPopUpButton : NSButton
{
    BOOL _pullsDown;
    id _target;     
    SEL _action;     
}

- (id)initWithFrame:(NSRect)buttonFrame pullsDown:(BOOL)flag;

- (void)setPullsDown:(BOOL)flag;
- (BOOL)pullsDown;

#ifndef STRICT_OPENSTEP
	/* Backdoor access for experts, allows "sizeToFit", etc. */
- (NSMatrix *)itemMatrix;    // NSMatrix of NSMenuCells
#endif

- (NSArray*)itemArray;

- (int)numberOfItems;
- (void)addItemWithTitle:(NSString *)title;
- (void)addItemsWithTitles:(NSArray *)itemTitles;
- (void)insertItemWithTitle:(NSString *)title atIndex:(int)index;
- (void)removeItemWithTitle:(NSString *)title;
- (void)removeItemAtIndex:(int)index;
- (void)removeAllItems;
- (void)synchronizeTitleAndSelectedItem;
- (void)selectItemWithTitle:(NSString *)title;
- (void)selectItemAtIndex:(int)index;
- (id<NSMenuItem>)itemAtIndex:(int)index;
- (id<NSMenuItem>)itemWithTitle:(NSString *)title;
- (id<NSMenuItem>)selectedItem;
- (id<NSMenuItem>)lastItem;
- (NSString *)itemTitleAtIndex:(int)index;
- (NSString *)titleOfSelectedItem;
- (int)indexOfSelectedItem;
- (int)indexOfItemWithTitle:(NSString *)title;
- (NSArray *)itemTitles;
- (NSFont *)font;
- (void)setFont:(NSFont *)fontObject;

	/* This is a no-op in NSControl, but it is here because we override */
	/* it to return the titleOfSelectedItem. This is useful if there is */
	/* a TextField or something that is supposed to reflect the most */
	/* recent PopUp selection. */
- (NSString *)stringValue;
	/* Adds semantic to NSButton's method that if there is no item in */
	/* popup matching title, then an item of that name is added. */
- (void)setTitle:(NSString *)aString;
- (id)target;
- (void)setTarget:(id)anObject;
- (SEL)action;
- (void)setAction:(SEL)aSelector;
- (void)setAutoenablesItems:(BOOL)flag;
- (BOOL)autoenablesItems;


@end
 
#endif // _NSPopUpButton_h_
