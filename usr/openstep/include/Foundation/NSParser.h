#ident "@(#) NSParser.h, Rev 1.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Parsing utilities

#import <Foundation/NSDictionary.h>
#import <Foundation/NSSet.h>
#ifdef __cplusplus 
extern "C" {
#endif

/***************	General Parser (PRIVATE)	***************/
// This class should (for now) be considered private

@interface NSParser:NSObject {
    NSDictionary	*grammar;
    unichar		*input;
    unsigned		inputLength;
    unsigned		inputPos;
    unsigned		inputLine;	/* for error messages */
    NSRange		tokenRange;
    unichar		*tokenBuffer;
    unsigned		tokenMax;
    unsigned		tokenCount;
    BOOL		tokenBufferReady;
    BOOL		tokenIsASCII;
    int			tokenFirst;
    char		tokenType;
    NSMutableArray	*parseStack; /* for error messages */
    unichar		*tokenStarters;
    unsigned		tokenStartersCount;
    unichar		*tokenFinishers;
    unsigned		tokenFinishersCount;
    NSMutableSet	*allStrings;
    unsigned		reserved; // to preserve size to be nice to subclassers
}

+ (NSDictionary *)parseGrammarFrom:(NSString *)grammarString;
    /* parses a grammar given the grammar definition */

- (id)initWithGrammar:(NSDictionary *)gram fromString:(NSString *)input;
    /* makes a new parse given a string */

- (void)setTokenStarters:(NSString *)starters;
    /* augment the set of characters that can start a token, e.g. @"_$" */

- (void)setTokenFinishers:(NSString *)finishers;
    /* augment the set of characters that can be in a token, e.g. @"/." */
    
- (void)parseError:(NSString *)format, ...;
    /* note that an error has occured */

/*
 * the following parseXXX methods either accept their XXX or
 * return nil
 */
 
- (id)parse:(NSString *)unit;

- (id)expect:(NSString *)unit;
    /* same as parse but raises if unit not found */
    
- (void)expectEndOfInput;

- (NSString *)parseToken;
    /* accepts a non quoted token */

- (NSString *)peekToken;
    /* tests for a non quoted token */

- (NSString *)parseQuotedString;
    /* accepts a quoted string */

- (NSString *)parseString;
    /* accepts a non quoted token or a quoted string */

- (NSString *)parseKeyword:(NSString *)keyword;

- (BOOL)parseMonochar:(unichar)ch;

- (void)expectMonochar:(unichar)ch;

- (NSString *)parseAny;
    /* Returns the next token, whatever that was */

- (NSArray *)parseSuiteOf:(NSString *)unit separator:(unichar)sep butoir:(unichar)butoir;
    /* {unit separator}* {unit}? butoir   accepted,
    /* i.e. last separator is optional, butoir is required */

- (NSDictionary *)parseSuiteOfPairsKey:(NSString *)keyUnit value:(NSString *)valueUnit;
    /* private: {key '=' unit ';'}*, last ';' optional if '}' seen */

- (NSDictionary *)parseDictionaryOfKey:(NSString *)keyUnit value:(NSString *)valueUnit;

- (NSDictionary *)parseDictionaryBracketLess;

- (NSArray *)parseArrayOf:(NSString *)unit :(unichar)beginPar :(unichar)separ :(unichar)endPar;

- (NSArray *)parseArrayOf:(NSString *)unit;

- (NSData *)parseData;

@end

extern NSString *NSParseErrorException;
#ifdef __cplusplus 
}
#endif
