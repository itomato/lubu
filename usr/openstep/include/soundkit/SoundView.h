#ident "@(#) SoundView.h, Rev 2.14, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1988, 1989, 1990, 1991, NeXT, Inc.
//	All rights reserved.

#import <AppKit/NSView.h>
#import <AppKit/NSGraphics.h>
#import <Foundation/Foundation.h>

@class NSEvent;
@class Sound;

@interface SoundView : NSView {
    Sound *sound;
    id _private;		/* 3.0 */
    id delegate;
    NSRect selectionRect;
    int displayMode;
    NSColor *backgroundColor;
    NSColor *foregroundColor;
    float reductionFactor;
    struct {
	unsigned int disabled:1;
	unsigned int continuous:1;
	unsigned int calcDrawInfo:1;
	unsigned int selectionDirty:1;
	unsigned int autoscale:1;
	unsigned int bezeled:1;
	unsigned int notEditable:1;
	unsigned int notOptimizedForSpeed:1;	/* 3.0 */
	unsigned int _reservedFlags:8;
    } svFlags;
    Sound *_scratchSound;
    int _currentSample;
}

/*
 * Display modes
 */
#define NX_SOUNDVIEW_MINMAX 0
#define NX_SOUNDVIEW_WAVE 1

/*
 * OBSOLETE display modes - use the NX ones above.
 */
#define SK_DISPLAY_MINMAX 0
#define SK_DISPLAY_WAVE 1

+ (void)initialize;
- (id)initWithFrame:(NSRect)aRect;
- (void)dealloc;
- (void)encodeWithCoder:(NSCoder *)stream;
- (id)initWithCoder:(NSCoder *)stream;
- (BOOL)writeSelectionToPasteboard:(NSPasteboard *)pboard types:(NSArray *)types;
- (BOOL)readSelectionFromPasteboard:(NSPasteboard *)pboard;
- (id)validRequestorForSendType:(NSString *)sendType returnType:(NSString *)returnType;
- (void)pasteboard:(NSPasteboard *)sender provideData:(NSString *)type;
- (Sound *)sound;
- (void)setSound:(Sound *)aSound; // Should be BOOL; affects NSButton
- (BOOL)setReductionFactor:(float)reductionFactor;
- (float)reductionFactor;
- (void)setFrameSize:(NSSize)newSize;
- (id)delegate;
- (void)setDelegate:(id)anObject;
- (void)tellDelegate:(SEL)theMessage;
- (void)getSelection:(int *)firstSample size:(int *)sampleCount;
- (void)setSelection:(int)firstSample size:(int)sampleCount;
- (void)hideCursor;
- (void)showCursor;
- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;
- (void)setForegroundColor:(NSColor *)color;
- (NSColor *)foregroundColor;
- (int)displayMode;
- (void)setDisplayMode:(int)aMode;
- (BOOL)isContinuous;
- (void)setContinuous:(BOOL)aFlag;
- (BOOL)isEnabled;
- (void)setEnabled:(BOOL)aFlag;
- (BOOL)isEditable;
- (void)setEditable:(BOOL)aFlag;
- (BOOL)isPlayable;
- (BOOL)isBezeled;
- (void)setBezeled:(BOOL)aFlag;
- (BOOL)isAutoScale;
- (void)setAutoscale:(BOOL)aFlag;
- (BOOL)isOptimizedForSpeed;		/* 3.0 */
- (void)setOptimizedForSpeed:(BOOL)aFlag;	/* 3.0 */
- (void)scaleToFit;
- (void)sizeToFit;
- (BOOL)drawSamplesFrom:(int)startX to:(int)endX;	/* 3.0 */
- (void)drawRect:(NSRect)rects;
- (void)mouseDown:(NSEvent *)theEvent;
- (BOOL)acceptsFirstResponder;
- (BOOL)becomeFirstResponder; 
- (BOOL)resignFirstResponder; 
- (void)selectAll:(id)sender;
- (void)delete:(id)sender;
- (void)cut:(id)sender;
- (void)copy:(id)sender;
- (void)paste:(id)sender;
- (void)play:(id)sender;
- (void)record:(id)sender;
- (void)stop:(id)sender;
- (void)pause:(id)sender;
- (void)resume:(id)sender;
- (id)soundBeingProcessed;
- (void)willPlay:(id)sender;
- (void)didPlay:(id)sender;
- (void)willRecord:(id)sender;
- (void)didRecord:(id)sender;
- (void)hadError:(id)sender;
@end

@interface SoundViewDelegate : NSObject
- (void)soundDidChange:(id)sender;
- (void)selectionDidChange:(id)sender;
- (void)willRecord:(id)sender;
- (void)didRecord:(id)sender;
- (void)willPlay:(id)sender;
- (void)didPlay:(id)sender;
- (void)hadError:(id)sender;
- (void)willFree:(id)sender;
@end

