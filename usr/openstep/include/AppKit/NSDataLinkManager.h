#ident "@(#) NSDataLinkManager.h, Rev 1.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#ifndef _NSDataLinkManager_h_
#define _NSDataLinkManager_h_

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSObject.h>
#import <AppKit/NSGraphics.h>

@class List;
@class NSPasteboard;
@class NSDataLink <NSCopying, NSCoding>;
@class NSSelection <NSCopying, NSCoding>;
@class NSWindow;

@interface NSDataLinkManager : NSObject <NSCoding> {
  @private
    id delegate;
    id ref;
    List *srcLinks;
    List *destLinks;
    struct _lmFlags {
	unsigned int isEdited:1;
	unsigned int doUI:1;
	unsigned int showOutlines:1;
	unsigned int registered:1;
	unsigned int linksDirty:1;
	unsigned int delegateVerifiesLinks:1;
	unsigned int RESERVED:10;
    } lmFlags;
    int destLinksCounter;
    time_t lastEditTime;
    List *linkInfo;
    NSPasteboard *linkInfoPboard;
    int linkInfoChangeCount;
    id tempArray;
    unsigned int _reservedLinkManager1;
}

- (id)initWithDelegate:(id)obj fromFile:(NSString *)path;
- (NSEnumerator *)sourceLinkEnumerator;
- (NSEnumerator *)destinationLinkEnumerator;
@end

#ifdef __cplusplus
extern "C" {
#endif

extern void NSFrameLinkRect(NSRect aRect, BOOL isDestination);
extern float NSLinkFrameThickness(void);

#ifdef __cplusplus
}
#endif

#endif // STRICT_OPENSTEP

#endif // _NSDataLinkManager_h_
