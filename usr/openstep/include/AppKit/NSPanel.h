#ident "@(#) NSPanel.h, Rev 1.5, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSWindow.h"

/*
 * In the following two functions, msg may be a printf-like message with
 * the arguments tacked onto the end.  Thus, to get a '%' in your message,
 * you must use '%%'
 */


#ifdef __cplusplus
extern "C" {
#endif

extern int NSRunAlertPanel(NSString * title, NSString * msg, NSString * defaultButton, NSString * alternateButton, NSString * otherButton, ...);

extern id NSGetAlertPanel(NSString * title, NSString * msg, NSString * defaultButton, NSString * alternateButton, NSString * otherButton, ...);

extern void NSReleaseAlertPanel(id panel);

#ifdef __cplusplus
}
#endif

/*
 * NXRunAlertPanel() return values (also returned by runModalSession: when
 * the modal session is run with a panel returned by NXGetAlertPanel()).
 */

enum {
    NSAlertDefaultReturn		= 1,
    NSAlertAlternateReturn		= 0,
    NSAlertOtherReturn			= -1,
    NSAlertErrorReturn			= -2
};

enum {
    NSOKButton				= 1,
    NSCancelButton			= 0
};

@interface NSPanel : NSWindow
{
}

- (BOOL)isFloatingPanel;
- (void)setFloatingPanel:(BOOL)flag;
- (BOOL)becomesKeyOnlyIfNeeded;
- (void)setBecomesKeyOnlyIfNeeded:(BOOL)flag;
- (BOOL)worksWhenModal;
- (void)setWorksWhenModal:(BOOL)flag;

@end
