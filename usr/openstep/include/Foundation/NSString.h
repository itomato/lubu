#ident "@(#) NSString.h, Rev 1.22, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

/*
NSString and NSMutableString are two abstract classes for string 
manipulation.  NSString provides methods for read-only access, while 
NSMutableString allows for changing the contents of the string. These 
classes provide factory methods which will return autoreleased instances 
of unspecified subclasses of strings.

Canonically, the contents of string objects are Unicode(tm) characters 
(defined by the unichar data type).  This means that the default set of 
methods where the word "character," "range," and "length" are used refer 
to strings of unichars and ranges and lengths of such strings. This is an 
important point, as the conversion between unichars and other character 
encodings is not one-to-one. For instance, a NEXTSTEP encoded string 
which is 10 characters might contain fewer or more characters when encoded 
as unichars. Another important point is that unichars don't necessarily 
have a one-to-one correspondence with what we tend to think of as "letters" 
in a string; if you need to go through a string in terms of "letters" (for 
instance, you are creating a crossword puzzle), use 
rangeOfComposedCharacterSequenceAtIndex:.

Methods which take "CString" arguments deal with the default 8-bit encoding 
of the environment. This is typically NEXTSTEP encoding, but could be EUC 
or ISOLatin1. You can also explicitly convert to and from any encoding by 
using methods such as initWithData:encoding: and dataUsingEncoding:. 

Constant NSStrings can be created with the @"..." option. At the moment 
they have a C-String backing. For most portable code, these strings should 
contain only ASCII chars, nothing more.

Strings are provided with generic coding behavior when used for storage or 
distribution.  This behavior is to copy the contents and provide a generic 
NSString implementation, losing class but preserving mutability.
*/



#ifndef _OBJC_UNICHAR_H_
#define _OBJC_UNICHAR_H_

typedef unsigned short unichar;

#endif /* _OBJC_UNICHAR_H_ */

#import <limits.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@class NSData <NSCopying, NSMutableCopying, NSCoding>;
@class NSArray <NSCopying, NSMutableCopying, NSCoding>;
@class NSCharacterSet  <NSCopying, NSMutableCopying, NSCoding>;
@class NSDictionary <NSCopying, NSMutableCopying, NSCoding>;

#define NSMaximumStringLength	(INT_MAX-1)


/* 
  Flags passed to compare & rangeOf...: With a zero mask passed in, the searches 
  are case sensitive, from the beginning, are non-anchored, and take Unicode 
  floating diacritics and other non-visible characters into account.
*/
enum {
    NSCaseInsensitiveSearch = 1,
    NSLiteralSearch = 2,	/* Character-by-character search */
    NSBackwardsSearch = 4,	/* Search backwards in the range */
    NSAnchoredSearch = 8	/* Search anchored within specified range (prefix or suffix) */
};

typedef unsigned NSStringEncoding;

enum {	/* Encodings supported by all OpenStep implementations */
    NSASCIIStringEncoding = 1,		/* 0..127 only */
    NSNEXTSTEPStringEncoding = 2,
    NSJapaneseEUCStringEncoding = 3,
    NSUTF8StringEncoding = 4,
    NSISOLatin1StringEncoding = 5,
    NSSymbolStringEncoding = 6,
    NSNonLossyASCIIStringEncoding = 7,	/* 7-bit verbose ASCII to represent all unichars */
    NSShiftJISStringEncoding = 8,
    NSISOLatin2StringEncoding = 9,
    NSUnicodeStringEncoding = 10
};


/**** The abstract NSString... ****/

@interface NSString : NSObject <NSCopying, NSMutableCopying, NSCoding>

/**** NSString primitives ****/

/* 
 The most basic (primitive) string methods. Note that the methods length and 
 characterAtIndex: work in terms of unichars, which don't necessarily have a 
 one-to-one correspondence with the "letters" in a string.  All direct subclassers
 need to implement these methods. For efficiency, it's recommended that 
 subclassers also implement getCharacters:range: (a non-primitive).
*/
- (unsigned int)length;			
- (unichar)characterAtIndex:(unsigned)index;

