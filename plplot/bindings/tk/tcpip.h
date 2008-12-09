/* $Id: tcpip.h,v 1.4 2002/12/03 08:39:22 airwin Exp $
 *
 * Maurice LeBrun
 * 31-May-95
 *
 * Declarations for IP utility routines.
 * Put here so as not to clutter up user codes.
 */

#ifndef __TCPIP_H__
#define __TCPIP_H__

#include "pdf.h"
#include <tcl.h>

/* Modified version of the "Tdp_PacketSend" command. */

int
pl_PacketSend		PLARGS((Tcl_Interp *interp, PLiodev *iodev,
				PDFstrm *pdfs));

/* Modified version of the "Tdp_PacketReceive" command. */

int
pl_PacketReceive	PLARGS((Tcl_Interp *interp, PLiodev *iodev,
				PDFstrm *pdfs));

#endif	/* __TCPIP_H__ */
