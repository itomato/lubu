#ident "@(#) performsound.h, Rev 2.8, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
// 	portions (c) Copyright 1988-89 NeXT, Inc.
//	All rights reserved.
//
// 	recording and playback of sound.

#import "soundstruct.h"
#import "sounderror.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*SNDNotificationFun)(SNDSoundStruct *s, int tag, SNDError err);
#define SND_NULL_FUN ((SNDNotificationFun)0)
#define SND_DEFAULT_NEWSOUND_LENGTH 20
/*
 * Notification functions are called when some event occurs in the sound 
 * library, and are always explicitly given to the sound library (i.e. as
 * arguments in SNDStartPlaying).
 * They always take three arguments: the sound structure, the tag, and
 * an error code.
 * The integer returned is ignored.
 */

int SNDPause();
int SNDResume();

int SNDStartPlaying(SNDSoundStruct *s, int tag, int priority, int preempt,
		    SNDNotificationFun beginFun, SNDNotificationFun endFun,
		    SNDNotificationFun updateFun);
/*
 * Initiates the playing of the sound "s". This function returns
 * immediately, and playing continues in the background until the
 * the entire sound has been played.
 * The tag is used for identification of the sound for the SNDStop, 
 * SNDWait, and SNDSamplesProcessed routines. It must be unique.
 * The priority is used to help resolve conflict if the sound cannot
 * be immediately played. Higher priorities can cause interruption
 * of lower priority sounds. Zero is defined to be lowest priority,
 * and larger numbers are of higher priority. Negative priorities are
 * reserved. When a sound is interrupted, it may not be resumed (i.e. an
 * interruption is equivalent to an abort).
 * The preempt flag, when non-zero, allows the sound to interrupt other
 * sounds of equal or inferior priority. If preempt is zero, then the sound is
 * enqueued for playback on a first-come-first-served basis (the priority is
 * not used to determine when to play the sound, but rather only to determine
 * what can interrupt it while it is playing).
 * Both the beginFun and endFun are optional: when non-null, they call
 * the given function with the soundstruct, tag, and an error code as
 * arguments, when playback of the  sound begins and ends, respectively.
 * updateFun, also optional, is called at 1/10 s intervals for purposes
 * of updating a UI on the sound's progress.
 * These functions are called in the context of a background thread. 
 * This routine returns an error if the sound cannot be played.
 */

int SNDWait(int tag);
/*
 * Return only when playback or recording of the sound matching the given tag 
 * has completed. If several requests have the same tag, the last one is
 * waited for.
 * An error code is returned.
 */

int SNDStop(int tag);
/*
 * Terminates the playback or recording of sound with the given tag.
 * An error code is returned.
 */

int SNDStartRecording(SNDSoundStruct *s, int tag, int priority, int preempt,
		     SNDNotificationFun beginFun, SNDNotificationFun endFun, SNDNotificationFun updateFun);
/*
 * Begins recording into the specified sound structure.
 * The codec type and compressed types are supported.
 */

int SNDStartRecordingFile(char *fileName, SNDSoundStruct *s,
			  int tag, int priority, int preempt,
			  SNDNotificationFun beginFun, SNDNotificationFun endFun, SNDNotificationFun updateFun);
/*
 * Same as SNDStartRecording() but writes directly to file fileName.  The sound data
 * is NOT returned in "s".
 */

int SNDSamplesProcessed(int tag);
/*
 * Return a count of the number of samples played or recorded in the sound 
 * matching the given tag.
 * A negative return value indicates an error.
 */

int SNDModifyPriority(int tag, int new_priority);
/*
 * Modifies the priority of the sound matching the given tag.
 * This could cause the sound to either be interrupted or played
 * immediately.
 * An error code is returned.
 */

int SNDSetVolume(int left, int right);
int SNDGetVolume(int *left, int *right);
/*
 * Get/set the volume of the sound for left and right channels.
 * The line out jacks on the back of the monitor are not affected;
 * only the speaker (if it is not muted) and the headphone levels
 * are affected.
 * An error code is returned.
 *  
 */

int SNDSetMute(int speakerOn);
int SNDGetMute(int *speakerOn);
/*
 * Set/get the state of the monitor's built-in speaker. Zero indicates
 * that the speaker is silent. This does not affect the line out jacks
 * on the back of the monitor -- they are always enabled.
 * An error code is returned.
 */


int SNDVerifyPlayable(SNDSoundStruct *s);
/*
 * Returns SND_ERR_NONE (0) if sound is in a playable format, or
 * SND_ERR_CANNOT_PLAY if it requires format conversion in advance
 * of playing (or if it is inherently unplayable such as format
 * SND_FORMAT_DSP_CORE).
 */
#ifdef __cplusplus
}
#endif
