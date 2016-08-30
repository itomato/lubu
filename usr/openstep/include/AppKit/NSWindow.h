#ident "@(#) NSWindow.h, Rev 1.31, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#ifndef _NSWindow_h_
#define _NSWindow_h_

//
// OpenStep includes
//

#import <AppKit/NSResponder.h>
#import <AppKit/NSScreen.h>
#import <AppKit/NSGraphics.h>
#import <AppKit/NSDragging.h>
#import <AppKit/NSColor.h>
#import <AppKit/NSSpellProtocol.h>
#import <objc/hashtable.h>

//
// forward declarations
//

@class NSText <NSChangeSpelling, NSIgnoreMisspelledWords>;
@class NSCursor <NSCoding>;
@class NSView;
@class NSEvent <NSCopying, NSCoding>;

//
// enums
//

enum {
    NSBorderlessWindowMask		= 0,
    NSTitledWindowMask			= 1 << 0,
    NSClosableWindowMask		= 1 << 1,
    NSMiniaturizableWindowMask		= 1 << 2,
    NSResizableWindowMask		= 1 << 3
};

enum {
    NSNormalWindowLevel			= 0,
    NSFloatingWindowLevel		= 3,
    NSDockWindowLevel			= 5,
    NSSubmenuWindowLevel		= 10,
    NSMainMenuWindowLevel		= 20
};

//
// global vars
//

extern NSSize NSIconSize;
extern NSSize NSTokenSize;

// notifications

extern NSString *NSWindowDidBecomeKeyNotification;
extern NSString *NSWindowDidBecomeMainNotification;
extern NSString *NSWindowDidChangeScreenNotification;
extern NSString *NSWindowDidDeminiaturizeNotification;
extern NSString *NSWindowDidExposeNotification;
extern NSString *NSWindowDidMiniaturizeNotification;
extern NSString *NSWindowDidMoveNotification;
extern NSString *NSWindowDidResignKeyNotification;
extern NSString *NSWindowDidResignMainNotification;
extern NSString *NSWindowDidResizeNotification;
extern NSString *NSWindowDidUpdateNotification;
extern NSString *NSWindowWillCloseNotification;

//
// interfaces
//

@interface NSWindow : NSResponder
{
    NSRect              _frame;
    NSString		*_title;
    id                  _contentView;
    id                  _delegate;
    NSResponder		*_firstResponder;
    id                  _lastLeftHit;
    id                  _lastRightHit;
    id                  _counterpart;
    id                  _fieldEditor;
    int                 _winEventMask;
    int                 _windowNum;
    int			_level;
    NSColor		*_backgroundColor;
    id                  _borderView;
    BOOL		_autodisplay;
    unsigned char	_styleMask;
    short               _flushDisabled;
    void		*_cursorRects;
    NXHashTable		*_trectTable;
    id			_invalidCursorView;
    NSImage		*_miniIcon;
    int			_lastResizeTime;
    NSMutableSet	*_dragTypes;
    NSString		*_representedFilename;
    NSSize		*_sizeLimits;
    NSSize              _aspectRatio;
    NSString		*_frameSaveName;
    NSSet		*_regDragTypes;
    id			_cachedImage;
    struct __wFlags {
        unsigned int	    style:4;
        unsigned int        backing:2;
        unsigned int        buttonMask:3;
        unsigned int        visible:1;
        unsigned int        isMainWindow:1;
        unsigned int        isKeyWindow:1;
        unsigned int        hidesOnDeactivate:1;
        unsigned int        dontFreeWhenClosed:1;
        unsigned int        oneShot:1;
        unsigned int        deferred:1;
        unsigned int        cursorRectsDisabled:1;
        unsigned int        haveFreeCursorRects:1;
        unsigned int        validCursorRects:1;
        unsigned int        docEdited:1;
        unsigned int        dynamicDepthLimit:1;
        unsigned int        worksWhenModal:1;
        unsigned int        limitedBecomeKey:1;
        unsigned int        needsFlush:1;
        unsigned int        viewsNeedDisplay:1;
        unsigned int        ignoredFirstMouse:1;
        unsigned int        repostedFirstMouse:1;
        unsigned int        windowDying:1;
        unsigned int        tempHidden:1;
        unsigned int        floatingPanel:1;
        unsigned int        wantsToBeOnMainScreen:1;
        unsigned int        optimizedDrawingOk:1;
        unsigned int        optimizeDrawing:1;
        unsigned int        titleIsRepresentedFilename:1;
        unsigned int        excludedFromWindowsMenu:1;
        unsigned int        depthLimit:4;
        unsigned int        delegateReturnsValidRequestor:1;
        unsigned int        lmouseupPending:1;
        unsigned int        rmouseupPending:1;
        unsigned int        wantsToDestroyRealWindow:1;
        unsigned int        userCantConstrainResize:1;
        unsigned int        wantsToRegDragTypes:1;
        unsigned int        titleNeedsDisplay:1;
        unsigned int        avoidsActivation:1;
        unsigned int        frameSavedUsingTitle:1;
        unsigned int        didRegDragTypes:1;
        unsigned int        deferredChangeKey:1;
        unsigned int        deferredAcceptFirstResp:1;
        unsigned int        delayedOneShot:1;
        unsigned int	    postedNeedsDisplayNote:1;
        unsigned int	    postedInvalidCursorRectsNote:1;
	unsigned int	    closePending:1;
	unsigned int	    isMiniaturized;
	unsigned int	    ignoreNextTakeFocus:1;
        unsigned int        RESERVED:8;
    }                   _wFlags;

@private
    id			_xTLW;
    NSScreen*		_currentScreen;
}

