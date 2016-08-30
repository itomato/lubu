#ident "@(#) editsound.h, Rev 2.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
// 	portions (c) Copyright 1988-89 NeXT, Inc.
//	All rights reserved.

#import "soundstruct.h"
#import "sounderror.h"

#ifdef __cplusplus
extern "C" {
#endif

int SNDCopySound(SNDSoundStruct **s1, SNDSoundStruct *s2);
int SNDCopySoundWithInfo(SNDSoundStruct **s1, SNDSoundStruct *s2, const char *infostring);
int SNDCopySamples(SNDSoundStruct **s1, SNDSoundStruct *s2,
		   int startSample, int sampleCount);
/*
 * Copy a segment of the sound s2 (specified by offset samples from the
 * beginning and running for count samples), into a newly allocated
 * SNDSoundStruct; s1 is set to point at the new SNDSoundStruct. 
 * The SNDCopySound function copies the entire sound, and works for
 * any type of sound, including dsp sounds.
 * An error code is returned. s2 is unaffected by this operation.
 */

int SNDInsertSamples(SNDSoundStruct *s1, SNDSoundStruct *s2, int startSample);
/*
 * Insert a copy of the sound s2 into the sound s1 at a position specified by 
 * offset. This operation may leave s1 fragmented; s2 is unaffected.
 */

int SNDDeleteSamples(SNDSoundStruct *s, int startSample, int sampleCount);
/*
 * Delete the segment of the sound s specified by startSample samples from 
 * the beginning and running for sampleCount samples. This operation may
 * leave s fragmented. The memory occupied by the segment of sound is freed.
 */

int SNDCompactSamples(SNDSoundStruct **s1, SNDSoundStruct *s2);
/*
 * Create a new sound s1 as a compacted version of the the sound s2.
 * Compaction eliminates the fragmentation caused by
 * insertion and deletion. An error code is returned.
 */

int SNDReverseSound(SNDSoundStruct *snd);
/*
 * Reverse the sound (only if mulaw)
 */

#ifdef __cplusplus
}
#endif
