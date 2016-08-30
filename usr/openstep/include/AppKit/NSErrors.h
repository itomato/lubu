#ident "@(#) NSErrors.h, Rev 1.4, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

/* Contains error numbers for the AppKit. */

#import <Foundation/NSString.h>

// The following strings are the names of exceptions the AppKit can raise

extern NSString *NSTextLineTooLongException;
extern NSString *NSTextNoSelectionException;
extern NSString *NSWordTablesWriteException;
extern NSString *NSWordTablesReadException;
extern NSString *NSTextReadException;
extern NSString *NSTextWriteException;
extern NSString *NSPasteboardCommunicationException;
extern NSString *NSPrintingCommunicationException;
extern NSString *NSAbortModalException;
extern NSString *NSAbortPrintingException;
extern NSString *NSIllegalSelectorException;
extern NSString *NSAppKitVirtualMemoryException;
extern NSString *NSBadRTFDirectiveException;
extern NSString *NSBadRTFFontTableException;
extern NSString *NSBadRTFStyleSheetException;
extern NSString *NSTypedStreamVersionException;
extern NSString *NSTIFFException;
extern NSString *NSPrintPackageException;
extern NSString *NSBadRTFColorTableException;
extern NSString *NSDraggingException;
extern NSString *NSColorListIOException;
extern NSString *NSColorListNotEditableException;
extern NSString *NSBadBitmapParametersException;
extern NSString *NSWindowServerCommunicationException;
#ifndef	STRICT_OPENSTEP
extern NSString *NSWindowServerProtocolException;
#endif
extern NSString *NSFontUnavailableException;
extern NSString *NSPPDIncludeNotFoundException;
extern NSString *NSPPDParseException;
extern NSString *NSPPDIncludeStackOverflowException;
extern NSString *NSPPDIncludeStackUnderflowException;
extern NSString *NSRTFPropertyStackOverflowException;
extern NSString *NSAppKitIgnoredException;
extern NSString *NSBadComparisonException;
extern NSString *NSImageCacheException;
extern NSString *NSNibLoadingException;
extern NSString *NSBrowserIllegalDelegateException;

