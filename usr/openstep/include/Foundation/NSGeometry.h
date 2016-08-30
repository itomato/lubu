#ident "@(#) NSGeometry.h, Rev 1.8, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Basic definitions for 2-D Geometry

#import <Foundation/NSString.h>
#import <Foundation/NSValue.h>
#import <Foundation/NSCoder.h>

#ifdef __cplusplus
extern "C" {
#endif

/***************	Basic definitions		***********/

typedef struct _NSPoint {
    float x;
    float y;
} NSPoint;

typedef struct _NSSize {
    float width;	// should never be negative
    float height;	// should never be negative
} NSSize;

typedef struct _NSRect {
    NSPoint origin;
    NSSize size;
} NSRect;

/* The sides of a rectangle */
typedef enum _NSRectEdge { 
    NSMinXEdge = 0,
    NSMinYEdge = 1,
    NSMaxXEdge = 2,
    NSMaxYEdge = 3	
} NSRectEdge;

extern const NSPoint NSZeroPoint;
extern const NSSize NSZeroSize;
extern const NSRect NSZeroRect;

/***************	Creation		***********/

static inline NSPoint NSMakePoint(float x, float y) {
    NSPoint p;
    p.x = x;  p.y = y;
    return p;
}

static inline NSSize NSMakeSize(float w, float h) {
    NSSize s;
    s.width = w;  s.height = h;
    return s;
}

static inline NSRect NSMakeRect(float x, float y, float w, float h) {
    NSRect r;
    r.origin.x = x;  r.origin.y = y;  r.size.width = w;  r.size.height = h;
    return r;
}

/***************	Geometric operations		***********/

/* Note that these functions assume width and height are never negative. */

static inline float NSMaxX(NSRect aRect) {
    return (aRect.origin.x + aRect.size.width);
}
static inline float NSMaxY(NSRect aRect) {
    return (aRect.origin.y + aRect.size.height);
}
static inline float NSMidX(NSRect aRect) {
    return (aRect.origin.x + (aRect.size.width / 2.0));
}
static inline float NSMidY(NSRect aRect) {
    return (aRect.origin.y + (aRect.size.height / 2.0));
}
static inline float NSMinX(NSRect aRect) {
    return (aRect.origin.x);
}
static inline float NSMinY(NSRect aRect) {
    return (aRect.origin.y);
}
static inline float NSWidth(NSRect aRect) {
    return (aRect.size.width);
}
static inline float NSHeight(NSRect aRect) {
    return (aRect.size.height);
}

extern NSRect NSUnionRect(NSRect aRect, NSRect bRect);
extern NSRect NSIntersectionRect(NSRect aRect, NSRect bRect);
extern NSRect NSInsetRect(NSRect aRect, float dX, float dY);
extern NSRect NSOffsetRect(NSRect aRect, float dX, float dY);
extern void NSDivideRect(NSRect inRect, NSRect *slice, NSRect *remainder, float amount, NSRectEdge edge);
extern NSRect NSIntegralRect(NSRect aRect);
extern BOOL NSEqualPoints(NSPoint aPoint, NSPoint bPoint);
extern BOOL NSEqualSizes(NSSize aSize, NSSize bSize);
extern BOOL NSEqualRects(NSRect aRect, NSRect bRect);
extern BOOL NSIsEmptyRect(NSRect aRect);
extern BOOL NSPointInRect(NSPoint aPoint, NSRect aRect);
extern BOOL NSMouseInRect(NSPoint aPoint, NSRect aRect, BOOL flipped);
extern BOOL NSContainsRect(NSRect a, NSRect b);
BOOL NSIntersectsRect(NSRect aRect, NSRect bRect);

extern NSString *NSStringFromPoint(NSPoint aPoint);
extern NSString *NSStringFromSize(NSSize aSize);
extern NSString *NSStringFromRect(NSRect aRect);

extern NSPoint NSPointFromString(NSString *aString);
extern NSSize NSSizeFromString(NSString *aString);
extern NSRect NSRectFromString(NSString *aString);

/***************	Geometry as NSValues		***********/

@interface NSValue (NSValueGeometryExtensions)

+ (NSValue *)valueWithPoint:(NSPoint)point;
+ (NSValue *)valueWithSize:(NSSize)size;
+ (NSValue *)valueWithRect:(NSRect)rect;

- (NSPoint)pointValue;
- (NSSize)sizeValue;
- (NSRect)rectValue;

@end

/***************	Archiving geometry		***********/

@interface NSCoder(NSGeometryCoding)

- (void)encodePoint:(NSPoint)point;
- (NSPoint)decodePoint;

- (void)encodeSize:(NSSize)size;
- (NSSize)decodeSize;

- (void)encodeRect:(NSRect)rect;
- (NSRect)decodeRect;

@end

#ifdef __cplusplus
}
#endif
