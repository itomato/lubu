#ident "@(#) NSDate.h, Rev 1.12, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Primitives for manipulating time

/*	
	Portions of the NSDate implementation are derived from
	public domain software described in
	 ``Calendrical Calculations'' by Nachum Dershowitz and
	 Edward M. Reingold, Software---Practice & Experience,
	vol. 20, no. 9 (September, 1990), pp. 899--928 and from
	``Calendrical Calculations, II: Three Historical Calendars''
	by Edward M. Reingold,  Nachum Dershowitz, and Stewart M. Clamen,
	Software---Practice & Experience, vol. 23, to appear.

*/

#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <sys/time.h>

/* This module implements the 'date and time' concept.  Features:
    - it is easy to compare dates and deal with time intervals;
    - fast (can use the native representation);
    - accuracy (other date representations can be added to the framework);
    - can support user-oriented representations (Gregorian, etc ...);
    - dates are immutable;
    - an absolute reference date to ease conversion to other representations; 
Our absolute reference date is the first instant of Jan 1st, 2001.
All representations must be able to convert to/from that absolute reference.
We ignore leap second accounting (e.g. pretend that they don't happen).
Our reference date corresponds to 978307200 seconds after the UNIX base (e.g.
1/1/1970 to 1/1/2001 is (31*365 + 8 (leaps: 1972, .., 2000))*24*60*60)

Other interesting numbers are the number of days to the Common Era 1/1/1 ((2000*365+25*20-20+5+1), and for astronomers, from there to the Julian Epoch, 1721425.5.

*/

typedef double NSTimeInterval;
    /* always in seconds; 
    yields sub-millisecond precision over a range of 10000 years */

#define NSTimeIntervalSince1970  978307200.0L

@class NSCalendarDate; // expresses Western dates (see below)
@class NSTimeZone <NSCopying, NSCoding>; // expresses a time zone (see below)

/***************	Date basics		***************/

@interface NSDate:NSObject <NSCopying, NSCoding>

- (NSTimeInterval)timeIntervalSinceReferenceDate;
    /* >0 if self is in the 3rd millenium */

@end

@interface NSDate (NSExtendedDate)

- (NSTimeInterval)timeIntervalSinceDate:(NSDate *)anotherDate;
    /* >0 if self is ahead of anotherDate;
    Conversion between two dates using the same representation should be exact */

- (NSTimeInterval)timeIntervalSinceNow;
    /* >0 if self is in the future */

- (NSTimeInterval)timeIntervalSince1970;
    /* convenience for POSIX calculations; neg if date is before 1970 */

- addTimeInterval:(NSTimeInterval)seconds;
    /* Returns an auto-released date; 
    may return a date from a different representation */

- (NSDate *)earlierDate:(NSDate *)anotherDate;
- (NSDate *)laterDate:(NSDate *)anotherDate;
- (NSComparisonResult)compare:(NSDate *)other;

+ (NSTimeInterval)timeIntervalSinceReferenceDate;
    /* returns the timeInterval of now to the reference date (<0 until 2001) */
    
@end

/***************	Creation of basic dates		***************/

@interface NSDate (NSDateCreation)

+ (id)allocWithZone:(NSZone *)zone;
    /* Create an uninitialized instance of a concrete date;
    When called with NSDate, substitutes a concrete class that guarantees a wide dynamic range, but as accurate as possible for dates close to boot time for use in timers;
    +alloc can also be used to that effect */

+ (NSDate *)date;
    /* now! */
    
+ (NSDate *)dateWithTimeIntervalSinceNow:(NSTimeInterval)secs;
    /* Creates a new autoreleased date before or after now */
    
+ (NSDate *)dateWithTimeIntervalSinceReferenceDate:(NSTimeInterval)secs;
    /* Creates a new autoreleased date before or after the absolute reference date */

+ (NSDate *)dateWithTimeIntervalSince1970:(NSTimeInterval)secs;
    /* creates a date given the POSIX delta */
    
+ (NSDate *)distantFuture;
    /* a date far far into the future */
    
+ (NSDate *)distantPast;
    /* a date far far in the past */
    
- (id)initWithTimeIntervalSinceReferenceDate:(NSTimeInterval)secsToBeAdded;
    /* Designated initializer: MUST BE IMPLEMENTED BY CONCRETE CLASSES;
    Creates a new date before or after the absolute reference date */

- (id)init;
    /*  returns the date for now */

- (NSDate *)initWithTimeInterval:(NSTimeInterval)secsToBeAdded sinceDate:(NSDate *)anotherDate;
    /* initializes a date given an offset from anotherDate;
    Conversion between two dates using the same representation should be exact;
    offset may be <0 (date is before anotherDate); */

- (NSDate *)initWithTimeIntervalSinceNow:(NSTimeInterval)secsToBeAddedToNow;
    /* initializes a date given an offset from now;
    offset may be <0 (date is before now); */

