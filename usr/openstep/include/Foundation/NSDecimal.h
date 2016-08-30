#ident "@(#) NSDecimal.h, Rev 1.5, 97/03/17"
//
//	Copyright (c) 1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1995-1996, NeXT Computer, Inc.
//	All rights reserved.
//
//	Public library for large precision base-10 arithmetic

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSDictionary.h>
#import <limits.h>


/***************	Type definitions		***********/

// Rounding policies :
// Original
//    value 1.2  1.21  1.25  1.35  1.27
// Plain    1.2  1.2   1.3   1.4   1.3
// Down     1.2  1.2   1.2   1.3   1.2
// Up       1.2  1.3   1.3   1.4   1.3
// Bankers  1.2  1.2   1.2   1.4   1.3

typedef enum {
    NSRoundPlain,   // Round up on a tie
    NSRoundDown,    // Always down == truncate
    NSRoundUp,      // Always up
    NSRoundBankers  // on a tie round so last digit is even
} NSRoundingMode;

typedef enum {
    NSCalculationNoError = 0,
    NSCalculationLossOfPrecision, // Result lost precision
    NSCalculationUnderflow,       // Result became 0
    NSCalculationOverflow,        // Result exceeds possible representation
    NSCalculationDivideByZero
} NSCalculationError;

#define NSDecimalMaxSize (8)
    // Give a precision of at least 38 decimal digits, 128 binary positions.

#define NSDecimalNoScale SHRT_MAX

typedef struct {
    signed   int _exponent:8;
    unsigned int _length:4;     // length == 0 && isNegative -> NaN
    unsigned int _isNegative:1;
    unsigned int _isCompact:1;
    unsigned int _reserved:18;
    unsigned short _mantissa[NSDecimalMaxSize];
} NSDecimal;

static inline BOOL NSDecimalIsNotANumber(const NSDecimal *decimal)
  { return ((decimal->_length == 0) && decimal->_isNegative); }

/***************	Operations		***********/

extern void NSDecimalCopy(NSDecimal *destination, const NSDecimal *source);

extern void NSDecimalCompact(NSDecimal *number);

extern NSComparisonResult NSDecimalCompare(const NSDecimal *leftOperand, const NSDecimal *rightOperand);
    // NSDecimalCompare:Compares leftOperand and rightOperand.

extern void NSDecimalRound(NSDecimal *result, const NSDecimal *number, int scale, NSRoundingMode roundingMode);
    // Rounds num to the given scale using the given mode.
    // result may be a pointer to same space as num.
    // scale indicates number of significant digits after the decimal point

extern NSCalculationError NSDecimalNormalize(NSDecimal *number1, NSDecimal *number2, NSRoundingMode roundingMode);

extern NSCalculationError NSDecimalAdd(NSDecimal *result, const NSDecimal *leftOperand, const NSDecimal *rightOperand, NSRoundingMode roundingMode);
    // Exact operations. result may be a pointer to same space as leftOperand or rightOperand

extern NSCalculationError NSDecimalSubtract(NSDecimal *result, const NSDecimal *leftOperand, const NSDecimal *rightOperand, NSRoundingMode roundingMode);
    // Exact operations. result may be a pointer to same space as leftOperand or rightOperand

extern NSCalculationError NSDecimalMultiply(NSDecimal *result, const NSDecimal *leftOperand, const NSDecimal *rightOperand, NSRoundingMode roundingMode);
    // Exact operations. result may be a pointer to same space as leftOperand or rightOperand

extern NSCalculationError NSDecimalDivide(NSDecimal *result, const NSDecimal *leftOperand, const NSDecimal *rightOperand, NSRoundingMode roundingMode);
    // Division could be silently inexact;
    // Exact operations. result may be a pointer to same space as leftOperand or rightOperand
    
extern NSCalculationError NSDecimalPower(NSDecimal *result, const NSDecimal *number, unsigned power, NSRoundingMode roundingMode);

extern NSCalculationError NSDecimalMultiplyByPowerOf10(NSDecimal *result, const NSDecimal *number, short power, NSRoundingMode roundingMode);

extern NSString *NSDecimalString(const NSDecimal *decimal, NSDictionary *locale);

#endif /* !STRICT_OPENSTEP */
