#ident "@(#) NSScanner.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Simple scanning on strings


#import <Foundation/NSString.h>
#import <Foundation/NSCharacterSet.h>
@class NSDictionary <NSCopying, NSMutableCopying, NSCoding>;

/* Abstract class for scanning strings. 
*/
@interface NSScanner : NSObject <NSCopying>

- (NSString *)string;
- (unsigned)scanLocation;
- (void)setScanLocation:(unsigned)pos;
- (void)setCharactersToBeSkipped:(NSCharacterSet *)set;	/* whitespaceAndNewlineCharacterSet by default */
- (void)setCaseSensitive:(BOOL)flag;			/* NO by default */
- (void)setLocale:(NSDictionary *)dict;			/* nil by default */

@end

@interface NSScanner (NSExtendedScanner)

- (NSCharacterSet *)charactersToBeSkipped;
- (BOOL)caseSensitive;
- (NSDictionary *)locale;

/* In all these methods, the ref-return (NSString **, int *, etc) is optional; you can pass in NULL if you don't care to get it back.
*/
- (BOOL)scanInt:(int *)value;
- (BOOL)scanHexInt:(unsigned int *)result;
- (BOOL)scanLongLong:(long long *)value;
- (BOOL)scanFloat:(float *)value;
- (BOOL)scanDouble:(double *)value;
- (BOOL)scanString:(NSString *)string intoString:(NSString **)value;
- (BOOL)scanCharactersFromSet:(NSCharacterSet *)set intoString:(NSString **)value;

/* If the next two don't find the desired string or characters, they parse to the end and return YES. They will return NO only if the no characters were parsed.
*/
- (BOOL)scanUpToString:(NSString *)string intoString:(NSString **)value;
- (BOOL)scanUpToCharactersFromSet:(NSCharacterSet *)set intoString:(NSString **)value;

/* Returns YES if only characters left are those in the charactersToBeSkipped set.
*/
- (BOOL)isAtEnd;

/* Creating scanners.
*/
- (id)initWithString:(NSString *)string;
+ (id)scannerWithString:(NSString *)string;
+ (id)localizedScannerWithString:(NSString *)string; /* Calls initWithString and sets locale to user's default */

@end


