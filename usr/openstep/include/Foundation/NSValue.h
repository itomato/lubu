#ident "@(#) NSValue.h, Rev 1.8, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>

/* An abstract class for wrapping any C-type with an object. Sample use: To put an NSRange into an NSArray, you would [myArray insertObject:[NSValue value:&range withObjCType:@encode(NSRange)] atIndex:n]; to get it back out, [[myArray objectAtIndex:n] getValue:&range].

NSValues are provided with generic coding & copying behavior. Subclassers wishing to preserve class when encoding or copying should override classForCoder (for encoding, in addition to initWithCoder: and encodeWithCoder:) and copyWithZone: (for copying).
*/
@interface NSValue : NSObject <NSCopying, NSCoding>

+ (NSValue *)value:(const void *)value withObjCType:(const char *)type;	/* Creation method */

- (void)getValue:(void *)value;	/* Value copied from the object to caller's variable... */
- (const char *)objCType;	/* Standard objC encoding string */

+ (NSValue *)valueWithBytes:(const void *)value objCType:(const char *)type;
- (id)initWithBytes:(const void *)value objCType:(const char *)type;
- (BOOL)isEqualToValue:(NSValue *)otherValue; 

@end


@interface NSValue (NSValueOtherTypes)

+ (NSValue *)valueWithNonretainedObject:(id)anObject;	/* Get objects into collections without retain */
- (id)nonretainedObjectValue;

+ (NSValue *)valueWithPointer:(const void *)pointer;	/* Get pointers into collections */
- (void *)pointerValue;

@end


/* An abstract class for wrapping C number types with an object. NSNumbers have the added feature that they can do type-coercion. The objCType method in an NSNumber can only be one of c, C, s, S, i, I, l, L, q, Q, f, or d.

NSNumbers are provided with generic coding & copying behavior. Subclassers wishing to preserve class when encoding or copying should override classForCoder (for encoding, in addition to initWithCoder: and encodeWithCoder:) and copyWithZone: (for copying).
*/
@interface NSNumber : NSValue

+ (NSNumber *)numberWithChar:(char)value;
+ (NSNumber *)numberWithUnsignedChar:(unsigned char)value;
+ (NSNumber *)numberWithShort:(short)value;
+ (NSNumber *)numberWithUnsignedShort:(unsigned short)value;
+ (NSNumber *)numberWithInt:(int)value;
+ (NSNumber *)numberWithUnsignedInt:(unsigned int)value;
+ (NSNumber *)numberWithLong:(long)value;
+ (NSNumber *)numberWithUnsignedLong:(unsigned long)value;
+ (NSNumber *)numberWithLongLong:(long long)value;
+ (NSNumber *)numberWithUnsignedLongLong:(unsigned long long)value;
+ (NSNumber *)numberWithFloat:(float)value;
+ (NSNumber *)numberWithDouble:(double)value;
+ (NSNumber *)numberWithBool:(BOOL)value;

- (id)initWithChar:(char)value;
- (id)initWithUnsignedChar:(unsigned char)value;
- (id)initWithShort:(short)value;
- (id)initWithUnsignedShort:(unsigned short)value;
- (id)initWithInt:(int)value;
- (id)initWithUnsignedInt:(unsigned int)value;
- (id)initWithLong:(long)value;
- (id)initWithUnsignedLong:(unsigned long)value;
- (id)initWithLongLong:(long long)value;
- (id)initWithUnsignedLongLong:(unsigned long long)value;
- (id)initWithFloat:(float)value;
- (id)initWithDouble:(double)value;
- (id)initWithBool:(BOOL)value;
- (BOOL)isEqualToNumber:(NSNumber *)otherNumber;

/* These methods return the number in the requested type. These methods will do type-coercion as defined by C. In certain cases the results may be undefined; for instance, trying to take the unsigned integer value of a negative number, or trying to get the short value of an float which is greater than the maximum short.
*/
- (char)charValue;
- (unsigned char)unsignedCharValue;
- (short)shortValue;
- (unsigned short)unsignedShortValue;
- (int)intValue;
- (unsigned int)unsignedIntValue;
- (long)longValue;
- (unsigned long)unsignedLongValue;
- (long long)longLongValue;
- (unsigned long long)unsignedLongLongValue;
- (float)floatValue;
- (double)doubleValue;
- (BOOL)boolValue;
- (NSString *)stringValue;	/* Calls description */
- (NSString *)descriptionWithLocale:(NSDictionary *)locale;

/* Compare the numbers exactly like C would.
*/
- (NSComparisonResult)compare:(NSNumber *)otherNumber;
@end

