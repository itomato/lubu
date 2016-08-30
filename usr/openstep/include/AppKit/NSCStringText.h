#ident "@(#) NSCStringText.h, Rev 1.13, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1994, NeXT Computer, Inc.
//      All rights reserved.

#import <AppKit/NSText.h>
#import <AppKit/NSEvent.h>
#import <AppKit/NSColor.h>
#import <AppKit/NSFontManager.h>
#import <AppKit/NSSpellChecker.h>

#import <DPS/dpsclient.h>

enum {
    NSTextBlockSize			= 512
};

/* NSTextChunks implement variable sized arrays of records.  Allocation is by the given size (in bytes) -- typically a multiple number of records, say 10. The block of memory never shrinks, and the chunk records the current number of elements.  To use the NSTextChunks, you declare a struct w/ NSTextChunks as its first field.
*/
typedef struct _NSTextChunk {
    short           growby;	/* increment to grow by */
    int             allocated;	/* how much is allocated */
    int             used;	/* how much is used */
} NSTextChunk;

typedef struct _NSTextBlock {
    struct _NSTextBlock *next;		/* next text block in link list */
    struct _NSTextBlock *prior;		/* previous text block in link list */
    struct _tbFlags {
	unsigned int    malloced:1;	/* true if block was malloced */
	unsigned int    PAD:15;
    } tbFlags;
    short           chars;		/* number of chars in this block */
    unsigned char  *text;		/* the text */
} NSTextBlock;

/* NSRun represents a single run of text w/ a given format
*/
  typedef struct {
    unsigned int underline:1;
    unsigned int dummy:1;		/* unused */
    unsigned int subclassWantsRTF:1;
    unsigned int graphic:1;
    unsigned int forcedSymbol:1;	/* did alt-char force use to use symbol */
    unsigned int RESERVED:11;
} NSRunFlags;

typedef struct _NSRun {
    id              font;	/* Font id */
    int             chars;	/* number of chars in run */
    void           *paraStyle;	/* implementation dependent paraStyle
				 * sheet info. */
    int		    textRGBColor;	/* text color */
    unsigned char   superscript;/* superscript in points */
    unsigned char   subscript;	/* subscript in points */
    id  	    info;	/* available for subclasses of Text */
    NSRunFlags rFlags;
} NSRun;

/* NSRunArray is a NSTextChunk that holds the set of formats for a Text object
*/

typedef struct _NSRunArray {
    NSTextChunk chunk;
    NSRun runs[1];
} NSRunArray;

/* NSBreakArray is a NSTextChunk that holds line break information for a Text Object. it is mostly an array of line descriptors.  each line descriptor contains 3 fields: 
 1) line change bit (sign bit), set if this line defines a new height 
 2) paragraph end bit (next to sign bit), set if the end of this line ends the paragraph 
 3) numbers of characters in the line (low order 14 bits) 
if the line change bit is set, the descriptor is the first field of a NSHeightChange. since this record is bracketed by negative short values, the breaks array can be sequentially accessed backwards and forwards. 
*/
#if m68k
typedef short NSLineDesc;
#else
typedef	int NSLineDesc;
#endif

typedef struct _NSHeightInfo {
    float         newHeight;	/* line height from here forward */
    float         oldHeight;	/* height before change */
    NSLineDesc      lineDesc;	/* line descriptor */
} NSHeightInfo;

typedef struct _NSHeightChange {
    NSLineDesc      lineDesc;	/* line descriptor */
    NSHeightInfo    heightInfo;
} NSHeightChange;

typedef struct _NSBreakArray {
    NSTextChunk         chunk;
    NSLineDesc      breaks[1];
} NSBreakArray;

/* NSLay represents a single run of text in a line and records everything needed to select or draw that piece.
*/
typedef struct {
    unsigned int mustMove:1;	/* unimplemented */
    unsigned int isMoveChar:1;
    unsigned int RESERVED:14;
} NSLayFlags;

typedef struct _NSLay {
    float         x;		/* x coordinate of moveto */
    float         y;		/* y coordinate of moveto */
    short           offset;	/* offset in line array for text */
    short           chars;	/* number of characters in lay */
    id              font;	/* font id */
    void           *paraStyle;	/* implementation dependent fontStyle
				 * sheet info. */
    NSRun *run;			/* run for lay */
    NSLayFlags	    lFlags;
} NSLay;

/* NSLayArray is a NSTextChunk that holds the layout for the current line
*/
typedef struct _NSLayArray {
    NSTextChunk chunk;
    NSLay lays[1];
} NSLayArray;

