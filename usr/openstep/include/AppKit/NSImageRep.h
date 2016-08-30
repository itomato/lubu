#ident "@(#) NSImageRep.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ident "@(#) NSImageRep.h, Rev 1.7, 97/03/17"

#ifndef _NSImageRep_h_
#define _NSImageRep_h_

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
#import <AppKit/NSGraphics.h>

@class NSPasteboard;

/* NSImageRepMatchesDevice indicates the value is variable, depending
 * on the output device. It can be passed in (or received back) as the
 * value of bitsPerSample, pixelsWide, and pixelsHigh.
 */
enum {
    NSImageRepMatchesDevice = 0
};

@interface NSImageRep : NSObject <NSCopying, NSCoding> {
    struct __repFlags {
	unsigned int hasAlpha:1;
	unsigned int isOpaque:1;
        unsigned int cacheParamsComputed:1;
        unsigned int cacheAlphaComputed:1;
        unsigned int reserved:4;
        unsigned int bitsPerSample:8;
	unsigned int gsaved:16;
    } _repFlags;
    NSString *_colorSpaceName;
    NSSize _size;
    int _pixelsWide;
    int _pixelsHigh;
}

//-----------------------------------------------------------------
// Creating an NSImageRep
//-----------------------------------------------------------------
/* Convenience methods: Checks to see if the provided file or pasteboard
 * types can be understood by a registered imagerep class after filtering;
 * if so, calls imageRepsWithData: or imageRepWithData:. If sent to a
 * subclass, does this just for the types understood by that subclass.
 */
+ (id)imageRepWithContentsOfFile:(NSString *)filename;

+ (NSArray *)imageRepsWithContentsOfFile:(NSString *)filename;

+ (id)imageRepWithPasteboard:(NSPasteboard *)pasteboard;

+ (NSArray *)imageRepsWithPasteboard:(NSPasteboard *)pasteboard;

//-----------------------------------------------------------------
// Checking Data Types
//-----------------------------------------------------------------
/* Should be overridden by subclassers to load an unfiltered image. 
 */
+ (BOOL)canInitWithData:(NSData *)data;

/* Convenience method: Checks to see if any of the types on the pasteboard
 * can be understood by a registered imagerep class after filtering or if
 * the pasteboard contains a filename that can be understood by a registered
 * imagerep class after filtering. If sent to a subclass, does this for just
 * the types understood by the subclass.
 */
+ (BOOL)canInitWithPasteboard:(NSPasteboard *)pasteboard;

/* These expand the unfiltered lists returned by imageUnfilteredFileTypes
 * and imageUnfilteredPasteboardTypes.
 */
+ (NSArray *)imageFileTypes;

+ (NSArray *)imagePasteboardTypes;

/* Implemented by subclassers to indicate what data types they can deal with.
 */
+ (NSArray *)imageUnfilteredFileTypes;

+ (NSArray *)imageUnfilteredPasteboardTypes;

//-----------------------------------------------------------------
// Setting the Size of the Image
//-----------------------------------------------------------------
/* Methods to return info about the image. NSImageRep provides storage
 * for all of these; however, it's illegal to set them in some subclasses.
 */
- (void)setSize:(NSSize)aSize;

- (NSSize)size;

//-----------------------------------------------------------------
// Specifying Information about the Representation
//-----------------------------------------------------------------
- (int)bitsPerSample;

- (NSString *)colorSpaceName;

- (BOOL)hasAlpha;

- (BOOL)isOpaque;

- (int)pixelsWide;

- (int)pixelsHigh;

- (void)setAlpha:(BOOL)flag;

- (void)setBitsPerSample:(int)anInt;

- (void)setColorSpaceName:(NSString *)string;

- (void)setOpaque:(BOOL)flag;

- (void)setPixelsHigh:(int)anInt;

- (void)setPixelsWide:(int)anInt;

//-----------------------------------------------------------------
// Drawing the Image
//-----------------------------------------------------------------
/* Drawing methods. drawAtPoint: and drawInRect: go through draw after
 * modifying the CTM.
 */
- (BOOL)draw;
- (BOOL)drawAtPoint:(NSPoint)point;
- (BOOL)drawInRect:(NSRect)rect;


//-----------------------------------------------------------------
// Managing NSImageRep Subclasses
//-----------------------------------------------------------------
/* Registry management: Subclasses which deal with file & pasteboard
 * types should register themselves (the +load method is a good place
 * for this). These classes should also implement imageUnfilteredFileTypes,
 * imageUnfilteredPasteboardTypes, initWithData:, canInitWithData:,
 * imageRepWithData:, and, if they have the ability to read multiple images
 * from a file, imageRepsWithData:. These last three should not do any
 * filtering; all filtering is automatic.
 */
+ (Class)imageRepClassForData:(NSData *)data;

+ (Class)imageRepClassForFileType:(NSString *)type;

+ (Class)imageRepClassForPasteboardType:(NSString *)type;

+ (void)registerImageRepClass:(Class)imageRepClass;

+ (NSArray *)registeredImageRepClasses;

+ (void)unregisterImageRepClass:(Class)imageRepClass;
	
@end

/* Notifications */
extern NSString *NSImageRepRegistryDidChangeNotification;

#endif _NSImageRep_h_
