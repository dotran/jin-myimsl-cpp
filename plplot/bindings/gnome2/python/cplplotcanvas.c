/* -- THIS FILE IS GENERATED - DO NOT EDIT *//* -*- Mode: C; c-basic-offset: 4 -*- */

#include <Python.h>



#line 52 "cplplotcanvas.override"
#include <Python.h>        
       
#include "pygobject.h"
#include "plplot.h"
#include "plplotcanvas.h"

#define PY_ARRAY_UNIQUE_SYMBOL plplotcanvasapi
#include "Numeric/arrayobject.h"
#line 17 "plplotcanvas.c"


/* ---------- types from other modules ---------- */
static PyTypeObject *_PyGnomeCanvas_Type;
#define PyGnomeCanvas_Type (*_PyGnomeCanvas_Type)


/* ---------- forward type declarations ---------- */
PyTypeObject PyPlplotCanvas_Type;


/* ----------- PlplotCanvas ----------- */

#line 142 "cplplotcanvas.override"
static int
_wrap_plplot_canvas_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    GType obj_type = pyg_type_from_object((PyObject *) self);

    self->obj = g_object_new(obj_type, "aa", TRUE, NULL);
    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create %(typename)s object");
        return -1;
    }

    pygobject_register_wrapper((PyObject *)self);
    return 0;
}
#line 46 "plplotcanvas.c"