//----------------------------------------------------------------------------
// Initializing and Getting a New NSWindow Object
//----------------------------------------------------------------------------

- (id)initWithContentRect:(NSRect)contentRect 
		styleMask:(unsigned int)aStyle 
		  backing:(NSBackingStoreType)bufferingType 
		    defer:(BOOL)flag;

- (id)initWithContentRect:(NSRect)contentRect 
		styleMask:(unsigned int)aStyle 
		  backing:(NSBackingStoreType)bufferingType 
		    defer:(BOOL)flag
		   screen:(NSScreen *)screen;

#ifndef STRICT_OPENSTEP

//
// Implementation Note: on X11 the NSWindowDepth is mapped onto a visual,
// depth pair, futhermore X Windows cannot change their visual and depth
// after creation, therefore there are two portability issues:
//
//	1) dynamic depth limits do not exist on X11 implementations
//
//	2) the depth limit of a window must be set *before* it is 
//	   created.
//
//	This *non-portable* interface allows the setting of the depth
//	limit prior to window creation, otherwise you must defer window
//	creation, then set the depth limit, and then cause the window
//	to be created subseqently.

- (id)initWithContentRect: (NSRect)	 	contentRect 
		styleMask: (unsigned int) 	aStyle 
		  backing: (NSBackingStoreType) bufferingType 
	       depthLimit: (NSWindowDepth) 	depthLimit
		    defer: (BOOL)		flag
		   screen: (NSScreen *)		screen;
#endif

//----------------------------------------------------------------------------
// Computing Frame and Content Rectangles
//----------------------------------------------------------------------------

+ (NSRect)contentRectForFrameRect:(NSRect)fRect 
			styleMask:(unsigned int)aStyle;

+ (NSRect)frameRectForContentRect:(NSRect)cRect 
			styleMask:(unsigned int)aStyle;

+ (float)minFrameWidthWithTitle:(NSString *)aTitle 
		      styleMask:(unsigned int)aStyle;

//----------------------------------------------------------------------------
// Accessing the Content View
//----------------------------------------------------------------------------

- (id)contentView;

- (void)setContentView:(NSView *)aView;

//----------------------------------------------------------------------------
// Window Graphics
//----------------------------------------------------------------------------

- (NSColor *)backgroundColor;

- (NSString *)representedFilename;

