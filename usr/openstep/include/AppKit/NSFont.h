#ident "@(#) NSFont.h, Rev 1.11, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import <Foundation/Foundation.h>
#import "NSFontManager.h"

extern const float *NSFontIdentityMatrix;
extern const float *NSFontFlippedMatrix;

typedef unsigned int NSGlyph;

@interface NSFont : NSObject <NSCopying, NSCoding> {
@private
    NSString *_name;
    float _size;
    int _style;
    float *_matrix;
    int _fontNum;
    struct _NSFaceInfo *_faceInfo;
    id _otherFont;
    struct __fFlags {
      /* the following instance variables are no longer part of the API */
	unsigned int usedByWS:1;
	unsigned int usedByPrinter:1;
	unsigned int isScreenFont:1;
	unsigned int _systemFontType:4;
	unsigned int _flippedUsedByWS:1;
	unsigned int _flippedUsedByPrinter:1;
	unsigned int _RESERVED:4;
	unsigned int _matrixIsIdentity:1;
	unsigned int _matrixIsFlipped:1;
	unsigned int _hasStyle:1;
    } _fFlags;
    unsigned short _reservedFont2;
    int _flippedFontNum;
}

+ (NSFont *)fontWithName:(NSString *)fontName size:(float)fontSize;
+ (NSFont *)fontWithName:(NSString *)fontName matrix:(const float *)fontMatrix;
+ (void)useFont:(NSString *)fontName;

+ (NSFont *)userFontOfSize:(float)fontSize;
+ (NSFont *)userFixedPitchFontOfSize:(float)fontSize;
+ (NSFont *)systemFontOfSize:(float)fontSize;
+ (NSFont *)boldSystemFontOfSize:(float)fontSize;
+ (void)setUserFont:(NSFont *)aFont;
+ (void)setUserFixedPitchFont:(NSFont *)aFont;

- (float)pointSize;
- (NSString *)fontName;
- (NSString *)familyName;
- (NSString *)displayName;

- (const float *)matrix;
- (void)set;
- (float)widthOfString:(NSString *)string;
- (NSFont *)screenFont;
- (NSFont *)printerFont;

- (BOOL)isBaseFont;

/* The "widths" method returns a pointer to an array of 256 widths.  They are unscaled but are pre-divided by 1000.  All other methods return scaled numbers.  If the font was created with a matrix, the matrix is applied automatically; otherwise the coordinates are multiplied by size.
*/

- (float *)widths;
- (NSRect)boundingRectForFont;
- (NSRect)boundingRectForGlyph:(NSGlyph)aGlyph;
- (NSSize)advancementForGlyph:(NSGlyph)ag;
- (NSPoint)positionOfGlyph:(NSGlyph)curGlyph precededByGlyph:(NSGlyph)prevGlyph isNominal:(BOOL *)nominal;
- (NSDictionary *)afmDictionary;
- (NSString *)afmFileContents;
- (BOOL)glyphIsEncoded:(NSGlyph)aGlyph;

/*
 * Added because this information is directly available and there's no
 * easy way to find it.
*/
- (BOOL)isFixedPitch;

- (float) underlinePosition;
- (float) underlineThickness;
- (float) italicAngle;
- (float) capHeight;
- (float) xHeight;
- (float) ascender;
- (float) descender;
- (NSString *) encodingScheme;
- (NSGlyph) glyphWithName:(NSString *)aName;

@end

/* These are the strings that are available in the "afmDictionary".  For other things, use "afmFileContents".  The floating point values (e.g., ascender, cap height) can be converted to floating point via NSString's "floatValue" method.
*/
extern NSString *NSAFMFamilyName;
extern NSString *NSAFMFontName;
extern NSString *NSAFMFormatVersion;
extern NSString *NSAFMFullName;
extern NSString *NSAFMNotice;
extern NSString *NSAFMVersion;
extern NSString *NSAFMWeight;
extern NSString *NSAFMEncodingScheme;
extern NSString *NSAFMCharacterSet;

extern NSString *NSAFMCapHeight;
extern NSString *NSAFMXHeight;
extern NSString *NSAFMAscender;
extern NSString *NSAFMDescender;
extern NSString *NSAFMUnderlinePosition;
extern NSString *NSAFMUnderlineThickness;
extern NSString *NSAFMItalicAngle;
extern NSString *NSAFMMappingScheme;
