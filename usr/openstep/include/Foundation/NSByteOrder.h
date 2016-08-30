#ident "@(#) NSByteOrder.h, Rev 1.2, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	portions (c) Copyright 1994, NeXT Computer, Inc.
//	All rights reserved.
//
//	Definitions for low-level byte swapping

#if !defined(STRICT_OPENSTEP)

#ifdef __GNUC__
#define INLINE __inline__
#elif defined(__cplusplus)
#define INLINE inline
#else
#define INLINE
#endif

#if defined(sparc)
#if !defined(__BIG_ENDIAN__)
#define __BIG_ENDIAN__
#endif
#elif defined(i386)
#if !defined(__LITTLE_ENDIAN__)
#define __LITTLE_ENDIAN__
#endif
#else
#error "Architecture not supported"
#endif

enum NSByteOrder {
    NS_UnknownByteOrder,
    NS_LittleEndian,
    NS_BigEndian
};

typedef unsigned long NSSwappedFloat;
typedef unsigned long long NSSwappedDouble;

static INLINE enum NSByteOrder NSHostByteOrder(void) {
    unsigned int _x;
    _x = (NS_BigEndian << 24) | NS_LittleEndian;
    return ((enum NSByteOrder)*((unsigned char *)&_x));
}

/****************	Basic arch-dependent swapping	****************/

#if defined(sparc)

static INLINE unsigned short NSSwapShort(unsigned short inv) {
    union sconv {
	unsigned short us;
	unsigned char uc[2];
    } *inp, outv;
    inp = (union sconv *)&inv;
    outv.uc[0] = inp->uc[1];
    outv.uc[1] = inp->uc[0];
    return (outv.us);
}

static INLINE unsigned int NSSwapInt(unsigned int inv) {
    union iconv {
	unsigned int ui;
	unsigned char uc[4];
    } *inp, outv;
    inp = (union iconv *)&inv;
    outv.uc[0] = inp->uc[3];
    outv.uc[1] = inp->uc[2];
    outv.uc[2] = inp->uc[1];
    outv.uc[3] = inp->uc[0];
    return (outv.ui);
}

static INLINE unsigned long NSSwapLong(unsigned long inv) {
    union lconv {
	unsigned long ul;
	unsigned char uc[4];
    } *inp, outv;
    inp = (union lconv *)&inv;
    outv.uc[0] = inp->uc[3];
    outv.uc[1] = inp->uc[2];
    outv.uc[2] = inp->uc[1];
    outv.uc[3] = inp->uc[0];
    return (outv.ul);
}

static INLINE unsigned long long NSSwapLongLong(unsigned long long inv) {
    union llconv {
	unsigned long long ull;
	unsigned char uc[8];
    } *inp, outv;
    inp = (union llconv *)&inv;
    outv.uc[0] = inp->uc[7];
    outv.uc[1] = inp->uc[6];
    outv.uc[2] = inp->uc[5];
    outv.uc[3] = inp->uc[4];
    outv.uc[4] = inp->uc[3];
    outv.uc[5] = inp->uc[2];
    outv.uc[6] = inp->uc[1];
    outv.uc[7] = inp->uc[0];
    return (outv.ull);
}

static INLINE NSSwappedFloat NSConvertHostFloatToSwapped(float x) {
    union fconv {
	float number;
	NSSwappedFloat sf;
    };
    return ((union fconv *)&x)->sf;
}

static INLINE float NSConvertSwappedFloatToHost(NSSwappedFloat x) {
    union fconv {
	float number;
	NSSwappedFloat sf;
    };
    return ((union fconv *)&x)->number;
}

static INLINE NSSwappedDouble NSConvertHostDoubleToSwapped(double x) {
    union dconv {
	double number;
	NSSwappedDouble sd;
    };
    return ((union dconv *)&x)->sd;
}

static INLINE double NSConvertSwappedDoubleToHost(NSSwappedDouble x) {
    union dconv {
	double number;
	NSSwappedDouble sd;
    };
    return ((union dconv *)&x)->number;
}

static INLINE NSSwappedFloat NSSwapFloat(NSSwappedFloat x) {
    return NSSwapLong(x);
}

static INLINE NSSwappedDouble NSSwapDouble(NSSwappedDouble x) {
    return NSSwapLongLong(x);
}



