#ident "@(#) NSDateFormatter.h, Rev 1.9, 97/03/17"
//
//	Copyright (c) 1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1995, NeXT Computer, Inc.
//	All rights reserved.

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSFormatter.h>

@class NSString <NSCopying, NSMutableCopying, NSCoding>;

@interface NSDateFormatter : NSFormatter
{
    NSString *_format;
    BOOL _naturalLanguage;
    int _reserved;
}

- (id)initWithDateFormat:(NSString *)format allowNaturalLanguage:(BOOL)flag;
- (NSString *)dateFormat;
- (BOOL)allowsNaturalLanguage;

@end

#endif




