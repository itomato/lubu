#ident "@(#) sounderror.h, Rev 2.4, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
// 	portions (c) Copyright 1988-89 NeXT, Inc.
//	All rights reserved.

typedef enum {
    SND_ERR_NONE		= 0,
    SND_ERR_NOT_SOUND		= 1,
    SND_ERR_BAD_FORMAT		= 2,
    SND_ERR_BAD_RATE		= 3,
    SND_ERR_BAD_CHANNEL		= 4,
    SND_ERR_BAD_SIZE		= 5,
    SND_ERR_BAD_FILENAME	= 6,
    SND_ERR_CANNOT_OPEN		= 7,
    SND_ERR_CANNOT_WRITE	= 8,
    SND_ERR_CANNOT_READ		= 9,
    SND_ERR_CANNOT_ALLOC	= 10,
    SND_ERR_CANNOT_FREE		= 11,
    SND_ERR_CANNOT_COPY		= 12,
    SND_ERR_CANNOT_RESERVE	= 13,
    SND_ERR_NOT_RESERVED	= 14,
    SND_ERR_CANNOT_RECORD	= 15,
    SND_ERR_ALREADY_RECORDING	= 16,
    SND_ERR_NOT_RECORDING	= 17,
    SND_ERR_CANNOT_PLAY		= 18,
    SND_ERR_ALREADY_PLAYING	= 19,
    SND_ERR_NOT_PLAYING		= 20,
    SND_ERR_NOT_PAUSED          = 21,
    SND_ERR_NOT_IMPLEMENTED	= 22,
    SND_ERR_CANNOT_FIND		= 23,
    SND_ERR_CANNOT_EDIT		= 24,
    SND_ERR_BAD_SPACE		= 25,
    SND_ERR_KERNEL		= 26,
    SND_ERR_BAD_CONFIGURATION	= 27,
    SND_ERR_CANNOT_CONFIGURE	= 28,
    SND_ERR_UNDERRUN		= 29,
    SND_ERR_ABORTED		= 30,
    SND_ERR_BAD_TAG		= 31,
    SND_ERR_CANNOT_ACCESS	= 32,
    SND_ERR_TIMEOUT		= 33,
    SND_ERR_BUSY		= 34,
    SND_ERR_CANNOT_ABORT	= 35,
    SND_ERR_INFO_TOO_BIG	= 36,
    SND_ERR_UNKNOWN=32767
} SNDError;

char *SNDSoundError(int err);
/*
 * This routine returns a pointer to a string that describes the
 * given error code. 
 */

