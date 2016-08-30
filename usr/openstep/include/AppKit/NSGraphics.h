#ident "@(#) NSGraphics.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSGraphics_h_
#define _NSGraphics_h_

#import <Foundation/Foundation.h> 
#import <DPS/dpsclient.h>

@class NSColor <NSCopying, NSCoding>;

/* Predefined colorspace names.
*/
extern NSString *NSCalibratedWhiteColorSpace;	/* 1.0 == white */
extern NSString *NSCalibratedBlackColorSpace;	/* 1.0 == black */
extern NSString *NSCalibratedRGBColorSpace;
extern NSString *NSDeviceWhiteColorSpace;	/* 1.0 == white */
extern NSString *NSDeviceBlackColorSpace;	/* 1.0 == black */
extern NSString *NSDeviceRGBColorSpace;
extern NSString *NSDeviceCMYKColorSpace;
extern NSString *NSNamedColorSpace;		/* Used for "catalog" colors */
extern NSString *NSCustomColorSpace;		/* Used to indicate a custom gstate in images */


/* NSWindowDepth defines the values used in setting window depth limits. 
  "0" indicates default depth. Window depths should not be made persistent 
  as they will not be the same across systems. Use the functions 
  NSBPSFromDepth(), NSColorSpaceFromDepth(), NSBitsPerPixelFromDepth(), and 
  NSPlanarFromDepth() to extract info from an NSWindowDepth. Use NSBestDepth()
  to compute window depths. NSBestDepth() will try to accomodate all the 
  parameters (match or better); if there are multiple matches, it gives the 
  closest, with matching colorSpace first, then bps, then planar, then bpp. 
  bpp is "bits per pixel"; 0 indicates default (same as the number of bits 
  per plane, either bps or bps * NSNumberOfColorComponents()); other values 
  maybe used as hints to provide backing stores of different configuration; 
  for instance, 8 bit color. exactMatch is optional and indicates whether 
  all the parameters matched exactly.
*/


#ifdef __cplusplus
extern "C" {
#endif

typedef int NSWindowDepth;
extern NSWindowDepth NSBestDepth (NSString *colorSpace, int bps, int bpp, BOOL planar, BOOL *exactMatch);
extern BOOL NSPlanarFromDepth (NSWindowDepth depth);
extern NSString *NSColorSpaceFromDepth (NSWindowDepth depth);
extern int NSBitsPerSampleFromDepth (NSWindowDepth depth);
extern int NSBitsPerPixelFromDepth (NSWindowDepth depth);
extern int NSNumberOfColorComponents (NSString *colorSpaceName);
extern const NSWindowDepth *NSAvailableWindowDepths (void); /* 0 terminated */


/* Standard gray values for the 2-bit deep grayscale colorspace.
*/
extern const float NSWhite;
extern const float NSLightGray;
extern const float NSDarkGray;
extern const float NSBlack;


/* Keys for deviceDictionary dictionaries.
*/
extern NSString *NSDeviceResolution;		/* NSValue containing NSSize, basically dpi */
extern NSString *NSDeviceColorSpaceName;	/* NSString */
extern NSString *NSDeviceBitsPerSample;		/* NSValue containing int */
extern NSString *NSDeviceIsScreen;		/* "YES" or not there */
extern NSString *NSDeviceIsPrinter;		/* "YES" or not there */
extern NSString *NSDeviceSize;			/* NSValue containing NSSize */


/* Graphics functions
*/
extern void NSRectFill(NSRect aRect);
extern void NSRectFillList(const NSRect *rects, int count);
extern void NSRectFillListWithGrays(const NSRect *rects, const float *grays, int num);
extern void NSFrameRect(NSRect aRect);
extern void NSFrameRectWithWidth(NSRect aRect, float frameWidth);
extern void NSRectClip(NSRect aRect);
extern void NSRectClipList(const NSRect *rects, int count);
extern NSRect NSDrawTiledRects(NSRect boundsRect, NSRect clipRect, const NSRectEdge *sides, const float *grays, int count);
extern void NSDrawGrayBezel(NSRect aRect, NSRect clipRect);
extern void NSDrawGroove(NSRect aRect, NSRect clipRect);
extern void NSDrawWhiteBezel(NSRect aRect, NSRect clipRect);
extern void NSDrawButton(NSRect aRect, NSRect clipRect);
extern void NSEraseRect(NSRect aRect);
extern NSColor *NSReadPixel(NSPoint passedPoint);
extern void NSDrawBitmap(NSRect rect, int width, int height, int bps, int spp, int bpp, int bpr, BOOL isPlanar, BOOL hasAlpha, NSString *colorSpaceName, const unsigned char *const data[5]);
extern void NSCopyBitmapFromGState(int srcGState, NSRect srcRect, NSRect destRect);
extern void NSCopyBits(int srcGState, NSRect srcRect, NSPoint destPoint);
extern void NSHighlightRect(NSRect aRect);
extern void NSBeep(void);


#ifndef STRICT_OPENSTEP

extern void NSConvertWindowNumberToGlobal(int winNum, unsigned int *globalNum);
extern void NSConvertGlobalToWindowNumber(int globalNum, unsigned int *winNum);

#endif
#ifdef __cplusplus
}
#endif

#endif // _NSGraphics_h_
