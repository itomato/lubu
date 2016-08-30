#ident "@(#) NSWorkspace.h, Rev 1.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSWorkspace_h_
#define _NSWorkspace_h_

#import <Foundation/NSObject.h>
#import <AppKit/NSGraphics.h>

@class NSImage <NSCopying, NSCoding>, NSView, NSNotificationCenter;

@interface NSWorkspace : NSObject {
  @private
    NSNotificationCenter *notificationCenter;
    int deviceStatusCount;
    int applicationStatusCount;
}

+ (NSWorkspace *)sharedWorkspace;

- (NSNotificationCenter *)notificationCenter;


- (BOOL)openFile:(NSString *)fullPath;  /* DONE */
- (BOOL)openFile:(NSString *)fullPath withApplication:(NSString *)appName;  /* DONE */
- (BOOL)openFile:(NSString *)fullPath withApplication:(NSString *)appName andDeactivate:(BOOL)flag;  /* DONE */

- (BOOL)openTempFile:(NSString *)fullPath; /* DONE */
- (BOOL)openFile:(NSString *)fullPath fromImage:(NSImage *)anImage at:(NSPoint)point inView:(NSView *)aView;  /* DONE */

- (BOOL)launchApplication:(NSString *)appName;  /* DONE */
- (BOOL)launchApplication:(NSString *)appName showIcon:(BOOL)showIcon autolaunch:(BOOL)autolaunch;
- (NSString *)fullPathForApplication:(NSString *)appName;  /* DONE */

- (BOOL)selectFile:(NSString *)fullPath inFileViewerRootedAtPath:(NSString *)rootFullpath;

- (void)findApplications;  /* DONE */

- (void)noteFileSystemChanged;
- (BOOL)fileSystemChanged;
- (void)noteUserDefaultsChanged;
- (BOOL)userDefaultsChanged;

/* Return values for type in getInfoForFile: */

extern NSString *NSPlainFileType, *NSDirectoryFileType, *NSApplicationFileType;
extern NSString *NSFilesystemFileType, *NSShellCommandFileType;

- (BOOL)getInfoForFile:(NSString *)fullPath application:(NSString **)appName type:(NSString **)type;  /* DONE */

- (NSImage *)iconForFile:(NSString *)fullPath;  /* DONE */
- (NSImage *)iconForFiles:(NSArray *)fullPaths;  /* DONE */
- (NSImage *)iconForFileType:(NSString *)fileType;  /* DONE */

- (BOOL)getFileSystemInfoForPath:(NSString *)fullPath isRemovable:(BOOL *)removableFlag isWritable:(BOOL *)writableFlag isUnmountable:(BOOL *)unmountableFlag description:(NSString **)description type:(NSString **)fileSystemType;

extern NSString *NSWorkspaceMoveOperation;
extern NSString *NSWorkspaceCopyOperation;
extern NSString *NSWorkspaceLinkOperation;
extern NSString *NSWorkspaceCompressOperation;
extern NSString *NSWorkspaceDecompressOperation;
extern NSString *NSWorkspaceEncryptOperation;
extern NSString *NSWorkspaceDecryptOperation;
extern NSString *NSWorkspaceDestroyOperation;
extern NSString *NSWorkspaceRecycleOperation;
extern NSString *NSWorkspaceDuplicateOperation;

- (BOOL)performFileOperation:(NSString *)operation source:(NSString *)source destination:(NSString *)destination files:(NSArray *)files tag:(int *)tag;  /* DONE */

- (BOOL)unmountAndEjectDeviceAtPath:(NSString *)path;
- (int)extendPowerOffBy:(int)requested;

- (void)slideImage:(NSImage *)image from:(NSPoint)fromPoint to:(NSPoint)toPoint;  /* DONE */

- (void)hideOtherApplications;

- (NSArray *)mountedRemovableMedia;
- (NSArray *)mountNewRemovableMedia;
- (void)checkForRemovableMedia;   /* DONE */

@end

/* Notifications (through the special notification center) */		// userInfo keys:
extern NSString *NSWorkspaceDidLaunchApplicationNotification;		//	@"NSApplicationName"
extern NSString *NSWorkspaceDidMountNotification;			//	@"NSDevicePath"
extern NSString *NSWorkspaceDidPerformFileOperationNotification;	//	@"NSOperationNumber"
extern NSString *NSWorkspaceDidTerminateApplicationNotification;	//	@"NSApplicationName"
extern NSString *NSWorkspaceDidUnmountNotification;			//	@"NSDevicePath"
extern NSString *NSWorkspaceWillLaunchApplicationNotification;		//	@"NSApplicationName"
extern NSString *NSWorkspaceWillPowerOffNotification;
extern NSString *NSWorkspaceWillUnmountNotification;			//	@"NSDevicePath"

#endif // _NSWorkspace_h_
