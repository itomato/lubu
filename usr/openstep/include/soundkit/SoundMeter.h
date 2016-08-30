#ident "@(#) SoundMeter.h, Rev 2.9, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1988, 1989, 1990, NeXT, Inc.
//	All rights reserved.

#import <AppKit/NSView.h>
#import <soundkit/Sound.h>

@interface SoundMeter:NSView
{
    id sound;
    int currentSample;
    float currentValue;
    float currentPeak;
    float minValue;
    float maxValue;
    float holdTime;
    NSColor *backgroundColor;
    NSColor *foregroundColor;
    NSColor *peakColor;
    struct {
	unsigned int running:1;
	unsigned int bezeled:1;
	unsigned int shouldStop:1;
	unsigned int _reservedFlags:13;
    } smFlags;
    int _valTime;
    int _peakTime;
    float _valOneAgo;
    float _valTwoAgo;
}

- initWithFrame: (NSRect) frameRect;

- (void) encodeWithCoder: (NSCoder *) coder;
- initWithCoder: (NSCoder *) coder;
- (float)holdTime;
- setHoldTime:(float)seconds;
- (NSColor *)backgroundColor;
- (void)setBackgroundColor:(NSColor *)aValue;
- (NSColor *)foregroundColor;
- (void)setForegroundColor:(NSColor *)aValue;
- (NSColor *)peakColor;
- (void)setPeakColor:(NSColor *)aValue;
- (Sound *) sound;
- (void) setSound: (Sound *) aSound;
- run:sender;
- (void) stop:sender;
- (BOOL)isRunning;
- (BOOL)isBezeled;
- setBezeled:(BOOL)aFlag;
- setFloatValue:(float)aValue;
- (float)floatValue;
- (float)peakValue;
- (float)minValue;
- (float)maxValue;
- drawRect: (NSRect) rect;
- drawCurrentValue;

/* 
 * The following new... methods are now obsolete.  They remain in this  
 * interface file for backward compatibility only.  Use Object's alloc method  
 * and the init... methods defined in this class instead.
 */
+ newFrame: (NSRect) frameRect;

@end
