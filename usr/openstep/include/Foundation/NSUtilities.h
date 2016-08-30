#ident "@(#) NSUtilities.h, Rev 1.11, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Utilities of all kind; Garbage sink

#import <Foundation/NSString.h>
#import <Foundation/NSDictionary.h>

#ifdef __cplusplus 
extern "C" {
#endif

/***************	Logging		***************/

extern void NSLog(NSString *format, ...);
extern void NSLogv(NSString *format, va_list args);
    /* log message, along with date and process, on stderr;
    An ending \n is added iff none at the end of format; %@ and istrings OK;
    Flushes stderr afterwards */

/***************	ASCII Property List encoding		***********/

@interface NSString (NSExtendedStringPropertyListParsing)
    
- (id)propertyList;
    /* understands the PropertyList classes (NSString, NSData, NSArray, NSDictionary);
    May raise */

- (NSDictionary *)propertyListFromStringsFileFormat;
    /* understands the .strings files;
    Using -propertyList should be preferred for non .strings files.
    May raise */

@end

@interface NSDictionary (NSExtendedPropertyListASCII)

- (NSString *)descriptionInStringsFileFormat;
    /* same format as the .strings files */

@end

/***********    Abstract class for Enumerators             ***********/

@interface NSEnumerator:NSObject

- (id)nextObject;
    // returns nil when no more

@end



@interface NSEnumerator (NSEnumeratorArraying)
 
- (NSArray *)allObjects;
    /* Calls -nextObject until no more; returns in an array */
 
@end


/***************	MIN, MAX, ABS macros		***********/

#ifndef MIN
#define  MIN(A,B)	((A) < (B) ? (A) : (B))
#endif
#ifndef MAX
#define  MAX(A,B)	((A) > (B) ? (A) : (B))
#endif
#ifndef ABS
#define  ABS(A)		((A) < 0 ? (-(A)) : (A))
#endif

#ifdef __cplusplus 
}
#endif