@end

@interface NSString (NSStringExtensionMethods)

/**** NSString methods built on the primitives ****/

/* Much faster alternative to multiple characterAtIndex: calls.
*/
- (void)getCharacters:(unichar *)buffer;
- (void)getCharacters:(unichar *)buffer range:(NSRange)aRange;

/* Substrings: Get a substring of an existing string. This operation is often fast. The first two methods are implemented in terms of the third one.
*/
- (NSString *)substringFromIndex:(unsigned)from;	/* From location to end of string */
- (NSString *)substringToIndex:(unsigned)to;		/* From beginning of string to location - 1 */
- (NSString *)substringWithRange:(NSRange)range;

/* 
  Comparison: Compare two strings. Possible options are: NSCaseInsensitiveSearch, 
  NSLiteralSearch. If the range argument is provided, the specified range in the 
  receiver is compared against the other string.
*/
- (NSComparisonResult)compare:(NSString *)obj;
- (NSComparisonResult)compare:(NSString *)obj options:(unsigned)mask;
- (NSComparisonResult)compare:(NSString *)obj options:(unsigned)mask range:(NSRange)compareRange;
- (NSComparisonResult)caseInsensitiveCompare:(NSString *)obj;

/* Check for equality.
*/
- (BOOL)isEqualToString:(NSString *)aString;

/* 
  Find: Find a string within another string.  If not found returned length is 
  set to zero.  Possible options are: NSCaseInsensitiveSearch, NSLiteralSearch, 
  NSBackwardsSearch, NSAnchoredSearch. hasPrefix: is a cover for 
  [str rangeOfString:str options:NSAnchoredSearch].length != 0. Note that 
  "not found" is returned if the searched string is the empty string.
*/
- (BOOL)hasPrefix:(NSString *)aString;
- (BOOL)hasSuffix:(NSString *)aString;
- (NSRange)rangeOfString:(NSString *)aString;
- (NSRange)rangeOfString:(NSString *)aString options:(unsigned)mask;
- (NSRange)rangeOfString:(NSString *)aString options:(unsigned)mask range:(NSRange)searchRange;

/* 
  Find: Find the first occurrence of a character from the specified set and 
  returns its range. Note that the range covers only the first found character, 
  not a sequence of characters. If not found, returned length is 0.  Possible 
  options are: NSLiteralSearch, NSBackwardsSearch, NSAnchoredSearch.
*/
- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)aSet;
- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)aSet options:(unsigned int)mask;
- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)aSet options:(unsigned int)mask range:(NSRange)searchRange;

/* 
  This method returns the range of the "composed character sequence" at the 
  specified location. Composed character sequences are what we normally think 
  of as letters. In the Unicode standard, sometimes multiple characters combine 
  to form one letter (for instance, "o" and dierisis).  You can use this method 
  to traverse a string by letters:
    range.location = range.length = 0;
    while ([str rangeOfComposedCharacterSequenceAtIndex:range.location + range.length].length) {
	NSString *letter = [str substringWithRange:range];
    }
*/
- (NSRange)rangeOfComposedCharacterSequenceAtIndex:(unsigned)index;

/* Appending: These are immutable versions of some of the popular mutable methods.
*/
- (NSString *)stringByAppendingString:(NSString *)aString;
- (NSString *)stringByAppendingFormat:(NSString *)format, ...;

/* 
  Float/Int Conversion: Simple-minded methods that skip whitespace and ignore 
  bogus characters past the end. On overflow they return HUGE_VAL, -HUGE_VAL, 
  INT_MIN, INT_MAX. doubleValue & floatValue return 0.0 on underflow. Use 
  NSScanner for more sophisticated scanning.
*/
- (double)doubleValue;
- (float)floatValue;
- (int)intValue;

/* 
  Exploding: Returns an array holding the substrings in the string which are 
  separated by the separator. All strings split into arrays of 1 or more elements. 
  For instance, if the string is "/A/B//C" and the separator is "/", the return 
  value will be ["", "A", "B", "", "C"]. The result will be [""] if the string 
  is empty. See also componentsJoinedByString: in NSArray.
*/
- (NSArray *)componentsSeparatedByString:(NSString *)separator;

