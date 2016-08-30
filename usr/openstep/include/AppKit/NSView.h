#ident "@(#) NSView.h, Rev 1.20, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSView_h_
#define _NSView_h_

//
// System includes
//

#import <time.h>
 
//
// OpenStep includes
//

#import <Foundation/Foundation.h>

#import <AppKit/NSWindow.h>
#import <AppKit/NSScreen.h>

//
// forward declarations
//

@class NSFocusState;
@class NSCursor <NSCoding>;
@class NSEvent <NSCopying, NSCoding>;
@class NSClipView ;
@class NSScrollView ;

//
// enums and typedefs
//

enum {
    NSViewNotSizable                    =  0,
    NSViewMinXMargin                    =  1,
    NSViewWidthSizable                  =  2,
    NSViewMaxXMargin                    =  4,
    NSViewMinYMargin                    =  8,
    NSViewHeightSizable                 = 16,
    NSViewMaxYMargin                    = 32
};

typedef enum _NSBorderType {
    NSNoBorder                          = 0,
    NSLineBorder                        = 1,
    NSBezelBorder                       = 2,
    NSGrooveBorder                      = 3
} NSBorderType;

typedef int NSTrackingRectTag;

//
// global vars
//

// notifications

extern NSString *NSViewFrameDidChangeNotification;
extern NSString *NSViewFocusDidChangeNotification;
extern NSString *NSViewBoundsDidChangeNotification;

//
// interfaces
//

@interface NSView : NSResponder
{
    @protected
    NSRect              _frame;
    NSRect              _bounds;
    id                  _superview;
    NSMutableArray      *_subviews;
    id                  _window;
    int                 _gState;
    id                  _frameMatrix;
    id                  _drawMatrix;
    NSMutableSet        *_dragTypes;
    NSRect              *_errorOffsets;
    @public
    struct __vFlags {
        unsigned int        rotatedFromBase:1;
        unsigned int        rotatedOrScaledFromBase:1;
        unsigned int        autosizing:6;
        unsigned int        autoresizeSubviews:1;
        unsigned int        wantsGState:1;
        unsigned int        needsDisplay:1;
        unsigned int        validGState:1;
        unsigned int        newGState:1;
        unsigned int        noVerticalAutosizing:1;
        unsigned int        frameChangeNotesSuspended:1;
        unsigned int        needsFrameChangeNote:1;
	unsigned int        needsBoundsChangeNote:1;
	unsigned int        boundsChangeNotesSuspended:1;
	unsigned int        specialArchiving:1;
	unsigned int        RESERVED:13;
    } _vFlags;
}


//-----------------------------------------------------------------
// Initializing NSView Objects
//-----------------------------------------------------------------

- (id)initWithFrame:(NSRect)frameRect;

//-----------------------------------------------------------------
// Managing the NSView Hierarchy
//-----------------------------------------------------------------

- (void)addSubview:(NSView *)aView;

- (void)addSubview:(NSView *)aView
        positioned:(NSWindowOrderingMode)place
        relativeTo:(NSView *)otherView;

- (NSView *)ancestorSharedWithView:(NSView *)aView;

- (BOOL)isDescendantOf:(NSView *)aView;

- (NSView *)opaqueAncestor;

- (void)removeFromSuperview;

- (void)replaceSubview:(NSView *)oldView
                  with:(NSView *)newView;

- (void)sortSubviewsUsingFunction:(int (*)(id, id, void *))compare
                          context:(void *)context;

- (NSArray *)subviews;

- (NSView *)superview;

- (NSWindow *)window;

- (void)viewWillMoveToWindow:(NSWindow *)newWindow;

- (void)viewWillMoveToSuperview:(NSView *)newSuperview;

//-----------------------------------------------------------------
// Modifying the Frame Rectangle
//-----------------------------------------------------------------

- (float)frameRotation;

- (NSRect)frame;

- (void)setFrame:(NSRect)frameRect;

- (void)setFrameOrigin:(NSPoint)newOrigin;

- (void)setFrameRotation:(float)angle;

- (void)setFrameSize:(NSSize)newSize;

//-----------------------------------------------------------------
// Modifying the Coordinate System
//-----------------------------------------------------------------

