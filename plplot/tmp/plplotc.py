# This file was created automatically by SWIG.
# Don't modify this file, modify the SWIG interface instead.
# This file is compatible with both classic and new-style classes.

import _plplotc

def _swig_setattr(self,class_type,name,value):
    if (name == "this"):
        if isinstance(value, class_type):
            self.__dict__[name] = value.this
            if hasattr(value,"thisown"): self.__dict__["thisown"] = value.thisown
            del value.thisown
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    self.__dict__[name] = value

def _swig_getattr(self,class_type,name):
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError,name

import types
try:
    _object = types.ObjectType
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0
del types



pltr0 = _plplotc.pltr0

pltr1 = _plplotc.pltr1

pltr2 = _plplotc.pltr2
PLESC_SET_RGB = _plplotc.PLESC_SET_RGB
PLESC_ALLOC_NCOL = _plplotc.PLESC_ALLOC_NCOL
PLESC_SET_LPB = _plplotc.PLESC_SET_LPB
PLESC_EXPOSE = _plplotc.PLESC_EXPOSE
PLESC_RESIZE = _plplotc.PLESC_RESIZE
PLESC_REDRAW = _plplotc.PLESC_REDRAW
PLESC_TEXT = _plplotc.PLESC_TEXT
PLESC_GRAPH = _plplotc.PLESC_GRAPH
PLESC_FILL = _plplotc.PLESC_FILL
PLESC_DI = _plplotc.PLESC_DI
PLESC_FLUSH = _plplotc.PLESC_FLUSH
PLESC_EH = _plplotc.PLESC_EH
PLESC_GETC = _plplotc.PLESC_GETC
PLESC_SWIN = _plplotc.PLESC_SWIN
PLESC_PLFLTBUFFERING = _plplotc.PLESC_PLFLTBUFFERING
PLESC_XORMOD = _plplotc.PLESC_XORMOD
PLESC_SET_COMPRESSION = _plplotc.PLESC_SET_COMPRESSION
PLESC_CLEAR = _plplotc.PLESC_CLEAR
PLESC_DASH = _plplotc.PLESC_DASH
PLESC_HAS_TEXT = _plplotc.PLESC_HAS_TEXT
PLESC_IMAGE = _plplotc.PLESC_IMAGE
PLESC_IMAGEOPS = _plplotc.PLESC_IMAGEOPS
DRAW_LINEX = _plplotc.DRAW_LINEX
DRAW_LINEY = _plplotc.DRAW_LINEY
DRAW_LINEXY = _plplotc.DRAW_LINEXY
MAG_COLOR = _plplotc.MAG_COLOR
BASE_CONT = _plplotc.BASE_CONT
TOP_CONT = _plplotc.TOP_CONT
SURF_CONT = _plplotc.SURF_CONT
DRAW_SIDES = _plplotc.DRAW_SIDES
FACETED = _plplotc.FACETED
MESH = _plplotc.MESH
PLSWIN_DEVICE = _plplotc.PLSWIN_DEVICE
PLSWIN_WORLD = _plplotc.PLSWIN_WORLD
PL_OPT_ENABLED = _plplotc.PL_OPT_ENABLED
PL_OPT_ARG = _plplotc.PL_OPT_ARG
PL_OPT_NODELETE = _plplotc.PL_OPT_NODELETE
PL_OPT_INVISIBLE = _plplotc.PL_OPT_INVISIBLE
PL_OPT_DISABLED = _plplotc.PL_OPT_DISABLED
PL_OPT_FUNC = _plplotc.PL_OPT_FUNC
PL_OPT_BOOL = _plplotc.PL_OPT_BOOL
PL_OPT_INT = _plplotc.PL_OPT_INT
PL_OPT_FLOAT = _plplotc.PL_OPT_FLOAT
PL_OPT_STRING = _plplotc.PL_OPT_STRING
PL_PARSE_PARTIAL = _plplotc.PL_PARSE_PARTIAL
PL_PARSE_FULL = _plplotc.PL_PARSE_FULL
PL_PARSE_QUIET = _plplotc.PL_PARSE_QUIET
PL_PARSE_NODELETE = _plplotc.PL_PARSE_NODELETE
PL_PARSE_SHOWALL = _plplotc.PL_PARSE_SHOWALL
PL_PARSE_OVERRIDE = _plplotc.PL_PARSE_OVERRIDE
PL_PARSE_NOPROGRAM = _plplotc.PL_PARSE_NOPROGRAM
PL_PARSE_NODASH = _plplotc.PL_PARSE_NODASH
PL_PARSE_SKIP = _plplotc.PL_PARSE_SKIP
PL_MAXKEY = _plplotc.PL_MAXKEY
PL_MAXWINDOWS = _plplotc.PL_MAXWINDOWS
PL_NOTSET = _plplotc.PL_NOTSET
PLESPLFLTBUFFERING_ENABLE = _plplotc.PLESPLFLTBUFFERING_ENABLE
PLESPLFLTBUFFERING_DISABLE = _plplotc.PLESPLFLTBUFFERING_DISABLE
PLESPLFLTBUFFERING_QUERY = _plplotc.PLESPLFLTBUFFERING_QUERY

plsxwin = _plplotc.plsxwin

pl_setcontlabelformat = _plplotc.pl_setcontlabelformat

pl_setcontlabelparam = _plplotc.pl_setcontlabelparam

pladv = _plplotc.pladv

plaxes = _plplotc.plaxes

