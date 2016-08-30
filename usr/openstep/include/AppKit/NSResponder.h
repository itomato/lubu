#ident "@(#) NSResponder.h, Rev 1.5, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import <Foundation/Foundation.h>
#import <Foundation/NSObject.h>
#import <DPS/dpsclient.h>
#import <Foundation/NSString.h>
#import <AppKit/NSEvent.h>

@interface NSResponder : NSObject <NSCoding>
{
    NSResponder* _nextResponder;
}

- (BOOL) tryToPerform: (SEL) anAction with: (id) anObject;

- (id) validRequestorForSendType: (NSString *) sendType
		      returnType: (NSString *) returnType;

/*
 * Mouse Events
 */
 
- (void) mouseDown:            (NSEvent *) theEvent;
- (void) mouseUp:              (NSEvent *) theEvent;
- (void) rightMouseDown:       (NSEvent *) theEvent;
- (void) rightMouseUp:         (NSEvent *) theEvent;
- (void) mouseMoved:           (NSEvent *) theEvent;
- (void) mouseDragged:         (NSEvent *) theEvent;
- (void) rightMouseDragged:    (NSEvent *) theEvent;
- (void) mouseEntered:         (NSEvent *) theEvent;
- (void) mouseExited:          (NSEvent *) theEvent;
 
/*
 * Key Events
 */
 
- (void) keyDown:              (NSEvent *) theEvent;
- (void) keyUp:                (NSEvent *) theEvent;
 
- (BOOL) performKeyEquivalent: (NSEvent *) theEvent;

- (void) flagsChanged:         (NSEvent *) theEvent;

- (void) noResponderFor: (SEL) eventSelector;

/*
 * responder chain ...
 */

- (NSResponder *) nextResponder;

- (BOOL) acceptsFirstResponder;
- (BOOL) becomeFirstResponder;
- (BOOL) resignFirstResponder;

- (void) setNextResponder: (NSResponder *) aResponder;

/*
 * help
 */

- (void) helpRequested: (NSEvent *) eventPtr;

@end
