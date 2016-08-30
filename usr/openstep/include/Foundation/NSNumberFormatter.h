#ident "@(#) NSNumberFormatter.h, Rev 1.12, 97/03/17"
//
//	Copyright (c) 1996, Sun Microsystems, Inc.
//	portions (c) portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSFormatter.h>
#import <Foundation/NSDecimalNumber.h>

/* not a real NSString */
#define NSString_ATTR NSString

@class NSDecimalNumber;
@class NSDictionary <NSCopying, NSMutableCopying, NSCoding>;
@class NSDecimalNumberHandler <NSDecimalNumberBehaviors>;

@interface NSNumberFormatter : NSFormatter
{
@private
    NSString               *_negativeFormat;
    NSString               *_positiveFormat;
    NSDictionary           *_negativeAttributes;
    NSDictionary    	   *_positiveAttributes;
    
    NSString_ATTR    	   *_attributedStringForZero;
    NSString_ATTR    	   *_attributedStringForNil;
    NSString_ATTR    	   *_attributedStringForNotANumber;
    
    NSDecimalNumber        *_minimum;
    NSDecimalNumber        *_maximum;
    NSDecimalNumberHandler *_roundingBehavior;
    
    NSString               *_decimalSeparator;
    NSString               *_thousandSeparator;
    void                   *_private;
    struct {
	unsigned int thousandSeparators:1;
	unsigned int localizesFormat:1;
	unsigned int allowsFloats:1;
	unsigned int RESERVED:29;
    } _flags;
    
    void *_reserved;
}


- (NSString *)negativeFormat;
- (void)setNegativeFormat:(NSString *)format;
- (NSDictionary *)textAttributesForNegativeValues;
- (void)setTextAttributesForNegativeValues:(NSDictionary *)newAttributes;

- (NSString *)positiveFormat;
- (void)setPositiveFormat:(NSString *)format;
- (NSDictionary *)textAttributesForPositiveValues;
- (void)setTextAttributesForPositiveValues:(NSDictionary *)newAttributes;

- (NSString *)format;
- (void)setFormat:(NSString *)format;

    // The formatter string can consist of one, two or three parts separated
    // by ';'. If the caller specifies three parts, the center part is used
    // to set the attributedStringForZero. The center part is always a string
    // constant. If attributedStringForZero has not been explicitly set, with
    // -setAttributedStringForZero, zeros are formatted with the positive
    // format.

- (BOOL)hasThousandSeparators;
- (void)setHasThousandSeparators:(BOOL)flag;
- (NSString *)thousandSeparator;
- (void)setThousandSeparator:(NSString *)newSeparator;

- (NSString *)decimalSeparator;
- (void)setDecimalSeparator:(NSString *)newSeparator;

- (BOOL)localizesFormat;
- (void)setLocalizesFormat:(BOOL)flag;

- (BOOL)allowsFloats;
- (void)setAllowsFloats:(BOOL)flag;

- (NSDecimalNumberHandler *)roundingBehavior;
- (void)setRoundingBehavior:(NSDecimalNumberHandler *)newRoundingBehavior;

- (NSDecimalNumber *)minimum;
- (void)setMinimum:(NSDecimalNumber *)aMinimum;
- (NSDecimalNumber *)maximum;
- (void)setMaximum:(NSDecimalNumber *)aMaximum;

/* old NSNumberFormatter methods */
- (id)initWithNumericFormat:(NSString *)format allowFloats:(BOOL)allowsFloats 
    minValue:(double)min maxValue:(double)max;
- (NSString *)numericFormat;
- (double)minValue;
- (double)maxValue;

@end

#endif
