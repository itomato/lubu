#ident "@(#) NSApplication.h, Rev 1.22, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#ifndef _NSApplication_h_
#define _NSApplication_h_

//
// OpenStep includes
//

#import <AppKit/NSResponder.h>
#import <AppKit/NSNibLoading.h>

//
// forward declarations
//

@class NSApplication;
@class NSWindow;
@class NSPasteboard;
@class NSEvent <NSCopying, NSCoding>;
@class NSImage <NSCopying, NSCoding>;
@class NSMenu;
@class NSHelpPanel;

//
// enums and typedefs
//

typedef struct _NSModalSession *NSModalSession;

// pre-defined return values for runModalFor and runModalSession
// (Note: system also reserves all values below these)

enum {
    NSRunStoppedResponse			= (-1000),
    NSRunAbortedResponse			= (-1001),
    NSRunContinuesResponse			= (-1002)
};

//
// global vars
//

// the Application

extern id	 NSApp;

// Modes passed to NSRunLoop

extern NSString *NSModalPanelRunLoopMode;
extern NSString *NSEventTrackingRunLoopMode;

// notifications 

extern NSString *NSApplicationDidBecomeActiveNotification;
extern NSString *NSApplicationDidHideNotification;
extern NSString *NSApplicationDidFinishLaunchingNotification;
extern NSString *NSApplicationDidResignActiveNotification;
extern NSString *NSApplicationDidUnhideNotification;
extern NSString *NSApplicationDidUpdateNotification;
extern NSString *NSApplicationWillBecomeActiveNotification;
extern NSString *NSApplicationWillHideNotification;
extern NSString *NSApplicationWillFinishLaunchingNotification;
extern NSString *NSApplicationWillResignActiveNotification;
extern NSString *NSApplicationWillUnhideNotification;
extern NSString *NSApplicationWillUpdateNotification;
extern NSString *NSApplicationWillTerminateNotification;

#ifndef port_t
typedef unsigned long port_t;
#endif

//
// interfaces
//

@interface NSApplication : NSResponder
{
    NSEvent            *_currentEvent;
    NSMutableArray     *_windowList;
    id                  _keyWindow;
    id                  _mainWindow;
    id                  _delegate;
//  int                *_hiddenList;		// HIDE
//  int                 _hiddenCount;		// HIDE
    NSDPSContext       *_context;
    id                  _appListener;
    id			_appSpeaker;
    port_t              _replyPort;
    short               _modalRunningCount;
    struct __appFlags {
	unsigned int		_hidden:1;
	unsigned int        	_isJournalable:1;
	unsigned int        	_active:1;
	unsigned int        	_hasBeenRun:1;
	unsigned int        	_doingUnhide:1;
	unsigned int	    	_delegateReturnsValidRequestor:1;
	unsigned int	    	_deactPending:1;
	unsigned int        	_invalidState:1;
	unsigned int        	_invalidEvent:1;
	unsigned int        	_postedWindowsNeedUpdateNote:1;
	unsigned int		_running:1;
	unsigned int		_withinDealloc:1;
	unsigned int        	_RESERVED:4;
    }   		_appFlags;
    id                  _slaveJournaler;
    id                  _masterJournaler;
    id                  _pboard;
    id                  _mainMenu;
    id                  _appIcon;
    id                  _nameTable;

    id			_appThread;
    int			_appThreadIsMain;
}

//-----------------------------------------------------------------
// Creating and Initializing the NSApplication
//-----------------------------------------------------------------

+ (NSApplication *)sharedApplication;

- (void)finishLaunching;

//-----------------------------------------------------------------
// Changing the Active Application
//-----------------------------------------------------------------

- (void)activateIgnoringOtherApps:(BOOL)flag;

- (void)deactivate;

- (BOOL)isActive;

//-----------------------------------------------------------------
// Running the Event Loop
//-----------------------------------------------------------------

- (void)abortModal;

- (NSModalSession)beginModalSessionForWindow:(NSWindow *)theWindow;

- (void)endModalSession:(NSModalSession)session;

- (BOOL)isRunning;

- (void)run;