/* NSWidthArray is a NSTextChunk that holds the widths for the current line
*/
typedef struct _NSWidthArray {
    NSTextChunk chunk;
    float widths[1];
} NSWidthArray;

/* NSCharArray is a NSTextChunk that holds the chars for the current line
*/
typedef struct _NSCharArray {
    NSTextChunk chunk;
    unsigned char text[1];
} NSCharArray;

/* Word definition Finite State Machine transition struct
*/
typedef struct _NSFSM {
    const struct _NSFSM  *next;	/* state to go to, NULL implies final state */
    short           delta;	/* if final state, this undoes lookahead */
    short           token;	/* if final state, < 0 word is newline,
				 * = is dark, > is white space */
} NSFSM;

/* Represents one end of a selection
*/
typedef struct _NSSelPt {
    int             cp;		/* character position */
    int             line;	/* offset of LineDesc in break table */
    float         x;		/* x coordinate */
    float         y;		/* y coordinate */
    int             c1st;	/* character position of first character
				 * on the line */
    float         ht;		/* line height */
} NSSelPt;

typedef struct _NSTabStop {
    short           kind;	/* only NSLeftTab implemented*/
    float         x;		/* x coordinate for stop */
} NSTabStop;

typedef struct _NSTextCache {
    int curPos;			/* current position in text stream */
    NSRun *curRun;		/* cache current block of text and */
    int runFirstPos;		/* character pos that corresponds */
    NSTextBlock *curBlock;	/* cache current block of text and */
    int blockFirstPos;		/* character pos that corresponds */
} NSTextCache;

typedef struct _NSLayInfo {
    NSRect rect;		/* bounds rect for current line. */
    float descent;		/* descent for current line, can be reset
				 * by scanFunc */
    float width;		/* width of line */
    float left;		/* left side visible coordinate */
    float right;		/* right side visible coordinate */
    float rightIndent;	/* how much white space is left at right
				 * side of line */
    NSLayArray *lays;		/* scanFunc fills with NSLay items */
    NSWidthArray *widths;	/* scanFunc fills with character widths */
    NSCharArray *chars;		/* scanFunc fills with characters */
    NSTextCache cache;		/* cache of current block & run */
    NSRect *textClipRect;	/* if non-nil, the current clip for drawing */
    struct _lFlags {
	unsigned int horizCanGrow:1;/* 1 if scanFunc should perform dynamic
				 * growing of x margins */
	unsigned int vertCanGrow:1;/* 1 if scanFunc should perform dynamic
				 * growing of y margins */
	unsigned int erase:1;	/* used to tell drawFunc to erase before
				 * drawing line  */
	unsigned int ping:1;	/* used to tell drawFunc to ping server */
	unsigned int endsParagraph:1;/* true if line ends the paragraph, eg
				 * ends in newline */
	unsigned int resetCache:1;/* used in scanFunc to reset local caches */
	unsigned int RESERVED:10;
    } lFlags;
} NSLayInfo;

typedef struct _NSTextStyle {
    float         indent1st;	/* how far first line in paragraph is
				 * indented */
    float         indent2nd;	/* how far second line is indented */
    float         lineHt;	/* line height */
    float         descentLine;	/* distance to ascent line from bottom of line */
    NSTextAlignment	  alignment;	/* justification */
    short           numTabs;	/* number of tab stops */
    NSTabStop      *tabs;	/* array of tab stops */
} NSTextStyle;

enum {
    NSLeftTab = 0
};

enum {
    NSBackspaceKey			= 8,
    NSCarriageReturnKey			= 13,
    NSDeleteKey				= 0x7f,
    NSBacktabKey			= 25
};

typedef enum _NSParagraphProperty {
    NSLeftAlignedParagraph		= NSLeftTextAlignment,
    NSRightAlignedParagraph		= NSRightTextAlignment,
    NSCenterAlignedParagraph		= NSCenterTextAlignment,
    NSJustificationAlignedParagraph	= NSJustifiedTextAlignment,
    NSFirstIndentParagraph		= 4,
    NSIndentParagraph			= 5,
    NSAddTabParagraph			= 6,
    NSRemoveTabParagraph		= 7,
    NSLeftMarginParagraph		= 8,
    NSRightMarginParagraph		= 9
} NSParagraphProperty;