- (void)setBackgroundColor:(NSColor *)color;

- (void)setRepresentedFilename:(NSString *)aString;

- (void)setTitle:(NSString *)aString;

- (void)setTitleWithRepresentedFilename:(NSString *)filename;

- (unsigned int)styleMask;

- (NSString *)title;

// These methods allow the caller to save a window's current "bits".
// The caller is then free to draw whatever they like into the window 
// (animation, etc.), after which they can quickly clear their
// drawing by "restore"ing the area(s) they have drawn over. This used to be
// accomplished with instance drawing.

// NOTES:
//	1. Calling this method discards any previously saved cached image.
//	2. Calling this method will cause a "displayIfNeeded" message to
//		be sent to the window, so that all bits are "up-to-date"
//		before the window's image is cached.
//	3. Calling [aWindow display] discards all saved bit rects.
//	(since if a Window's Views draw, the cached image will be out-of-date).
//	4. It is typically much faster to cache an image of the whole window
//		(cacheImage) and just keep restoring that one
//		saved cache, rather than to keep recaching smaller areas
//		(with cacheImageInRect:).
#ifndef STRICT_OPENSTEP
// Basically just "[aWindow cacheImageInRect:[[aWindow contentView] frame]]"
- (void)cacheImage;
#endif
- (void)cacheImageInRect:(NSRect)aRect;

// This method will redraw ("blast") the cached image back into the window,
// erasing whatever was previously there.
// NOTE: This method will *not* "flush" the window. For the "restoration"
//	to appear in your Window, you may need to call "flushWindowIfNeeded".
//	Only call "flushWindowIfNeeded" if you are not already calling 
//	"flushWindow" following your "restoreCachedImage" call, or you may get
//	some flicker.
- (void)restoreCachedImage;

// This method releases the memory used to store the saved bit image.
// This method should be called after the final "restoreCachedImage" is called.
- (void)discardCachedImage;

#ifndef STRICT_OPENSTEP
// NOTE: MouseMove events are coalesced, by default. This method allows one
// 		to retrieve *all* MouseMove events, with no coalescing.
- (NSEvent *)nextEventMatchingMask:(unsigned int)mask coalesce:(BOOL)coalesceFlag;
#endif


//----------------------------------------------------------------------------
// Window Device Attributes
//----------------------------------------------------------------------------

- (NSBackingStoreType)backingType;

- (NSDictionary *)deviceDescription;

- (int)gState;

- (BOOL)isOneShot;

- (void)setBackingType:(NSBackingStoreType)bufferingType;

- (void)setOneShot:(BOOL)flag;

- (int)windowNumber;

//----------------------------------------------------------------------------
// The Miniwindow
//----------------------------------------------------------------------------

- (NSImage *)miniwindowImage;

- (NSString *)miniwindowTitle;

- (void)setMiniwindowImage:(NSImage *)image;

- (void)setMiniwindowTitle:(NSString *)title;

//----------------------------------------------------------------------------
// The Field Editor
//----------------------------------------------------------------------------

- (void)endEditingFor:(id)anObject;

- (NSText *)fieldEditor:(BOOL)createFlag 
              forObject:(id)anObject;

//----------------------------------------------------------------------------
// Window Status and Ordering 
//----------------------------------------------------------------------------

- (void)becomeKeyWindow;

- (void)becomeMainWindow;

- (BOOL)canBecomeKeyWindow;

- (BOOL)canBecomeMainWindow;

- (BOOL)hidesOnDeactivate;

- (BOOL)isKeyWindow;

- (BOOL)isMainWindow;

- (BOOL)isMiniaturized;

- (BOOL)isVisible;

- (int)level;

- (void)makeKeyAndOrderFront:(id)sender;

- (void)makeKeyWindow;

- (void)makeMainWindow;

- (void)orderBack:(id)sender;

- (void)orderFront:(id)sender;

- (void)orderFrontRegardless;

- (void)orderOut:(id)sender;

