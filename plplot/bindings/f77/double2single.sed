# $Id: double2single.sed,v 1.3 2005/04/27 06:43:09 rlaboiss Exp $
#
# Copyright (C) 2004  Alan W. Irwin
#
# This file is part of PLplot.
#
# PLplot is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Library Public License as published
# by the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# PLplot is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public License
# along with PLplot; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

# This sed command script converts sfstubs.fm4 from double to single
# precision.  Currently the only double-precision construct that file
# has in it is "real*8" so that is all this script converts.  See
# ../../examples/f77/double2single.sed for an example of a more complicated
# case.

# Convert real*8
s/real\*8/real*4/

