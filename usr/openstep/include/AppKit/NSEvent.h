#ident "@(#) NSEvent.h, Rev 1.9, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#import <DPSClient/dpsOpenStep.h>
#import <DPSClient/NSDPSContext.h>

@class NSWindow;

typedef enum _NSEventType {		/* various types of events */
	NSNoEvent		= 0,
	NSLeftMouseDown		= 1,
	NSLeftMouseUp		= 2,
	NSRightMouseDown	= 3,
	NSRightMouseUp		= 4,
	NSMouseMoved		= 5,
	NSLeftMouseDragged	= 6,
	NSRightMouseDragged	= 7,
	NSMouseEntered		= 8,
	NSMouseExited		= 9,
	NSKeyDown		= 10,
	NSKeyUp			= 11,
	NSFlagsChanged		= 12,
#ifndef STRICT_OPENSTEP
	NSAppKitDefined		= 13,
	NSSystemDefined		= 14,
	NSApplicationDefined	= 15,
#endif
	NSPeriodic		= 16,
	NSCursorUpdate		= 17
} NSEventType;

enum {					/* masks for the types of events */
	NSLeftMouseDownMask		= 1 << NSLeftMouseDown,
	NSLeftMouseUpMask		= 1 << NSLeftMouseUp,
	NSRightMouseDownMask		= 1 << NSRightMouseDown,
	NSRightMouseUpMask		= 1 << NSRightMouseUp,
	NSMouseMovedMask		= 1 << NSMouseMoved,
	NSLeftMouseDraggedMask		= 1 << NSLeftMouseDragged,
	NSRightMouseDraggedMask		= 1 << NSRightMouseDragged,
	NSMouseEnteredMask		= 1 << NSMouseEntered,
	NSMouseExitedMask		= 1 << NSMouseExited,
	NSKeyDownMask			= 1 << NSKeyDown,
	NSKeyUpMask			= 1 << NSKeyUp,
	NSFlagsChangedMask		= 1 << NSFlagsChanged,
#ifndef STRICT_OPENSTEP
	NSAppKitDefinedMask		= 1 << NSAppKitDefined,
	NSSystemDefinedMask		= 1 << NSSystemDefined,
	NSApplicationDefinedMask	= 1 << NSApplicationDefined,
#endif
	NSPeriodicMask			= 1 << NSPeriodic,
	NSCursorUpdateMask		= 1 << NSCursorUpdate,
	NSAnyEventMask			= 0xffffffff
};

static inline unsigned int
NSEventMaskFromType(NSEventType type) { return (1 << type); }

/* Device-independent bits found in event modifier flags */
enum {
	NSAlphaShiftKeyMask =		1 << 16,	/* 00010000 */
	NSShiftKeyMask =		1 << 17,	/* 00020000 */
	NSControlKeyMask =		1 << 18,	/* 00040000 */
	NSAlternateKeyMask =		1 << 19,	/* 00080000 */
	NSCommandKeyMask =		1 << 20,	/* 00100000 */
	NSNumericPadKeyMask =		1 << 21,	/* 00200000 */
	NSHelpKeyMask =			1 << 22,	/* 00400000 */
	NSFunctionKeyMask =		1 << 23		/* 00800000 */
};

@interface NSEvent : NSObject <NSCopying, NSCoding> {
	NSEventType			_type;
	NSPoint				_location;
	unsigned int			_modifierFlags;
	unsigned int			_WSTimestamp; // used to be int
	NSTimeInterval			_timestamp;
	int				_windowNumber;
	NSWindow*			_window;
	NSDPSContext*			_context;
	union {
		struct {
			int		eventNumber;
			int		clickCount;
			float		pressure;
		} mouse;

		struct {
			NSString*	keys;
			NSString*	unmodKeys;
			unsigned short	keyCode;
			BOOL		isARepeat;
		} key;

		struct {
			int		eventNumber;
			int		trackingNumber;
			void*		userData;
		} tracking;

