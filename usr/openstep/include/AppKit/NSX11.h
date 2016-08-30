#ident "@(#) NSX11.h, Rev 1.12, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      All rights reserved.

// This file includes a number of convenience routines used to access
// window system facilities when running OpenStep in the X11 environment.
// In general these routines are designed to duplicate functions that
// Openstep programmers might have used when programming OpenStep
// applications on other window system platforms. Note that these
// routines do not represent elements of the OpenStep specification.

#ifndef _NSX11_H_
#define _NSX11_H_

#if !defined(STRICT_OPENSTEP)
#import <objc/objc.h>
#import <Foundation/NSGeometry.h>

@class NSEvent <NSCopying, NSCoding>;
@class NSWindow;

#ifdef  __cplusplus
extern "C" {
#endif

extern void NSWindowCurrentMouse(NSWindow* self, float* rx, float* ry);

extern BOOL NSWindowStillDown(NSWindow* self, NSEvent* nsEvent);

extern void NSSetWindowLevel(NSWindow* self, unsigned int level);

extern NSPoint NSMouseScreenLocation(NSWindow* window);

extern void NSHideAppsExcept(unsigned long ctxtid);

extern void NSActivateContextNumber(unsigned long ctxtid);

extern void NSActivateNextApp();

#ifdef  __cplusplus
}
#endif

#endif

#endif // _NSX11_H_