/* Word tables for various languages.  The SmartLeft and SmartRight arrays are suitable as arguments for the messages setPreSelSmartTable: and setPostSelSmartTable.  When doing a paste, if the character to the left (right) of the new word is not in the left (right) table, an extra space is added on that side.  The CharCats tables define the character classes used in the word wrap or click tables.  The BreakTables are finite state machines that determine word wrapping.  The ClickTables are finite state machines that determine which characters are selected when the user double clicks.
*/
extern const unsigned char *NSEnglishSmartLeftChars;
extern const unsigned char *NSEnglishSmartRightChars;
extern const unsigned char *NSEnglishCharCatTable;
extern const NSFSM *NSEnglishBreakTable;
extern int NSEnglishBreakTableSize;
extern const NSFSM *NSEnglishNoBreakTable;
extern int NSEnglishNoBreakTableSize;
extern const NSFSM *NSEnglishClickTable;
extern int NSEnglishClickTableSize;

extern const unsigned char *NSCSmartLeftChars;
extern const unsigned char *NSCSmartRightChars;
extern const unsigned char *NSCCharCatTable;
extern const NSFSM *NSCBreakTable;
extern int NSCBreakTableSize;
extern const NSFSM *NSCClickTable;
extern int NSCClickTableSize;

typedef int (*NSTextFunc) (id self, NSLayInfo *layInfo);
typedef unsigned short (*NSCharFilterFunc) (unsigned short charCode, int flags, NSStringEncoding theEncoding);
typedef char  *(*NSTextFilterFunc) (id self, unsigned char * insertText, int *insertLength, int position);

@class NSEvent <NSCopying, NSCoding>;

typedef struct _NSCStringTextInternalState  {
    const NSFSM        *breakTable;
    const NSFSM        *clickTable;
    const unsigned char *preSelSmartTable;
    const unsigned char *postSelSmartTable;
    const unsigned char *charCategoryTable;
    char                delegateMethods;
    NSCharFilterFunc    charFilterFunc;
    NSTextFilterFunc    textFilterFunc;
    NSString	       *_string;
    NSTextFunc          scanFunc;
    NSTextFunc          drawFunc;
    id                  delegate;
    int                 tag;
    void	       *cursorTE;
    NSTextBlock        *firstTextBlock;
    NSTextBlock        *lastTextBlock;
    NSRunArray         *theRuns;
    NSRun               typingRun;
    NSBreakArray       *theBreaks;
    int                 growLine;
    int                 textLength;
    float             maxY;
    float             maxX;
    NSRect              bodyRect;
    float             borderWidth;
    char                clickCount;
    char		displayDisabled;
    NSSelPt             sp0;
    NSSelPt             spN;
    NSSelPt             anchorL;
    NSSelPt             anchorR;
    NSSize              maxSize;
    NSSize              minSize;
    struct _tFlags {
#ifdef __BIG_ENDIAN__
	unsigned int        _editMode:2;
	unsigned int        _selectMode:2;
	unsigned int        _caretState:2;
	unsigned int        changeState:1;
	unsigned int        charWrap:1;
	unsigned int        haveDown:1;
	unsigned int        anchorIs0:1;
	unsigned int        horizResizable:1;
	unsigned int        vertResizable:1;
	unsigned int        overstrikeDiacriticals:1;
	unsigned int        monoFont:1;
	unsigned int        disableFontPanel:1;
	unsigned int        inClipView:1;
#else
	unsigned int        inClipView:1;
	unsigned int        disableFontPanel:1;
	unsigned int        monoFont:1;
	unsigned int        overstrikeDiacriticals:1;
	unsigned int        vertResizable:1;
	unsigned int        horizResizable:1;
	unsigned int        anchorIs0:1;
	unsigned int        haveDown:1;
	unsigned int        charWrap:1;
	unsigned int        changeState:1;
	unsigned int        _caretState:2;
	unsigned int        _selectMode:2;
	unsigned int        _editMode:2;
#endif
    }                   tFlags;
    void               *_info;
    void	       *_textStr;
    id			_caretPixmap;
    BOOL		_caretPixmapIsValid;
    BOOL                _dontCheckForKey;
}  NSCStringTextInternalState;

@interface NSCStringText : NSText

+ excludeFromServicesMenu:(BOOL)flag;
+ (NSFont *)defaultFont;
+ (void)setDefaultFont:(NSFont *)anObject;

- (id)initWithFrame:(NSRect)frameRect text:(NSString *)theText alignment:(NSTextAlignment)mode;

- (NSCStringTextInternalState *)cStringTextInternalState;

