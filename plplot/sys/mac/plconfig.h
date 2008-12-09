/* -*-C-*-
/* $Id: plconfig.h,v 1.1 2000/05/12 18:05:32 furnish Exp $
 * $Log: plconfig.h,v $
 * Revision 1.1  2000/05/12 18:05:32  furnish
 * Imported latest Mac port work by Rob Managan.
 *
 * Revision 1.1  1994/08/10  01:08:24  mjl
 * New directory structure, config files, and other modifications for PLplot
 * 4.99h/djgpp DOS port, submitted by Paul Kirschner.  New driver supports
 * color fill.
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
#undef pid_t

/* Define to `char *' if <sys/types.h> doesn't define.  */
#undef caddr_t

/* Define as the return type of signal handlers (int or void).  */
#undef RETSIGTYPE

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

/* Define vfork as fork if vfork does not work.  */
#undef vfork

/* Install directories. */

#define LIB_DIR ""
#undef BIN_DIR
#undef TCL_DIR

#define PL_DOUBLE

#endif	/* __PLCONFIG_H__ */