#elif defined(i386)

static INLINE unsigned short NSSwapShort (unsigned short inv) {
    union sconv {
	unsigned short	us;
	unsigned char	uc[2];
    } *inp, outv;
    
    inp = (union sconv *)&inv;
    
    outv.uc[0] = inp->uc[1];
    outv.uc[1] = inp->uc[0];
    
    return (outv.us);
}
 
static INLINE unsigned int NSSwapInt (unsigned int inv) {
    union iconv {
	unsigned int	ui;
	unsigned char	uc[4];
    } *inp, outv;
    
    inp = (union iconv *)&inv;
    
    outv.uc[0] = inp->uc[3];
    outv.uc[1] = inp->uc[2];
    outv.uc[2] = inp->uc[1];
    outv.uc[3] = inp->uc[0];
    
    return (outv.ui);
}
 
static INLINE unsigned long NSSwapLong(unsigned long inv) {
    union lconv {
	unsigned long	ul;
	unsigned char	uc[4];
    } *inp, outv;
    
    inp = (union lconv *)&inv;
    
    outv.uc[0] = inp->uc[3];
    outv.uc[1] = inp->uc[2];
    outv.uc[2] = inp->uc[1];
    outv.uc[3] = inp->uc[0];
    
    return (outv.ul);
}

static INLINE unsigned long long NSSwapLongLong(unsigned long long inv) {
    union llconv {
	unsigned long long ull;
	unsigned long ul[2];
    } *inp, outv;
    inp = (union llconv *)&inv;
    outv.ul[0] = NSSwapLong(inp->ul[1]);
    outv.ul[1] = NSSwapLong(inp->ul[0]);
    return (outv.ull);
}

static INLINE NSSwappedFloat NSConvertHostFloatToSwapped(float x) {
    union fconv {
	float number;
	NSSwappedFloat sf;
    };
    return ((union fconv *)&x)->sf;
}

static INLINE float NSConvertSwappedFloatToHost(NSSwappedFloat x) {
    union fconv {
	float number;
	NSSwappedFloat sf;
    };
    return ((union fconv *)&x)->number;
}

static INLINE NSSwappedDouble NSConvertHostDoubleToSwapped(double x) {
    union dconv {
	double number;
	NSSwappedDouble sd;
    };
    return ((union dconv *)&x)->sd;
}

static INLINE double NSConvertSwappedDoubleToHost(NSSwappedDouble x) {
    union dconv {
	double number;
	NSSwappedDouble sd;
    };
    return ((union dconv *)&x)->number;
}

static INLINE NSSwappedFloat NSSwapFloat(NSSwappedFloat x) {
    return NSSwapLong(x);
}

static INLINE NSSwappedDouble NSSwapDouble(NSSwappedDouble x) {
    return NSSwapLongLong(x);
}


#else
#error "Architecture not supported"
#endif

/*************** Swapping to big/little endian ***************/

#if defined(__BIG_ENDIAN__)

static INLINE unsigned short NSSwapBigShortToHost(unsigned short x) {
    return (x);
}

static INLINE unsigned int NSSwapBigIntToHost(unsigned int x) {
    return (x);
}

static INLINE unsigned long NSSwapBigLongToHost(unsigned long x) {
    return (x);
}

static INLINE unsigned long long NSSwapBigLongLongToHost(unsigned long long x) {
    return (x);
}

static INLINE double NSSwapBigDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(x);
}

static INLINE float NSSwapBigFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(x);
}

static INLINE unsigned short NSSwapHostShortToBig(unsigned short x) {
    return (x);
}

static INLINE unsigned int NSSwapHostIntToBig(unsigned int x) {
    return (x);
}

static INLINE unsigned long NSSwapHostLongToBig(unsigned long x) {
    return (x);
}

static INLINE unsigned long long NSSwapHostLongLongToBig(unsigned long long x) {
    return (x);
}

static INLINE NSSwappedDouble NSSwapHostDoubleToBig(double x) {
    return NSConvertHostDoubleToSwapped(x);
}

static INLINE NSSwappedFloat NSSwapHostFloatToBig(float x) {
    return NSConvertHostFloatToSwapped(x);
}

static INLINE unsigned short NSSwapLittleShortToHost(unsigned short x) {
    return NSSwapShort(x);
}

