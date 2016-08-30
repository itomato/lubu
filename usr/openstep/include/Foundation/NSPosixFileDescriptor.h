#ident "@(#) NSPosixFileDescriptor.h, Rev 1.15, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSData.h>

/* The purpose of this object is to offer cover methods for the Posix
 * functions operating on file descriptors. This is a low level API, and
 * high level APIs should be prefered to this one.
 *
 * In particular, cover the methods in NSData.h for getting an NSData
 * from a file should be preferred to these ones.
 * 
 */

typedef enum {
	NSPosixNoActivity = 0,
	NSPosixReadableActivity = 1,
	NSPosixWritableActivity = 2,
	NSPosixExceptionalActivity = 4
} NSPosixFileActivities;	// may be |'d

/***************	Exceptions		***********/

/* All methods may raise NSPosixFileOperationFailed,
 * which format is: 
 *	the name of the method raising, errno
 */

#define NSPosixFileOperationFailed 123456

/***************	Class		***********/

@interface NSPosixFileDescriptor:NSObject {
@public
	short		fd;
	char		activity;
	char		flags;
	id		delegate;
	id		_private;
}

/***************	Accessing directly stdin, etc...	***********/

- initWithStandardInput;
- initWithStandardOutput;
- initWithStandardError;

- initWithFileDescriptor:(int)fd;
	// fd is not closed upon deallocation

/***************	Cover open()	***********/

/* file descriptor is freed when object is deallocated */

- initWithPath:(NSString *)path;
	/* ReadOnly */
	
- initWithPath:(NSString *)path
	flags:(int)flags;
	/* flags as in open() but not O_CREAT */

- initWithPath:(NSString *)path
	flags:(int)flags
	createMode:(int)mode;
	/* same arguments as in open() */

/***************	instance access	***********/

- (int)fd;

- (void)setDelegate:delegate;

- delegate;

- (void)monitorActivity:(NSPosixFileActivities)activity;
	/* delegate will be informed  of activity occurring
	 * during modes of the runLoop for which this fd was added
	 */

- (NSPosixFileActivities)activity;

- (void)monitorActivity:(NSPosixFileActivities)activity
	delegate:delegate;
	/* convenience: schedules delegate for notification of activity
	 * in the default runLoop mode
	 */

- (void)ceaseMonitoringActivity;
	/* convenience: stops delegate notification of activity in the
	 * default runLoop mode
	 */

/***************	Covers for read() and write()	***********/

- (NSData *)readEntireFile;
	/* seek position is set to end of file afterwards */

- (NSData *)readRestOfFile;
	/* from the seek position;
	 * seek position is set to end of file afterwards
	 */

- (NSData *)readFileRange:(NSRange)range;
	/* seeks to range.location, and then reads range.length bytes;
	 * seek position is set to range.location + range.length
	 * afterwards
	 */

- (NSData *)readFileLength:(unsigned)length;
	/* reads at most length bytes; UINT_MAX can be given to read
	 * the entire file.
	 * seek position is incremented by [data length] afterwards
	 */

- (void)writeData:(NSData *)data;
	/* appends data bytes onto file */

- (void)writeData:(NSData *)data
		range:(NSRange)range;
	/* range specifies the portion of data that must be appended onto file */

/***************	Covers for mmap()	***********/

- (NSData *)mapFileRange:(NSRange)range;
	/* seek position is set to range.location + range.length afterwards */

- (NSData *)mapFile;
	/* Entire file is mapped; seek position is set to beginning */

/***************	Cover for lseek()		***********/

- (unsigned)position;

- (unsigned)seekToEnd;

- (unsigned)seekToPosition:(unsigned)position;

/***************	Covers for ftruncate(), fync()	***********/

- (void)truncateAtPosition:(unsigned)position;

- (void)synchronize;

@end


/***************	Delegate methods		***********/

@interface NSObject (NSPosixFileDescriptorDelegateMethods)

- (void)activity:(NSPosixFileActivities)activity
	posixFileDescriptor:(NSPosixFileDescriptor *)pfd;

@end

#endif // STRICT_OPENSTEP

