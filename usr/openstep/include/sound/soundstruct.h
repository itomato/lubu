#ident "@(#) soundstruct.h, Rev 2.3, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//      portions (c) Copyright 1988-89 NeXT, Inc.
//	All rights reserved.

/*
 * SNDSoundStruct - This data format for sound is used as the soundfile
 * format, and also the "NeXT sound pasteboard type". It consists of a header
 * and two variable length quantities: textual information (the info string)
 * and raw data. The raw data starts past the info; the dataLocation is
 * normally used to specify an offset from the beginning of the SNDSoundStruct
 * structure to this data. The dataSize is the length of the raw data in bytes. 
 * The dataFormat, samplingRate, and channelCount further describe the data.
 * The data itself may be anything; the format determines what the data
 * actually means (i.e. sample data, dsp core structure).
 * The magic number value may be used to determine the byte order of the data.
 * The info string is any null-terminated data that the application may need
 * (i.e. copyright information, textual description). The four bytes allocated
 * are a minimum; the info string may extend any length beyond the structure.
 */

#ifndef __SOUNDSTRUCT__
#define __SOUNDSTRUCT__

typedef struct {
    int magic;          /* must be equal to SND_MAGIC */
    int dataLocation;   /* Offset or pointer to the raw data */
    int dataSize;       /* Number of bytes of data in the raw data */
    int dataFormat;     /* The data format code */
    int samplingRate;   /* The sampling rate */
    int channelCount;   /* The number of channels */
    char info[4];       /* Textual information relating to the sound. */
} SNDSoundStruct;


/*
 * The magic number must appear at the beginning of every SNDSoundStruct.
 * It is used for type checking and byte ordering information.
 */
#define SND_MAGIC ((int)0x2e736e64)

/*
 * NeXT data format codes. User-defined formats should be greater than 255.
 * Negative format numbers are reserved.
 */
#define SND_FORMAT_UNSPECIFIED          (0)
#define SND_FORMAT_MULAW_8              (1)
#define SND_FORMAT_LINEAR_8             (2)
#define SND_FORMAT_LINEAR_16            (3)
#define SND_FORMAT_LINEAR_24            (4)
#define SND_FORMAT_LINEAR_32            (5)
#define SND_FORMAT_FLOAT                (6)
#define SND_FORMAT_DOUBLE               (7)
#define SND_FORMAT_INDIRECT             (8)
#define SND_FORMAT_NESTED               (9)
#define SND_FORMAT_DSP_CORE             (10)
#define SND_FORMAT_DSP_DATA_8           (11)
#define SND_FORMAT_DSP_DATA_16          (12)
#define SND_FORMAT_DSP_DATA_24          (13)
#define SND_FORMAT_DSP_DATA_32          (14)
#define SND_FORMAT_DISPLAY              (16)
#define SND_FORMAT_MULAW_SQUELCH        (17)
#define SND_FORMAT_EMPHASIZED           (18)
#define SND_FORMAT_COMPRESSED           (19)
#define SND_FORMAT_COMPRESSED_EMPHASIZED (20)
#define SND_FORMAT_DSP_COMMANDS         (21)
#define SND_FORMAT_DSP_COMMANDS_SAMPLES (22)
#define SND_FORMAT_ADPCM_G721           (23)
#define SND_FORMAT_ADPCM_G722           (24)
#define SND_FORMAT_ADPCM_G723_3         (25)
#define SND_FORMAT_ADPCM_G723_5         (26)
#define SND_FORMAT_ALAW_8               (27)
#define SND_FORMAT_AES                  (28)
#define SND_FORMAT_DELTA_MULAW_8	(29)

/*
 * Compression subheader which appears at the beginning of the data 
 * (after the SNDSoundStruct header) in a compressed sound.
 */
typedef struct {
    int originalSize;           /* in bytes */
    int method;                 /* e.g. SND_CFORMAT_ATC (below) */
    int numDropped;             /* for SND_CFORMAT_BITS_DROPPED */
    int encodeLength;           /* uncompressed samples per encoded block */
    int reserved;
} SNDCompressionSubheader;

/*
 * Compression types
 */
#define SND_CFORMAT_BITS_DROPPED        (0)
#define SND_CFORMAT_BIT_FAITHFUL        (1)
#define SND_CFORMAT_ATC                 (2) /* Audio Transform Compression*/

/* 
 * After the compression subheader, each frame of an ATC-format soundfile
 * begins with two bytes which characterize the frame as follows:
 * 
 * Byte 	Contents
 * -----	--------
 *   0		Frame length in bytes, including these 2 leading bytes
 *   1		Peak level for the frame, in log-base-2 relative to 0dB.
 *
 * With these two bytes, an amplitude envelope can be constructed as follows:
 * 
 *	SNDCompressionSubheader *subheader = ((unsigned char *)soundPtr) 
 *					+ soundPtr->dataLocation;
 *      unsigned char *fp = ((unsigned char *)subheader)
 *					+ sizeof(SNDCompressionSubheader);
 *      for (sample=0; sample < subheader->originalSize/sizeof(short);) {
 *          frameSize = *fp;
 *          frameExponent = *(fp+1);
 *          frameAmplitude = (32767 >> frameExponent); // approx amplitude
 *          fp += frameSize;
 *          sample += ATC_FRAME_SIZE;  // sample count represented by frame
 *          ...
 *      }
 *
 * where ATC_FRAME_SIZE is the number of samples of the original sound
 * which were compressed to create each frame, defined below.
 *
 * For stereo sounds, left and right channels are frame-interleaved.
 * The first frame is a left-channel frame, the second is right, and so on.
 *
 * For mono sounds, and for each channel of a stereo sound, the frames
 * are best handled in successive pairs.  For example, to modify the playback
 * speed of a sound by repeating or deleting frames, adjacent pairs of frames
 * should be repeated or deleted.  Similarly, playing a sound from an interior
 * point should begin on an "even" frame boundary, where frame 0 is the first.
 * This restriction is because ATC alternates the discrete sine transform (DST)
 * with the discrete cosine transform (DCT) on a frame by frame basis.
 *
 */
#define ATC_FRAME_SIZE (256)

/*
 * Sampling rates directly supported in hardware.
 */
#define SND_RATE_CODEC          (8012.8210513)
#define SND_RATE_LOW            (22050.0)
#define SND_RATE_HIGH           (44100.0)
#define SND_RATE_LOW_PC         (11025.0)

#endif __SOUNDSTRUCT__
