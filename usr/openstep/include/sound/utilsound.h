#ident "@(#) utilsound.h, Rev 2.6, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
// 	portions (c) Copyright 1988-89 NeXT, Inc.
//	All rights reserved.

#import "soundstruct.h"
#import "sounderror.h"
#import <Foundation/NSString.h>

#ifdef __cplusplus
extern "C" {
#endif

int SNDSampleCount(SNDSoundStruct *s);
/*
 * Returns the number of sample frames in the sound. If the format is not
 * recognized, or the sample count cannot be determined, then -1 is 
 * returned.
 */

int SNDGetDataPointer(SNDSoundStruct *s, char **ptr, int *size, int *width);
/*
 * Return a pointer to the data portion of a soundstruct in ptr, the
 * number of samples (NOT sample frames) in size, and the number of bytes per
 * sample in width. Fragmented sounds return an error.
 * Returns an error code.
 */

int SNDBytesToSamples(int byteCount, int channelCount, int dataFormat);
int SNDSamplesToBytes(int sampleCount, int channelCount, int dataFormat);

/*
 * Converts bytes to samples and the converse, given also the channelCount
 * and dataFormat. If the dataFormat is not recognized, then a negative value 
 * is returned.
 * The number returned from SNDSamplesToBytes is useful as the "dataSize" 
 * argument to SNDAlloc.
 */

NSString *SNDSoundFormatDescription(int formatCode);
/*
 * Returns a plausible string explanation of the given format.
 */

int SNDAlloc(SNDSoundStruct **s,
	     int dataSize, 
	     int dataFormat,
	     int samplingRate,
	     int channelCount,
	     int infoSize);
/*
 * Allocate a sound structure and initialize its fields. The actual sample
 * data is uninitialized, and the info string buffer is extended to the 
 * smallest quad boundary greater than zero. Both the dataSize and infoSize
 * are expressed in bytes. An error code is returned.
 * If no error, then a pointer to the allocated data is returned in "s".
 */

int SNDFree(SNDSoundStruct *s);
/*
 * Frees "s", which was created and returned by one of the sound library
 * routines.
 */

int SNDPlaySoundfile(char *path, int priority);
/*
 * Play the soundfile specified by path. Playback occurs in the background,
 * and this routine returns immediately. Playback interrupts any currently
 * playing sound of the same or lower priority. When playback completes, 
 * the storage allocated by this function is automatically deallocated.
 * An error code is returned.
 */

/* New for 3.1 */
int SNDSwapHostToSound(void *dest, void *src, int sampleCount,
		       int channelCount, int dataFormat);
int SNDSwapSoundToHost(void *dest, void *src, int sampleCount,
		       int channelCount, int dataFormat);
#ifdef __cplusplus
}
#endif
