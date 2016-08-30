#ident "@(#) convertsound.h, Rev 2.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
// 	portions (c) Copyright 1988-89 NeXT, Inc.
//	All rights reserved.

#import "soundstruct.h"
#import "sounderror.h"

#ifdef __cplusplus
extern "C" {
#endif

unsigned char SNDMulaw(short n);
short SNDiMulaw(unsigned char m);
/*
 * Routines to convert from 8 bit mulaw sound to/from 16 linear sound.
 * SNDMulaw returns the mulaw value for the given 16 bit linear value,
 * and SNDiMulaw returns the 16 bit linear value for the given mulaw value.
 */

int SNDConvertSound(SNDSoundStruct *s1, SNDSoundStruct **s2);
/*
 * Routine to convert the sound specified by s1 into a new sound designated
 * by the header s2, which identifies the resultant data format, channel count,
 * and sampling rate. If the dataSize in s2 is non-zero, then the s2's data 
 * contains optional arguments for the conversion (these arguments are
 * conversion-specific). A new SNDSoundStruct is created which contains the
 * converted sound, and s2 is set to point at it. An error code is returned.
 */

int SNDCompatible(SNDSoundStruct *s1, SNDSoundStruct *s2);
/*
 * Routine to tell you whether s1 needs to be converted to s2 or not.
 */

#ifdef __cplusplus
}
#endif

