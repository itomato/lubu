#ident "@(#) NSSpellChecker.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import "NSSpellProtocol.h"

@class NSPanel;
@class NSPopUpButton;
@class NSView;
@class NSArray <NSCopying, NSMutableCopying, NSCoding>;
@class NSMutableArray;

/* The NSSpellChecker object is used by a client (e.g. a document in
an application) to spell-check a given NSString.  There is only one
NSSpellChecker instance per application (since spell-checking is
interactive and you only have one mouse and one keyboard).

The string being spell-checked need only be valid for the duration of
the call to checkSpellingOfString:... or countWordsInString:.

The usual usage of this is to implement a checkSpelling: method in an
object that has text to check, then, upon receiving checkSpelling:,
the object calls [[NSSpellChecker sharedInstance] checkSpellingOfString:...] 
with an NSString object consisting of the
text that should be checked.  The caller is responsible for selecting
the misspelled word that is found and for updating the panel UI if
desired with the updateSpellPanelWithMisspelledWord: method.  */

@interface NSSpellChecker : NSObject  {

@private
    // All instance variables are private and subject to future change.  Do not access them.
    id _guessesBrowser;
    id _wordField;
    NSPopUpButton *_languagePopUp;
    NSArray *_guessesList;
    id _panel;
    NSMutableArray *_userDictionaries;
    id _correctButton;
    id _guessButton;
    id _ignoreButton;
    id _accessoryView;
    id _dictionaryBrowser;
    NSString *_selectionString;
    void *_spellServers;
    NSString *_lastGuess;
    BOOL _autoShowGuessPanel;
    BOOL _needDelayedGuess;
    BOOL _unignoreInProgress;
    BOOL _doTimings;
    id _deleteButton;
    id _openButton;
    id _learnButton;
    id _forgetButton;
}

/* Only one per application. */
+ (NSSpellChecker *)sharedSpellChecker;
+ (BOOL)sharedSpellCheckerExists;

/* returns a guaranteed unique tag to use as the spell document tag
for a document.  You should use this method to generate tags, if
possible, to avoid collisions with other objects that can be spell
checked. */

+ (int)uniqueSpellDocumentTag;

/* Initiates a spell-check of a string.  Returns the range of the first
misspelled word (and optionally the wordCount by reference). */

- (NSRange)checkSpellingOfString:(NSString *)stringToCheck startingAt:(int)startingOffset language:(NSString *)language wrap:(BOOL)wrapFlag inSpellDocumentWithTag:(int)tag wordCount:(int *)wordCount;

- (NSRange)checkSpellingOfString:(NSString *)stringToCheck startingAt:(int)startingOffset;

/* Just counts the words without checking spelling.  Returns -1 if
counting words isn't supported by the spell server selected. */

- (int)countWordsInString:(NSString *)stringToCount language:(NSString *)language;

/* The checkSpellingOfString:... methods return the range of the
misspelled word found.  It is up to the client to select that word in
their document and to cause the spelling panel to update itself to
reflect the found misspelling.  Clients can call
updateSpellPanelWithMisspelledWord: to insure that the spell panel is
up to date. */

- (void)updateSpellingPanelWithMisspelledWord:(NSString *)word;

/* Sets and gets attributes of the spell-correction panel. */

- (NSPanel *)spellingPanel;
- (NSView *)accessoryView;
- (void)setAccessoryView:(NSView *)aView;

/* This method should be called from the client's implementation of -ignoreSpelling: */
- (void)ignoreWord:(NSString *)wordToIgnore inSpellDocumentWithTag:(int)tag;

- (NSArray *)ignoredWordsInSpellDocumentWithTag:(int)tag;
- (void)setIgnoredWords:(NSArray *)words inSpellDocumentWithTag:(int)tag;

/* When a document closes, it should notify the NSSpellChecker via
closeSpellDocumentWithTag: so that its ignored word list gets cleaned
up. */

- (void)closeSpellDocumentWithTag:(int)tag;

/* Allows programmatic setting of the language to spell-check in
(normally chosen by a pop-up-list in the spelling panel and defaulted
to the user's preferred language, so call this with care). */

- (NSString *)language;
- (BOOL)setLanguage:(NSString *)language;

/* Allows programmatic setting of the misspelled word field. */
- (void)setWordFieldStringValue:(NSString *)aString;

@end
