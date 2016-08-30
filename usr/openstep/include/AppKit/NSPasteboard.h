#ident "@(#) NSPasteboard.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSPasteboard_h_
#define _NSPasteboard_h_

#import <Foundation/NSObject.h>

@class NSString <NSCopying, NSMutableCopying, NSCoding>;
@class NSMutableArray;
@class NSArray <NSCopying, NSMutableCopying, NSCoding>;
@class NSData <NSCopying, NSMutableCopying, NSCoding>;

#ifdef __cplusplus
extern "C" {
#endif


/* standard Pasteboard types */

extern NSString *NSStringPboardType;
extern NSString *NSFilenamesPboardType;
extern NSString *NSPostScriptPboardType;
extern NSString *NSTIFFPboardType;
extern NSString *NSRTFPboardType;
extern NSString *NSTabularTextPboardType;
extern NSString *NSFontPboardType;
extern NSString *NSRulerPboardType;
extern NSString *NSFileContentsPboardType;
extern NSString *NSColorPboardType;

/* standard Pasteboard names */

extern NSString *NSGeneralPboard;
extern NSString *NSFontPboard;
extern NSString *NSRulerPboard;
extern NSString *NSFindPboard;
extern NSString *NSDragPboard;


extern NSString *NSCreateFilenamePboardType(NSString *fileType);
extern NSString *NSCreateFileContentsPboardType(NSString *fileType);
extern NSString *NSGetFileType(NSString *pboardType);
extern NSArray *NSGetFileTypes(NSArray *pboardTypes);

#ifdef __cplusplus
}
#endif


@interface NSPasteboard : NSObject

{
    id                  _owner;
    int                 _realChangeCount;
    int                 _ourChangeCount;
    unsigned long       _server;
    NSMutableArray	*_owners;
    NSArray		*_types;
    unsigned long       _client;
    NSMutableArray	*_typesProvided;
    NSString		*_name;
    NSString		*_host;
    int			_serverVersion;
}

+ (NSPasteboard *)generalPasteboard;
+ (NSPasteboard *)pasteboardWithName:(NSString *)name;
+ (NSPasteboard *)pasteboardWithUniqueName;

+ (NSArray *)typesFilterableTo:(NSString *)type;

+ (NSPasteboard *)pasteboardByFilteringFile:(NSString *)filename;
+ (NSPasteboard *)pasteboardByFilteringData:(NSData *)data ofType:(NSString *)type;
+ (NSPasteboard *)pasteboardByFilteringTypesInPasteboard:(NSPasteboard *)pboard;

- (NSString *)name;

- (void)releaseGlobally;

- (int)declareTypes:(NSArray *)newTypes owner:(id)newOwner;
- (int)addTypes:(NSArray *)newTypes owner:(id)newOwner;
- (int)changeCount;

- (NSArray *)types;
- (NSString *)availableTypeFromArray:(NSArray *)types;

- (BOOL)setData:(NSData *)data forType:(NSString *)dataType;
- (NSData *)dataForType:(NSString *)dataType;

- (BOOL)setPropertyList:(id)plist forType:(NSString *)dataType;
- (id)propertyListForType:(NSString *)dataType;

- (BOOL)setString:(NSString *)string forType:(NSString *)dataType;
- (NSString *)stringForType:(NSString *)dataType;

@end

@interface NSPasteboard(NSFileContents)
- (BOOL)writeFileContents:(NSString *)filename;
- (NSString *)readFileContentsType:(NSString *)type toFile:(NSString *)filename;
@end

@interface NSObject(NSPasteboardOwner)
- (void)pasteboard:(NSPasteboard *)sender provideDataForType:(NSString *)type;
- (void)pasteboardChangedOwner:(NSPasteboard *)sender;
@end
 
#endif // _NSPasteboard_h_
