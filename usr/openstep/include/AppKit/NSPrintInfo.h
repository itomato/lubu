#ident "@(#) NSPrintInfo.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSPrintInfo_h_
#define _NSPrintInfo_h_

/*
NSPrintInfo is a data container for parameters that help control the generation of PostScript output.  It is passed to the NSPrintOperation object, which makes a copy of it to use during the operation.
*/

#import <Foundation/NSObject.h>
#import <AppKit/NSGraphics.h>

@class NSPrinter <NSCopying, NSCoding>;

typedef enum _NSPrintingOrientation {
    NSPortraitOrientation		= 0,
    NSLandscapeOrientation		= 1
} NSPrintingOrientation;

typedef enum _NSPrintingPaginationMode {
    NSAutoPagination			= 0,
    NSFitPagination			= 1, // Force image to fit on one page
    NSClipPagination			= 2  // Let image be clipped by page
} NSPrintingPaginationMode;


@interface NSPrintInfo : NSObject <NSCopying, NSCoding>
{
@private
    NSMutableDictionary	*dictionary;
}


/* Set/get the paper attributes.  The set methods in this group may change other values in the group to keep all three values (type, size, and orientation) consistent.  To avoid this behavior, set the values in the dictionary directly.
 */
- (void)setDocumentName:(NSString *)name;
- (NSString *)documentName;
- (void)setPaperName:(NSString *)name;
- (NSString *)paperName;
- (void)setPaperSize:(NSSize)aSize;
- (NSSize)paperSize;
- (void)setOrientation:(NSPrintingOrientation)orientation;
- (NSPrintingOrientation)orientation;

/* Covers for a number of the keys on the dictionary.
*/
- (void)setLeftMargin:(float)margin;
- (void)setRightMargin:(float)margin;
- (void)setTopMargin:(float)margin;
- (void)setBottomMargin:(float)margin;
- (float)leftMargin;
- (float)rightMargin;
- (float)topMargin;
- (float)bottomMargin;
- (void)setHorizontallyCentered:(BOOL)flag;
- (BOOL)isHorizontallyCentered;
- (void)setVerticallyCentered:(BOOL)flag;
- (BOOL)isVerticallyCentered;
- (void)setHorizontalPagination:(NSPrintingPaginationMode)mode;
- (NSPrintingPaginationMode)horizontalPagination;
- (void)setVerticalPagination:(NSPrintingPaginationMode)mode;
- (NSPrintingPaginationMode)verticalPagination;

/* If job features are not implemented on this new printer, flush them when the printer is set. */
- (void)setPrinter:(NSPrinter *)pr;
- (NSPrinter *)printer;

- (void)setJobDisposition:(NSString *)disposition;
- (NSString *)jobDisposition;

/* Called when a print operation is about to start.  It allows this object to set default values for any keys that are not already set.
*/
- (void)setUpPrintOperationDefaultValues;

/* The dictionary containing the key/values for this object.
*/
- (NSMutableDictionary *)dictionary;

/* Create a PrintInfo from an existing NSDictionary.  Designated initializer.
*/
- (id)initWithDictionary:(NSDictionary *)aDict;

/* NOT the designated initializer.  Init with no values.
*/


/* Set/get the shared PrintInfo instance.  This defines the settings for the PageLayout panel and print operations that will be used if no PrintInfo is specified for those operations.  This PrintInfo instance can be thought of as being "shared" among documents in the app.  This should never be set to nil.
*/
+ (void)setSharedPrintInfo:(NSPrintInfo *)printInfo;
+ (NSPrintInfo *)sharedPrintInfo;


/* Set/get the user's default printer.
*/
+ (NSPrinter *)defaultPrinter;
+ (void)setDefaultPrinter:(NSPrinter *)pr;

/* Get the size of a paper name */
+ (NSSize)sizeForPaperName:(NSString *)name;

@end


/* The list below defines the keys in the dictionary, and the types that they are assumed to be.  Values that are not objects are stored as NSValues.

		Dictionary Key		   Type			Description
		--------------		   ----			-----------	*/