- (void)orderWindow:(NSWindowOrderingMode)place 
	 relativeTo:(int)otherWin;

- (void)resignKeyWindow;

- (void)resignMainWindow;

- (void)setHidesOnDeactivate:(BOOL)flag;

- (void)setLevel:(int)newLevel;

//----------------------------------------------------------------------------
// Moving and Resizing the Window
//----------------------------------------------------------------------------

- (NSPoint)cascadeTopLeftFromPoint:(NSPoint)topLeftPoint;

- (void)center;

- (NSRect)constrainFrameRect:(NSRect)frameRect 
		    toScreen:(NSScreen *)screen;

- (NSRect)frame;

- (NSSize)minSize;

- (NSSize)maxSize;

- (NSSize) resizeIncrements;

- (void)setContentSize:(NSSize)aSize;

- (void)setFrame:(NSRect)frameRect 
	 display:(BOOL)flag;

- (void)setFrameOrigin:(NSPoint)aPoint;

- (void)setFrameTopLeftPoint:(NSPoint)aPoint;

- (void)setMinSize:(NSSize)size;

- (void)setMaxSize:(NSSize)size;

- (void) setResizeIncrements: (NSSize) increments;

- (void) setAspectRatio: (NSSize) ratio;

- (NSSize) aspectRatio;

//----------------------------------------------------------------------------
// Converting Coordinates
//----------------------------------------------------------------------------

- (NSPoint)convertBaseToScreen:(NSPoint)aPoint;

- (NSPoint)convertScreenToBase:(NSPoint)aPoint;

//----------------------------------------------------------------------------
// Managing the Display
//----------------------------------------------------------------------------

- (void)display;

- (void)disableFlushWindow;

- (void)displayIfNeeded;

- (void)enableFlushWindow;

- (void)flushWindow;

- (void)flushWindowIfNeeded;

- (BOOL)isAutodisplay;

- (BOOL)isFlushWindowDisabled;

- (void)setAutodisplay:(BOOL)flag;

- (void)setViewsNeedDisplay:(BOOL)flag;

- (void)update;

- (void)useOptimizedDrawing:(BOOL)flag;

- (BOOL)viewsNeedDisplay;

//----------------------------------------------------------------------------
// Screens and Window Depths
//----------------------------------------------------------------------------

+ (NSWindowDepth)defaultDepthLimit;

- (BOOL)canStoreColor;

- (NSScreen *)deepestScreen;

- (NSWindowDepth)depthLimit;

- (BOOL)hasDynamicDepthLimit;

- (NSScreen *)screen;

- (void)setDepthLimit:(NSWindowDepth)limit;

- (void)setDynamicDepthLimit:(BOOL)flag;

//----------------------------------------------------------------------------
// Cursor Management
//----------------------------------------------------------------------------

- (BOOL)areCursorRectsEnabled;

- (void)disableCursorRects;

- (void)discardCursorRects;

- (void)enableCursorRects;

- (void)invalidateCursorRectsForView:(NSView *)aView;

- (void)resetCursorRects;

//----------------------------------------------------------------------------
// Handling User Actions and Events
//----------------------------------------------------------------------------

- (void)close;

- (void)deminiaturize:(id)sender;

- (BOOL)isDocumentEdited;

- (BOOL)isReleasedWhenClosed;

- (void)miniaturize:(id)sender;

- (void)performClose:(id)sender;

- (void)performMiniaturize:(id)sender;

- (int)resizeFlags;

- (void)setDocumentEdited:(BOOL)flag;

- (void)setReleasedWhenClosed:(BOOL)flag;

//----------------------------------------------------------------------------
// Aiding Event Handling
//----------------------------------------------------------------------------

- (BOOL)acceptsMouseMovedEvents;

- (NSEvent *)currentEvent;

- (void)discardEventsMatchingMask:(unsigned int)mask 
		      beforeEvent:(NSEvent *)lastEvent;

- (NSResponder *)firstResponder;

- (void)keyDown:(NSEvent *)theEvent;

- (BOOL)makeFirstResponder:(NSResponder *)aResponder;