@end

/*******	Conveniences to deal with Western calendar	*******/

@interface NSDate (NSCalendarDateExtras)

- (id)initWithString:(NSString *)description;

- (NSCalendarDate *)dateWithCalendarFormat:(NSString *)format timeZone:(NSTimeZone *)aTimeZone;

- (NSString *)description;
    /* use the default time zone and default format */

- (NSString *)descriptionWithLocale:(NSDictionary *)locale;
    /* use the default time zone and locale's NSTimeDateFormatString */

- (NSString *)descriptionWithCalendarFormat:(NSString *)format timeZone:(NSTimeZone *)aTimeZone locale:(NSDictionary *)locale;
@end

/************ Time Zone Abstract Class *********************************/

/* An abstract TimeZone class.  TimeZones provide "locality" to universal dates.  Since many areas provide Daylight Savings Time in one form or another, we consider a NSTimeZone to represent the geo-political area, and a NSTimeZoneDetail as a specialization that contains the details of abbreviation and offset.
   Private concrete classes are provided that supply
  	- unnamed offset style timezones, e.g. +0900
  	- unchanging named timezones "GMT" +0000
  	- varying timezones, e.g. PST/PDT, derived from underlying
	  system resources
   The initialization method will substitute a private concrete instance.
 */

@class NSTimeZoneDetail;

@interface NSTimeZone: NSObject <NSCopying, NSCoding>

// The default time zone is established via TZFILE environment variable
// which should name a path for tzfile(5) information 
// (/etc/zoneinfo/localtime is the default if TZFILE is not set)
+ (void)setDefaultTimeZone:(NSTimeZone *)aTimeZone;
+ (NSTimeZoneDetail *)defaultTimeZone;

// provides a defaultTimeZone look-alike except that when decoding
// it replaces itself with the current defaultTimeZone
// this is useful for NSCalendarDates that have a particular
// format but wish to always use the current (local) timezone.
+ (NSTimeZone *)localTimeZone;

+ (NSDictionary *)abbreviationDictionary;
   // maps abbreviation to regionName (which is currently a file name)
   // e.g. { PST = US/Pacific; PDT = US/Pacific; MDT = US/Mountain; ...}
   // keys may be used to obtain timeZones via timeZoneWithName
   // values may also be used to obtain timezones via timeZoneWithRegionName

+ (NSArray *)timeZoneArray;
   // supplies all regionNames grouped as subarrays per geographical region
   // e.g. ( ... ( US/Pacific, US/Pacific-New, Canada/Pacific), ...)

+ (NSTimeZone *)timeZoneWithName:(NSString *)aTimeZoneName;
   // provide timezone with this timeZoneName
   // currently, timeZoneName names a file in tzfile(5) format

+ (NSTimeZoneDetail *)timeZoneWithAbbreviation:(NSString *)abbreviation;
   // provide timezone with this abbreviation (if in abbreviationDictionary)
   
+ (NSTimeZone *)timeZoneForSecondsFromGMT:(int)seconds;
   // yield an unnamed timezone for this offset

- (NSString *)timeZoneName;

- (NSArray *)timeZoneDetailArray;
- (NSTimeZoneDetail *)timeZoneDetailForDate:(NSDate *)date;

@end

@interface NSTimeZoneDetail : NSTimeZone
- (int)timeZoneSecondsFromGMT;
- (NSString *)timeZoneAbbreviation;
- (BOOL)isDaylightSavingTimeZone;
@end

/***************	Calendar Utilities		***************/


    /* Calendar formatting
    	%% encode a '%' character
	%a abbreviated weekday name
	%A full weekday name
	%b abbreviated month name
	%B full month name
	%c time and date using 
        %C year of common era divided by 100
	%d day of the month as a decimal number (01-31)
	%H hour based on a 24-hour clock as a decimal number (00-23)
	%I hour based on a 12-hour clock as a decimal number (01-12)
	%j day of the year as a decimal number (001-366)
	%m month as a decimal number (01-12)
	%M minute as a decimal number (00-59)
	%p AM/PM designation associated with a 12-hour clock
	%S second as a decimal number (00-61)
	%w weekday as a decimal number (0-6), where Sunday is 0
	%x date using the NSDateFormatString representation for the locale
	%X time using the NSTimeFormatString representation for the locale
	%y year without century (00-99) for date creation 1900 will be used
	   if the year is >= 69, otherwise 2000 will be used
	%Y year with century (e.g. 1990)
	%Z time zone detail name
      and additionally
      	%z timezone offset in hours & minutes from GMT (HHMM)
	
      The locale information may be supplied in the form of a dictionary,
      where the keys and canonical contents are:
      	{
	    NSDateFormatString = "%a %b %d %Y";
	    NSTimeDateFormatString = "%a %b %d %H:%M:%S %Z %Y";
	    NSTimeFormatString = "%H:%M:%S %Z";
	    NSAMPMDesignation = ( AM, PM );
	    NSMonthNameArray = ( January, February, March, April, May,
	    	June, July, August, September, October, November,
		December );
	    NSShortMonthNameArray = ( Jan, Feb, Mar, Apr, May, Jun, Jul,
	    	Jul, Aug, Sep, Oct, Nov, Dec );
	    NSWeekDayNameArray = ( Sunday, Monday, Tuesday, Wednesday,
	     	Thursday, Friday, Saturday );
	    NSShortWeekDayNameArray = ( Sun, Mon, Tue, Wed, Thu, Fri, Sat );
	}
   */
   

