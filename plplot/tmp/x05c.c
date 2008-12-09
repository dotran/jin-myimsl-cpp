/* $Id: x05c.c,v 1.16 2005/04/05 19:16:15 airwin Exp $

	Histogram demo.
*/

#include "plcdemos.h"

#define NPTS 2047

/*--------------------------------------------------------------------------*\
 * main
 *
 * Draws a histogram from sample data.
\*--------------------------------------------------------------------------*/

int
main(int argc, char *argv[])
{
    int i;
    PLFLT data[NPTS], delta;

/* Parse and process command line arguments */

    (void) plparseopts(&argc, argv, PL_PARSE_FULL);

/* Initialize plplot */

    plinit();

/* Fill up data points */

    delta = 2.0 * PI / (double) NPTS;
    for (i = 0; i < NPTS; i++)
	data[i] = sin(i * delta);

    plcol0(1);
    plhist(NPTS, data, -1.1, 1.1, 44, 0);
    plcol0(2);
    pllab("#frValue", "#frFrequency",
	  "#frPLplot Example 5 - Probability function of Oscillator");

    plend();
    exit(0);
}
