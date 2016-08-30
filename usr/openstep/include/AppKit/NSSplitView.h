#ident "@(#) NSSplitView.h, Rev 1.3, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import "NSView.h"

@interface NSSplitView : NSView
{
    id	_delegate;
}

- (void)setDelegate:(id)anObject;
- (id)delegate;
- (void)adjustSubviews;
- (float)dividerThickness;
- (void)drawDividerInRect:(NSRect)aRect;

@end

@interface NSObject(NSSplitViewDelegate)
- (void)splitView:(NSSplitView *)sender resizeSubviewsWithOldSize:(NSSize)oldSize;
- (void)splitView:(NSSplitView *)sender constrainMinCoordinate:(float *)min maxCoordinate:(float *)max ofSubviewAt:(int)offset;
- (void)splitViewWillResizeSubviews:(NSNotification *)notification;
- (void)splitViewDidResizeSubviews:(NSNotification *)notification;
@end

/* Notifications */
extern NSString *NSSplitViewDidResizeSubviewsNotification;
extern NSString *NSSplitViewWillResizeSubviewsNotification;
