#ident "@(#) NSNotification.h, Rev 1.9, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Posting and observing notifications;

#import <Foundation/NSDictionary.h>

@class NSString <NSCopying, NSCoding, NSMutableCopying>, NSDictionary <NSCopying, NSCoding, NSMutableCopying>;

/****************	Notifications	****************/

@interface NSNotification : NSObject <NSCopying, NSCoding>
// Note that notifications may contain extra information, but then that extra data
// must be agreed upon between notifiers and observers

- (NSString *)name;
//	A string denoting the notification

- (id)object;
//	The object of the notification; often is the object that posted a notification about itself;
//	may be nil 

- (NSDictionary *)userInfo;
   /* May return nil */

@end

@interface NSNotification (NSNotificationCreation)

+ (id)notificationWithName:(NSString *)aName object:(id)anObject;
//	 copies name; retains object; retains aUserInfo; aUserInfo may be nil

+ (id)notificationWithName:(NSString *)aName object:(id)anObject userInfo:(NSDictionary *)aUserInfo;
//	copies name; retains object

@end

/****************	Notification Center	****************/

@interface NSNotificationCenter : NSObject {
    @private
    id _lock;
    void *_registry;
    unsigned int _registry_size;
    unsigned int _registry_count;
    int *_niltable;
    unsigned int _niltable_size;
    unsigned int _niltable_count;
    int *_hashtable;
    unsigned int _hashtable_size;
    unsigned int _hashtable_count;
    unsigned int _deleted_count;
    void *_reserved1;
    void *_reserved;
}

+ (NSNotificationCenter *)defaultCenter;
//	a per-task notification center used for generic notifications

- (void)addObserver:(id)observer selector:(SEL)aSelector name:(NSString *)aName object:(id)anObject;
//	observer will perform selector with the notification as argument when notification with
//	given name from given object is posted; observer is not retained which implies that
//	removeObserver: must be called prior to invalidating the observer;
//	If object is nil, observer will get posted whatever the object was;
//	object (when non-nil) is not retained by the notification center which implies that
//	removeObserver: must be called prior to invalidating the object;
//	object identity is pointer equality;
//	If aName is nil, observer will get posted whatever for all notifications that match object.

- (void)postNotification:(NSNotification *)notification;

- (void)removeObserver:(id)observer;
//	Removes all the observations of observer;

- (void)removeObserver:(id)observer name:(NSString *)aName object:(id)anObject;
//	This method will remove all observers with same name and same object (even when object is nil)

@end

@interface NSNotificationCenter (NSNotificationPostingConveniences)

- (void)postNotificationName:(NSString *)aName object:(id)anObject;
- (void)postNotificationName:(NSString *)aName object:(id)anObject userInfo:(NSDictionary *)aUserInfo;

@end

