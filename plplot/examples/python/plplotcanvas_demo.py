#!/usr/bin/env python
"""
demo.py - Demonstrates the simplest use of the plplot canvas widget with gtk.

  Copyright (C) 2004, 2005 Thomas J. Duck
  All rights reserved.

  Thomas J. Duck <tom.duck@dal.ca>
  Department of Physics and Atmospheric Science,
  Dalhousie University, Halifax, Nova Scotia, Canada, B3H 3J5

  $Author: airwin $
  $Revision: 1.7 $
  $Date: 2005/05/07 00:20:52 $
  $Name: cvs-tarball_2005-05-13-12-54-59 $


NOTICE

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
  MA  02110-1301  USA
"""
import Numeric
import plplot_python_start
import plplotcanvas
import plplot
import gtk
import sys

# The width and height of the plplot canvas widget
WIDTH = 1000 # 500
HEIGHT = 600 # 300

# Delete event callback
def delete_event(widget, event, data=None):
    return gtk.FALSE

# Destroy event calback
def destroy(widget, data=None):
    gtk.main_quit()

# Parse the options
plplot.plparseopts(sys.argv,plplot.PL_PARSE_FULL);

# The data to plot
x = Numeric.arange(11)
y = x**2/10.

# Create the canvas and set its size; during the creation process,
# the gcw driver is loaded into plplot, and plinit() is invoked.
canvas=plplotcanvas.Canvas()  
canvas.set_size(WIDTH,HEIGHT)

# Create a new window and stuff the canvas into it
window = gtk.Window(gtk.WINDOW_TOPLEVEL)
window.set_border_width(10)
window.add(canvas)

# Connect the signal handlers to the window decorations
window.connect("delete_event",delete_event)
window.connect("destroy",destroy)

# Display everything
window.show_all()

# Draw on the canvas with Plplot
canvas.pladv(0)  # Advance the page
canvas.plcol0(15) # Set color to black
canvas.plwid(2) # Set the pen width
canvas.plvsta() # Set the viewport
canvas.plwind(0.,10.,0.,10.); # Set the window
canvas.plbox("bcnst",0.,0,"bcnstv",0.,0); # Set the box
canvas.pllab("x-axis","y-axis","A Simple Plot") # Draw some labels

# Draw the line
canvas.plcol0(1) # Set the pen color
canvas.plline(x,y)

# Advancing the page finalizes this plot
canvas.pladv(0)

# Start the gtk main loop
gtk.main()
