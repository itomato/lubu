#ident "@(#) Layout.h, Rev 2.6, 97/03/17"
//
//      Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#import <Foundation/NSObject.h>
#import <AppKit/NSApplication.h>

#define MINIATURIZE_ITEM        0x1
#define CLOSE_ITEM              0x2
#define WINDOW_ALL_ITEMS        0x3

#define CUT_ITEM                0x1
#define COPY_ITEM               0x2
#define PASTE_ITEM              0x4
#define SELECTALL_ITEM          0x8
#define EDIT_ALL_ITEMS          0xf

@interface Layout : NSObject
{
  id view;
}

- willUnselect: sender;
- didUnselect: sender;

- willSelect: sender;
- didSelect: sender;

- didHide: sender;
- didUnhide: sender;

- view;

@end


@interface NSApplication (PublicMethods)

- (BOOL)loadNibForLayout: (const char *)r owner: o;
- enableWindow: (int) flag;
- enableEdit: (int) flag;
- appWindow;

@end
