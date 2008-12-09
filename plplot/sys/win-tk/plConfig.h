/* -*-C-*- */
/* $Id: plConfig.h,v 1.2 2002/07/04 15:17:15 vincentdarley Exp $
 * $Log: plConfig.h,v $
 * Revision 1.2  2002/07/04 15:17:15  vincentdarley
 * win-tk build
 *
 * Revision 1.1  2002/07/02 09:35:31  vincentdarley
 * windows tk build
 *
 * Revision 1.10  2000/05/15 07:16:38  furnish
 * Add perfunctory stub for PL_DOUBLE.
 *
 * Revision 1.9  1996/04/30 23:10:32  furnish
 * Introduce HAVE_ITK macro.
 *
 * Revision 1.8  1995/10/13  21:04:07  mjl
 * Added USE_FSEEK macro.
 *
 * Revision 1.7  1995/06/01  21:35:54  mjl
 * Added HAVE_POPEN and HAVE_ITCL macros.
 *
 * Revision 1.6  1995/05/15  07:56:07  mjl
 * Made the macros DEBUGGING_MALLOC and NOBRAINDEAD configurable.
 *
 * Revision 1.5  1994/08/05  22:23:35  mjl
 * Eliminated dangling comment to get rid of compiler warning on NEC.
 *
 * Revision 1.4  1994/07/28  07:40:47  mjl
 * Added define for caddr_t to prevent future problems with broken X11R4
 * headers and _POSIX_SOURCE.  Not defined if sys/types.h goes ahead
 * and typedef's it anyway, when it's not supposed to.
 *
 * Revision 1.3  1994/07/25  05:56:30  mjl
 * Added check for unistd.h.
 *
 * Revision 1.2  1994/07/23  04:41:08  mjl
 * I'm going to try defining _POSIX_SOURCE here now.
 *
 * Revision 1.1  1994/07/19  22:26:57  mjl
 * Header file for holding miscellaneous config info, including install
 * directories, system dependencies, etc.  Included by plplotP.h.
*/

/*
    plConfig.h.in

    Maurice LeBrun
    IFS, University of Texas at Austin
    18-Jul-1994

    Contains macro definitions that determine miscellaneous PLplot library
    configuration defaults, such as macros for bin, font, lib, and tcl
    install directories, and various system dependencies.  On a Unix
    system, typically the configure script builds plConfig.h from
    plConfig.h.in.  Elsewhere, it's best to hand-configure a plConfig.h
    file and keep it with the system-specific files.
*/

#ifndef __PLCONFIG_H__
#define __PLCONFIG_H__

/* Define if on a POSIX.1 compliant system.  */
#undef _POSIX_SOURCE

/* Define HAVE_UNISTD_H if unistd.h is available. */
#undef HAVE_UNISTD_H

/* Define if you have vfork.h.  */
#undef HAVE_VFORK_H

/* Define to `int' if <sys/types.h> doesn't define.  */
#define pid_t int

/* Define to `char *' if <sys/types.h> doesn't define.  */
#undef caddr_t

/* Define as the return type of signal handlers (int or void).  */
#undef RETSIGTYPE

/* Define if you have the ANSI C header files.  */
#undef STDC_HEADERS

/* Define vfork as fork if vfork does not work.  */
#undef vfork

/* Define if popen is available.  */
#undef HAVE_POPEN

/* Define if we're using a debugging malloc */
#undef DEBUGGING_MALLOC

/* If you don't know what this is for, you shouldn't be using it */
#undef NOBRAINDEAD

/* Define if fgetpos/fsetpos is busted */
#undef USE_FSEEK

/* Define if [incr Tcl] is available */
#undef HAVE_ITCL

/* Define if [incr Tk] is available */
#undef HAVE_ITK

/* Define if you want PLplot's float type to be double */
#undef PL_DOUBLE

/* Install directories. */

#undef LIB_DIR
#undef BIN_DIR
#undef TCL_DIR

#endif	/* __PLCONFIG_H__ */