- (void)renewRuns:(NSRunArray *)newRuns text:(NSString *)newText frame:(NSRect)newFrame tag:(int)newTag;
- (void)renewFont:(NSFont *)newFontId text:(NSString *)newText frame:(NSRect)newFrame tag:(int)newTag;
- (void)renewFont:(NSString *)newFontName size:(float)newFontSize style:(int)newFontStyle text:(NSString *)newText frame:(NSRect)newFrame tag:(int)newTag;
- (void)adjustPageHeightNew:(float *)newBottom top:(float)oldTop bottom:(float)oldBottom limit:(float)bottomLimit;
- (NSRect)paragraphRect:(int)prNumber start:(int *)startPos end:(int *)endPos;
- (void)setCharFilter:(NSCharFilterFunc)aFunc;
- (NSCharFilterFunc)charFilter;
- (void)setTextFilter:(NSTextFilterFunc)aFunc;
- (NSTextFilterFunc)textFilter;
- (const unsigned char *)preSelSmartTable;
- (void)setPreSelSmartTable:(const unsigned char *)aTable;
- (const unsigned char *)postSelSmartTable;
- (void)setPostSelSmartTable:(const unsigned char *)aTable;
- (const unsigned char *)charCategoryTable;
- (void)setCharCategoryTable:(const unsigned char *)aTable;
- (const NSFSM *)breakTable;
- (void)setBreakTable:(const NSFSM *)aTable;
- (const NSFSM *)clickTable;
- (void)setClickTable:(const NSFSM *)aTable;
- (void)setTag:(int)anInt;
- (int)tag;
- (NSColor *)runColor: (NSRun *)run;
- (NSColor *)selColor;

- (void)finishReadingRichText;
- (void)startReadingRichText;
- (void)setRetainedWhileDrawing:(BOOL)aFlag;
- (BOOL)isRetainedWhileDrawing;
- (NSTextBlock *)firstTextBlock;
- (void)setScanFunc:(NSTextFunc)aFunc;
- (NSTextFunc)scanFunc;
- (void)setDrawFunc:(NSTextFunc)aFunc;
- (NSTextFunc)drawFunc;

@end

@interface NSCStringText(NSFrameRect)
- (void)resizeTextWithOldBounds:(NSRect)oldBounds maxRect:(NSRect)maxRect;
@end

@interface NSCStringText(NSLayout)
- (int)calcLine;
- (void *)paragraphStyleForFont:(NSFont *)fontId alignment:(int)alignment;
- (BOOL)charWrap;
- (float)descentLine;
- (void)getMarginLeft:(float *)leftMargin right:(float *)rightMargin top:(float *)topMargin bottom:(float *)bottomMargin;
- (void)getMinWidth:(float *)width minHeight:(float *)height maxWidth:(float)widthMax maxHeight:(float)heightMax;
- (void *)defaultParagraphStyle;
- (float)lineHeight;
- (void)setCharWrap:(BOOL)flag;
- (void)setDescentLine:(float)value;
- (void)setLineHeight:(float)value;
- (void)setMarginLeft:(float)leftMargin right:(float)rightMargin top:(float)topMargin bottom:(float)bottomMargin;
- (void)setNoWrap;
- (void)setParagraphStyle:(void *)paraStyle;
@end

@interface NSCStringText(NSLinePosition)
- (int)lineFromPosition:(int)position;
- (int)positionFromLine:(int)line;
@end

@interface NSCStringText(NSEvent)
- (void)clear:(id)sender;
- (void)moveCaret:(unsigned short)theKey;
- (void)becomeKeyWindow;
- (void)resignKeyWindow;
- (void)selectText:(id)sender;
@end

@interface NSCStringText(NSSelection)
- (void)setSelectionStart:(int)start end:(int)end;
- (void)getSelectionStart:(NSSelPt *)start end:(NSSelPt *)end;
- (void)hideCaret;
- (void)replaceSel:(NSString *)aString;
- (void)replaceSel:(NSString *)aString length:(int)length;
- (void)replaceSel:(NSString *)aString length:(int)length runs:(NSRunArray *)insertRuns;
- (void)scrollSelToVisible;
- (void)selectError;
- (void)selectNull;
- (void)setSelColor:(NSColor *)color;
- (void)showCaret;
- (id)validRequestorForSendType:(NSString *)sendType returnType:(NSString *)returnType;
- (BOOL)readSelectionFromPasteboard:(NSPasteboard *)pboard;
- (BOOL)writeSelectionToPasteboard:(NSPasteboard *)pboard types:(NSArray *)types;
@end

