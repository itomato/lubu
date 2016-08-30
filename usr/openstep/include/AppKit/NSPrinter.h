#ident "@(#) NSPrinter.h, Rev 1.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import <Foundation/NSObject.h>
#import "NSGraphics.h"


typedef enum _NSPrinterTableStatus {
    NSPrinterTableOK			= (0),
    NSPrinterTableNotFound		= (1),
    NSPrinterTableError			= (2)
} NSPrinterTableStatus;

@interface NSPrinter:NSObject <NSCopying, NSCoding>
{
    NSString *_printerName;
    NSString *_hostName;
    NSString *_domainName;
    NSString *_printerType;
    BOOL _ignore;
    BOOL _valid;
    int _creationNum;
    void *_nodes;
    struct timeval _previousValid;
    long _niInstance;
    NSDictionary *_deviceDict;
    void *_priv;
}

+ (NSPrinter *)printerWithName:(NSString *)name;
#ifndef STRICT_OPENSTEP
+ (NSPrinter *)printerWithName:(NSString *)name domain:(NSString *)domain includeUnavailable:(BOOL)flag;
#endif
+ (NSArray *)printerNames;
+ (NSPrinter *)printerWithType:(NSString *)type;
+ (NSArray *)printerTypes;

- (NSString *)name;
#ifndef STRICT_OPENSTEP
- (NSString *)domain;
#endif
- (NSString *)host;
- (NSString *)type;
- (NSString *)note;
- (BOOL)isColor;
- (BOOL)acceptsBinary;
- (BOOL)isOutputStackInReverseOrder;
- (NSSize)pageSizeForPaper:(NSString *)paperName;
- (NSRect)imageRectForPaper:(NSString *)paperName;
- (int)languageLevel;
- (BOOL)isFontAvailable:(NSString *)faceName;
- (NSPrinterTableStatus)statusForTable:(NSString *)table;
- (NSDictionary *)deviceDescription;

- (BOOL)isKey:(NSString *)key inTable:(NSString *)table;
- (NSString *)stringForKey:(NSString *)key inTable:(NSString *)table;
- (NSSize)sizeForKey:(NSString *)key inTable:(NSString *)table;
- (NSRect)rectForKey:(NSString *)key inTable:(NSString *)table;
- (int)intForKey:(NSString *)key inTable:(NSString *)table;
- (float)floatForKey:(NSString *)key inTable:(NSString *)table;
- (BOOL)booleanForKey:(NSString *)key inTable:(NSString *)table;
- (NSArray *)stringListForKey:(NSString *)key inTable:(NSString *)table;

@end
