#ident "@(#) NSSelection.h, Rev 1.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSObject.h>
#import <Foundation/Foundation.h>
#import "NSPasteboard.h"

extern NSString *NSSelectionPboardType;

@interface NSSelection : NSObject <NSCopying, NSCoding>
{
  @private
    NSData *data;
    struct _selFlags {
	unsigned int reserved:1;
	unsigned int isMagic:1;
	unsigned int RESERVED:14;
    } selFlags;
    unsigned int _reservedSel1;
}

/* these methods return special objects that indicate special selections */
+ (NSSelection *)emptySelection;		/* nothing selected */
+ (NSSelection *)allSelection;			/* the result of a select all */
+ (NSSelection *)currentSelection;		/* whatever is currently selected */

/* data should be architecture independant and include a version stamp */
- (id)initWithDescriptionData:(NSData *)newData;
- (id)initWithPasteboard:(NSPasteboard *)pasteboard;
+ (NSSelection *)selectionWithDescriptionData:(NSData *)newData;

- (NSData *)descriptionData;

- (void)writeToPasteboard:(NSPasteboard *)pasteboard;

- (BOOL)isWellKnownSelection;

@end

#endif // STRICT_OPENSTEP

