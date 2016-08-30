#ident "@(#) NSDataLink.h, Rev 1.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#ifndef _NSDataLink_h_
#define _NSDataLink_h_

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSObject.h>
#import <sys/types.h>

@class NSDataLinkManager <NSCoding>;
@class NSPasteboard;
@class NSSelection <NSCopying, NSCoding>;
@class NSArray <NSCopying, NSMutableCopying, NSCoding>;
@class NSDate <NSCopying, NSCoding>;


typedef enum _NSDataLinkUpdateMode {
	NSUpdateContinuously = 1,
	NSUpdateWhenSourceSaved = 2,
	NSUpdateManually = 3,
	NSUpdateNever = 4
} NSDataLinkUpdateMode;

typedef enum _NSDataLinkDisposition {
	NSLinkInDestination = 1,
	NSLinkInSource = 2,
	NSLinkBroken = 3
} NSDataLinkDisposition;

/* A persistent identifier of links on the destination side. Never 0. */
typedef int NSDataLinkNumber;

@interface NSDataLink : NSObject <NSCopying, NSCoding>
{
  @private
    NSSelection *srcSelection;
    id srcFile;
    NSString *srcAppName;
    id srcMgr;
    NSSelection *destSelection;
    NSString *destFileName;
    NSString *destAppName;
    id destMgr;
    time_t lastUpdateTime;
    NSDataLinkNumber linkNum;
    struct _dlFlags {
	unsigned int dirty:1;
	unsigned int memorable:1;
	unsigned int mode:2;
	unsigned int canUpdateContinuously:1;
	unsigned int updateMode:4;
	unsigned int appVerifiesLinks:1;
	unsigned int willOpenSource:1;
	unsigned int willUpdate:1;
	unsigned int dead:1;
	unsigned int cyclical:1;
	unsigned int RESERVED:2;
    } dlFlags;
    NSArray *types;
    unsigned int _reservedDataLink1;
}

- (NSArray *)types;
- (NSSelection *)sourceSelection;
- (NSSelection *)destinationSelection;
- (NSString *)sourceFilename;
- (NSString *)currentSourceFilename;
- (NSString *)destinationFilename;
- (NSString *)sourceApplicationName;
- (NSString *)destinationApplicationName;
- (NSDataLinkManager *)manager;
- (NSDate *)lastUpdateTime;
- (NSDataLinkNumber)linkNumber;
- (NSDataLinkDisposition)disposition;

@end

#endif // STRICT_OPENSTEP

#endif // _NSDataLink_h_