/* Finds the longest common prefix between the two strings. Returns the substring of the receiver. Possible options are: NSCaseInsensitiveSearch, NSLiteralSearch.
*/
- (NSString *)commonPrefixWithString:(NSString *)aString options:(unsigned)mask;

/* Methods to return uppercase (HI THERE), lowercase (hi there), and capitalized (Hi There) versions of a string.
*/
- (NSString *)uppercaseString;
- (NSString *)lowercaseString;
- (NSString *)capitalizedString;

/* Returns the string itself.
*/
- (NSString *)description;

/* NSObject Protocol
*/
- (unsigned)hash;


/**** Encoding related methods follow. ****/

/* Default implementations of these methods might end up converting to Unicode 
   and back in some cases; subclassers with non-Unicode backing stores might 
   want to override some of these methods for added efficiency. 
 */

/* Encoding in which this string can be expressed (with lossless conversion) in 
   a quick manner (both this method and the conversion will be fast; space 
   efficiency is a secondary issue).
*/
- (NSStringEncoding)fastestEncoding;

/* Encoding in which this string can be expressed (with lossless conversion) in 
   a space efficient manner (this method and the conversion might be slow; 
   however, it will indicate the most space efficient encoding).
*/
- (NSStringEncoding)smallestEncoding;

/* Contents in specified encoding, in the generic plain text format for the 
   encoding. This method will return nil if the conversion cannot be performed. 
   With this data and the encoding you can recreate the string using the 
   initFromData:encoding: method. The result of this method is the only way you 
   should make contents of strings persistent.
*/
- (NSData *)dataUsingEncoding:(NSStringEncoding)encoding allowLossyConversion:(BOOL)lossy;
- (NSData *)dataUsingEncoding:(NSStringEncoding)encoding;	/* Not lossy */

/* Returns whether it is possible to convert the whole string to the specified 
   encoding. Might call dataUsingEncoding: in some cases, so if you are going 
   to do the conversion anyway, you might as well skip this method.
*/
- (BOOL)canBeConvertedToEncoding:(NSStringEncoding)encoding;

/* These methods basically use the default 8-bit character encoding. This 
   encoding is most likely NEXTSTEP; use +defaultCStringEncoding if you need 
   to know what it is. The getCString: methods all zero-terminate the buffer; 
   so buffer should actually contain max + 1 bytes (when max is provided).
*/
- (const char *)cString;	/* "Autoreleased," null-terminated C string. Raises if conversion not possible. */
- (const char *)lossyCString;
- (unsigned)cStringLength;
- (void)getCString:(char *)bytes;
- (void)getCString:(char *)bytes maxLength:(unsigned)maxLength;
- (void)getCString:(char *)bytes maxLength:(unsigned)maxLength range:(NSRange)aRange remainingRange:(NSRange *)leftoverRange;
+ (NSStringEncoding)defaultCStringEncoding;	/* Returns the encoding used for the CString methods */

/* Writes the contents of the string to the specified file. This is a convenience 
   method;it will first try to write the file in default CString encoding; if this 
   isn't possible, it will write it in Unicode encoding. initWithContentsOfFile: 
   is the corresponding method for input. If you want to write a file with a given
   encoding, use dataUsingEncoding:/initWithData:encoding:
*/
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;

/* Methods to obtain info about supported encodings.
*/
+ (const NSStringEncoding *)availableStringEncodings; /* 0 terminated array */
+ (NSString *)localizedNameOfStringEncoding:(NSStringEncoding)encoding;

- (BOOL)getFileSystemRepresentation:(char *)buffer 
	maxLength:(unsigned)max;
- (const char *)fileSystemRepresentation;

/**** Methods to create strings ***/

