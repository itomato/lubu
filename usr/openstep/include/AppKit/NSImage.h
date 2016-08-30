#ident "@(#) NSImage.h, Rev 1.11, 97/03/17"
//
//	Copyright (C) 1994-1996 Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#ifndef _NSImage_h_
#define _NSImage_h_

/*****************
 * system includes
 *****************/

/*****************
 * X11/DPS includes
 *****************/

/*****************
 * Objc includes
 *****************/

/*****************
 * OpenStep Includes
 *****************/
#import <Foundation/NSObject.h>
#import <DPSClient/dpsOpenStep.h>
#import <AppKit/NSGraphics.h>
#import <AppKit/NSBitmapImageRep.h>

@class NSColor <NSCopying, NSCoding>;
@class NSImageRep <NSCopying, NSCoding>;
@class NSPasteboard;
@class NSArray <NSCopying, NSMutableCopying, NSCoding>;


@interface NSImage : NSObject <NSCopying, NSCoding> {
    NSString *_name;
    NSSize _size;
    struct __imageFlags {
	unsigned int scalable:1;
	unsigned int dataRetained:1;
	unsigned int uniqueWindow:1;
	unsigned int sizeWasExplicitlySet:1;
	unsigned int builtIn:1;
	unsigned int needsToExpand:1;
	unsigned int useEPSOnResolutionMismatch:1;
	unsigned int colorMatchPreferred:1;
	unsigned int multipleResolutionMatching:1;
	unsigned int subImage:1;
	unsigned int archiveByName:1;
	unsigned int unboundedCacheDepth:1;
	unsigned int flipped: 1;
	unsigned int reserved1:19;
    } _flags;
    void *_reps;
    NSColor *_color;
}

//-----------------------------------------------------------------
// Initializing a New NSImage Instance
//-----------------------------------------------------------------

- (id)initByReferencingFile:(NSString *)fileName;	/* When archived,
							 * saves fileName
							 */

- (id)initWithContentsOfFile:(NSString *)fileName;	/* When archived,
							 * saves contents
							 */

- (id)initWithData:(NSData *)data;			/* When archived,
							 * saves contents
							 */

- (id)initWithPasteboard:(NSPasteboard *)pasteboard;

- (id)initWithSize:(NSSize)aSize;

//-----------------------------------------------------------------
// Setting the Size of the Image
//-----------------------------------------------------------------

- (void)setSize:(NSSize)aSize;

- (NSSize)size;

//-----------------------------------------------------------------
// Referring to Images by Name
//-----------------------------------------------------------------
+ (id)imageNamed:(NSString *)name;	/* If this finds & creates the image,
					 * only name is saved when archived
					 */

- (BOOL)setName:(NSString *)string;

- (NSString *)name;

//-----------------------------------------------------------------
// Specifying the Image
//-----------------------------------------------------------------

- (void)addRepresentations:(NSArray *)imageReps;

- (void)addRepresentation:(NSImageRep *)imageRep;

- (void)lockFocus;

- (void)lockFocusOnRepresentation:(NSImageRep *)imageRepresentation;

- (void)unlockFocus;

//-----------------------------------------------------------------
// Using the Image
//-----------------------------------------------------------------
- (void)compositeToPoint:(NSPoint)point
	       operation:(NSCompositingOperation)op;

- (void)compositeToPoint:(NSPoint)point
		fromRect:(NSRect)rect
	       operation:(NSCompositingOperation)op;

- (void)dissolveToPoint:(NSPoint)point
	       fraction:(float)aFloat;

- (void)dissolveToPoint:(NSPoint)point
	       fromRect:(NSRect)rect
	       fraction:(float)aFloat;

//-----------------------------------------------------------------
// Choosing Which Image Representation to Use
//-----------------------------------------------------------------
- (void)setPrefersColorMatch:(BOOL)flag;

- (BOOL)prefersColorMatch;

- (void)setUsesEPSOnResolutionMismatch:(BOOL)flag;

- (BOOL)usesEPSOnResolutionMismatch;

- (void)setMatchesOnMultipleResolution:(BOOL)flag;

- (BOOL)matchesOnMultipleResolution;

//-----------------------------------------------------------------
// Getting the Representation
//-----------------------------------------------------------------
- (NSImageRep *)bestRepresentationForDevice:(NSDictionary *)deviceDescription;

- (NSArray *)representations;

- (void)removeRepresentation:(NSImageRep *)imageRep;

//-----------------------------------------------------------------
// Determining How the Image is Stored
//-----------------------------------------------------------------
- (void)setCachedSeparately:(BOOL)flag;

- (BOOL)isCachedSeparately;

- (void)setDataRetained:(BOOL)flag;

- (BOOL)isDataRetained;

- (void)setCacheDepthMatchesImageDepth:(BOOL)flag;

- (BOOL)cacheDepthMatchesImageDepth;

//-----------------------------------------------------------------
// Determining How the Image is Drawn
//-----------------------------------------------------------------
- (BOOL)isValid;

- (void)setScalesWhenResized:(BOOL)flag;

- (BOOL)scalesWhenResized;

- (void)setBackgroundColor:(NSColor *)aColor;

- (NSColor *)backgroundColor;

- (BOOL)drawRepresentation:(NSImageRep *)imageRep
		    inRect:(NSRect)rect;

- (void)recache;

//-----------------------------------------------------------------
// Assigning a Delegate
//-----------------------------------------------------------------
- (void)setDelegate:(id)anObject;

- (id)delegate;

//-----------------------------------------------------------------
// Producing TIFF Data for the Image
//-----------------------------------------------------------------
- (NSData *)TIFFRepresentation;

- (NSData *)TIFFRepresentationUsingCompression:(NSTIFFCompression)comp
					factor:(float)aFloat;

//-----------------------------------------------------------------
// Managing NSImageRep Subclasses
//-----------------------------------------------------------------
/* These return union of all the types registered with NSImageRep.
*/
+ (NSArray *)imageUnfilteredFileTypes;

+ (NSArray *)imageUnfilteredPasteboardTypes;

//-----------------------------------------------------------------
// Testing Image Data Sources
//-----------------------------------------------------------------
+ (BOOL)canInitWithPasteboard:(NSPasteboard *)pasteboard;

- (void)setFlipped:(BOOL)flag;
- (BOOL)isFlipped;


/* These return union of all the types registered with NSImageRep.
*/
+ (NSArray *)imageFileTypes;

+ (NSArray *)imagePasteboardTypes;

@end

@interface NSObject(NSImageDelegate)
//-----------------------------------------------------------------
// Testing Image Data Sources
//-----------------------------------------------------------------
- (NSImage *)imageDidNotDraw:(id)sender inRect:(NSRect)aRect;

@end

@interface NSBundle(NSBundleImageExtension)
- (NSString *)pathForImageResource:(NSString *)name;	/* May return nil if
							 * no file found
							 */
@end

#endif _NSImage_h_
