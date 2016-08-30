#ident "@(#) NSMenuItem.h, Rev 1.5, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	All rights reserved.

#import <Foundation/Foundation.h>

@protocol NSMenuItem <NSObject>

- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (id)target;
- (void)setTarget:(id)anObject;
- (SEL)action;
- (void)setAction:(SEL)aSelector;
- (int)tag;
- (void)setTag:(int)anInt;
- (BOOL)isEnabled;
- (void)setEnabled:(BOOL)flag;
- (NSString *)keyEquivalent;

- (void)setKeyEquivalent:(NSString *)aKeyEquivalent;

- (BOOL)hasSubmenu;
@end