plbin = _plplotc.plbin

plbop = _plplotc.plbop

plbox = _plplotc.plbox

plbox3 = _plplotc.plbox3

plcalc_world = _plplotc.plcalc_world

plclear = _plplotc.plclear

plcol0 = _plplotc.plcol0

plcol1 = _plplotc.plcol1

plcont = _plplotc.plcont

plcpstrm = _plplotc.plcpstrm

plend = _plplotc.plend

plend1 = _plplotc.plend1

plenv = _plplotc.plenv

pleop = _plplotc.pleop

plerrx = _plplotc.plerrx

plerry = _plplotc.plerry

plfamadv = _plplotc.plfamadv

plfill = _plplotc.plfill

plfill3 = _plplotc.plfill3

plflush = _plplotc.plflush

plfont = _plplotc.plfont

plfontld = _plplotc.plfontld

plgchr = _plplotc.plgchr

plgcol0 = _plplotc.plgcol0

plgcolbg = _plplotc.plgcolbg

plgcompression = _plplotc.plgcompression

plgdev = _plplotc.plgdev

plgdidev = _plplotc.plgdidev

plgdiori = _plplotc.plgdiori

plgdiplt = _plplotc.plgdiplt

plgfam = _plplotc.plgfam

plgfci = _plplotc.plgfci

plgfnam = _plplotc.plgfnam

plglevel = _plplotc.plglevel

plgpage = _plplotc.plgpage

plgra = _plplotc.plgra

plgspa = _plplotc.plgspa

plgstrm = _plplotc.plgstrm

plgver = _plplotc.plgver

plgvpd = _plplotc.plgvpd

plgvpw = _plplotc.plgvpw

plgxax = _plplotc.plgxax

plgyax = _plplotc.plgyax

plgzax = _plplotc.plgzax

plhist = _plplotc.plhist

plhls = _plplotc.plhls

plhlsrgb = _plplotc.plhlsrgb

plinit = _plplotc.plinit

pljoin = _plplotc.pljoin

pllab = _plplotc.pllab

pllightsource = _plplotc.pllightsource

plline = _plplotc.plline

plline3 = _plplotc.plline3

pllsty = _plplotc.pllsty

plmesh = _plplotc.plmesh

plmeshc = _plplotc.plmeshc

plmkstrm = _plplotc.plmkstrm

plmtex = _plplotc.plmtex

plot3d = _plplotc.plot3d

plot3dc = _plplotc.plot3dc

plot3dcl = _plplotc.plot3dcl

plsurf3d = _plplotc.plsurf3d

plsurf3dl = _plplotc.plsurf3dl

plparseopts = _plplotc.plparseopts

plpat = _plplotc.plpat

plpoin = _plplotc.plpoin

plpoin3 = _plplotc.plpoin3

plpoly3 = _plplotc.plpoly3

plprec = _plplotc.plprec

plpsty = _plplotc.plpsty

plptex = _plplotc.plptex

plreplot = _plplotc.plreplot

plrgbhls = _plplotc.plrgbhls

plschr = _plplotc.plschr

plscmap0 = _plplotc.plscmap0

plscmap0n = _plplotc.plscmap0n

plscmap1 = _plplotc.plscmap1

plscmap1l = _plplotc.plscmap1l

plscmap1n = _plplotc.plscmap1n

plscol0 = _plplotc.plscol0

plscolbg = _plplotc.plscolbg

plscolor = _plplotc.plscolor

plscompression = _plplotc.plscompression

plsdev = _plplotc.plsdev

plsdidev = _plplotc.plsdidev

plsdimap = _plplotc.plsdimap

plsdiori = _plplotc.plsdiori

plsdiplt = _plplotc.plsdiplt

plsdiplz = _plplotc.plsdiplz

plsesc = _plplotc.plsesc

plsetopt = _plplotc.plsetopt

plsfam = _plplotc.plsfam

plsfci = _plplotc.plsfci

plsfnam = _plplotc.plsfnam

plshades = _plplotc.plshades

plshade = _plplotc.plshade

plsmaj = _plplotc.plsmaj

plsmin = _plplotc.plsmin

plsori = _plplotc.plsori

plspage = _plplotc.plspage

plspause = _plplotc.plspause

plsstrm = _plplotc.plsstrm

plssub = _plplotc.plssub

plssym = _plplotc.plssym

plstar = _plplotc.plstar

plstart = _plplotc.plstart

plstripa = _plplotc.plstripa

plstripc = _plplotc.plstripc

plstripd = _plplotc.plstripd

plstyl = _plplotc.plstyl

plsvect = _plplotc.plsvect

plsvpa = _plplotc.plsvpa

plsxax = _plplotc.plsxax

plsyax = _plplotc.plsyax

plsym = _plplotc.plsym

plszax = _plplotc.plszax

pltext = _plplotc.pltext

plvasp = _plplotc.plvasp

plvect = _plplotc.plvect

plvpas = _plplotc.plvpas

plvpor = _plplotc.plvpor

plvsta = _plplotc.plvsta

plw3d = _plplotc.plw3d

plwid = _plplotc.plwid

plwind = _plplotc.plwind

plxormod = _plplotc.plxormod

plClearOpts = _plplotc.plClearOpts

plResetOpts = _plplotc.plResetOpts

plSetUsage = _plplotc.plSetUsage

plOptUsage = _plplotc.plOptUsage

plGetCursor = _plplotc.plGetCursor

