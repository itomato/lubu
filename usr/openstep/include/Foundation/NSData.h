#ident "@(#) NSData.h, Rev 1.4, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Object container for bags of bytes

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

/* The motivation for this interface is
	- to have an object cover for bags of bytes
	- to hide low-level vm primitives (e.g. the difference between malloc() and vm_allocate())
*/

/***************	Read only Abstract Class		***********/

@interface NSData:NSObject <NSCopying, NSMutableCopying, NSCoding>
/* NOTES:
    -copyWithZone: and -copy guarantee an immutable returned value;
    -isEqual: checks argument is an NSData, and then byte-for-byte identity;
    NSData objects are always encoded/decoded as a Property List.  Therefore mutability and class are not preserved for distribution or persistency.
     */

- (unsigned)length;
    /* The number of bytes in the bag of bytes */
    
- (const void *)bytes;
    /* Direct access to the bag of bytes; Read-only */

@end

@interface NSData (NSExtendedData)

- (NSData *)subdataWithRange:(NSRange)range;
    /* Returns an NSData that snapshots a range; 
    [self length] must be greater than range.location + range.length;
    Very efficient: no copy of the bytes is done if initial range is immutable, and if big mutable are virtually copied */
     
- (void)getBytes:(void *)buffer;
    /* Copies all the bytes into buffer; Efficient (virtual) copy will be done if appropriate */
    
- (void)getBytes:(void *)buffer length:(unsigned)length;
    /* Copies bytes (but at most length) into buffer; 
    Given length is the maximum length of the buffer, the bag of bytes may hold fewer bytes;
    Efficient (virtual) copy will be done if appropriate */

- (void)getBytes:(void *)buffer range:(NSRange)range;
    /* Copies bytes (but at most length) into buffer; 
    Range start needs to be within the bag of bytes;
    Efficient (virtual) copy will be done if appropriate */

- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
    /* writes a given file, using a ~ file if useAuxiliaryFile (to have atomic update of file);
    returned value indicates success */

- (BOOL)isEqualToData:(NSData *)other;
    /* Byte-for-byte identity check */

- (NSString *)description;
    /* Produces a string that can be read by the ASCII parser */

@end

/***************	Read/Write Abstract Class	***************/

@interface NSMutableData:NSData

- (void *)mutableBytes;
    /* Returns a pointer to the bag of bytes that can be used for writing;
    [data mutableBytes] is identical to [data bytes] (but types differ) */

- (void)setLength:(unsigned)length;
    /* Can be used to truncate or to extend; 
    When extending, the extension area is zero-filled */

@end

@interface NSMutableData (NSExtendedMutableData)

- (void)replaceBytesInRange:(NSRange)range withBytes:(const void *)bytes;
    /* Substitutes bytes; 
    Range start needs to be within the bag of bytes or just at the end;
    Efficient (virtual) copy will be done if appropriate */

- (void)resetBytesInRange:(NSRange)range;
    /* Substitutes zeros in range; 
    Range start needs to be within the bag of bytes or just at the end;
    Efficient (virtual) copy will be done if appropriate */

- (void)appendBytes:(const void *)bytes length:(unsigned)length;
    /* Appends bytes; 
    Efficient (virtual) copy will be done if appropriate */

- (void)appendData:(NSData *)other;
    /* Appends another bag of bytes */

- (void)increaseLengthBy:(unsigned)extraLength;
    /* appends a zero-filled area of length extraLength;
    Efficient shortcut for [self setLength:[self length]+extraLength] */

@end

/***************	Immutable Creation		***************/

@interface NSData (NSDataCreation)

+ (id)allocWithZone:(NSZone *)zone;
    /* Create an uninitialized instance of a concrete class;
    substitutes a concrete class if called with NSData;
    +alloc can also be used to that effect */

+ (id)data;
    /* Creates an autorelease empty bag of bytes; 
    mostly useful when called with NSMutableData */

+ (id)dataWithBytes:(const void *)bytes length:(unsigned)length;
    /* Creates an autorelease bag of bytes; 
    leaves bytes untouched */

+ (id)dataWithBytesNoCopy:(void *)bytes length:(unsigned)length;
    /* Creates an autorelease bag of bytes; 
    bytes will be freed using free() when data is released */

+ (id)dataWithContentsOfFile:(NSString *)path;
    /* Creates an autorelease bag of bytes; 
    reads all bytes from given file; file is opened and closed;
    returns nil on error */

+ (id)dataWithContentsOfMappedFile:(NSString *)path;
    /* Creates an autorelease bag of bytes; 
    reads all bytes from given file; file is mapped.
    Because of file mapping restrictions, this should only be used if file is guaranteed to exist until data disappears*/

- (id)initWithBytesNoCopy:(void *)bytes length:(unsigned)length;
    /* bytes will be freed using free() upon freeing of object;
    designated initializer */

- (id)initWithBytes:(const void *)bytes length:(unsigned)length;
    /* leaves bytes untouched */
    
- (id)initWithData:(NSData *)data;

- (id)initWithContentsOfFile:(NSString *)path;
    /* reads all bytes from given file; file is opened and closed;
    returns nil on error */
    
- (id)initWithContentsOfMappedFile:(NSString *)path;
    /* reads all bytes from given file; file is mapped.
    Because of file mapping restrictions, this should only be used if file is guaranteed to exist until data disappears*/
    
@end

/***************	Mutable Creation		***********/

@interface NSMutableData (NSMutableDataCreation)

+ (id)allocWithZone:(NSZone *)zone;
    /* Create an uninitialized instance of a concrete class;
    substitutes a concrete class if called with NSMutableData;
    +alloc can also be used to that effect */
     
+ (id)dataWithCapacity:(unsigned)aNumItems;
    /* Creates an autoreleased mutable data;
    aNumItems is only a hint */

+ (id)dataWithLength:(unsigned)length;
    /* Creates an autoreleased mutable data, zero-filled */

- (id)initWithCapacity:(unsigned)capacity;
    /* just a hint for ultimate length; length is set to 0 */

- (id)initWithLength:(unsigned)length;
    /* provides zero-fill data of length length*/

@end

