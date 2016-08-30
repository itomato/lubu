#ident "@(#) NSNibLoading.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSNibLoading_h_
#define _NSNibLoading_h_


#import <Foundation/NSBundle.h>

@class NSString <NSCopying, NSMutableCopying, NSCoding>;
@class NSDictionary <NSCopying, NSMutableCopying, NSCoding>;

@interface NSBundle(NSNibLoading)

+ (BOOL)loadNibFile:(NSString *)fileName externalNameTable:(NSDictionary *)context withZone:(NSZone *)zone;
    /* This is the primitive that loads the contents of a .nib file.  Context holds key value pairs that can name objects that are referenced by the objects within the nib file (e.g., "NSOwner").  Objects from the nib are allocated in zone. */

+ (BOOL)loadNibNamed:(NSString *)aNibName owner:(id)owner;
   /* A cover method where an external name table is created with owner as the only element with key "NSOwner".  Objects from the nib are allocated in owner's zone. If there is a bundle for owner's class, this method looks in that bundle for a nib with the given file name.  Otherwise, it looks in the mainBundle. */

- (BOOL)loadNibFile:(NSString*)fileName externalNameTable:(NSDictionary *)context withZone:(NSZone *)zone;
    /* This is the primitive that loads the contents of a .nib file.  Context holds key value pairs that can name objects that are referenced by the objects within the nib file (e.g., "NSOwner").  Objects from the nib are allocated in zone. Using this method promotes better modularity than the class method.*/

@end


@interface NSObject(NSNibAwaking)
- (void)awakeFromNib;

#ifndef STRICT_OPENSTEP
- (id)nibInstantiate;
#endif // STRICT_OPENSTEP

@end

 
#endif // _NSNibLoading_h_