- (int)runModalForWindow:(NSWindow *)theWindow;

- (int)runModalSession:(NSModalSession)session;

- (void)sendEvent:(NSEvent *)theEvent;

- (void)stop:(id)sender;

- (void)stopModal;

- (void)stopModalWithCode:(int)returnCode;

//-----------------------------------------------------------------
// Getting, Removing, and Posting Events
//-----------------------------------------------------------------

- (NSEvent *)currentEvent;

- (void)discardEventsMatchingMask:(unsigned int)mask 
		      beforeEvent:(NSEvent *)lastEvent;

- (NSEvent *)nextEventMatchingMask:(unsigned int)mask 
                         untilDate:(NSDate *)expiration 
                            inMode:(NSString *)mode 
                           dequeue:(BOOL)deqFlag;

#ifndef STRICT_OPENSTEP
// NOTE: MouseMove events are coalesced, by default. This method allows one
// 		to retrieve *all* MouseMove events, with no coalescing.
- (NSEvent *)nextEventMatchingMask:(unsigned int)mask coalesce:(BOOL)coalesceFlag;
#endif

- (void)postEvent:(NSEvent *)event 
	  atStart:(BOOL)flag;

//-----------------------------------------------------------------
// Sending Action Messages
//-----------------------------------------------------------------

- (BOOL)sendAction:(SEL)theAction 
		to:(id)theTarget 
	      from:(id)sender;

- (id)targetForAction:(SEL)theAction;

- (BOOL)tryToPerform:(SEL)anAction 
		with:(id)anObject;

//-----------------------------------------------------------------
// Setting the Application's Icon
//-----------------------------------------------------------------

- (void)setApplicationIconImage:(NSImage *)image;

- (NSImage *)applicationIconImage;

//-----------------------------------------------------------------
// Hiding All Windows
//-----------------------------------------------------------------

- (void)hide:(id)sender;

- (BOOL)isHidden;

- (void)unhide:(id)sender;

- (void)unhideWithoutActivation;

//-----------------------------------------------------------------
// Managing Windows
//-----------------------------------------------------------------

- (NSWindow *)keyWindow;

- (NSWindow *)mainWindow;

- (NSWindow *)makeWindowsPerform:(SEL)aSelector inOrder:(BOOL)flag;

- (void)miniaturizeAll:(id)sender;

- (void)preventWindowOrdering;

- (void)setWindowsNeedUpdate:(BOOL)needUpdate;

- (void)updateWindows;

- (NSArray *)windows;

- (NSWindow *)windowWithWindowNumber:(int)windowNum;

//-----------------------------------------------------------------
// Showing Standard Panels
//-----------------------------------------------------------------

// ??? TODO

//-----------------------------------------------------------------
// Getting the Main Menu
//-----------------------------------------------------------------

- (NSMenu *)mainMenu;

- (void)setMainMenu:(NSMenu *)aMenu;

//-----------------------------------------------------------------
// Managing the Windows Menu
//-----------------------------------------------------------------

// see category below

//-----------------------------------------------------------------
// Managing the Services Menu
//-----------------------------------------------------------------

// see category below

//-----------------------------------------------------------------
// Getting the Display PostScript Context
//-----------------------------------------------------------------

- (NSDPSContext *)context;

//-----------------------------------------------------------------
// Reporting an Exception
//-----------------------------------------------------------------

- (void)reportException:(NSException *)theException;

//-----------------------------------------------------------------
// Terminating the Application
//-----------------------------------------------------------------

- (void)terminate:(id)sender;

//-----------------------------------------------------------------
// Assigning a Delegate
//-----------------------------------------------------------------

- (id)delegate;

- (void)setDelegate:(id)anObject;

@end

@interface NSObject (NSApplicationDelegate)

//-----------------------------------------------------------------
// Implemented by the Delegate
//-----------------------------------------------------------------

- (BOOL)application:(NSApplication *)sender 
  openFileWithoutUI:(NSString *)filename;

- (BOOL)application:(NSApplication *)sender 
	   openFile:(NSString *)filename;

- (BOOL)application:(NSApplication *)sender 
       openTempFile:(NSString *)filename;