static INLINE unsigned int NSSwapLittleIntToHost(unsigned int x) {
    return NSSwapInt(x);
}

static INLINE unsigned long NSSwapLittleLongToHost(unsigned long x) {
    return NSSwapLong(x);
}

static INLINE unsigned long long NSSwapLittleLongLongToHost(unsigned long long x) {
    return NSSwapLongLong(x);
}

static INLINE double NSSwapLittleDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(NSSwapDouble(x));
}

static INLINE float NSSwapLittleFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(NSSwapFloat(x));
}

static INLINE unsigned short NSSwapHostShortToLittle(unsigned short x) {
    return NSSwapShort(x);
}

static INLINE unsigned int NSSwapHostIntToLittle(unsigned int x) {
    return NSSwapInt(x);
}

static INLINE unsigned long NSSwapHostLongToLittle(unsigned long x) {
    return NSSwapLong(x);
}

static INLINE unsigned long long NSSwapHostLongLongToLittle(unsigned long long x) {
    return NSSwapLongLong(x);
}

static INLINE NSSwappedDouble NSSwapHostDoubleToLittle(double x) {
    return NSSwapDouble(NSConvertHostDoubleToSwapped(x));
}

static INLINE NSSwappedFloat NSSwapHostFloatToLittle(float x) {
    return NSSwapFloat(NSConvertHostFloatToSwapped(x));
}

#elif defined(__LITTLE_ENDIAN__)

static INLINE unsigned short NSSwapBigShortToHost(unsigned short x) {
    return NSSwapShort(x);
}

static INLINE unsigned int NSSwapBigIntToHost(unsigned int x) {
    return NSSwapInt(x);
}

static INLINE unsigned long NSSwapBigLongToHost(unsigned long x) {
    return NSSwapLong(x);
}

static INLINE unsigned long long NSSwapBigLongLongToHost(unsigned long long x) {
    return NSSwapLongLong(x);
}

static INLINE double NSSwapBigDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(NSSwapDouble(x));
}

static INLINE float NSSwapBigFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(NSSwapFloat(x));
}

static INLINE unsigned short NSSwapHostShortToBig(unsigned short x) {
    return NSSwapShort(x);
}

static INLINE unsigned int NSSwapHostIntToBig(unsigned int x) {
    return NSSwapInt(x);
}

static INLINE unsigned long NSSwapHostLongToBig(unsigned long x) {
    return NSSwapLong(x);
}

static INLINE unsigned long long NSSwapHostLongLongToBig(unsigned long long x) {
    return NSSwapLongLong(x);
}

static INLINE NSSwappedDouble NSSwapHostDoubleToBig(double x) {
    return NSSwapDouble(NSConvertHostDoubleToSwapped(x));
}

static INLINE NSSwappedFloat NSSwapHostFloatToBig(float x) {
    return NSSwapFloat(NSConvertHostFloatToSwapped(x));
}

static INLINE unsigned short NSSwapLittleShortToHost(unsigned short x) {
    return (x);
}

static INLINE unsigned int NSSwapLittleIntToHost(unsigned int x) {
    return (x);
}

static INLINE unsigned long NSSwapLittleLongToHost(unsigned long x) {
    return (x);
}

static INLINE unsigned long long NSSwapLittleLongLongToHost(unsigned long long x) {
    return (x);
}

static INLINE double NSSwapLittleDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(x);
}

static INLINE float NSSwapLittleFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(x);
}

static INLINE unsigned short NSSwapHostShortToLittle(unsigned short x) {
    return (x);
}

static INLINE unsigned int NSSwapHostIntToLittle(unsigned int x) {
    return (x);
}

static INLINE unsigned long NSSwapHostLongToLittle(unsigned long x) {
    return (x);
}

static INLINE unsigned long long NSSwapHostLongLongToLittle(unsigned long long x) {
    return (x);
}

static INLINE NSSwappedDouble NSSwapHostDoubleToLittle(double x) {
    return NSConvertHostDoubleToSwapped(x);
}

static INLINE NSSwappedFloat NSSwapHostFloatToLittle(float x) {
    return NSConvertHostFloatToSwapped(x);
}

#else
#error "Architecture not supported"
#endif

#endif /* !STRICT_OPENSTEP */