- (void)rotateByAngle:(float)angle;

- (float)boundsRotation;

- (NSRect)bounds;

- (BOOL)isFlipped;

- (BOOL)isRotatedFromBase;

- (BOOL)isRotatedOrScaledFromBase;

- (void)scaleUnitSquareToSize:(NSSize)newUnitSize;

- (void)setBounds:(NSRect)aRect;

- (void)setBoundsOrigin:(NSPoint)newOrigin;

- (void)setBoundsRotation:(float)angle;

- (void)setBoundsSize:(NSSize)newSize;

- (void)translateOriginToPoint:(NSPoint)translation;

//-----------------------------------------------------------------
// Converting Coordinates
//-----------------------------------------------------------------

- (NSRect)centerScanRect:(NSRect)aRect;

- (NSPoint)convertPoint:(NSPoint)aPoint
               fromView:(NSView *)aView;

- (NSPoint)convertPoint:(NSPoint)aPoint
                 toView:(NSView *)aView;

- (NSRect)convertRect:(NSRect)aRect
             fromView:(NSView *)aView;

- (NSRect)convertRect:(NSRect)aRect
               toView:(NSView *)aView;

- (NSSize)convertSize:(NSSize)aSize
             fromView:(NSView *)aView;

- (NSSize)convertSize:(NSSize)aSize
               toView:(NSView *)aView;

//-----------------------------------------------------------------
// Notifying Ancestor Views
//-----------------------------------------------------------------

- (BOOL)postsFrameChangedNotifications;

- (void)setPostsFrameChangedNotifications:(BOOL)flag;

- (BOOL)postsBoundsChangedNotifications;

- (void)setPostsBoundsChangedNotifications:(BOOL)flag;


//-----------------------------------------------------------------
// Resizing Subviews
//-----------------------------------------------------------------

- (void)resizeSubviewsWithOldSize:(NSSize)oldSize;

- (void)setAutoresizesSubviews:(BOOL)flag;

- (BOOL)autoresizesSubviews;

- (void)setAutoresizingMask:(unsigned int)mask;

- (unsigned int)autoresizingMask;

- (void)resizeWithOldSuperviewSize:(NSSize)oldSize;

//-----------------------------------------------------------------
// Graphics State Objects
//-----------------------------------------------------------------

- (void)allocateGState;

- (void)releaseGState;

- (int)gState;

- (void)renewGState;

- (void)setUpGState;

//-----------------------------------------------------------------
// Focusing
//-----------------------------------------------------------------

+ (NSView *)focusView;

- (void)lockFocus;

- (void)unlockFocus;

//-----------------------------------------------------------------
// Displaying
//-----------------------------------------------------------------

- (BOOL)canDraw;

- (void)display;

- (void)displayIfNeeded;

- (void)displayIfNeededIgnoringOpacity;

- (void)displayRect:(NSRect)rect;

- (void)displayRectIgnoringOpacity:(NSRect)rect;

- (void)displayIfNeededInRect:(NSRect)aRect;

- (void)displayIfNeededInRectIgnoringOpacity:(NSRect)aRect;

- (void)drawRect:(NSRect)rect;

- (NSRect)visibleRect;

- (BOOL)isOpaque;

- (BOOL)needsDisplay;

- (void)setNeedsDisplay:(BOOL)flag;

- (void)setNeedsDisplayInRect:(NSRect)invalidRect;

- (BOOL)shouldDrawColor;

//-----------------------------------------------------------------
// Scrolling
//-----------------------------------------------------------------

- (NSRect)adjustScroll:(NSRect)newVisible;

- (BOOL)autoscroll:(NSEvent *)theEvent;

- (void)scrollPoint:(NSPoint)aPoint;

- (void)scrollRect:(NSRect)aRect 
                by:(NSSize)delta;

- (BOOL)scrollRectToVisible:(NSRect)aRect;

- (NSScrollView *)enclosingScrollView;

//-----------------------------------------------------------------
// Managing the Cursor
//-----------------------------------------------------------------

- (void)addCursorRect:(NSRect)aRect
               cursor:(NSCursor *)anObj;

- (void)discardCursorRects;

