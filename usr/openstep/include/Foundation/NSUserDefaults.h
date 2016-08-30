#ident "@(#) NSUserDefaults.h, Rev 1.11, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

/*
The NSUserDefaults object offers methods for manipulating a user's defaults. Each user has a set of defaults which is divided into domains.  Each domain  has a name and a dictionary of default/value pairs.  The default is a string key and the value can be any plist object (dictionary, array, string, or data). Each application can create one or more domains.  There are also predefined NSGlobalDomain and NSArgumentDomain domains.  The NSGlobalDomain is for defaults that are meant to be seen by all applications.  The NSArgumentDomain is composed of defaults parsed from the application's arguments.  

The NSUserDefaults object lets an application manipulate ALL of the domains for a particular user.  It also lets the application set up a searchlist which is a SUBSET of all the user's domains.  The main job of NSUserDefaults is to provide a way to get a value for a default.  To get a value for a certain default, ONLY the domains in the searchlist are searched.  The first value found is returned, if no value is found nil is returned.  If a domain is not in the searchlist it is not searched.

The standard simple way that NSUserDefaults are most commonly used is as follows.  First use the standardUserDefaults factory method to get the NSUserDefaults object.  Then use the objectForKey:, setObject:forKey:, and removeObjectForKey: methods to set and get user defaults.  The standardUserDefaults returns a global NSUserDefaults object with a searchList already initialized.  

The rest of the API is for more complex defaults management.  You can create your own domains, modify any domain, set up a custom searchList, and even control the synchronization of the in-memory and on-disk defaults representations.  

A user can create either persistent or volatile domains.  Persistent domains are permanent and last past the life of the NSUserDefaults object.  Any changes to the persistent domains are committed to disk.  Volatile domains only last as long as the NSUserDefaults object.  The NSGlobalDomain domain is persistent, the NSArgumentDomain is volatile.  

If no persistent defaults exist, then NSUserDefaults tries to find pre4.0 defaults and copy them over.  Also, an empty NSGlobalDomain is always inserted at init time if it is not already present.

Things to watch out for:
  User defaults are not thread safe.  
  The autosave to disk depends on a run-loop being present.

*/

#import <Foundation/NSDictionary.h>
#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>

extern NSString *NSGlobalDomain;
extern NSString *NSArgumentDomain;
extern NSString *NSRegistrationDomain;


@class NSLockedPropertyListFile;

@interface NSUserDefaults:NSObject {
    NSLockedPropertyListFile		*_dlplf;    /* The _dlplf containing defaults info */
    NSMutableArray	*_search;   /* Current search list set up by user */
    NSMutableDictionary	*_temp;     /* Dictionary of volatile domains     */
    id                  _resolver;
    NSMutableDictionary *_dictRep;  /* cache of dictionaryRepresenation */
    NSString            *_appDomain;    
    NSString            *_path;
}

/*********** Getting the shared instance ***********/

+ (NSUserDefaults *)standardUserDefaults;
	/* Returns the shared instance of user defaults.  If it doesn't yet exist, it is created first.  The search list starts out with four domains:  The NSArgumentDomain is first, then a domain with the process' name, then the NSGlobalDomain, then the NSRegistrationDomain.  The shared instance is provided as a convenience.  It is still possible to create as many other instances as you need.  If you modify the search list of the shared instance, it will stay modified.  That is, the modified search list will become the search list for the shared instance even if you call this method again. */



/*********** Searching ***********/

- (id)objectForKey:(NSString *)defaultName;
	/* Searches the domains specified by searchList for the given default.  This search starts at the 0 index of the array. If the default is found its value is returned.  Otherwise nil is returned. */

/*********** Changing the app domain ************/

- (void)setObject:(id)value forKey:(NSString *)defaultName;
	/* Sets given value for given default in the domain corresponding to your application's name.  This will have no effect on the value returned by the objectForKey:defaultName method if the same key exists in the NSArgument domain. */

- (void)removeObjectForKey:(NSString *)defaultName;
	/* Removes the value for the given default in the domain corresponding to your application's name.  This will have no effect on the value returned by the objectForKey:defaultName method if the same key exists in the NSArgument domain. */

@end

/***************************/
/**** Time Designations ****/
/***************************/

@interface NSUserDefaults (NSUserDefaultsTypeCovers)

// the following methods return nil if the default doesn't exist or the key contains the wrong type of value
- (NSString *)stringForKey:(NSString *)defaultName;
- (NSArray *)arrayForKey:(NSString *)defaultName;
- (NSDictionary *)dictionaryForKey:(NSString *)defaultName;
- (NSData *)dataForKey:(NSString *)defaultName;
- (NSArray *)stringArrayForKey:(NSString *)defaultName;

