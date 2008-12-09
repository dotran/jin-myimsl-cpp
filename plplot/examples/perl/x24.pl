#! /usr/bin/env perl
#
# Demo x24 for the PLplot PDL binding
#
# Unicode Pace Flag
#
# Copyright (C) 2005  Rafael Laboissiere
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
#
# In Debian, run like this:
#
# PLPLOT_FREETYPE_SANS_FONT=/usr/share/fonts/truetype/arphic/bkai00mp.ttf \
# PLPLOT_FREETYPE_SERIF_FONT=/usr/share/fonts/truetype/freefont/FreeSerif.ttf \
# PLPLOT_FREETYPE_MONO_FONT=/usr/share/fonts/truetype/ttf-devanagari-fonts/lohit_hi.ttf \
# PLPLOT_FREETYPE_SCRIPT_FONT=/usr/share/fonts/truetype/unfonts/UnBatang.ttf \
# PLPLOT_FREETYPE_SYMBOL_FONT=/usr/share/fonts/truetype/ttf-bangla-fonts/JamrulNormal.ttf \
# ./x24c -dev png -drvopt text,smooth=0 -o x24c.png
#
# Packages needed:
#
# ttf-arphic-bkai00mp
# ttf-freefont
# ttf-indic-fonts
# ttf-unfonts
# ttf-bangla-fonts

# SYNC: x24c.c 1.6

use PDL;
use PDL::Graphics::PLplot;

my $red   = pdl [240, 204, 204, 204,   0,  39, 125];
my $green = pdl [240,   0, 125, 204, 204,  80,   0];
my $blue  = pdl [240,   0,   0,   0,   0, 204, 125];

my $px = pdl [0.0, 0.0, 1.0, 1.0];
my $py = pdl [0.0, 0.16667, 0.16667, 0.0];

my @sx = (
  0.16374,
  0.15844,
  0.15255,
  0.17332,
  0.50436,
  0.51721,
  0.49520,
  0.48713,
  0.83976,
  0.81688,
  0.82231,
  0.82647
);

my @sy = (
  0.11341,
  0.35481,
  0.61621,
  0.86525,
  0.13249,
  0.37995,
  0.61584,
  0.86303,
  0.13901,
  0.30533,
  0.63165,
  0.87598
);


# Taken from http://www.columbia.edu/~fdc/pace/

my @peace = (
  # Mandarin
  "#<0x00>和平",
  # Hindi
  "#<0x20>शांति",
  # English
  "#<0x10>Peace",
  # Hebrew
  "#<0x10>םולש",
  # Russian
  "#<0x10>Мир",
  # German
  "#<0x10>Friede",
  # Korean
  "#<0x30>평화",
  # French
  "#<0x10>Paix",
  # Spanish
  "#<0x10>Paz",
  # Arabic
  "#<0x10>مﻼﺳ",
  # Turkis
  "#<0x10>Barış",
  # Kurdish
  "#<0x10>Hasîtî",
);

plParseOpts (\@ARGV, PL_PARSE_SKIP | PL_PARSE_NOPROGRAM);

plinit ();

pladv (0);
plvpor (0.0, 1.0, 0.0, 1.0);
plwind (0.0, 1.0, 0.0, 1.0);
plcol0 (0);
plbox ("", 1.0, 0, "", 1.0, 0);

plscmap0n (7);
plscmap0 ($red, $green, $blue, 7);

plschr (0, 4.0);
plfont (1);

for (my $i = 0; $i < 6; $i++) {

  plcol0 ($i + 1);
  plfill ($px, $py);

  $py += 1.0 / 6.0;

}

plcol0 (0);
for (my $i = 0; $i < 12; $i++) {
  plptex ($sx [$i], $sy [$i], 1.0, 0.0, 0.5, $peace [$i]);
}

plend ();

