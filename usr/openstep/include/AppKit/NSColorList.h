#ident "@(#) NSColorList.h, Rev 1.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSColorList_h_
#define _NSColorList_h_

/* An NSColorList is an ordered list of NSColors, identified by keys. These keys are used to identify the colors in the list and are used to display the color to the user in the color panel. When a color is obtained from a color list, it does not bring along with its key.

Instances of NSColorList are created for all user-created color lists (those in the color panel) and various color catalogs (such as Pantone) available on the system.

NSColorList posts a "NSColorListChanged" notification when changed.
*/

#import <Foundation/Foundation.h>

@class NSColor <NSCopying, NSCoding>;

@interface NSColorList : NSObject <NSCoding> {
    NSMutableArray *_keyArray;
    NSMutableArray *_colorArray;
    id _hashTable;
    NSString *_name;
    NSString *_printerType;
    NSString *_fileName;
    struct _colorListFlags {
	unsigned int colorsLoaded:1;
	unsigned int editable:1;
	unsigned int hasDeviceSpecificLists:1;
	unsigned int dirty:1;
	unsigned int hasFrozen:1;
	unsigned int notificationsDisabled:1;
	unsigned int :26;
    } _flags;
}

+ (NSArray *)availableColorLists;
+ (NSColorList *)colorListNamed:(NSString *)name;

- (id)initWithName:(NSString *)name;
- (id)initWithName:(NSString *)name fromFile:(NSString *)path;

- (NSString *)name;

/* If key already exists, sets the corresponding color. Otherwise inserts the color at the end.
*/
- (void)setColor:(NSColor *)color forKey:(NSString *)key;

/* Inserts color at the specified location. If a color by the same key is already in the list but at a different location it is removed from there.
*/
- (void)insertColor:(NSColor *)color key:(NSString *)key atIndex:(unsigned)loc;

/* No-op if key doesn't exist.
*/
- (void)removeColorWithKey:(NSString *)key;

/* Returns nil if key doesn't exist.
*/
- (NSColor *)colorWithKey:(NSString *)key;

/* Use this array to get count of colors and enumerate them according to the ordering specified when inserting.
*/
- (NSArray *)allKeys;

/* Depends on the source of the colorlist file
*/
- (BOOL)isEditable;

/* Use "nil" to save to the user's private colorlists directory.
*/
- (BOOL)writeToFile:(NSString *)path;	

/* Removes the corresponding file in user's private colorlists directory.
*/
- (void)removeFile;	

@end

/* Notifications */
extern NSString *NSColorListDidChangeNotification;

#endif // _NSColorList_h_