- (void)applicationDidBecomeActive:(NSNotification *)notification;

- (void)applicationDidFinishLaunching:(NSNotification *)notification;

- (void)applicationDidHide:(NSNotification *)notification;

- (void)applicationDidResignActive:(NSNotification *)notification;

- (void)applicationDidUnhide:(NSNotification *)notification;

- (void)applicationDidUpdate:(NSNotification *)notification;

- (void)applicationWillTerminate:(NSNotification *)notification;

- (BOOL)applicationOpenUntitledFile:(NSApplication *)sender;

- (BOOL)applicationShouldTerminate:(NSApplication *)sender;

- (void)applicationWillBecomeActive:(NSNotification *)notification;

- (void)applicationWillFinishLaunching:(NSNotification *)notification;

- (void)applicationWillHide:(NSNotification *)notification;

- (void)applicationWillResignActive:(NSNotification *)notification;

- (void)applicationWillUnhide:(NSNotification *)notification;

- (void)applicationWillUpdate:(NSNotification *)notification;

@end

//-----------------------------------------------------------------
// Managing the Windows Menu
//-----------------------------------------------------------------

@interface NSApplication (NSWindowsMenu)

- (void)addWindowsItem:(NSWindow *)win 
		 title:(NSString *)aString 
	      filename:(BOOL)isFilename;

- (void)arrangeInFront:(id)sender;

- (void)changeWindowsItem:(NSWindow *)win 
		    title:(NSString *)aString 
		 filename:(BOOL)isFilename;

- (void)removeWindowsItem:(NSWindow *)win;

- (void)setWindowsMenu:(id)menu;

- (void)updateWindowsItem:(NSWindow *)win;

- (NSMenu *)windowsMenu;

@end

//-----------------------------------------------------------------
// Managing the Services Menu
//-----------------------------------------------------------------

@interface NSApplication (NSServicesMenu)

- (void)registerServicesMenuSendTypes:(NSArray *)sendTypes 
			  returnTypes:(NSArray *)returnTypes;

- (NSMenu *)servicesMenu;

- (void)setServicesMenu:(NSMenu *)aMenu;

- (id)validRequestorForSendType:(NSString *)sendType 
		     returnType:(NSString *)returnType;

@end


// Not in spec

@interface NSObject (NSServicesRequests)

- (BOOL)writeSelectionToPasteboard:(NSPasteboard *)pboard types:(NSArray *)types;

- (BOOL)readSelectionFromPasteboard:(NSPasteboard *)pboard;

@end


//-----------------------------------------------------------------
// Managing the Services Menu -- Functions
//-----------------------------------------------------------------

// Functions to enable/disable Services Menu items.  These should
// usually only be called by service PROVIDERS (since they are the
// only ones who know the name of the services, requestors don't).
// The itemName in the two functions below is the language-independent
// "Menu Item:" entry in the __services section (which all provided
// services must have).  The set function returns whether it was
// successful.  NXUpdateDynamicServices() causes the services
// information for the system to be updated.  This will only be
// necessary if your program adds dynamic services to the system
// (i.e. services not found in macho segments of executables).

#ifdef __cplusplus
extern "C" {
#endif

extern int 	NSSetShowsServicesMenuItem( NSString *itemName, 
					    BOOL enabled );
extern BOOL 	NSShowsServicesMenuItem( NSString *itemName );
extern BOOL 	NSPerformService( NSString *itemName, NSPasteboard *pboard );
extern void 	NSUpdateDynamicServices( void );


#ifdef __cplusplus
}
#endif



//Service Provider Category.

@interface NSApplication(NSServicesHandling)
- (void)setServicesProvider:(id)provider;
- (id)servicesProvider;
@end

//Service Provider Function Prototypes.

#ifdef __cplusplus
extern "C" {
#endif

extern void NSRegisterServicesProvider(id provider, NSString *name);
extern void NSUnregisterServicesProvider(NSString *name);
 
#ifdef __cplusplus
}
#endif

extern int NSApplicationMain( int argc, const char *argv[]);

#endif /* _NSApplication_h_ */

