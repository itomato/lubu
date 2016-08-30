#ifndef EVENT_H
#define EVENT_H

#ident "@(#) event.h, Rev 3.5, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
// 	portions (c) Copyright 1988, NeXT, Inc.
//	All rights reserved.


#import <DPS/dpsfriends.h>
#import <Foundation/NSGeometry.h>

typedef	NSPoint	NXPoint;
typedef NSSize	NXSize;
typedef	NSRect	NXRect;

#define NX_NULLEVENT		0	/* internal use */

/* mouse events */

#define NX_LMOUSEDOWN		1	/* left mouse-down event	*/
#define NX_LMOUSEUP		2	/* left mouse-up event		*/
#define NX_RMOUSEDOWN		3	/* right mouse-down event	*/
#define NX_RMOUSEUP		4	/* right mouse-up event		*/
#define NX_MOUSEMOVED		5	/* mouse-moved event		*/
#define NX_LMOUSEDRAGGED	6	/* left mouse-dragged event	*/
#define NX_RMOUSEDRAGGED	7	/* right mouse-dragged event	*/
#define NX_MOUSEENTERED		8	/* mouse-entered event		*/
#define NX_MOUSEEXITED		9	/* mouse-exited event		*/

/* keyboard events */

#define NX_KEYDOWN		10	/* key-down event		*/
#define NX_KEYUP		11	/* key-up event			*/
#define NX_FLAGSCHANGED		12	/* flags-changed event		*/

/* composite events */

#define NX_KITDEFINED		13	/* appkit-defined event		*/
#define NX_SYSDEFINED		14	/* system-defined event		*/
#define NX_APPDEFINED		15	/* application-defined event	*/
#define NX_TIMER		16	/* timer used for tracking	*/
#define NX_CURSORUPDATE		17	/* cursor tracking event	*/
#define NX_JOURNALEVENT		18	/* event used by journaling	*/
#define NX_RESERVEDEVENT4	19	/* reserved			*/
#define NX_RESERVEDEVENT5	20	/* reserved			*/
#define NX_RESERVEDEVENT6	21	/* reserved			*/
#define NX_RESERVEDEVENT7	22	/* reserved			*/
#define NX_RESERVEDEVENT8	23	/* reserved			*/
#define NX_RESERVEDEVENT9	24	/* reserved			*/
#define NX_RESERVEDEVENT10	25	/* reserved			*/
#define NX_RESERVEDEVENT11	26	/* reserved			*/
#define NX_RESERVEDEVENT12	27	/* reserved			*/
#define NX_RESERVEDEVENT13	28	/* reserved			*/
#define NX_RESERVEDEVENT14	29	/* reserved			*/
#define NX_RESERVEDEVENT15	30	/* reserved			*/
#define NX_RESERVEDEVENT16	31	/* reserved			*/

#define NX_FIRSTEVENT		0
#define NX_LASTEVENT		18

#ifndef	_NSApplication_h_

/* KITDEFINED subtypes */
 
#define NX_WINEXPOSED           0
#define NX_APPACT               1
#define NX_APPDEACT             2
#define NX_WINMOVED             4
#define NX_APPHIDE		7
#define NX_APPACTDEFERRED	9
#define	NX_APPUNHIDE		10

#ifndef OPENSTEP
#define NX_SCREENCHANGED        8       // noop under X11
#endif  /* OPENSTEP */

#define NX_WINRESIZED           11

/* SYSDEFINED subtypes */
 
#define NX_POWEROFF             1

#endif	/* _NSApplication_h_ */

#define NX_MOUSEDOWN		NX_LMOUSEDOWN		/* Synonym	*/
#define NX_MOUSEUP		NX_LMOUSEUP		/* Synonym	*/
#define	NX_MOUSEDRAGGED		NX_LMOUSEDRAGGED	/* Synonym	*/


/* Event masks */

