#ident "@(#) NSPrintOperation.h, Rev 1.8, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#ifndef _NSPrintOperation_h_
#define _NSPrintOperation_h_

/*
NSPrintOperation controls the generation of PostScript code.  It is
used to generate both Encapsulated PostScript output and PostScript
print jobs.  It uses a specified View instance to produce the
PostScript -- it doesn't do any PostScript generation itself.  Also,
most parameters for PostScript generation are specified to the object
through a PrintInfo object.  This object controls the user interface
(the Print panel), the printing DPS context, and state for the
particular operation, like job page order, the output stream, a copy of
the PrintInfo, etc.

The object does keep a private instance of PrintInfo during the
operation.  This should contain the settings that need to be preserved
to duplicate the operation.  It may be copied at the end of the
operation to be used in a subsequent operation.  So Print panel values
like the starting and ending pages should be stored in the operation's
PrintInfo, but the current page number should not -- it won't be reset
during a subsequent operation.

If the current NSDPSContext's purpose is NSCopying or NSPrinting, there
will be a current NSPrintOperation instance.  Drawing code should first
check to see whether printing or copying is going on, and then it can
assume there is an NSPrintOperation that can be consulted if needed.

The standard implementation for the print: method is very simple.  This
code uses the global PrintInfo:

- print:sender {
    [[NSPrintOperation printOperationWithView:self] runOperation];
    return self;
}

A document might have a documentPrint: method like:

- documentPrint:sender {
    [[NSPrintOperation printOperationWithView:[self documentView] printInfo:[self printInfo]] runOperation];
    return self;
}

An application can produce a print job without the Print panel using
code like this.  Note that the PrintInfo object would need to contain
any non-default settings that would normally be collected from the
Print panel -- for instance, one might use a copy of the PrintInfo from
a previous print job.

- (void)printWithNoPanel {
    NSPrintOperation *op;
    
    op = [NSPrintOperation printOperationWithView:[self myView] printInfo:[self previousPrintInfo]];
    [op setShowPanels:NO];
    [op runOperation];
}


*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>

@class NSDPSContext;
@class NSPrintPanel;
@class NSView;
@class NSPrintInfo <NSCopying, NSCoding>;
@class NSMutableData;

typedef enum _NSPrintingPageOrder {
    NSDescendingPageOrder		= (-1),
    NSSpecialPageOrder			= 0, // Tells spooler to not rearrange
    NSAscendingPageOrder		= 1,
    NSUnknownPageOrder			= 2  // No page order written out
} NSPrintingPageOrder;


/***** Exceptions *****/
extern NSString *NSPrintOperationExistsException;
#ifndef port_t
typedef unsigned long port_t;
#endif


@interface NSPrintOperation : NSObject
{
@private
    NSView *view;
    NSPrintInfo *printInfo;
    BOOL isEPS;
    BOOL showPanels;
    NSRect epsBounds;
    NSMutableData *epsStream;
    NSDPSContext *context;
    NSPrintingPageOrder pageOrder;
    NSPrintPanel *printPanel;
     id _accessoryView;
    NSMutableData *printStream;
    port_t replyPort;
    BOOL releaseData;
    void *jobVars;
}

/* The following methods create an NSPrintOperation instance and make it the current print operation for the thread.  They raise an exception if there is already a current print operation.  These are the recommended methods for creating an NSPrintOperation instance.
*/
+ (NSPrintOperation *)printOperationWithView:(NSView *)aView;		// Use the global PrintInfo.
+ (NSPrintOperation *)printOperationWithView:(NSView *)aView printInfo:(NSPrintInfo *)aPrintInfo;

+ (NSPrintOperation *)EPSOperationWithView:(NSView *)aView insideRect:(NSRect)rect toData:(NSMutableData *)data;
+ (NSPrintOperation *)EPSOperationWithView:(NSView *)aView insideRect:(NSRect)rect toData:(NSMutableData *)data printInfo:(NSPrintInfo *)aPrintInfo;
+ (NSPrintOperation *)EPSOperationWithView:(NSView *)aView insideRect:(NSRect)rect toPath:(NSString *)path printInfo:(NSPrintInfo *)aPrintInfo;

/* Set/get the current print operation for this thread.  If this is nil, there is no current operation.
*/
+ (NSPrintOperation *)currentOperation;
+ (void)setCurrentOperation:(NSPrintOperation *)operation;


/* Designated initializer.  If called directly, returns a print job operation.  The specified PrintInfo object is copied -- that instance is *not* used in the operation.
*/
- (id)initWithView:(NSView *)aView printInfo:(NSPrintInfo *)aPrintInfo;

/* Initializer for an EPS operation.
*/
- (id)initEPSOperationWithView:(NSView *)aView insideRect:(NSRect)rect toData:(NSMutableData *)data printInfo:(NSPrintInfo *)aPrintInfo;

/* Returns whether the operation is doing EPS generation ("copying") or building a print job ("printing").
*/
- (BOOL)isEPSOperation;

/* Do the print operation.  Returns YES if the operation completed successfully, NO if there was an error or the user cancelled the operation.  This can only be called once.  Create a new NSPrintOperation instance for each operation.  When this method completes, the object is removed from being the current operation if it is the current operation.
*/
- (BOOL)runOperation;

/* Control whether panels are shown during the operation (doesn't necessarily include alerts).
*/
- (void)setShowPanels:(BOOL)flag;
- (BOOL)showPanels;


/* Allow developers to supply an accessory view
*/
- (void)setAccessoryView:(NSView *)aView;
- (NSView *)accessoryView;

/* Set/get the current PrintInfo object for the operation.  Setting the PrintInfo object should be done very carefully.  The safest approach is to copy all the settings from the new object into current object, rather than replacing the object.
*/
- (void)setPrintInfo:(NSPrintInfo *)aPrintInfo;
- (NSPrintInfo *)printInfo;

/* The view being printed.
*/
- (NSView *)view;

/* The current page number.
*/
- (int)currentPage;

/* Set/get the page order that will be used to generate the pages in this job.  This is the physical page order of the pages.  It depends on the stacking order of the printer, the capability of the app to reverse page order, etc.
*/
- (void)setPageOrder:(NSPrintingPageOrder)order;
- (NSPrintingPageOrder)pageOrder;

/* The DPS context for the output of this operation.
*/
- (NSDPSContext *)context;

/* Create the DPS context using the current PrintInfo settings, stream, etc.  Should not be called directly.  This is called before any output is generated by the operation.
*/
- (NSDPSContext *)createContext;

/* Destroy the DPS context.  This is called at the end of the operation.  Should not be called directly.
*/
- (void)destroyContext;

/* This spools the job, calls the Preview app, etc. -- whatever needs to be done to complete the operation.  Return YES is operation was completely successful, NO otherwise.  It is called after the job has been completely generated.  Should not be called directly.
*/
- (BOOL)deliverResult;

/* Clean up an operation after it has been completed.  The object removes itself from being the current operation if it is the current operation.  
*/
- (void)cleanUpOperation;

@end

 
#endif // _NSPrintOperation_h_
