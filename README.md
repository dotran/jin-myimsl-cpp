# Instructions on the Use of PLPLOT and MYIMSL

## Introduction

This document describes how to link the `plplot` and `myimsl` libraries into your own codes using MS Visual C++ on machines running MS Windows 98/XP (this version may work on other versions of Windows).

`plplot` is a scientific plotting package which can be used to create standard x-y plots, semi-log plots, log-log plots, contour plots, 3D surface plots, mesh plots, bar charts and pie charts. The `plplot` package is distributable under the terms of the GNU Library General Public License (LGPL) with some exceptions. For more information about "Copyright" and "on-line manual", please see the home page (http://plplot.sourceforge.net).

`myimsl` is a small-sized package solving specialized problems which is coded and distributed by **Professor Gang-Gyoo Jin** of Korea Maritime University in Busan, South Korea. The `myimsl` library contains modules for eigenvalues, polynomial roots, sort, norms, FFT, cubic spline, ODEs, real-coded genetic algorithm (RCGA), symbolic-coded genetic algorithm (SCGA), Simulated Annealing, fuzzy control, etc. `myimsl` includes the new vector and matrix classes coded by **Alexander Volya** (http://www.nscl.msu.edu/~volya/alexander/) for easy manipulation of real and complex vectors and matrices.

## Contents of `plplot.zip` and `myimsl.zip`

### `plplot.zip`

For the detailed information, please see the above home page.

### `myimsl.zip`

Below you can find simplified descriptions of this library.

Module       | Description
:------------|:-------------------------------------------------------------------
`myimsl.lib` | library file
`anneal.h`   | prototypes for Simulated Annealing
`cmatrix.h`  | prototypes of the functions using complex matrix and vector classes
`complex.h`  | prototypes for complex numbers
`diffeqs.h`  | prototypes for ODEs and difference equations
`fuzzy.h`    | prototypes for fuzzy control
`imsl.h`     | prototypes of the functions using vector and matrix array
`rcgas.h`    | prototypes for RCGAs
`realtype.h` | prototypes and codes for some basic functions
`rmatrix.h`  | prototypes of the functions using real matrix and vector classes
`scgas.h`    | prototypes for SCGAs

## Requirements

You would need MS Visual C++ version 5, 6 or higher for linking two libraries created in `release` mode.

## Installation and setting instructions

1. Unzip the two zipped files into the directories, `C:\plplot` and `C:\myimsl`, respectively. You can extract the files of `myimsl` in any directory you want, but not `plplot`.

2. During execution of your program, `plplot` find the font files (located in `C:\plplot\lib` with the extension `.fnt`). You have to set the environmental variable `PLPLOT_HOME` as `SET PLPLOT_HOME="C:\PLPLOT"` and restart your PC or simply put the font files in the same directory where your `plplot` program is executed.

3. Run MS Visual C++ and create an empty project for win32 console applications. When library functions are used in your code, you need to include related header files with the `#include` preprocessor directive.

4. Add two include and library directory paths to MS Visual C++.

5. When calling functions in a library, the library name must be included in the library module box.

6. When you have some link errors ('conflicts with use of other libs') during the link process, add `/nodefaultlib:"libc.lib"` for the `release` mode or `/nodefaultlib:"libcd.lib"` for the `debug` mode in the project option box. This is due to the lower version of `plplot`.
