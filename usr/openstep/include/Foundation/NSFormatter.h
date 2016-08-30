#ident "@(#) NSFormatter.h, Rev 1.6, 97/03/17"
//
//	Copyright (c) 1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1995, NeXT Computer, Inc.
//	All rights reserved.

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSDictionary.h>

@class NSString;
@class NSDictionary;

@interface NSFormatter : NSObject <NSCopying, NSCoding>

- (NSString *)stringForObjectValue:(id)obj;
    // Raises NSInvalidArgumentException

- (NSString *)editingStringForObjectValue:(id)obj;
    // Returns [self stringForObjectValue:obj];

- (BOOL)getObjectValue:(id *)obj forString:(NSString *)string errorDescription:(NSString **)error;
    // Raises NSInvalidArgumentException

- (BOOL)isPartialStringValid:(NSString *)partialString newEditingString:(NSString **)newString errorDescription:(NSString **)error;
    // Returns YES

@end

#endif