- (void)removeCursorRect:(NSRect)aRect
                  cursor:(NSCursor *)anObj;

- (void)resetCursorRects;

//-----------------------------------------------------------------
// Assign a tag
//-----------------------------------------------------------------

- (id)viewWithTag:(int)aTag;

- (int)tag;

//-----------------------------------------------------------------
// Aiding Event Handling
//-----------------------------------------------------------------

- (BOOL)acceptsFirstMouse:(NSEvent *)theEvent;

- (NSView *)hitTest:(NSPoint)aPoint;

- (BOOL)mouse:(NSPoint)aPoint
       inRect:(NSRect)aRect;

- (BOOL)performKeyEquivalent:(NSEvent *)theEvent;

- (void)removeTrackingRect:(NSTrackingRectTag)tag;

- (BOOL)shouldDelayWindowOrderingForEvent:(NSEvent *)theEvent;

- (NSTrackingRectTag)addTrackingRect:(NSRect)aRect
                               owner:(id)anObject
                            userData:(void *)data
                        assumeInside:(BOOL)flag;

@end

//-----------------------------------------------------------------
// Dragging
//-----------------------------------------------------------------

@interface NSView(NSDrag)

- (BOOL)dragFile:(NSString *)   filename
        fromRect:(NSRect)       rect
       slideBack:(BOOL)         aFlag
           event:(NSEvent *)    event;

- (void)dragImage:(NSImage *)           anImage
               at:(NSPoint)             viewLocation
           offset:(NSSize)              initialOffset
            event:(NSEvent *)           event
       pasteboard:(NSPasteboard *)      pboard
           source:(id)                  sourceObj
        slideBack:(BOOL)                slideFlag;

- (void)registerForDraggedTypes:(NSArray *)newTypes;

- (void)unregisterDraggedTypes;

@end

//-----------------------------------------------------------------
// Printing
//-----------------------------------------------------------------

@interface NSView(NSPrinting)

- (NSData *)dataWithEPSInsideRect:(NSRect)rect;

#ifndef STRICT_OPENSTEP
#ifdef FAX_SUPPORT
- (void)fax:(id)sender;
#endif
#endif

- (void)print:(id)sender;

- (void)writeEPSInsideRect:(NSRect)rect
              toPasteboard:(NSPasteboard *)pasteboard;

//-----------------------------------------------------------------
// Pagination
//-----------------------------------------------------------------

- (void)adjustPageHeightNew:(float *)   newBottom
                        top:(float)     oldTop
                     bottom:(float)     oldBottom
                      limit:(float)     bottomLimit;

- (void)adjustPageWidthNew:(float *)    newRight
                      left:(float)      oldLeft
                     right:(float)      oldRight
                     limit:(float)      rightLimit;

- (float)heightAdjustLimit;

- (BOOL)knowsPagesFirst:(int *)firstPageNum
                   last:(int *)lastPageNum;

- (NSPoint)locationOfPrintRect:(NSRect)aRect;

- (NSRect)rectForPage:(int)page;

- (float)widthAdjustLimit;

//-----------------------------------------------------------------
// Write Conforming PostScript
//-----------------------------------------------------------------

- (void)addToPageSetup;

- (void)beginPage:(int)         ordinalNum
            label:(NSString *)  aString
             bBox:(NSRect)      pageRect
            fonts:(NSString *)  fontNames;

- (void)beginPageSetupRect:(NSRect)     aRect
                 placement:(NSPoint)    location;

- (void)beginPrologueBBox:(NSRect)      boundingBox
             creationDate:(NSString *)  dateCreated
                createdBy:(NSString *)  anApplication
                    fonts:(NSString *)  fontNames
                  forWhom:(NSString *)  user
                    pages:(int)         numPages
                    title:(NSString *)  aTitle;

- (void)beginSetup;

- (void)beginTrailer;

- (void)drawPageBorderWithSize:(NSSize)borderSize;

- (void)drawSheetBorderWithSize:(NSSize)borderSize;

- (void)endHeaderComments;

- (void)endPrologue;

- (void)endSetup;

- (void)endPageSetup;

- (void)endPage;

- (void)endTrailer;

@end

#endif  _NSView_h_