static PyObject *
_wrap_plplot_canvas_devinit(PyGObject *self)
{
    plplot_canvas_devinit(PLPLOT_CANVAS(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_dispose(PyGObject *self)
{
    plplot_canvas_dispose(PLPLOT_CANVAS(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_get_stream_number(PyGObject *self)
{
    int ret;

    ret = plplot_canvas_get_stream_number(PLPLOT_CANVAS(self->obj));
    return PyInt_FromLong(ret);
}

static PyObject *
_wrap_plplot_canvas_set_size(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "width", "height", NULL };
    int width, height;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:PlplotCanvas.set_size", kwlist, &width, &height))
        return NULL;
    plplot_canvas_set_size(PLPLOT_CANVAS(self->obj), width, height);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_set_zoom(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "magnification", NULL };
    double magnification;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "d:PlplotCanvas.set_zoom", kwlist, &magnification))
        return NULL;
    plplot_canvas_set_zoom(PLPLOT_CANVAS(self->obj), magnification);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_use_text(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "use_text", NULL };
    int use_text;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.use_text", kwlist, &use_text))
        return NULL;
    plplot_canvas_use_text(PLPLOT_CANVAS(self->obj), use_text);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_use_pixmap(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "use_pixmap", NULL };
    int use_pixmap;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.use_pixmap", kwlist, &use_pixmap))
        return NULL;
    plplot_canvas_use_pixmap(PLPLOT_CANVAS(self->obj), use_pixmap);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_use_persistence(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "use_persistence", NULL };
    int use_persistence;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.use_persistence", kwlist, &use_persistence))
        return NULL;
    plplot_canvas_use_persistence(PLPLOT_CANVAS(self->obj), use_persistence);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_pl_setcontlabelformat(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "lexp", "sigdig", NULL };
    int lexp, sigdig;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:PlplotCanvas.pl_setcontlabelformat", kwlist, &lexp, &sigdig))
        return NULL;
    plplot_canvas_pl_setcontlabelformat(PLPLOT_CANVAS(self->obj), lexp, sigdig);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_pl_setcontlabelparam(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "offset", "size", "spacing", "active", NULL };
    int active;
    double offset, size, spacing;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dddi:PlplotCanvas.pl_setcontlabelparam", kwlist, &offset, &size, &spacing, &active))
        return NULL;
    plplot_canvas_pl_setcontlabelparam(PLPLOT_CANVAS(self->obj), offset, size, spacing, active);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_pladv(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "page", NULL };
    int page;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.pladv", kwlist, &page))
        return NULL;
    plplot_canvas_pladv(PLPLOT_CANVAS(self->obj), page);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plbop(PyGObject *self)
{
    plplot_canvas_plbop(PLPLOT_CANVAS(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plclear(PyGObject *self)
{
    plplot_canvas_plclear(PLPLOT_CANVAS(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plcol0(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "icol0", NULL };
    int icol0;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.plcol0", kwlist, &icol0))
        return NULL;
    plplot_canvas_plcol0(PLPLOT_CANVAS(self->obj), icol0);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plcol1(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "col1", NULL };
    double col1;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "d:PlplotCanvas.plcol1", kwlist, &col1))
        return NULL;
    plplot_canvas_plcol1(PLPLOT_CANVAS(self->obj), col1);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plcpstrm(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "iplsr", "flags", NULL };
    int iplsr, flags;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:PlplotCanvas.plcpstrm", kwlist, &iplsr, &flags))
        return NULL;
    plplot_canvas_plcpstrm(PLPLOT_CANVAS(self->obj), iplsr, flags);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plend(PyGObject *self)
{
    plplot_canvas_plend(PLPLOT_CANVAS(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plend1(PyGObject *self)
{
    plplot_canvas_plend1(PLPLOT_CANVAS(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plenv(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "xmin", "xmax", "ymin", "ymax", "just", "axis", NULL };
    int just, axis;
    double xmin, xmax, ymin, ymax;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ddddii:PlplotCanvas.plenv", kwlist, &xmin, &xmax, &ymin, &ymax, &just, &axis))
        return NULL;
    plplot_canvas_plenv(PLPLOT_CANVAS(self->obj), xmin, xmax, ymin, ymax, just, axis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plenv0(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "xmin", "xmax", "ymin", "ymax", "just", "axis", NULL };
    int just, axis;
    double xmin, xmax, ymin, ymax;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ddddii:PlplotCanvas.plenv0", kwlist, &xmin, &xmax, &ymin, &ymax, &just, &axis))
        return NULL;
    plplot_canvas_plenv0(PLPLOT_CANVAS(self->obj), xmin, xmax, ymin, ymax, just, axis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_pleop(PyGObject *self)
{
    plplot_canvas_pleop(PLPLOT_CANVAS(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plfamadv(PyGObject *self)
{
    plplot_canvas_plfamadv(PLPLOT_CANVAS(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plflush(PyGObject *self)
{
    plplot_canvas_plflush(PLPLOT_CANVAS(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plfont(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "ifont", NULL };
    int ifont;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.plfont", kwlist, &ifont))
        return NULL;
    plplot_canvas_plfont(PLPLOT_CANVAS(self->obj), ifont);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plfontld(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "fnt", NULL };
    int fnt;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.plfontld", kwlist, &fnt))
        return NULL;
    plplot_canvas_plfontld(PLPLOT_CANVAS(self->obj), fnt);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plgra(PyGObject *self)
{
    plplot_canvas_plgra(PLPLOT_CANVAS(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plhls(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "h", "l", "s", NULL };
    double h, l, s;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ddd:PlplotCanvas.plhls", kwlist, &h, &l, &s))
        return NULL;
    plplot_canvas_plhls(PLPLOT_CANVAS(self->obj), h, l, s);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plinit(PyGObject *self)
{
    plplot_canvas_plinit(PLPLOT_CANVAS(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_pljoin(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x1", "y1", "x2", "y2", NULL };
    double x1, y1, x2, y2;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dddd:PlplotCanvas.pljoin", kwlist, &x1, &y1, &x2, &y2))
        return NULL;
    plplot_canvas_pljoin(PLPLOT_CANVAS(self->obj), x1, y1, x2, y2);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_pllightsource(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", "y", "z", NULL };
    double x, y, z;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ddd:PlplotCanvas.pllightsource", kwlist, &x, &y, &z))
        return NULL;
    plplot_canvas_pllightsource(PLPLOT_CANVAS(self->obj), x, y, z);
    Py_INCREF(Py_None);
    return Py_None;
}

#line 158 "cplplotcanvas.override"
static PyObject* _wrap_plplot_canvas_plline(PyGObject *self,
					    PyObject *args)
{
    PyObject *x_,*y_;
    PyArrayObject *x, *y;

    if(!PyArg_UnpackTuple(args,"ref",2,2,&x_,&y_))
	return NULL;

    if(!PyArray_Check(x_)) return NULL;
    if( (x = (PyArrayObject *)
	 PyArray_ContiguousFromObject(x_, PyArray_DOUBLE, 1, 1)) == NULL)
	return NULL;

    if(!PyArray_Check(y_)) return NULL;
    if( (y = (PyArrayObject *)
	 PyArray_ContiguousFromObject(y_, PyArray_DOUBLE, 1, 1)) == NULL)
	return NULL;

    plplot_canvas_plline(PLPLOT_CANVAS(self->obj),
			 x->dimensions[0],(double*)x->data,(double*)y->data);

    return Py_BuildValue("");
}
#line 408 "plplotcanvas.c"


static PyObject *
_wrap_plplot_canvas_pllsty(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "lin", NULL };
    int lin;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.pllsty", kwlist, &lin))
        return NULL;
    plplot_canvas_pllsty(PLPLOT_CANVAS(self->obj), lin);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plprec(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "setp", "prec", NULL };
    int setp, prec;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:PlplotCanvas.plprec", kwlist, &setp, &prec))
        return NULL;
    plplot_canvas_plprec(PLPLOT_CANVAS(self->obj), setp, prec);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plpsty(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "patt", NULL };
    int patt;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.plpsty", kwlist, &patt))
        return NULL;
    plplot_canvas_plpsty(PLPLOT_CANVAS(self->obj), patt);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plreplot(PyGObject *self)
{
    plplot_canvas_plreplot(PLPLOT_CANVAS(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plrgb(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "r", "g", "b", NULL };
    double r, g, b;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ddd:PlplotCanvas.plrgb", kwlist, &r, &g, &b))
        return NULL;
    plplot_canvas_plrgb(PLPLOT_CANVAS(self->obj), r, g, b);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plrgb1(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "r", "g", "b", NULL };
    int r, g, b;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iii:PlplotCanvas.plrgb1", kwlist, &r, &g, &b))
        return NULL;
    plplot_canvas_plrgb1(PLPLOT_CANVAS(self->obj), r, g, b);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plschr(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "def_", "scale", NULL };
    double def, scale;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd:PlplotCanvas.plschr", kwlist, &def, &scale))
        return NULL;
    plplot_canvas_plschr(PLPLOT_CANVAS(self->obj), def, scale);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plscmap0n(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "ncol0", NULL };
    int ncol0;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.plscmap0n", kwlist, &ncol0))
        return NULL;
    plplot_canvas_plscmap0n(PLPLOT_CANVAS(self->obj), ncol0);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plscmap1n(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "ncol1", NULL };
    int ncol1;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.plscmap1n", kwlist, &ncol1))
        return NULL;
    plplot_canvas_plscmap1n(PLPLOT_CANVAS(self->obj), ncol1);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plscol0(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "icol0", "r", "g", "b", NULL };
    int icol0, r, g, b;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiii:PlplotCanvas.plscol0", kwlist, &icol0, &r, &g, &b))
        return NULL;
    plplot_canvas_plscol0(PLPLOT_CANVAS(self->obj), icol0, r, g, b);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plscolbg(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "r", "g", "b", NULL };
    int r, g, b;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iii:PlplotCanvas.plscolbg", kwlist, &r, &g, &b))
        return NULL;
    plplot_canvas_plscolbg(PLPLOT_CANVAS(self->obj), r, g, b);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plscolor(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "color", NULL };
    int color;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.plscolor", kwlist, &color))
        return NULL;
    plplot_canvas_plscolor(PLPLOT_CANVAS(self->obj), color);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plscompression(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "compression", NULL };
    int compression;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.plscompression", kwlist, &compression))
        return NULL;
    plplot_canvas_plscompression(PLPLOT_CANVAS(self->obj), compression);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plsdidev(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "mar", "aspect", "jx", "jy", NULL };
    double mar, aspect, jx, jy;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dddd:PlplotCanvas.plsdidev", kwlist, &mar, &aspect, &jx, &jy))
        return NULL;
    plplot_canvas_plsdidev(PLPLOT_CANVAS(self->obj), mar, aspect, jx, jy);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plsdimap(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "dimxmin", "dimxmax", "dimymin", "dimymax", "dimxpmm", "dimypmm", NULL };
    int dimxmin, dimxmax, dimymin, dimymax;
    double dimxpmm, dimypmm;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiiidd:PlplotCanvas.plsdimap", kwlist, &dimxmin, &dimxmax, &dimymin, &dimymax, &dimxpmm, &dimypmm))
        return NULL;
    plplot_canvas_plsdimap(PLPLOT_CANVAS(self->obj), dimxmin, dimxmax, dimymin, dimymax, dimxpmm, dimypmm);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plsdiori(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "rot", NULL };
    double rot;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "d:PlplotCanvas.plsdiori", kwlist, &rot))
        return NULL;
    plplot_canvas_plsdiori(PLPLOT_CANVAS(self->obj), rot);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plsdiplt(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "xmin", "ymin", "xmax", "ymax", NULL };
    double xmin, ymin, xmax, ymax;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dddd:PlplotCanvas.plsdiplt", kwlist, &xmin, &ymin, &xmax, &ymax))
        return NULL;
    plplot_canvas_plsdiplt(PLPLOT_CANVAS(self->obj), xmin, ymin, xmax, ymax);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plsdiplz(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "xmin", "ymin", "xmax", "ymax", NULL };
    double xmin, ymin, xmax, ymax;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dddd:PlplotCanvas.plsdiplz", kwlist, &xmin, &ymin, &xmax, &ymax))
        return NULL;
    plplot_canvas_plsdiplz(PLPLOT_CANVAS(self->obj), xmin, ymin, xmax, ymax);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plsesc(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "esc", NULL };
    char esc;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "c:PlplotCanvas.plsesc", kwlist, &esc))
        return NULL;
    plplot_canvas_plsesc(PLPLOT_CANVAS(self->obj), esc);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plsfam(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "fam", "num", "bmax", NULL };
    int fam, num, bmax;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iii:PlplotCanvas.plsfam", kwlist, &fam, &num, &bmax))
        return NULL;
    plplot_canvas_plsfam(PLPLOT_CANVAS(self->obj), fam, num, bmax);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plsmaj(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "def_", "scale", NULL };
    double def, scale;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd:PlplotCanvas.plsmaj", kwlist, &def, &scale))
        return NULL;
    plplot_canvas_plsmaj(PLPLOT_CANVAS(self->obj), def, scale);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plsmin(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "def_", "scale", NULL };
    double def, scale;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd:PlplotCanvas.plsmin", kwlist, &def, &scale))
        return NULL;
    plplot_canvas_plsmin(PLPLOT_CANVAS(self->obj), def, scale);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plsori(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "ori", NULL };
    int ori;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.plsori", kwlist, &ori))
        return NULL;
    plplot_canvas_plsori(PLPLOT_CANVAS(self->obj), ori);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plspage(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "xp", "yp", "xleng", "yleng", "xoff", "yoff", NULL };
    int xleng, yleng, xoff, yoff;
    double xp, yp;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ddiiii:PlplotCanvas.plspage", kwlist, &xp, &yp, &xleng, &yleng, &xoff, &yoff))
        return NULL;
    plplot_canvas_plspage(PLPLOT_CANVAS(self->obj), xp, yp, xleng, yleng, xoff, yoff);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plspause(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "pause", NULL };
    int pause;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.plspause", kwlist, &pause))
        return NULL;
    plplot_canvas_plspause(PLPLOT_CANVAS(self->obj), pause);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plsstrm(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "strm", NULL };
    int strm;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.plsstrm", kwlist, &strm))
        return NULL;
    plplot_canvas_plsstrm(PLPLOT_CANVAS(self->obj), strm);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plssub(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "nx", "ny", NULL };
    int nx, ny;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:PlplotCanvas.plssub", kwlist, &nx, &ny))
        return NULL;
    plplot_canvas_plssub(PLPLOT_CANVAS(self->obj), nx, ny);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plssym(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "def_", "scale", NULL };
    double def, scale;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd:PlplotCanvas.plssym", kwlist, &def, &scale))
        return NULL;
    plplot_canvas_plssym(PLPLOT_CANVAS(self->obj), def, scale);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plstar(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "nx", "ny", NULL };
    int nx, ny;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:PlplotCanvas.plstar", kwlist, &nx, &ny))
        return NULL;
    plplot_canvas_plstar(PLPLOT_CANVAS(self->obj), nx, ny);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plstripa(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "id", "pen", "x", "y", NULL };
    int id, pen;
    double x, y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iidd:PlplotCanvas.plstripa", kwlist, &id, &pen, &x, &y))
        return NULL;
    plplot_canvas_plstripa(PLPLOT_CANVAS(self->obj), id, pen, x, y);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plstripd(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "id", NULL };
    int id;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.plstripd", kwlist, &id))
        return NULL;
    plplot_canvas_plstripd(PLPLOT_CANVAS(self->obj), id);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plsvpa(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "xmin", "xmax", "ymin", "ymax", NULL };
    double xmin, xmax, ymin, ymax;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dddd:PlplotCanvas.plsvpa", kwlist, &xmin, &xmax, &ymin, &ymax))
        return NULL;
    plplot_canvas_plsvpa(PLPLOT_CANVAS(self->obj), xmin, xmax, ymin, ymax);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plsxax(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "digmax", "digits", NULL };
    int digmax, digits;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:PlplotCanvas.plsxax", kwlist, &digmax, &digits))
        return NULL;
    plplot_canvas_plsxax(PLPLOT_CANVAS(self->obj), digmax, digits);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plsxwin(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "window_id", NULL };
    int window_id;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.plsxwin", kwlist, &window_id))
        return NULL;
    plplot_canvas_plsxwin(PLPLOT_CANVAS(self->obj), window_id);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plsyax(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "digmax", "digits", NULL };
    int digmax, digits;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:PlplotCanvas.plsyax", kwlist, &digmax, &digits))
        return NULL;
    plplot_canvas_plsyax(PLPLOT_CANVAS(self->obj), digmax, digits);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plszax(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "digmax", "digits", NULL };
    int digmax, digits;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:PlplotCanvas.plszax", kwlist, &digmax, &digits))
        return NULL;
    plplot_canvas_plszax(PLPLOT_CANVAS(self->obj), digmax, digits);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_pltext(PyGObject *self)
{
    plplot_canvas_pltext(PLPLOT_CANVAS(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plvasp(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "aspect", NULL };
    double aspect;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "d:PlplotCanvas.plvasp", kwlist, &aspect))
        return NULL;
    plplot_canvas_plvasp(PLPLOT_CANVAS(self->obj), aspect);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plvpas(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "xmin", "xmax", "ymin", "ymax", "aspect", NULL };
    double xmin, xmax, ymin, ymax, aspect;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ddddd:PlplotCanvas.plvpas", kwlist, &xmin, &xmax, &ymin, &ymax, &aspect))
        return NULL;
    plplot_canvas_plvpas(PLPLOT_CANVAS(self->obj), xmin, xmax, ymin, ymax, aspect);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plvpor(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "xmin", "xmax", "ymin", "ymax", NULL };
    double xmin, xmax, ymin, ymax;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dddd:PlplotCanvas.plvpor", kwlist, &xmin, &xmax, &ymin, &ymax))
        return NULL;
    plplot_canvas_plvpor(PLPLOT_CANVAS(self->obj), xmin, xmax, ymin, ymax);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plvsta(PyGObject *self)
{
    plplot_canvas_plvsta(PLPLOT_CANVAS(self->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plw3d(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "basex", "basey", "height", "xmin0", "xmax0", "ymin0", "ymax0", "zmin0", "zmax0", "alt", "az", NULL };
    double basex, basey, height, xmin0, xmax0, ymin0, ymax0, zmin0, zmax0, alt, az;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ddddddddddd:PlplotCanvas.plw3d", kwlist, &basex, &basey, &height, &xmin0, &xmax0, &ymin0, &ymax0, &zmin0, &zmax0, &alt, &az))
        return NULL;
    plplot_canvas_plw3d(PLPLOT_CANVAS(self->obj), basex, basey, height, xmin0, xmax0, ymin0, ymax0, zmin0, zmax0, alt, az);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plwid(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "width", NULL };
    int width;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PlplotCanvas.plwid", kwlist, &width))
        return NULL;
    plplot_canvas_plwid(PLPLOT_CANVAS(self->obj), width);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_plplot_canvas_plwind(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "xmin", "xmax", "ymin", "ymax", NULL };
    double xmin, xmax, ymin, ymax;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dddd:PlplotCanvas.plwind", kwlist, &xmin, &xmax, &ymin, &ymax))
        return NULL;
    plplot_canvas_plwind(PLPLOT_CANVAS(self->obj), xmin, xmax, ymin, ymax);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef _PyPlplotCanvas_methods[] = {
    { "devinit", (PyCFunction)_wrap_plplot_canvas_devinit, METH_NOARGS },
    { "dispose", (PyCFunction)_wrap_plplot_canvas_dispose, METH_NOARGS },
    { "get_stream_number", (PyCFunction)_wrap_plplot_canvas_get_stream_number, METH_NOARGS },
    { "set_size", (PyCFunction)_wrap_plplot_canvas_set_size, METH_VARARGS|METH_KEYWORDS },
    { "set_zoom", (PyCFunction)_wrap_plplot_canvas_set_zoom, METH_VARARGS|METH_KEYWORDS },
    { "use_text", (PyCFunction)_wrap_plplot_canvas_use_text, METH_VARARGS|METH_KEYWORDS },
    { "use_pixmap", (PyCFunction)_wrap_plplot_canvas_use_pixmap, METH_VARARGS|METH_KEYWORDS },
    { "use_persistence", (PyCFunction)_wrap_plplot_canvas_use_persistence, METH_VARARGS|METH_KEYWORDS },
    { "pl_setcontlabelformat", (PyCFunction)_wrap_plplot_canvas_pl_setcontlabelformat, METH_VARARGS|METH_KEYWORDS },
    { "pl_setcontlabelparam", (PyCFunction)_wrap_plplot_canvas_pl_setcontlabelparam, METH_VARARGS|METH_KEYWORDS },
    { "pladv", (PyCFunction)_wrap_plplot_canvas_pladv, METH_VARARGS|METH_KEYWORDS },
    { "plbop", (PyCFunction)_wrap_plplot_canvas_plbop, METH_NOARGS },
    { "plclear", (PyCFunction)_wrap_plplot_canvas_plclear, METH_NOARGS },
    { "plcol0", (PyCFunction)_wrap_plplot_canvas_plcol0, METH_VARARGS|METH_KEYWORDS },
    { "plcol1", (PyCFunction)_wrap_plplot_canvas_plcol1, METH_VARARGS|METH_KEYWORDS },
    { "plcpstrm", (PyCFunction)_wrap_plplot_canvas_plcpstrm, METH_VARARGS|METH_KEYWORDS },
    { "plend", (PyCFunction)_wrap_plplot_canvas_plend, METH_NOARGS },
    { "plend1", (PyCFunction)_wrap_plplot_canvas_plend1, METH_NOARGS },
    { "plenv", (PyCFunction)_wrap_plplot_canvas_plenv, METH_VARARGS|METH_KEYWORDS },
    { "plenv0", (PyCFunction)_wrap_plplot_canvas_plenv0, METH_VARARGS|METH_KEYWORDS },
    { "pleop", (PyCFunction)_wrap_plplot_canvas_pleop, METH_NOARGS },
    { "plfamadv", (PyCFunction)_wrap_plplot_canvas_plfamadv, METH_NOARGS },
    { "plflush", (PyCFunction)_wrap_plplot_canvas_plflush, METH_NOARGS },
    { "plfont", (PyCFunction)_wrap_plplot_canvas_plfont, METH_VARARGS|METH_KEYWORDS },
    { "plfontld", (PyCFunction)_wrap_plplot_canvas_plfontld, METH_VARARGS|METH_KEYWORDS },
    { "plgra", (PyCFunction)_wrap_plplot_canvas_plgra, METH_NOARGS },
    { "plhls", (PyCFunction)_wrap_plplot_canvas_plhls, METH_VARARGS|METH_KEYWORDS },
    { "plinit", (PyCFunction)_wrap_plplot_canvas_plinit, METH_NOARGS },
    { "pljoin", (PyCFunction)_wrap_plplot_canvas_pljoin, METH_VARARGS|METH_KEYWORDS },
    { "pllightsource", (PyCFunction)_wrap_plplot_canvas_pllightsource, METH_VARARGS|METH_KEYWORDS },
    { "plline", (PyCFunction)_wrap_plplot_canvas_plline, METH_VARARGS },
    { "pllsty", (PyCFunction)_wrap_plplot_canvas_pllsty, METH_VARARGS|METH_KEYWORDS },
    { "plprec", (PyCFunction)_wrap_plplot_canvas_plprec, METH_VARARGS|METH_KEYWORDS },
    { "plpsty", (PyCFunction)_wrap_plplot_canvas_plpsty, METH_VARARGS|METH_KEYWORDS },
    { "plreplot", (PyCFunction)_wrap_plplot_canvas_plreplot, METH_NOARGS },
    { "plrgb", (PyCFunction)_wrap_plplot_canvas_plrgb, METH_VARARGS|METH_KEYWORDS },
    { "plrgb1", (PyCFunction)_wrap_plplot_canvas_plrgb1, METH_VARARGS|METH_KEYWORDS },
    { "plschr", (PyCFunction)_wrap_plplot_canvas_plschr, METH_VARARGS|METH_KEYWORDS },
    { "plscmap0n", (PyCFunction)_wrap_plplot_canvas_plscmap0n, METH_VARARGS|METH_KEYWORDS },
    { "plscmap1n", (PyCFunction)_wrap_plplot_canvas_plscmap1n, METH_VARARGS|METH_KEYWORDS },
    { "plscol0", (PyCFunction)_wrap_plplot_canvas_plscol0, METH_VARARGS|METH_KEYWORDS },
    { "plscolbg", (PyCFunction)_wrap_plplot_canvas_plscolbg, METH_VARARGS|METH_KEYWORDS },
    { "plscolor", (PyCFunction)_wrap_plplot_canvas_plscolor, METH_VARARGS|METH_KEYWORDS },
    { "plscompression", (PyCFunction)_wrap_plplot_canvas_plscompression, METH_VARARGS|METH_KEYWORDS },
    { "plsdidev", (PyCFunction)_wrap_plplot_canvas_plsdidev, METH_VARARGS|METH_KEYWORDS },
    { "plsdimap", (PyCFunction)_wrap_plplot_canvas_plsdimap, METH_VARARGS|METH_KEYWORDS },
    { "plsdiori", (PyCFunction)_wrap_plplot_canvas_plsdiori, METH_VARARGS|METH_KEYWORDS },
    { "plsdiplt", (PyCFunction)_wrap_plplot_canvas_plsdiplt, METH_VARARGS|METH_KEYWORDS },
    { "plsdiplz", (PyCFunction)_wrap_plplot_canvas_plsdiplz, METH_VARARGS|METH_KEYWORDS },
    { "plsesc", (PyCFunction)_wrap_plplot_canvas_plsesc, METH_VARARGS|METH_KEYWORDS },
    { "plsfam", (PyCFunction)_wrap_plplot_canvas_plsfam, METH_VARARGS|METH_KEYWORDS },
    { "plsmaj", (PyCFunction)_wrap_plplot_canvas_plsmaj, METH_VARARGS|METH_KEYWORDS },
    { "plsmin", (PyCFunction)_wrap_plplot_canvas_plsmin, METH_VARARGS|METH_KEYWORDS },
    { "plsori", (PyCFunction)_wrap_plplot_canvas_plsori, METH_VARARGS|METH_KEYWORDS },
    { "plspage", (PyCFunction)_wrap_plplot_canvas_plspage, METH_VARARGS|METH_KEYWORDS },
    { "plspause", (PyCFunction)_wrap_plplot_canvas_plspause, METH_VARARGS|METH_KEYWORDS },
    { "plsstrm", (PyCFunction)_wrap_plplot_canvas_plsstrm, METH_VARARGS|METH_KEYWORDS },
    { "plssub", (PyCFunction)_wrap_plplot_canvas_plssub, METH_VARARGS|METH_KEYWORDS },
    { "plssym", (PyCFunction)_wrap_plplot_canvas_plssym, METH_VARARGS|METH_KEYWORDS },
    { "plstar", (PyCFunction)_wrap_plplot_canvas_plstar, METH_VARARGS|METH_KEYWORDS },
    { "plstripa", (PyCFunction)_wrap_plplot_canvas_plstripa, METH_VARARGS|METH_KEYWORDS },
    { "plstripd", (PyCFunction)_wrap_plplot_canvas_plstripd, METH_VARARGS|METH_KEYWORDS },
    { "plsvpa", (PyCFunction)_wrap_plplot_canvas_plsvpa, METH_VARARGS|METH_KEYWORDS },
    { "plsxax", (PyCFunction)_wrap_plplot_canvas_plsxax, METH_VARARGS|METH_KEYWORDS },
    { "plsxwin", (PyCFunction)_wrap_plplot_canvas_plsxwin, METH_VARARGS|METH_KEYWORDS },
    { "plsyax", (PyCFunction)_wrap_plplot_canvas_plsyax, METH_VARARGS|METH_KEYWORDS },
    { "plszax", (PyCFunction)_wrap_plplot_canvas_plszax, METH_VARARGS|METH_KEYWORDS },
    { "pltext", (PyCFunction)_wrap_plplot_canvas_pltext, METH_NOARGS },
    { "plvasp", (PyCFunction)_wrap_plplot_canvas_plvasp, METH_VARARGS|METH_KEYWORDS },
    { "plvpas", (PyCFunction)_wrap_plplot_canvas_plvpas, METH_VARARGS|METH_KEYWORDS },
    { "plvpor", (PyCFunction)_wrap_plplot_canvas_plvpor, METH_VARARGS|METH_KEYWORDS },
    { "plvsta", (PyCFunction)_wrap_plplot_canvas_plvsta, METH_NOARGS },
    { "plw3d", (PyCFunction)_wrap_plplot_canvas_plw3d, METH_VARARGS|METH_KEYWORDS },
    { "plwid", (PyCFunction)_wrap_plplot_canvas_plwid, METH_VARARGS|METH_KEYWORDS },
    { "plwind", (PyCFunction)_wrap_plplot_canvas_plwind, METH_VARARGS|METH_KEYWORDS },
    { NULL, NULL, 0 }
};

PyTypeObject PyPlplotCanvas_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "c_plplotcanvas.Canvas",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,			/* tp_getattro */
    (setattrofunc)0,			/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyPlplotCanvas_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_plplot_canvas_new,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- functions ----------- */

PyMethodDef cplplotcanvas_functions[] = {
    { NULL, NULL, 0 }
};

/* initialise stuff extension classes */
void
cplplotcanvas_register_classes(PyObject *d)
{
    PyObject *module;

    if ((module = PyImport_ImportModule("gnome.canvas")) != NULL) {
        PyObject *moddict = PyModule_GetDict(module);

        _PyGnomeCanvas_Type = (PyTypeObject *)PyDict_GetItemString(moddict, "Canvas");
        if (_PyGnomeCanvas_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name Canvas from gnome.canvas");
            return;
        }
    } else {
        PyErr_SetString(PyExc_ImportError,
            "could not import gnome.canvas");
        return;
    }


#line 1125 "plplotcanvas.c"
    pygobject_register_class(d, "PlplotCanvas", PLPLOT_TYPE_CANVAS, &PyPlplotCanvas_Type, Py_BuildValue("(O)", &PyGnomeCanvas_Type));
}
