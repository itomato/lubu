#ident "@(#) NSMenu.h, Rev 1.9, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

//
// OpenStep includes
//

#import "NSMenuItem.h"
#import "NSPanel.h"

//
// forward declarations
//


@class NSMatrix;
@class NSActionCell;
@class NSMenuCell<NSMenuItem>;

//
// interfaces
//

@interface NSMenu : NSPanel
{
    id                  _supermenu;
    NSMatrix		*_matrix;
    id                  _attachedMenu;
    NSPoint             _lastLocation;
    id                  _backupWindow;    
    struct __menuFlags {
      unsigned int              _backupWindowUp:1;
	unsigned int		sizeFitted:1;
	unsigned int   		autoenablesItems:1;
	unsigned int   		attached:1;
	unsigned int   		tornOff:1;
	unsigned int    	wasAttached:1;
	unsigned int    	wasTornOff:1;
	unsigned int    	templateType:2;
	unsigned int    	isServicesMenu:1;
        unsigned int    	RESERVED:22;
    }                   _menuFlags;
}

//----------------------------------------------------------------------------
// Controlling Allocation Zones
//----------------------------------------------------------------------------

+ (NSZone *)menuZone;

+ (void)setMenuZone:(NSZone *)aZone;

//----------------------------------------------------------------------------
// Initializing a New NSMenu
//----------------------------------------------------------------------------

- (id)initWithTitle:(NSString *)aTitle;

//----------------------------------------------------------------------------
// Setting Up the Menu Commands
//----------------------------------------------------------------------------


- (id<NSMenuItem>)addItemWithTitle:(NSString *)	aString 
		action:(SEL)		aSelector 
	 keyEquivalent:(NSString *)	charCode;

- (id<NSMenuItem>)insertItemWithTitle:(NSString *)		aString 
		   action:(SEL)			aSelector 
	    keyEquivalent:(NSString *)		charCode 
		  atIndex:(unsigned int)	index;

#if !defined(STRICT_OPENSTEP)
- (NSMatrix *)itemMatrix;

- (void)setItemMatrix:(NSMatrix *)aMatrix;
#endif


//----------------------------------------------------------------------------
// Finding Menu Items
//----------------------------------------------------------------------------

- (id<NSMenuItem>)itemWithTag:(int)aTag;

//----------------------------------------------------------------------------
// Building Submenus
//----------------------------------------------------------------------------

- (void)setSubmenu:(NSMenu *)		aMenu 
	   forItem:(id<NSMenuItem>)	aCell;

- (void)submenuAction:(id)sender;

//----------------------------------------------------------------------------
// Managing NSMenu Windows
//----------------------------------------------------------------------------

- (NSMenu *)attachedMenu;

- (BOOL)isAttached;

- (BOOL)isTornOff;

- (NSPoint)locationForSubmenu:(NSMenu *)aSubmenu;

- (void)sizeToFit;

- (NSMenu *)supermenu;

//----------------------------------------------------------------------------
// Displaying the Menu
//----------------------------------------------------------------------------

- (BOOL)autoenablesItems;

- (void)setAutoenablesItems:(BOOL)flag;

//----------------------------------------------------------------------------
// Finding, removing items
//----------------------------------------------------------------------------

- (id <NSMenuItem>)itemWithTitle:(NSString *)aTitle;

- (void)removeItem:(id <NSMenuItem>)item;

- (NSArray *)itemArray;

@end



// TODO: cleanup
// Don't know why this was split off...
//
//@interface NSMenu(NSSubmenuDummyAction)
//- (void)submenuAction:(id)sender;
//@end


@interface NSObject(NSMenuActionResponder)
// Argument must conform to NSMenuItem protocol.
- (BOOL)validateMenuItem:(id<NSMenuItem>)aCell;
@end

