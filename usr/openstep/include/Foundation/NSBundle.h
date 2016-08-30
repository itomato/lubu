#ident "@(#) NSBundle.h, Rev 1.18, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Dynamically loadable code with resources

#import <Foundation/NSArray.h>

/* 
 * This module is a cover/replacement for the old NXBundle
 * with some foundation conveniences;
 */

/***************	Class		***********/

@interface NSBundle:NSObject {
    @private
    id		_realBundle;
    BOOL	isLoaded;
}

+ (NSBundle *)bundleWithPath:(NSString *)path;

- (id)initWithPath:(NSString *)path;
    /* Path is the path for the bundle itself, e.g. "/NextApps/MyApp/foo.bundle";
    returns nil if no bundle at that path */

+ (NSBundle *)mainBundle;

+ (NSBundle *)bundleForClass:(Class)aClass;

+ (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext inDirectory:(NSString *)bundlePath;
    /* Returns nil of that path; ext may be nil */

#ifndef STRICT_OPENSTEP
+ (NSArray *)loadedBundles;
    /* somewhat of a misnomer - returns an array of all bundles that have been created, not just the ones that have been loaded.*/
#endif

- (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext;

- (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext inDirectory:(NSString *)subpath;

- (NSArray *)pathsForResourcesOfType:(NSString *)ext inDirectory:(NSString *)subpath;

- (NSString *)bundlePath;

- (NSString *)resourcePath;

- (Class)classNamed:(NSString *)className;

- (Class)principalClass;

- (NSString *)localizedStringForKey:(NSString *)key value:(NSString *)value table:(NSString *)tableName;

#ifndef STRICT_OPENSTEP
- (NSDictionary *)infoDictionary;
#endif

@end


extern NSString *NSBundleDidLoadNotification;
extern NSString *NSLoadedClasses;	// notification key

//Sun's implemetation for NSLocalizedString that uses gettext. 
#define NSLocalizedString(string,comment) \
	    NSLocalizedStringFromTable(string,nil,comment)
#define NSLocalizedStringFromTable(string,table,comment) \
	    NSLocalizedStringFromTableInBundle(string,table,[NSBundle mainBundle],comment)
#define NSLocalizedStringFromTableInBundle(string,tab,bundle,comment) \
	    [bundle localizedStringForKey:string value:@"" table:tab]