		struct {
			int		subtype;
			int		data1;
			int		data2;
		} misc;
	} _data;
}


/* these messages are valid for all events */

- (NSEventType) type;

- (NSPoint) locationInWindow;

- (unsigned int) modifierFlags;

- (NSTimeInterval) timestamp;

- (NSWindow *) window;

- (int) windowNumber;

- (NSDPSContext *) context;

/* these messages are valid for all mouse down/up/drag events */

- (int) clickCount;

- (float) pressure;

/* these messages are valid for all mouse down/up/drag and enter/exit events */

- (int) eventNumber;

/* these messages are valid for keyup and keydown events */
- (NSString *) characters;
- (NSString *) charactersIgnoringModifiers;

/* the chars that would have been generated,
 * regardless of modifier keys (except shift)
 */

- (BOOL) isARepeat;

/* this message is valid for keyup, keydown and flagschanged events */

- (unsigned short) keyCode;		/* device-dependent key number */

/* these messages are valid for enter and exit events */

- (int) trackingNumber;

- (void *) userData;

/* these messages are valid for kit, system, and app-defined events */

- (short) subtype;

- (int) data1;
- (int) data2;

/* used for initial delay and periodic behavior in tracking loops */
+ (void) startPeriodicEventsAfterDelay: (NSTimeInterval) delay
			    withPeriod: (NSTimeInterval) period;
+ (void)stopPeriodicEvents;

/* apps will rarely create these objects */

+ (NSEvent *) mouseEventWithType: (NSEventType)    type
		        location: (NSPoint)	   location
		   modifierFlags: (unsigned int)   flags
		       timestamp: (NSTimeInterval) time
		    windowNumber: (int)		   wNum
			 context: (NSDPSContext *) context
		     eventNumber: (int)	           eNum
		      clickCount: (int)		   cNum
			pressure: (float)	   pressure;

+ (NSEvent *) keyEventWithType: (NSEventType)	 type
		      location: (NSPoint)	 location
		 modifierFlags: (unsigned int)   flags
		     timestamp: (NSTimeInterval) time
		  windowNumber: (int)		 wNum
		       context: (NSDPSContext *) context
		    characters: (NSString *)	 keys
   charactersIgnoringModifiers: (NSString *)	 ukeys
		     isARepeat: (BOOL)	 	 flag
		       keyCode: (unsigned short) code;

+ (NSEvent *) enterExitEventWithType: (NSEventType)    type
			    location: (NSPoint)	       location
		       modifierFlags: (unsigned int)   flags
			   timestamp: (NSTimeInterval) time
			windowNumber: (int)	       wNum
			     context: (NSDPSContext *) context
			 eventNumber: (int)	       eNum
		      trackingNumber: (int)	       tNum
			    userData: (void *)	       data;

+ (NSEvent *) otherEventWithType: (NSEventType)	   type
			location: (NSPoint)	   location
		   modifierFlags: (unsigned int)   flags
		       timestamp: (NSTimeInterval) time
		    windowNumber: (int)		   wNum
			 context: (NSDPSContext *) context
			 subtype: (short)	   subtype
			   data1: (int)		   d1
			   data2: (int)		   d2;

@end


/* Unicodes we reserve for function keys on the keyboard,  
 * OpenStep reserves the range 0xF700-0xF8FF for this purpose.  
 * The availability of various keys will be system dependent.
 */