extern NSString *NSPrintPaperName;	// NSString		Paper name: Letter, Legal, etc.
extern NSString *NSPrintPaperSize;	// NSSize		Height and width of paper
extern NSString *NSPrintOrientation;	// NSPrintingOrientation Portrait/Landscape
extern NSString *NSPrintLeftMargin;	// float		Margins, in points:
extern NSString *NSPrintRightMargin;	// float
extern NSString *NSPrintTopMargin;	// float
extern NSString *NSPrintBottomMargin;	// float
extern NSString *NSPrintHorizontallyCentered;	// BOOL			Pages are centered horizontally.
extern NSString *NSPrintVerticallyCentered;	// BOOL			Pages are centered horizontally.
extern NSString *NSPrintHorizontalPagination;// NSPrintingPaginationMode
extern NSString *NSPrintVerticalPagination;	// NSPrintingPaginationMode

extern NSString *NSPrintScalingFactor;	// float		Scale before pagination.
extern NSString *NSPrintAllPages;	// BOOL			Include all pages in the job.
extern NSString *NSPrintReversePageOrder;// BOOL		Print last page first.
extern NSString *NSPrintFirstPage;	// int			First page to print in job.
extern NSString *NSPrintLastPage;	// int			Last page to print in job.
extern NSString *NSPrintCopies;		// int			Number of copies to spool.
extern NSString *NSPrintPagesPerSheet;	// int
extern NSString *NSPrintJobFeatures;	// NSMutableDictionary	Key = Name.  Value = Setting.
						// Feature names come from the NSPrinter/PPD info.
						// Example:  Key=@"Resolution" Value=@"600dpi"
extern NSString *NSPrintPaperFeed;	// NSString		Generally, the input slot.
extern NSString *NSPrintManualFeed;	// @"NSPrintManualFeed" refers to manual feed.
extern NSString *NSPrintPrinter;	// NSPrinter		Printer to use for print job.
extern NSString *NSPrintJobDisposition;	// NSString		What to do with the print stream:
extern NSString *NSPrintSavePath;	// NSString		Path if disposition = @"NSSave".
extern NSString *NSPrintDocumentName;   // NSString		Document name to be printer on the burst page.

#ifndef STRICT_OPENSTEP
#ifdef FAX_SUPPORT
extern NSString *NSPrintFaxReceiverNames;// NSArray of NSStrings  Names of receivers of the fax.
extern NSString *NSPrintFaxReceiverNumbers;// NSArray of NSStrings  Phone numbers of receivers.
							     // Must parallel NSFaxReceiverNames.
extern NSString *NSPrintFaxSendTime;	// NSDate		When to send the fax.
extern NSString *NSPrintFaxUseCoverSheet;// BOOL		Whether to use a cover sheet.
extern NSString *NSPrintFaxCoverSheetName;// NSString		The cover sheet to use.
extern NSString *NSPrintFaxReturnReceipt;// BOOL		Whether to send mail when fax is sent.
extern NSString *NSPrintFaxHighResolution;// BOOL		Whether to send at low resolution.
extern NSString *NSPrintFaxTrimPageEnds;// BOOL			Whether to trim page ends or send complete pages.
extern NSString *NSPrintFaxModem;	// NSPrinter		The fax modem to use.
#endif
#endif

/* Valid values for job disposition */
extern NSString *NSPrintSpoolJob;	// @"NSPrintSpoolJob"	Normal print job.
#ifndef STRICT_OPENSTEP
#ifdef FAX_SUPPORT
extern NSString *NSPrintFaxJob;		// @"NSPrintFaxJob"	Fax job.
#endif
#endif
extern NSString *NSPrintPreviewJob;	// @"NSPrintPreviewJob"	Send to Preview app.
extern NSString *NSPrintSaveJob;	// @"NSPrintSaveJob"	Save to a file.
extern NSString *NSPrintCancelJob;	// @"NSPrintCancelJob"	Save to a file.
 
#endif // _NSPrintInfo_h_
