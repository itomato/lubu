#ident "@(#) NSPathUtilities.h, Rev 1.9, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	NSString protocol extension to deal with Posix file names.

#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>

#ifdef __cplusplus 
extern "C" {
#endif

@interface NSString (NSStringPathExtensions)

- (NSString *)pathExtension;
    /* /Foo/Bar.tiff -> tiff,   /Foo/Bar or /Foo/Bar/ -> "" */

- (NSString *)lastPathComponent;
    /* /Foo/Bar.tiff -> Bar.tiff,   /Foo/Bar or /Foo/Bar/ -> Bar,   Foo -> Foo,  / -> "" */

- (NSString *)stringByDeletingPathExtension;
    /* /Foo/Bar.tiff -> /Foo/Bar,   /A/ -> /A,   / -> /   */

- (NSString *)stringByAppendingPathExtension:(NSString *)str;
    /* /Foo/Bar.x -> /Foo/Bar.x.tiff,   /Foo/ -> /Foo/.tiff,   Foo -> Foo.tiff */

- (NSArray *)stringsByAppendingPaths:(NSArray *)paths;

- (NSString *)stringByDeletingLastPathComponent;
    /* /Foo/Bar.tiff -> /Foo,    /Foo/ -> /,    / -> /,   Foo -> "" */

- (NSString *)stringByAppendingPathComponent:(NSString *)str;
    /* /Foo and /Foo/ -> /Foo/New.tiff,  / -> /New.tiff, "" -> New.tiff */

- (NSString *)stringByExpandingTildeInPath;
    /* Expands ~user/path or ~/path. OK to send to a string without a ~; return value is the same. If user does not exist the same path is returned. */

- (NSString *)stringByAbbreviatingWithTildeInPath;
    /* Replaces user name with ~. */

- (NSString *)stringByStandardizingPath;
    /* Expands ~ in a path.  Removes "/private", if possible.  Condenses "//" and "/./". Replaces any use of ".." in absolute paths by taking the real .. if possible, else it just trims the previous component.  Should raise on failure, never return nil. This does not stat the path, just cleans up the syntax. */

- (NSString *)stringByResolvingSymlinksInPath;
    /* Resolves all symlinks in path, leaving a path with no symlinks and cleaned up. On error the empty string will be returned. */

- (unsigned)completePathIntoString:(NSString * *)outputName caseSensitive:(BOOL)flag matchesIntoArray:(NSArray * *)outputArray filterTypes:(NSArray *)filterTypes;
    /*  Regards "self" as a possible partial filename.  Returns in "outputName" the longest matching string.  Returns 0 and leaves outputName untouched if no matches.  Returns 1 if there's a unique match, and fills in "outputName" to the longest matching filename/username.  If more than one match, fills in "outputName" as usual and returns > 1.  If the "typeList" argument is non-null, each filename is scrutinized to see if it matches one of the types; if not, it is discarded.  If there is an output array pointer given, then all the matching file names are put into an array and returned.  When an array is thus returned, the returned count is ACCURATE; otherwise the returned count is simply ">1" to indicate there is not a unique match.*/

@end

//	These represent the public API to get at standard locations in OpenStep
//
extern NSString *NSHomeDirectory(void);
extern NSString *NSUserName(void);
extern NSString *NSHomeDirectoryForUser(NSString *userName);

extern NSString *NSOpenStepPathForUser(NSString *userName);
extern NSString *NSDotOpenStepPathForUser(NSString *userName);
extern NSString *NSOpenStepPath();
extern NSString *NSLocalPath();
extern NSString *NSLocalePath();

extern NSString *NSTempPath(void);
extern NSString *NSVolatileTempPath(void);
extern NSString *NSPersistentTempPath(void);

extern NSArray *NSStandardApplicationPaths();
extern NSArray *NSStandardFontPaths();
extern NSArray *NSStandardLibraryPaths();

#ifdef __cplusplus 
}
#endif
