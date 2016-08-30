#ident "@(#) NSCharacterSet.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import <Foundation/NSString.h>
@class NSData <NSCopying, NSMutableCopying, NSCoding>;
@class NSCharacterSet  <NSCopying, NSMutableCopying, NSCoding>;

enum {
    NSOpenStepUnicodeReservedBase = 0xF400
};

@interface NSCharacterSet : NSObject <NSCopying, NSMutableCopying, NSCoding>

/* Getting predefined sets */
+ (NSCharacterSet *)controlCharacterSet;
+ (NSCharacterSet *)whitespaceCharacterSet;
+ (NSCharacterSet *)whitespaceAndNewlineCharacterSet;
+ (NSCharacterSet *)decimalDigitCharacterSet;
+ (NSCharacterSet *)letterCharacterSet; // upper+lower+modifier+other+NSM+CM
+ (NSCharacterSet *)lowercaseLetterCharacterSet;
+ (NSCharacterSet *)uppercaseLetterCharacterSet;
+ (NSCharacterSet *)nonBaseCharacterSet; // == NSM+CM
+ (NSCharacterSet *)alphanumericCharacterSet; // all kinds of letters & digits
+ (NSCharacterSet *)decomposableCharacterSet; // precomposed things, EXCEPT HANGUL!
+ (NSCharacterSet *)illegalCharacterSet; // non-Unicodes
+ (NSCharacterSet *)punctuationCharacterSet;


/* Getting autoreleased instances */
+ (NSCharacterSet *)characterSetWithRange:(NSRange)aRange;
+ (NSCharacterSet *)characterSetWithCharactersInString:(NSString *)aString;
+ (NSCharacterSet *)characterSetWithBitmapRepresentation:(NSData *)data;

/* Other instance methods - only the first TWO must be implemented by all subclasses.  There is an abstract implementation of the inverted set.
*/
- (BOOL)characterIsMember:(unichar)aCharacter;
- (NSData *)bitmapRepresentation;
- (NSCharacterSet *)invertedSet;

@end

@interface NSMutableCharacterSet : NSCharacterSet <NSCopying, NSMutableCopying>

/* Mutable subclasses must implement ALL of these methods.
*/
- (void)addCharactersInRange:(NSRange)aRange;
- (void)removeCharactersInRange:(NSRange)aRange;
- (void)addCharactersInString:(NSString *)aString;
- (void)removeCharactersInString:(NSString *)aString;
- (void)formUnionWithCharacterSet:(NSCharacterSet *)otherSet;
- (void)formIntersectionWithCharacterSet:(NSCharacterSet *)otherSet;
- (void)invert;

@end