// the following methods return 0 if the default doesn't exist or the key contains the wrong type of value
- (int)integerForKey:(NSString *)defaultName; 
- (float)floatForKey:(NSString *)defaultName; 

- (BOOL)boolForKey:(NSString *)defaultName;  
// returns YES if the default is a string of "yes" or "y" (case insensitive) or if it is a string representing a nonzero integer.  Otherwise returns NO.  Returns NO when the default is not found or when it cannot be parsed properly.

// These methods write a string representation of the given type.
- (void)setInteger:(int)value forKey:(NSString *)defaultName;
- (void)setFloat:(float)value forKey:(NSString *)defaultName;
- (void)setBool:(BOOL)value forKey:(NSString *)defaultName;
// write a YES or NO string

@end


@interface NSUserDefaults (NSExtendedUserDefaults)

- (id)init;
	/* Initializes defaults for current user. (from environment).  Returns an object with an empty search list.  This is called only when standardUserDefaults is not used. */

- (id)initWithUser:(NSString *)username;
	/* Initializes defaults for the specified user. Returns an object with an empty search list. */
	
- (NSArray *)searchList;
- (void)setSearchList:(NSArray *)newSearchList;
	/* Returns the search array (array of domain names).  This is filled in with the names of the domains that objectForKey: will search.   If bad domain names (no corresponding domain) are put in, they will be ignored. */

- (void)registerDefaults:(NSDictionary *)registrationDictionary;
	/* Adds the contents of the given dictionary to the registration dictionary.  If there is no registration dictionary, it is created and added to the end of the search list. */

- (NSDictionary *)dictionaryRepresentation;
  	/* Returns a dictionary that is the union of all the keys in the search list.  The value for each key is the value of the frontmost domain in the search list that contains that key. */


@end



@interface NSUserDefaults (NSUserDefaultsDomainMaintenance)

- (NSArray *)volatileDomainNames;
	/* returns a list of volatile domain names */
- (NSDictionary *)volatileDomainForName:(NSString *)domainName;
	/* returns the dictionary of name->values associated with domainName.  */
- (void)setVolatileDomain:(NSDictionary *)domain forName:(NSString *)domainName;
	/* Sets a dictionary for the given domain name.  Raises if a persistent domain called domainName exists */
- (void)removeVolatileDomainForName:(NSString *)domainName;
	/* removes the domain. */		
	
- (NSArray *)persistentDomainNames;	
	/* returns a list of persistent domain names */
- (NSDictionary *)persistentDomainForName:(NSString *)domainName;
	/* returns the dictionary of name->values associated with domainName.  */
- (void)setPersistentDomain:(NSDictionary *)domain forName:(NSString *)domainName;
	/* Sets a dictionary for the given domain name.  Raises if a volatile domain called domainName exists */
- (void)removePersistentDomainForName:(NSString *)domainName;
	/* removes the domain. */		

- (BOOL)synchronize;
	/* Saves any modifications to the persistent domains and updates all persistent domains that were not modified to what is on disk.  Note: The synchronize method is automatically called within 30 seconds after any change is made.  Use this method only if you cannot wait for the automatic synchronization, or if you want to update user defaults to what is on disk even though you have not made any changes.  The first time that persistent user defaults are changed after a synchronize call, an NSUserDefaultsChanged event is posted (this is to be able to detect changes when multiple entities are using the same NSUserDefaults object). The synchronize method returns NO if it could not save data to disk. */

@end

#ifdef __cplusplus 
extern "C" {
#endif

/* Public notification */
extern NSString *NSUserDefaultsDidChangeNotification;

/* Publicly available keys for language-dependent information...
*/
extern NSString *NSWeekDayNameArray;
extern NSString *NSShortWeekDayNameArray;
extern NSString *NSMonthNameArray;
extern NSString *NSShortMonthNameArray;
extern NSString *NSTimeFormatString;
extern NSString *NSDateFormatString;
extern NSString *NSTimeDateFormatString;
extern NSString *NSShortTimeDateFormatString;
extern NSString *NSCurrencySymbol;
extern NSString *NSDecimalSeparator;
extern NSString *NSThousandsSeparator;
extern NSString *NSInternationalCurrencyString;
extern NSString *NSCurrencyString;
extern NSString *NSDecimalDigits;
extern NSString *NSAMPMDesignation;

extern NSString *NSHourNameDesignations;
extern NSString *NSYearMonthWeekDesignations;
extern NSString *NSEarlierTimeDesignations;
extern NSString *NSLaterTimeDesignations;
extern NSString *NSThisDayDesignations;
extern NSString *NSNextDayDesignations;
extern NSString *NSNextNextDayDesignations;
extern NSString *NSPriorDayDesignations;
extern NSString *NSDateTimeOrdering;

#ifdef __cplusplus 
}
#endif