@interface NSCalendarDate : NSDate {
    NSTimeInterval _timeIntervalSinceReferenceDate;
    NSTimeZoneDetail *_timeZone;
    NSString *_formatString;
}

+ (NSCalendarDate *)dateWithYear:(int)year month:(unsigned)month day:(unsigned)day hour:(unsigned)hour minute:(unsigned)minute second:(unsigned)second timeZone:(NSTimeZone *)aTimeZone;

+ (NSCalendarDate *)dateWithString:(NSString *)description calendarFormat:(NSString *)format;

+ (NSCalendarDate *)dateWithString:(NSString *)description calendarFormat:(NSString *)format locale:(NSDictionary *)dict;

+ (NSCalendarDate *)calendarDate;

- (id)initWithYear:(int)year month:(unsigned)month day:(unsigned)day hour:(unsigned)hour minute:(unsigned)minute second:(unsigned)second timeZone:(NSTimeZone *)aTimeZone;
    /* e.g. [[NSDate alloc] initWithYear:1789 month:7 day:14 hour:12 minute:0 second:0 timeZone:[NSTimeZone timeZoneDetailForKey:@"MST"]]; 
    raises if no timezone supplied */
    
- (id)initWithString:(NSString *)description;
     /* inverts 1994-01-14 15:25:02 +0900 */

    
- (id)initWithString:(NSString *)description calendarFormat:(NSString *)format;
     /* uses canonical (Western) style month and day names */

- (id)initWithString:(NSString *)description calendarFormat:(NSString *)format locale:(NSDictionary *)dict;
    /* Uses dictionary provided month and day names for input resolution. */

- (NSTimeZoneDetail *)timeZoneDetail;
- (void)setTimeZone:(NSTimeZone *)aTimeZone;
    // picks the correct detail

- (NSString *)calendarFormat;
- (void)setCalendarFormat:(NSString *)format;
    /* default: %Y-%m-%d %H:%M:%S %z for an international style header */

- (int)yearOfCommonEra;	/* 1 C.E. (AD) is the base */
- (int)monthOfYear;	/* 1 - 12 */
- (int)dayOfMonth;	/* 1 - 31 */
- (int)dayOfWeek;	/* 0 - 6 */
- (int)dayOfYear;	/* 1 - 366 */
- (int)dayOfCommonEra;	/* 1 - ????? */
- (int)hourOfDay;	/* 0 - 23 */
- (int)minuteOfHour;	/* 0 - 59 */
- (int)secondOfMinute;	/* 0 - 59 */


- (void)years:(int *)yp months:(int *)mop days:(int *)dp hours:(int *)hp minutes:(int *)mip seconds:(int *)sp sinceDate:(NSCalendarDate *)date;


- (NSCalendarDate *)dateByAddingYears:(int)year months:(int)month days:(int)day hours:(int)hour minutes:(int)minute seconds:(int)second;
    /* All offsets may be negative; autoreleased result.
       Will attempt to retain class
       Adding 1 day across a timezone change will keep the same hour/minute/second offset (e.g. 2:30pm will stay 2:30pm)  */

- (NSString *)description;
    /* uses calendarFormat and timeZone, canonical locale */

- (NSString *)descriptionWithLocale:(NSDictionary *)locale;
    /* uses calendarFormat and timeZone, supplied locale */

- (NSString *)descriptionWithCalendarFormat:(NSString *)format;
    /* uses supplied format, canonical locale */

- (NSString *)descriptionWithCalendarFormat:(NSString *)format locale:(NSDictionary *)locale;
    /* uses supplied format and locale */
@end

@interface NSCalendarDate (NSNaturalLanguageDate)
+ dateWithNaturalLanguageString:(NSString *)string date:(NSCalendarDate *)today locale:(NSDictionary *)locale;
@end // NSCalendarDate (NSNaturalLanguageDate)

@interface NSDate (NSNaturalLanguageDate)
+ dateWithNaturalLanguageString:(NSString *)string date:(NSCalendarDate *)today locale:(NSDictionary *)locale;
+ dateWithNaturalLanguageString:(NSString *)string;
+ dateWithNaturalLanguageString:(NSString *)string locale:(NSDictionary *)locale;
@end
