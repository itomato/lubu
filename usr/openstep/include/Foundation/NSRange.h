#ident "@(#) NSRange.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Definitions relative to ranges

#import <Foundation/NSObject.h>

#ifdef __cplusplus 
extern "C" {
#endif

@class NSString <NSCopying, NSMutableCopying, NSCoding>;

/***************	Basic definitions		***********/

/* An open struct for specifying a range of items in arrays, strings, etc. */
typedef struct _NSRange {
    unsigned int location;
    unsigned int length;
} NSRange;


/***************	Creation		***********/

static inline NSRange NSMakeRange(unsigned int location, unsigned int length) {
    NSRange r;
    r.location = location;  r.length = length;
    return r;
}

/***************	Operations		***********/

static inline unsigned NSMaxRange(NSRange range) {
    /* Note that this can easily overflow if range.length big */
    return range.location + range.length;
}

static inline BOOL NSLocationInRange(unsigned location, NSRange range) {
    return (location >= range.location) && (location < NSMaxRange(range));
}

static inline BOOL NSEqualRanges(NSRange range1, NSRange range2) {
    return (range1.location == range2.location) && (range1.length == range2.length);
}

extern NSRange NSUnionRange(NSRange range1, NSRange range2);

extern NSRange NSIntersectionRange(NSRange range1, NSRange range2);
    /* !length => ranges don't intersect, and then location is meaningless */

extern NSString *NSStringFromRange(NSRange range);
    /* Returns a string of the form: {location = 34; length = 12} */
extern NSRange NSRangeFromString(NSString *aString);
    /* Returns an NSRange where the string is of the form: {location = 34; length = 12} */

#ifdef __cplusplus 
}
#endif
