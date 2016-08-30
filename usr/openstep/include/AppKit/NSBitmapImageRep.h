#ident "@(#) NSBitmapImageRep.h, Rev 1.3, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSImageRep.h"
#import "NSGraphics.h"

typedef enum _NSTIFFCompression {
    NSTIFFCompressionNone		= 1,
    NSTIFFCompressionCCITTFAX3		= 3,		/* 1 bps only */
    NSTIFFCompressionCCITTFAX4		= 4,		/* 1 bps only */
    NSTIFFCompressionLZW		= 5,
    NSTIFFCompressionJPEG		= 6,
    NSTIFFCompressionNEXT		= 32766,	/* Input only */
    NSTIFFCompressionPackBits		= 32773,
    NSTIFFCompressionOldJPEG		= 32865		/* Input only */
} NSTIFFCompression;


@interface NSBitmapImageRep : NSImageRep {
    struct __bitmapRepFlags {
        unsigned int bitsPerPixel:8;	
	unsigned int isPlanar:1;
	unsigned int explicitPlanes:1;
	unsigned int isUnpacked:1;
	unsigned int dataLoaded:1;
        unsigned int numColors:4;	/* Cache */
        unsigned int memory:2;
        unsigned int compressionFactor:14;
        unsigned int imageNumber:12;
	unsigned int compression:20;
    } _moreRepFlags;
    unsigned int _bytesPerRow;
    unsigned char *_data;
    NSData *_tiffData;
}

- (id)initWithFocusedViewRect:(NSRect)rect;

- (id)initWithBitmapDataPlanes:(unsigned char **)planes pixelsWide:(int)width pixelsHigh:(int)height bitsPerSample:(int)bps samplesPerPixel:(int)spp hasAlpha:(BOOL)alpha isPlanar:(BOOL)isPlanar colorSpaceName:(NSString *)colorSpaceName bytesPerRow:(int)rBytes bitsPerPixel:(int)pBits; 

+ (NSArray *)imageRepsWithData:(NSData *)tiffData;	/* TIFFs can contain multiple images */

+ (id)imageRepWithData:(NSData *)tiffData;	/* Convenience of initWithData: */
- (id)initWithData:(NSData *)tiffData;

- (unsigned char *)bitmapData;
- (void)getBitmapDataPlanes:(unsigned char **)data;
- (BOOL)isPlanar;
- (int)samplesPerPixel;
- (int)bitsPerPixel;
- (int)bytesPerRow;
- (int)bytesPerPlane;
- (int)numberOfPlanes;

- (void)getCompression:(NSTIFFCompression *)compression factor:(float *)factor;
- (void)setCompression:(NSTIFFCompression)compression factor:(float)factor;

- (NSData *)TIFFRepresentation;
- (NSData *)TIFFRepresentationUsingCompression:(NSTIFFCompression)comp factor:(float)factor;

+ (NSData *)TIFFRepresentationOfImageRepsInArray:(NSArray *)array;
+ (NSData *)TIFFRepresentationOfImageRepsInArray:(NSArray *)array usingCompression:(NSTIFFCompression)comp factor:(float)factor;

+ (void)getTIFFCompressionTypes:(const NSTIFFCompression **)list count:(int *)numTypes;
+ (NSString *)localizedNameForTIFFCompressionType:(NSTIFFCompression)compression;
- (BOOL)canBeCompressedUsing:(NSTIFFCompression)compression;

@end