#define NX_NULLEVENTMASK	(1 << NX_NULLEVENT)	/* a non-event	    */
#define NX_LMOUSEDOWNMASK	(1 << NX_LMOUSEDOWN)	/* left mouse-down  */
#define NX_LMOUSEUPMASK		(1 << NX_LMOUSEUP)	/* left mouse-up    */
#define NX_RMOUSEDOWNMASK	(1 << NX_RMOUSEDOWN)	/* right mouse-down */
#define NX_RMOUSEUPMASK		(1 << NX_RMOUSEUP)	/* right mouse-up   */
#define NX_MOUSEMOVEDMASK	(1 << NX_MOUSEMOVED)	/* mouse-moved	    */
#define NX_LMOUSEDRAGGEDMASK	(1 << NX_LMOUSEDRAGGED)	/* left-dragged	    */
#define NX_RMOUSEDRAGGEDMASK	(1 << NX_RMOUSEDRAGGED)	/* right-dragged    */
#define NX_MOUSEENTEREDMASK	(1 << NX_MOUSEENTERED)	/* mouse-entered    */
#define NX_MOUSEEXITEDMASK	(1 << NX_MOUSEEXITED)	/* mouse-exited     */
#define NX_KEYDOWNMASK		(1 << NX_KEYDOWN)	/* key-down         */
#define NX_KEYUPMASK		(1 << NX_KEYUP)		/* key-up	    */
#define NX_FLAGSCHANGEDMASK	(1 << NX_FLAGSCHANGED)	/* flags-changed    */
#define NX_KITDEFINEDMASK 	(1 << NX_KITDEFINED)	/* appkit-defined   */
#define NX_APPDEFINEDMASK 	(1 << NX_APPDEFINED)	/* app-defined      */
#define NX_SYSDEFINEDMASK 	(1 << NX_SYSDEFINED)	/* system-defined   */
#define NX_TIMERMASK		(1 << NX_TIMER)		/* tracking timer   */
#define NX_CURSORUPDATEMASK	(1 << NX_CURSORUPDATE)	/* cursor trackingi */
#define NX_JOURNALEVENTMASK	(1 << NX_JOURNALEVENT)	/* journaling event */
#define NX_RESERVEDEVENT4MASK	(1 << NX_RESERVEDEVENT4)	/* reserved */
#define NX_RESERVEDEVENT5MASK	(1 << NX_RESERVEDEVENT5)	/* reserved */
#define NX_RESERVEDEVENT6MASK	(1 << NX_RESERVEDEVENT6)	/* reserved */
#define NX_RESERVEDEVENT7MASK	(1 << NX_RESERVEDEVENT7)	/* reserved */
#define NX_RESERVEDEVENT8MASK	(1 << NX_RESERVEDEVENT8)	/* reserved */
#define NX_RESERVEDEVENT9MASK	(1 << NX_RESERVEDEVENT9)	/* reserved */
#define NX_RESERVEDEVENT10MASK	(1 << NX_RESERVEDEVENT10)	/* reserved */
#define NX_RESERVEDEVENT11MASK	(1 << NX_RESERVEDEVENT11)	/* reserved */
#define NX_RESERVEDEVENT12MASK	(1 << NX_RESERVEDEVENT12)	/* reserved */
#define NX_RESERVEDEVENT13MASK	(1 << NX_RESERVEDEVENT13)	/* reserved */
#define NX_RESERVEDEVENT14MASK	(1 << NX_RESERVEDEVENT14)	/* reserved */
#define NX_RESERVEDEVENT15MASK	(1 << NX_RESERVEDEVENT15)	/* reserved */
#define NX_RESERVEDEVENT16MASK	(1 << NX_RESERVEDEVENT16)	/* reserved */

#define	NX_MOUSEDOWNMASK	NX_LMOUSEDOWNMASK	/* Synonym */
#define NX_MOUSEUPMASK		NX_LMOUSEUPMASK		/* Synonym */
#define	NX_MOUSEDRAGGEDMASK	NX_LMOUSEDRAGGEDMASK	/* Synonym */

#define NX_EVENTCODEMASK(type) (1 << (type))
#define NX_ALLEVENTS	-1	/* Check for all events */

/* masks for the bits in the flags field */
/* Device-independent bits */

