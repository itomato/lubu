#ident "%Z% %M%, Rev %I%, %D%"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
//#import <objc/objc-runtime.h>

@interface NSProcessInfo:NSObject {
    @private	
    NSDictionary	*environment;
    NSArray		*arguments;
    NSString		*hostName;    
    NSString		*name;    
}

+ (NSProcessInfo *)processInfo;	
    // Returns the NSProcessInfo object for your process.
    // Initialized on first call.

- (NSDictionary *)environment;
    // Returns a dictionary of variables defined for the environment from which the process was launched. 

- (NSArray *)arguments;
    // Returns the arguments (as NSStrings) from the command line.

- (NSString *)hostName;
    // The name of the machine.

- (NSString *)processName;
    // The name of the process.  This is the name under which this program's user defaults domain is created, and the name used in error messages.  It does not have to uniquely identify the process.  Initially it is read from argv[0], or if that fails MachO is used.

- (void)setProcessName:(NSString *)newName;
    // Sets the name.  Warning:  Things like userDefaults might depend on the appName, be sure you know what you are doing when you change this.  Also, this set is not thread-safe.

- (NSString *)globallyUniqueString;
    // generates a new string on each call; uses hostName, processName, process id, timestamp, and counter to be globally unique string
@end