/* Some cover methods to return autoreleased strings. These methods are the simple 
   way to create new strings. A more complete set of initialization methods is 
   presented further below.
*/
+ (id)stringWithCharacters:(const unichar *)characters length:(unsigned)length;
+ (id)stringWithCString:(const char *)bytes length:(unsigned)length;
+ (id)stringWithCString:(const char *)bytes;
+ (id)stringWithFormat:(NSString *)format, ...;
+ (id)stringWithContentsOfFile:(NSString *)path; /* defaultCString encoding OR Unicode encoding */ 
+ (id)localizedStringWithFormat:(NSString *)format, ...; /* Uses user's defaults */
#ifndef STRICT_OPENSTEP
+ (id)string; /* default empty string */
#endif

/* 
 Initialization methods which concrete subclasses of NSString and NSMutableString
 provided by foundation respond to. Note that because the alloc methods of 
 NSString and NSMutableString return instances of a concrete subclass, these 
 init methods can be sent to that object.

 These methods will not work in custom subclasses of NSString & NSMutableString. 
 Custom subclassers should provide their own init... methods, and call [super init]
 in their designated initializers.
*/
- (id)init;
- (id)initWithCharactersNoCopy:(unichar *)characters length:(unsigned)length freeWhenDone:(BOOL)freeBuffer;
- (id)initWithCharacters:(const unichar *)characters length:(unsigned)length;
- (id)initWithCStringNoCopy:(char *)bytes length:(unsigned)length freeWhenDone:(BOOL)freeBuffer;
- (id)initWithCString:(const char *)bytes length:(unsigned)length;
- (id)initWithCString:(const char *)bytes; /* Zero terminated */
- (id)initWithString:(NSString *)aString;
- (id)initWithFormat:(NSString *)format, ...; /* For localized formatting use initWithFormat:locale: */
- (id)initWithFormat:(NSString *)format arguments:(va_list)argList;
- (id)initWithFormat:(NSString *)format locale:(NSDictionary *)dict, ...;
- (id)initWithFormat:(NSString *)format locale:(NSDictionary *)dict arguments:(va_list)argList;
- (id)initWithData:(NSData *)data encoding:(NSStringEncoding)encoding;
- (id)initWithContentsOfFile:(NSString *)path; /* defaultCString encoding OR Unicode encoding */

@end


@interface NSString(EncodingExtensionFix)

+ (void)setChangesEncodingOnUnarchival:(BOOL)flag;
+ (BOOL)changesEncodingOnUnarchival;

@end

/**** Abstract mutable string class... ****/

@interface NSMutableString : NSString

/**** Primitives (needs to be implemented by subclassers)... ****/

- (void)replaceCharactersInRange:(NSRange)range withString:(NSString *)aString;

@end

@interface NSMutableString (NSMutableStringExtensionMethods)

/**** Mutable string methods built on the primitives ****/

- (void)insertString:(NSString *)aString atIndex:(unsigned)loc;
- (void)deleteCharactersInRange:(NSRange)range;
- (void)appendString:(NSString *)aString;
- (void)appendFormat:(NSString *)format, ...;
- (void)setString:(NSString *)aString;	/* Copy the contents of the other string */

/**** Methods to create mutable strings ****/

+ (id)stringWithCapacity:(unsigned)capacity;

- (id)initWithCapacity:(unsigned)capacity;

@end

/**** 
  The rest of this file is bookkeeping stuff that has to be here (for now). 
   Don't use this stuff, don't refer to it.
*/
/* 
   To reduce confusion with the old (private) NXString. If you need to import 
   the old headers, do so after NSString.h.
*/
#ifndef _OBJC_UNICHAR_H_
#define _OBJC_UNICHAR_H_
#endif
#define NS_UNICHAR_IS_EIGHT_BIT 0

@interface NSSimpleCString : NSString {
@protected
    char *bytes;
    unsigned int numBytes;
}
@end

/* NSConstantStrings are strings created by the compiler with the @" "
   construct.  Upon encountering @" ", the compiler will take the characters
   between the quotes and create an NSConstantString instance.  Instances of
   NXConstantString cannot be created at runtime.
 */

@interface NSConstantString : NSSimpleCString
@end