#define	NX_ALPHASHIFTMASK	(1 << 16)	/* if alpha lock is on	  */
#define	NX_SHIFTMASK		(1 << 17)	/* if shift key is down   */
#define NX_CONTROLMASK		(1 << 18)	/* if control key is down */
#define NX_ALTERNATEMASK	(1 << 19)	/* if alt key is down     */
#define NX_COMMANDMASK		(1 << 20)	/* if command key is down */
#define NX_NUMERICPADMASK	(1 << 21)	/* if key on numeric pad  */
#define NX_HELPMASK		(1 << 22)	/* if help key is down    */

/* Device-dependent bits */

#define NX_NEXTCTRLKEYMASK	(1 << 0)	/* control key		  */
#define NX_NEXTLSHIFTKEYMASK	(1 << 1)	/* left side shift key	  */
#define NX_NEXTRSHIFTKEYMASK	(1 << 2)	/* right side shift key	  */
#define NX_NEXTLCMDKEYMASK	(1 << 3)	/* left side command key  */
#define NX_NEXTRCMDKEYMASK	(1 << 4)	/* right side command key */
#define NX_NEXTLALTKEYMASK	(1 << 5)	/* left side alt key	  */
#define NX_NEXTRALTKEYMASK	(1 << 6)	/* right side alt key	  */
#define NX_STYLUSPROXIMITYMASK	(1 << 7)	/* if stylus is in proximity
						 * (for tablets)
						 */
#define NX_NONCOALSESCEDMASK	(1 << 8)	/* event was generated with
						 * event coalescing disabled
						 */

/*
 * click state values If you have the following event in close succession,
 * the click field has the indicated value:
 *
 * Event		Click Value	Comments
 * mouse-down		1		Not part of any click yet
 * mouse-up		1		Aha! A click! 
 * mouse-down		2 		Doing a double-click
 * mouse-up		2		It's finished
 * mouse-down		3		A triple
 * mouse-up		3
 */

/* Values for the character set in event.data.key.charSet */

#define	NX_ASCIISET		0
#define NX_SYMBOLSET		1
#define	NX_DINGBATSSET		2

/* EventData type: defines the data field of an event */

typedef union {
	struct {				/* For mouse events */
		short           reserved;
		short           eventNum;	/* unique identifier for this
						 * button
						 */

		int             click;		/* click state of this event */

		unsigned char   pressure;	/* pressure value:
						 * 0=none,
						 * 255=full
						 */
		char            reserved1;
		short           reserved2;
	} mouse;

	struct {				/* For key events */
		short           reserved;
		short           repeat;		/* for key-down:
						 * nonzero if really a repeat
						 */

		unsigned short  charSet;	/* character set code */
		unsigned short  charCode;	/* character code in that set */

		unsigned short  keyCode;	/* device-dependent key
						 * number
						 */

		short           keyData;	/* device-dependent info */
	} key;

	struct {		/* For mouse-entered and mouse-exited events */
		short           reserved;
		short           eventNum;	/* unique identifier from
						 * mouse down event
						 */

		int             trackingNum;	/* unique identifier from
						 * settrackingrect
						 */

		int             userData;	/* uninterpreted integer from
						 * settrackingrect
						 */
	} tracking;

	struct {		/* For appkit-defined, sys-defined, and
				 * app-defined events
				 */
		short           reserved;
		short           subtype;	/* event subtype for compound
						 * events
						 */
		union {
			float           F[2];	/* for use in compound events */
			long            L[2];	/* for use in compound events */
			short           S[4];	/* for use in compound events */
			char            C[8];	/* for use in compound events */
		} misc;
	} compound;
} NXEventData;

/* Finally! The event record! */

typedef struct _NXEvent {
	int             type;		/* An event type from above	    */
	NXPoint         location;	/* Base coordinates in window, from
					 * lower-left
					 */

	long            time;		/* vertical intervals since launch  */
	int             flags;		/* key state flags		    */
	unsigned int    window;		/* window number of assigned window */
	NXEventData     data;		/* type-dependent data		    */
	DPSContext      ctxt;		/* context the event came from	    */
} NXEvent, *NXEventPtr;
#endif /* EVENT_H */