@interface NSCStringText(NSFont)
- (void)setFont:(NSFont *)fontObj paragraphStyle:(void *)paraStyle;
- (void)setSelFontFamily:(NSString *)fontName;
- (void)setSelFontSize:(float)size;
- (void)setSelFontStyle:(NSFontTraitMask)traits;
- (void)setSelFont:(NSFont *)fontId;
- (void)setSelFont:(NSFont *)fontId paragraphStyle:(void *)paraStyle;
- (BOOL)changeTabStopAt:(float)oldX to:(float)newX;
- (BOOL)setSelProp:(NSParagraphProperty)prop to:(float)val;
@end

@class NSCell <NSCopying, NSCoding>;

@interface NSCStringText(NSGraphics)
- (void)replaceSelWithCell:(NSCell *)cell;
- (NSPoint)locationOfCell:(NSCell *)cell;
- (void)setLocation:(NSPoint)origin ofCell:(NSCell *)cell;
+ registerDirective:(NSString *)directive forClass:classx;
@end

@interface NSCStringText(NSFind)
- (BOOL)findText:(NSString *)textPattern ignoreCase:(BOOL)ignoreCase backwards:(BOOL)backwards wrap:(BOOL)wrap;
@end

@interface NSObject(NSCStringTextDelegate)
- (BOOL)text:(NSText *)textView shouldChangeTextInRange:(NSRange)affectedCharRange replacementString:(NSString *)replacementString;
- (void)textWillResize:(NSCStringText *)textObject;
- (NSRect)textDidResize:(NSCStringText *)textObject oldBounds:(NSRect)oldBounds;
- (void)textWillSetSel:(NSCStringText *)textObject toFont:(NSFont *)font;
- (NSFont *)textWillConvert:(NSCStringText *)textObject fromFont:(NSFont *)from toFont:(NSFont *)to;
- (void)textWillStartReadingRichText:(NSCStringText *)textObject;
- (void)textWillFinishReadingRichText:(NSCStringText *)textObject;
- (NSSize)textWillWrite:(NSCStringText *)textObject;
- (void)textDidRead:(NSCStringText *)textObject paperSize:(NSSize)paperSize;
@end

@interface NSObject(NSTextCell)
/* Any object added to the Text object via replaceSelWithCell: must respond to all of the following messages:
*/
- (void)highlight:(BOOL)flag withFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)drawWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (BOOL)trackMouse:(NSEvent *)theEvent inRect:(NSRect)cellFrame ofView:(NSView *)controlView untilMouseUp:(BOOL)flag;
- (NSSize)cellSize;
- (void)readRichText:(NSString *)string forView:(NSView *)view;
- (NSString *)richTextForView:(NSView *)view;
@end

#ifdef __cplusplus
extern "C" {
#endif

extern void NSTextFontInfo(id fid, float *ascender, float *descender, float *lineHt);
extern int NSScanALine(id self, NSLayInfo *layInfo);
extern int NSDrawALine(id self, NSLayInfo *layInfo);
extern unsigned short NSFieldFilter(unsigned short theChar, int flags, NSStringEncoding theEncoding);
extern unsigned short NSEditorFilter(unsigned short theChar, int flags, NSStringEncoding theEncoding);
extern NSData *NSDataWithWordTable(const unsigned char *smartLeft, const unsigned char *smartRight, const unsigned char *charClasses, const NSFSM *wrapBreaks, int wrapBreaksCount, const NSFSM *clickBreaks, int clickBreaksCount, BOOL charWrap);
extern void NSReadWordTable(NSZone *zone, NSData *data, unsigned char **smartLeft, unsigned char **smartRight, unsigned char **charClasses, NSFSM **wrapBreaks, int *wrapBreaksCount, NSFSM **clickBreaks, int *clickBreaksCount, BOOL *charWrap);

extern NSTextChunk *NSChunkMalloc(int growBy, int initUsed);
extern NSTextChunk *NSChunkRealloc(NSTextChunk *pc);
extern NSTextChunk *NSChunkGrow(NSTextChunk *pc, int newUsed);
extern NSTextChunk *NSChunkCopy(NSTextChunk *pc, NSTextChunk *dpc);

extern NSTextChunk *NSChunkZoneMalloc(int growBy, int initUsed, NSZone *zone);
extern NSTextChunk *NSChunkZoneRealloc(NSTextChunk *pc, NSZone *zone);
extern NSTextChunk *NSChunkZoneGrow(NSTextChunk *pc, int newUsed, NSZone *zone);
extern NSTextChunk *NSChunkZoneCopy(NSTextChunk *pc, NSTextChunk *dpc, NSZone *zone);

#ifdef __cplusplus
}
#endif