- (NSPoint)mouseLocationOutsideOfEventStream;

- (NSEvent *)nextEventMatchingMask:(unsigned int)mask;

- (NSEvent *)nextEventMatchingMask:(unsigned int)mask 
                         untilDate:(NSDate *)expiration 
                            inMode:(NSString *)mode 
                           dequeue:(BOOL)deqFlag;

- (void)postEvent:(NSEvent *)event 
	  atStart:(BOOL)flag;

- (void)setAcceptsMouseMovedEvents:(BOOL)flag;

- (void)sendEvent:(NSEvent *)theEvent;

- (BOOL)tryToPerform:(SEL)anAction 
		with:(id)anObject;

- (BOOL)worksWhenModal;

//----------------------------------------------------------------------------
// Dragging
//----------------------------------------------------------------------------

// see category below

//----------------------------------------------------------------------------
// Services and Windows Menu Support
//----------------------------------------------------------------------------

- (BOOL)isExcludedFromWindowsMenu;

- (void)setExcludedFromWindowsMenu:(BOOL)flag;

- (id)validRequestorForSendType:(NSString *)sendType 
		     returnType:(NSString *)returnType;

//----------------------------------------------------------------------------
// Saving and Restoring the Frame
//----------------------------------------------------------------------------

+ (void)removeFrameUsingName:(NSString *)name;

- (NSString *)frameAutosaveName;

- (void)saveFrameUsingName:(NSString *)name;

- (BOOL)setFrameAutosaveName:(NSString *)name;

- (void)setFrameFromString:(NSString *)string;

- (BOOL)setFrameUsingName:(NSString *)name;

- (NSString *)stringWithSavedFrame;

//----------------------------------------------------------------------------
// Printing and PostScript
//----------------------------------------------------------------------------

- (NSData *)dataWithEPSInsideRect:(NSRect)rect;

#ifndef STRICT_OPENSTEP
#ifdef FAX_SUPPORT
- (void)fax:(id)sender;
#endif
#endif

- (void)print:(id)sender;

//----------------------------------------------------------------------------
// Assigning a Delegate
//----------------------------------------------------------------------------

- (id)delegate;

- (void)setDelegate:(id)anObject;


@end


//----------------------------------------------------------------------------
// Dragging
//----------------------------------------------------------------------------


@interface NSWindow(NSDrag)

- (void)dragImage:(NSImage *)anImage 
	       at:(NSPoint)baseLocation 
	   offset:(NSSize)initialOffset 
	    event:(NSEvent *)event 
       pasteboard:(NSPasteboard *)pboard 
	   source:(id)sourceObj 
	slideBack:(BOOL)slideFlag;

- (void)registerForDraggedTypes:(NSArray *)newTypes;

- (void)unregisterDraggedTypes;

@end


//----------------------------------------------------------------------------
// Implemented by the Delegate
//----------------------------------------------------------------------------


@interface NSObject(NSWindowDelegate)

- (BOOL)windowShouldClose:(id)sender;

- (id)windowWillReturnFieldEditor:(NSWindow *)sender 
			 toObject:(id)client;

@end


@interface NSObject(NSWindowNotifications)

- (void)windowDidBecomeKey:(NSNotification *)notification;

- (void)windowDidBecomeMain:(NSNotification *)notification;

- (void)windowDidChangeScreen:(NSNotification *)notification;

- (void)windowDidDeminiaturize:(NSNotification *)notification;

- (void)windowDidExpose:(NSNotification *)notification;

- (void)windowDidMiniaturize:(NSNotification *)notification;

- (void)windowDidMove:(NSNotification *)notification;

- (void)windowDidResignKey:(NSNotification *)notification;

- (void)windowDidResignMain:(NSNotification *)notification;

- (void)windowDidResize:(NSNotification *)notification;

- (void)windowDidUpdate:(NSNotification *)notification;

- (void)windowWillClose:(NSNotification *)notification;

@end

#endif // _NSWindow_h_
