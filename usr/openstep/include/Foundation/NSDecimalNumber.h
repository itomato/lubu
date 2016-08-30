#ident "@(#) NSDecimalNumber.h, Rev 1.6, 97/03/17"
//
//	Copyright (c) 1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1995-1996, NeXT Computer, Inc.
//	All rights reserved.
//
//	Public class for large precision base-10 arithmetic

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSValue.h>
#import <Foundation/NSScanner.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSDecimal.h>

/***************	Exceptions		***********/

extern NSString *NSDecimalNumberExactnessException;
extern NSString *NSDecimalNumberOverflowException;
extern NSString *NSDecimalNumberUnderflowException;
extern NSString *NSDecimalNumberDivideByZeroException;

/***************	Rounding and Exception behavior		***********/

@class NSDecimalNumber;

@protocol NSDecimalNumberBehaviors

- (NSRoundingMode)roundingMode;

- (short)scale;
    // The scale could return NO_SCALE for no defined scale.

- (NSDecimalNumber *)exceptionDuringOperation:(SEL)operation error:(NSCalculationError)error leftOperand:(NSDecimalNumber *)leftOperand rightOperand:(NSDecimalNumber *)rightOperand;
    // Receiver can raise, return a new value, or return nil to ignore the exception.

@end

/***************	NSDecimalNumber: the class		***********/

@interface NSDecimalNumber:NSNumber {
    signed   int _exponent:8;
    unsigned int _length:4;
    unsigned int _isNegative:1;
    unsigned int _isCompact:1;
    unsigned int _reserved:1;
    unsigned int _hasExternalRefCount:1;
    unsigned int _refs:16;
    unsigned short _mantissa[1]; // Variable length.
}

- (id)initWithMantissa:(unsigned long long)mantissa exponent:(short)exponent isNegative:(BOOL)flag;
- (id)initWithDecimal:(NSDecimal)decimal;
- (id)initWithString:(NSString *)numberValue;
- (id)initWithString:(NSString *)numberValue locale:(NSDictionary *)locale;

- (NSString *)descriptionWithLocale:(NSDictionary *)locale;

- (NSDecimal)decimalValue;

+ (NSDecimalNumber *)decimalNumberWithMantissa:(unsigned long long)mantissa exponent:(short)exponent isNegative:(BOOL)flag;
+ (NSDecimalNumber *)decimalNumberWithDecimal:(NSDecimal)decimal;
+ (NSDecimalNumber *)decimalNumberWithString:(NSString *)numberValue;
+ (NSDecimalNumber *)decimalNumberWithString:(NSString *)numberValue locale:(NSDictionary *)locale;

+ (NSDecimalNumber *)zero;
+ (NSDecimalNumber *)one;
+ (NSDecimalNumber *)minimumDecimalNumber;
+ (NSDecimalNumber *)maximumDecimalNumber;
+ (NSDecimalNumber *)notANumber;

- (NSDecimalNumber *)decimalNumberByAdding:(NSDecimalNumber *)decimalNumber;
- (NSDecimalNumber *)decimalNumberByAdding:(NSDecimalNumber *)decimalNumber withBehavior:(id <NSDecimalNumberBehaviors>)behavior;

- (NSDecimalNumber *)decimalNumberBySubtracting:(NSDecimalNumber *)decimalNumber;
- (NSDecimalNumber *)decimalNumberBySubtracting:(NSDecimalNumber *)decimalNumber withBehavior:(id <NSDecimalNumberBehaviors>)behavior;

- (NSDecimalNumber *)decimalNumberByMultiplyingBy:(NSDecimalNumber *)decimalNumber;
- (NSDecimalNumber *)decimalNumberByMultiplyingBy:(NSDecimalNumber *)decimalNumber withBehavior:(id <NSDecimalNumberBehaviors>)behavior;

- (NSDecimalNumber *)decimalNumberByDividingBy:(NSDecimalNumber *)decimalNumber;
- (NSDecimalNumber *)decimalNumberByDividingBy:(NSDecimalNumber *)decimalNumber withBehavior:(id <NSDecimalNumberBehaviors>)behavior;

- (NSDecimalNumber *)decimalNumberByRaisingToPower:(unsigned)power;
- (NSDecimalNumber *)decimalNumberByRaisingToPower:(unsigned)power withBehavior:(id <NSDecimalNumberBehaviors>)behavior;

- (NSDecimalNumber *)decimalNumberByMultiplyingByPowerOf10:(short)power;
- (NSDecimalNumber *)decimalNumberByMultiplyingByPowerOf10:(short)power withBehavior:(id <NSDecimalNumberBehaviors>)behavior;


- (NSDecimalNumber *)decimalNumberByRoundingAccordingToBehavior:(id <NSDecimalNumberBehaviors>)behavior;
    // Round to the scale of the behavior.

- (NSComparisonResult)compare:(NSNumber *)decimalNumber;
    // compare two NSDecimalNumbers

+ (void)setDefaultBehavior:(id <NSDecimalNumberBehaviors>)behavior;

+ (id <NSDecimalNumberBehaviors>)defaultBehavior;
    // One behavior per NSThread ? The default behavior is
    //   rounding mode: NSRoundPlain
    //   scale: No defined scale (full precision)
    //   ignore exactnessException
    //   raise on overflow, underflow and divide by zero.

- (const char *)objCType;
    // return 'd' for double
    
- (double)doubleValue;
    // return an approximate double value
    
@end

/***********	A class for defining common behaviors		*******/

@interface NSDecimalNumberHandler : NSObject <NSDecimalNumberBehaviors> {
  @private
    NSRoundingMode _roundingMode;
    short _scale;
    unsigned _raiseOnExactness:1;
    unsigned _raiseOnOverflow:1;
    unsigned _raiseOnUnderflow:1;
    unsigned _raiseOnDivideByZero:1;
    void *_reserved;
}

+ (id)defaultDecimalNumberHandler;
    // rounding mode: NSRoundPlain
    // scale: No defined scale (full precision)
    // ignore exactnessException (return nil)
    // raise on overflow, underflow and divide by zero.

- (id)initWithRoundingMode:(NSRoundingMode)roundingMode scale:(short)scale raiseOnExactness:(BOOL)exact raiseOnOverflow:(BOOL)overflow raiseOnUnderflow:(BOOL)underflow raiseOnDivideByZero:(BOOL)divideByZero;

+ (id)decimalNumberHandlerWithRoundingMode:(NSRoundingMode)roundingMode scale:(short)scale raiseOnExactness:(BOOL)exact raiseOnOverflow:(BOOL)overflow raiseOnUnderflow:(BOOL)underflow raiseOnDivideByZero:(BOOL)divideByZero;

@end

/***********	Extensions to other classes		*******/

@interface NSNumber (NSDecimalNumberExtensions)

- (NSDecimal)decimalValue;
    // Could be silently inexact for float and double.

@end

@interface NSScanner (NSDecimalNumberScanning)

- (BOOL)scanDecimal:(NSDecimal *)decimal;

@end

#endif /* !STRICT_OPENSTEP */
