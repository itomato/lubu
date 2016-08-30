#ident "@(#) objc-debug.h, Rev 1.9, 97/03/17"
//
//	Copyright (c) 1996, Sun Microsystems, Inc.
//	All rights reserved.


#define OBJC_REMOTE_DEBUG 1

enum {
    DisableDebugSilently	= -1,
    DisableDebug		= 0,
    EnableDebug			= 1,
    EnableDebugShowAllMessages	= 2,
    EnableDebugSilently		= 3
};

// These two enums do not, as yet, refer to any public API
enum {
    ShowMetaAndNonMeta	= -1,
    ShowOnlyMeta	= '+',
    ShowOnlyNonMeta	= '-'
};

enum {
    StartLeakChecking	= '1',
    StopLeakChecking	= '2',
    AddFilter		= '3',
    UpdateFilter        = '4',
    UpdateFilterID      = '5',
    RemoveFilter	= '6',
    RemoveAllFilters	= '7',
    DumpFiltersToRemote = '8'
};

typedef struct _FilterData
{
    int filterID;
    SEL selector;
    id receiver;
    const char *receiverClassName;
    char metaMethodVisibility;
    BOOL callMessageMatchedFilterFunction;
    unsigned int matchCount;
    struct _FilterData *next;
    struct _FilterData *prev;
} FilterData;

extern int objc_enableMessageSendDebug(int flag);

extern void objc_messageSendDebugHelp();

// Conveniences... use "objc_addFilterFromString" for real power.
extern BOOL objc_addFilterForClass(const char *className);
extern BOOL objc_addFilterForSelector(const char *selectorName);
extern BOOL objc_addFilterForReceiver(id receiver);

// Pass this a string of the form:
// "1,NSScrollView,drawRect:,0x15a6,some message I want to see,NO"
// Where above fields map to:
// "FilterID, ClassName | *, [+ | -]selectorName | [+ | -]*, receiverID or *, UserInfoString | 0, YES | NO [whether or not to call objc_messageMatchedFilter() when a filter matches]"
// OR SIMPLY "GENERIC_FILTER"
extern BOOL objc_parseStringIntoFilter(const char *filterString, FilterData *newFilter);
// Same as above, but adds the created filter to the filterList.
extern BOOL objc_addFilterFromString(const char *filterString);

// Will cause "objc_messageMatchedFilter()" to be called for *any* filter
// match!
extern void objc_callMessageMatchedFilter(BOOL callOrNot);

// To set whether or not you want the call level indicated by indenting output.
extern void objc_enableFilterCallLevelIndentation(BOOL enable);

/* Called when a filter matches, so you can put a breakpoint here, and stop */
/* when your filter matches. */
extern void objc_messageMatchedFilter();

// Creates default "liberal" filter. Use this as a basis, then change fields
// as needed, then objc_addFilter with "objc_addFilter".
// This function will always return the same pointer, to the same "static"
// filter, however the fields will all be reset to their "liberal" values
// (like the media and Bill Clinton), with each call to this function.
extern FilterData *objc_genericFilter(void);
extern void objc_addFilter(FilterData *aFilter);
// Put these values into filter with matching FilterID...
extern void objc_updateFilter(FilterData *aFilter);
extern void objc_removeFilter(FilterData *aFilter);
extern void objc_removeAllFilters();
extern void objc_remoteAlloc(id receiver);
extern void objc_remoteDealloc(id receiver);

// Advanced:

// Set your own function to be called whenever a message comes in. You
// can do your own filter testing here, and/or call to the default function.
extern void objc_setMessageSendFilterFunction(void (*customFilterFunction)(Class receiverClass,id receiver, SEL selector,void *callLevel, void *threadID));
// Might be desirable from within your own messageSendFilterFunction...
extern void objc_defaultMessageSendFilterFunction(Class receiverClass,id receiver, SEL selector,void *callLevel, void *threadID);
// Use this to get at the linked list of filters...
extern FilterData *objc_filterList(void);