enum {
	NSUpArrowFunctionKey		= 0xF700,
	NSDownArrowFunctionKey		= 0xF701,
	NSLeftArrowFunctionKey		= 0xF702,
	NSRightArrowFunctionKey		= 0xF703,
	NSF1FunctionKey			= 0xF704,
	NSF2FunctionKey			= 0xF705,
	NSF3FunctionKey			= 0xF706,
	NSF4FunctionKey			= 0xF707,
	NSF5FunctionKey			= 0xF708,
	NSF6FunctionKey			= 0xF709,
	NSF7FunctionKey			= 0xF70A,
	NSF8FunctionKey			= 0xF70B,
	NSF9FunctionKey			= 0xF70C,
	NSF10FunctionKey		= 0xF70D,
	NSF11FunctionKey		= 0xF70E,
	NSF12FunctionKey		= 0xF70F,
	NSF13FunctionKey		= 0xF710,
	NSF14FunctionKey		= 0xF711,
	NSF15FunctionKey		= 0xF712,
	NSF16FunctionKey		= 0xF713,
	NSF17FunctionKey		= 0xF714,
	NSF18FunctionKey		= 0xF715,
	NSF19FunctionKey		= 0xF716,
	NSF20FunctionKey		= 0xF717,
	NSF21FunctionKey		= 0xF718,
	NSF22FunctionKey		= 0xF719,
	NSF23FunctionKey		= 0xF71A,
	NSF24FunctionKey		= 0xF71B,
	NSF25FunctionKey		= 0xF71C,
	NSF26FunctionKey		= 0xF71D,
	NSF27FunctionKey		= 0xF71E,
	NSF28FunctionKey		= 0xF71F,
	NSF29FunctionKey		= 0xF720,
	NSF30FunctionKey		= 0xF721,
	NSF31FunctionKey		= 0xF722,
	NSF32FunctionKey		= 0xF723,
	NSF33FunctionKey		= 0xF724,
	NSF34FunctionKey		= 0xF725,
	NSF35FunctionKey		= 0xF726,
	NSInsertFunctionKey		= 0xF727,
	NSDeleteFunctionKey		= 0xF728,
	NSHomeFunctionKey		= 0xF729,
	NSBeginFunctionKey		= 0xF72A,
	NSEndFunctionKey		= 0xF72B,
	NSPageUpFunctionKey		= 0xF72C,
	NSPageDownFunctionKey		= 0xF72D,
	NSPrintScreenFunctionKey	= 0xF72E,
	NSScrollLockFunctionKey		= 0xF72F,
	NSPauseFunctionKey		= 0xF730,
	NSSysReqFunctionKey		= 0xF731,
	NSBreakFunctionKey		= 0xF732,
	NSResetFunctionKey		= 0xF733,
	NSStopFunctionKey		= 0xF734,
	NSMenuFunctionKey		= 0xF735,
	NSUserFunctionKey		= 0xF736,
	NSSystemFunctionKey		= 0xF737,
	NSPrintFunctionKey		= 0xF738,
	NSClearLineFunctionKey		= 0xF739,
	NSClearDisplayFunctionKey	= 0xF73A,
	NSInsertLineFunctionKey		= 0xF73B,
	NSDeleteLineFunctionKey		= 0xF73C,
	NSInsertCharFunctionKey		= 0xF73D,
	NSDeleteCharFunctionKey		= 0xF73E,
	NSPrevFunctionKey		= 0xF73F,
	NSNextFunctionKey		= 0xF740,
	NSSelectFunctionKey		= 0xF741,
	NSExecuteFunctionKey		= 0xF742,
	NSUndoFunctionKey		= 0xF743,
	NSRedoFunctionKey		= 0xF744,
	NSFindFunctionKey		= 0xF745,
	NSHelpFunctionKey		= 0xF746,
	NSModeSwitchFunctionKey		= 0xF747
};


#ifndef STRICT_OPENSTEP

enum {		/* event subtypes for NSAppkitDefined events */
    NSWindowExposedEventType		= 0,
    NSApplicationActivatedEventType	= 1,
    NSApplicationDeactivatedEventType	= 2,
    NSWindowMovedEventType 		= 4,
    NSScreenChangedEventType		= 8,	// not applicable to Sun
    NSWindowResizedEventType		= 16,	// Sun Specific
    NSApplicationHideEventType		= 32
};

enum {		/* event subtypes for NSSystemDefined events */
    NSPowerOffEventType			= 1
};

#endif
