#ident "@(#) NSSpellServer.h, Rev 1.7, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.

#import <Foundation/NSObject.h>
#import "NSSpellProtocol.h"
#import <Foundation/NSRange.h>
/*
The server just handles all the checking in and IAC and delegates the real work to its delegate.  A single server can handle more than one language.  Services is used to rendezvous applications with servers.  The format of a services descriptor for a spell-checker:

Spell Checker: NeXT
Language: French
Language: English
Executable: franglais.daemon
*/

@class NSConnection;
@class NSArray <NSCopying, NSMutableCopying, NSCoding>;

@interface NSSpellServer : NSObject {

@private
    // All instance variables are private and subject to future change.  Do not access them.
    id _delegate;
    NSConnection *_spellServerConnection;
    NSArray *_ignoredWords;
    BOOL _delegateLearnsWords;
    BOOL _delegateForgetsWords;
}

- (void)setDelegate:(id)anObject;
- (id)delegate;

/* Used to check in */
- (BOOL)registerLanguage:(NSString *)language byVendor:(NSString *)vendor;
- (NSArray *) _suggestGuessesForWord: (NSString *)	word 
                          inLanguage: (NSString *)	language;
- (BOOL)isWordInUserDictionaries:(NSString *)word
        caseSensitive:(BOOL)checkCase;
/* Waits for spell-check request to come in. */
- (void)run;

@end


/* This is the protocol the object in the server that does the real
 * work must respond to.  The first method checks spelling and the
 * second suggests proper corrections.  The third and fourth allow the
 * delegate to be notified when new words are learned or forgotten.
 * Only the first method is required.
 *
 * The argument wordCount is an out parameter.  It should return the
 * number of words found in the document from startPosition until the
 * misspelled word was found (or the end of the stream) If your spell
 * server can't count words (though it is hard to imagine why that
 * might be), return -1 in wordCount.  countOnly of Yes means forget
 * about checking the spelling of words, just count them until you get
 * to the end of the stream. */


@interface NSObject(NSSpellServerDelegate)

- (NSRange)		spellServer: (NSSpellServer *)	sender 
         findMisspelledWordInString: (NSString *)	stringToCheck 
		           language: (NSString *)	language 
	                  wordCount: (int *)		wordCount 
	                  countOnly: (BOOL)		countOnly;

- (NSArray *) spellServer: (NSSpellServer *)	sender 
    suggestGuessesForWord: (NSString *)		word 
               inLanguage: (NSString *)		language;

- (void) spellServer: (NSSpellServer *)	sender 
	didLearnWord: (NSString *)	word 
	  inLanguage: (NSString *)	language;

- (void) spellServer: (NSSpellServer *)	sender 
       didForgetWord: (NSString *)	word 
	  inLanguage: (NSString *)	language;

@end

// EOF
