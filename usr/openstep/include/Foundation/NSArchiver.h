#ident "@(#) NSArchiver.h, Rev 1.10, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import <Foundation/NSCoder.h>
#import <Foundation/NSData.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSMapTable.h>
#import <Foundation/NSHashTable.h>

/************		Archiving: Writing	****************/

@interface NSArchiver:NSCoder {
    @private
    NSMutableData	*mdata;
    NSMapTable		*pointerTable; // pointer -> num
    NSMapTable		*stringTable; // string -> num
    BOOL		noteConditionals; /* when YES, a no-write pass */
    NSHashTable		*ids;	/* Set of all visited IDs */
    NSMutableDictionary	*map;
}

- (id)initForWritingWithMutableData:(NSMutableData *)mdata;
    /* mdata is retained */
    
- (NSMutableData *)archiverData;

- (void)encodeRootObject:(id)rootObject;
    /* Specifies that a data structure might contain backpointers, and writes it as with -encodeObject:.  This method cannot be called recursively.  The implementation works in 2 passes, which implies that write: methods will be performed twice. */

- (void)encodeConditionalObject:(id)object;
    /* Indicates that object is a back pointer, and writes it as with -encodeObject: or writes nil depending on whether object is written by an unconditional -encodeObject: otherwise.  Implies a previous call to -encodeRootObject:. */

+ (NSData *)archivedDataWithRootObject:(id)rootObject;

+ (BOOL)archiveRootObject:(id)rootObject toFile:(NSString *)path;
    /* returns whether successful */

- (void)encodeClassName:(NSString *)trueName intoClassName:(NSString *)inArchiveName;
    /* Enables to write other names than the true name onto the archive;
    Example:
    	[NSArchiver encodeClassName:@"NSView" intoClassName:@"View"]; */

- (NSString *)classNameEncodedForTrueClassName:(NSString *)trueName;
    /* Returns the name used to archive instances of class trueName */

@end

/************		Archiving: Reading		****************/

@interface NSUnarchiver:NSCoder {
    @private
    id			data;
    unsigned		cursor;
    NSZone		*objectZone;
    unsigned		systemVersion;
    signed char		streamerVersion;
    NSMapTable		*pointerTable; // num -> pointer
    NSMapTable		*stringTable; // num -> string
    NSMutableDictionary	*classVersions;	/* className -> version */
    int			lastLabel;
    NSMutableDictionary	*map;
}

- (id)initForReadingWithData:(NSData *)data;

- (void)setObjectZone:(NSZone *)zone;
    /* zone may be NULL */

- (NSZone *)objectZone;

- (BOOL)isAtEnd;
    /* indicates whether or not more data follows. */

- (unsigned)systemVersion;
    /* Returns the version used for writing the stream.
    A version less than 1000 means a pre-OpenStep archive */

+ (id)unarchiveObjectWithData:(NSData *)data;
    /* object is autoreleased */

+ (id)unarchiveObjectWithFile:(NSString *)path;
    /* Returns nil if file not readable */
    /* object is autoreleased */

+ (void)decodeClassName:(NSString *)inArchiveName asClassName:(NSString *)trueName;
    /* Enables to change archive names into better names on read;
    Example:
    	[NSUnarchiver decodeClassName:@"View" asClassName:@"NSView"]; */

- (void)decodeClassName:(NSString *)inArchiveName asClassName:(NSString *)trueName;
    /* Enables to change archive names into better names on read;
    Example:
    	[self decodeClassName:@"View" asClassName:@"NSView"]; */

+ (NSString *)classNameDecodedForArchiveClassName:(NSString *)inArchiveName;
    /* Returns the true classname of objects archived as inArchiveName */

- (NSString *)classNameDecodedForArchiveClassName:(NSString *)inArchiveName;
    /* Returns the true classname of objects archived as inArchiveName */

@end

/************		Exceptions		****************/

/* The archiver may raise the following exception upon dearchiving: */
extern NSString *NSInconsistentArchiveException;

/************		Object call back		****************/

@interface NSObject (NSArchiverCallBack)

- (Class)classForArchiver;
    /* Allows substitution of the class used in archiving,
    thus providing very specialized behavior for this style of coding
    and general behavior for others.
    default is to call -classForCoder. */
    
- (id)replacementObjectForArchiver:(NSArchiver *)archiver;
    /* Allows argument to propose a substitute when encoding;
    nil means no to encode nothing;
    default is to call -replacementObjectForCoder: */ 

@end

/*
 * jak 6/9/95 - InterfaceBuilder must be able to perform the same kind of
 * mapping between old 3.0 NextStep class names and new 4.0 OpenStep
 * class names when it loads the data.classes file.
 */

@interface NSUnarchiver (IB)

+ (NSString*)decodedClassNameForName:(NSString*)oldName;

@end

#if !defined(STRICT_OPENSTEP)

@interface NSArchiver (SunExtensions)

- (void)encodeArrayOfObjCType:(const char *)type count:(unsigned)count at:(const void *)array;

@end

@interface NSUnarchiver (SunExtensions)

- (void)decodeArrayOfObjCType:(const char *)itemType count:(unsigned)count at:(void *)array;
    /* Expects array to be a previously allocated array of count elements of type itemType. */
    /* objects in array are NOT autoreleased: caller must release */

@end

#endif

@interface NSArchiver (EncodeBytesConcreteImplementation)
- (void)encodeBytes:(void *)byteaddr length:(unsigned)length;
@end

@interface NSUnarchiver (EncodeBytesConcreteImplementation)
- (void *)decodeBytesWithReturnedLength:(unsigned *)lengthp;
@end
