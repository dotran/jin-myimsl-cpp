/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version: 1.3.22
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package plplot.core;

public class plplotjavac implements plplotjavacConstants {
  public static void pl_setcontlabelformat(int lexp, int sigdig) {
    plplotjavacJNI.pl_setcontlabelformat(lexp, sigdig);
  }

  public static void pl_setcontlabelparam(double offset, double size, double spacing, int active) {
    plplotjavacJNI.pl_setcontlabelparam(offset, size, spacing, active);
  }

  public static void pladv(int page) {
    plplotjavacJNI.pladv(page);
  }

  public static void plaxes(double x0, double y0, String xopt, double xtick, int nxsub, String yopt, double ytick, int nysub) {
    plplotjavacJNI.plaxes(x0, y0, xopt, xtick, nxsub, yopt, ytick, nysub);
  }

  public static void plbin(double[] n, double[] ArrayCk, int center) {
    plplotjavacJNI.plbin(n, ArrayCk, center);
  }

  public static void plbop() {
    plplotjavacJNI.plbop();
  }

  public static void plbox(String xopt, double xtick, int nxsub, String yopt, double ytick, int nysub) {
    plplotjavacJNI.plbox(xopt, xtick, nxsub, yopt, ytick, nysub);
  }

  public static void plbox3(String xopt, String xlabel, double xtick, int nsubx, String yopt, String ylabel, double ytick, int nsuby, String zopt, String zlabel, double ztick, int nsubz) {
    plplotjavacJNI.plbox3(xopt, xlabel, xtick, nsubx, yopt, ylabel, ytick, nsuby, zopt, zlabel, ztick, nsubz);
  }

  public static void plcalc_world(double rx, double ry, double[] arg2, double[] arg3, int[] arg4) {
    plplotjavacJNI.plcalc_world(rx, ry, arg2, arg3, arg4);
  }

  public static void plclear() {
    plplotjavacJNI.plclear();
  }

  public static void plcol0(int icol0) {
    plplotjavacJNI.plcol0(icol0);
  }

  public static void plcol1(double col1) {
    plplotjavacJNI.plcol1(col1);
  }

  public static void plcont(double[][] Matrix, int kx, int lx, int ky, int ly, double[] Array, double[][] pltr, double[][] OBJECT_DATA) {
    plplotjavacJNI.plcont(Matrix, kx, lx, ky, ly, Array, pltr, OBJECT_DATA);
  }

  public static void plcpstrm(int iplsr, int flags) {
    plplotjavacJNI.plcpstrm(iplsr, flags);
  }

  public static void plend() {
    plplotjavacJNI.plend();
  }

  public static void plend1() {
    plplotjavacJNI.plend1();
  }

  public static void plenv(double xmin, double xmax, double ymin, double ymax, int just, int axis) {
    plplotjavacJNI.plenv(xmin, xmax, ymin, ymax, just, axis);
  }

  public static void pleop() {
    plplotjavacJNI.pleop();
  }

  public static void plerrx(double[] n, double[] arg1, double[] arg2) {
    plplotjavacJNI.plerrx(n, arg1, arg2);
  }

  public static void plerry(double[] n, double[] arg1, double[] arg2) {
    plplotjavacJNI.plerry(n, arg1, arg2);
  }

  public static void plfamadv() {
    plplotjavacJNI.plfamadv();
  }

  public static void plfill(double[] n, double[] ArrayCk) {
    plplotjavacJNI.plfill(n, ArrayCk);
  }

  public static void plfill3(double[] n, double[] arg1, double[] arg2) {
    plplotjavacJNI.plfill3(n, arg1, arg2);
  }

  public static void plflush() {
    plplotjavacJNI.plflush();
  }

  public static void plfont(int ifont) {
    plplotjavacJNI.plfont(ifont);
  }

  public static void plfontld(int fnt) {
    plplotjavacJNI.plfontld(fnt);
  }

  public static void plgchr(double[] arg0, double[] arg1) {
    plplotjavacJNI.plgchr(arg0, arg1);
  }

  public static void plgcol0(int icol0, int[] arg1, int[] arg2, int[] arg3) {
    plplotjavacJNI.plgcol0(icol0, arg1, arg2, arg3);
  }

  public static void plgcolbg(int[] arg0, int[] arg1, int[] arg2) {
    plplotjavacJNI.plgcolbg(arg0, arg1, arg2);
  }

  public static void plgcompression(int[] OUTPUT) {
    plplotjavacJNI.plgcompression(OUTPUT);
  }

  public static void plgdev(StringBuffer OUTPUT) {
    plplotjavacJNI.plgdev(OUTPUT);
  }

  public static void plgdidev(double[] arg0, double[] arg1, double[] arg2, double[] arg3) {
    plplotjavacJNI.plgdidev(arg0, arg1, arg2, arg3);
  }

  public static void plgdiori(double[] OUTPUT) {
    plplotjavacJNI.plgdiori(OUTPUT);
  }

  public static void plgdiplt(double[] arg0, double[] arg1, double[] arg2, double[] arg3) {
    plplotjavacJNI.plgdiplt(arg0, arg1, arg2, arg3);
  }

  public static void plgfam(int[] arg0, int[] arg1, int[] arg2) {
    plplotjavacJNI.plgfam(arg0, arg1, arg2);
  }

  public static void plgfci(long[] OUTPUT) {
    plplotjavacJNI.plgfci(OUTPUT);
  }

  public static void plgfnam(StringBuffer OUTPUT) {
    plplotjavacJNI.plgfnam(OUTPUT);
  }

  public static void plglevel(int[] OUTPUT) {
    plplotjavacJNI.plglevel(OUTPUT);
  }

  public static void plgpage(double[] arg0, double[] arg1, int[] arg2, int[] arg3, int[] arg4, int[] arg5) {
    plplotjavacJNI.plgpage(arg0, arg1, arg2, arg3, arg4, arg5);
  }

  public static void plgra() {
    plplotjavacJNI.plgra();
  }

  public static void plgspa(double[] arg0, double[] arg1, double[] arg2, double[] arg3) {
    plplotjavacJNI.plgspa(arg0, arg1, arg2, arg3);
  }

  public static void plgstrm(int[] OUTPUT) {
    plplotjavacJNI.plgstrm(OUTPUT);
  }

  public static void plgver(StringBuffer OUTPUT) {
    plplotjavacJNI.plgver(OUTPUT);
  }

  public static void plgvpd(double[] arg0, double[] arg1, double[] arg2, double[] arg3) {
    plplotjavacJNI.plgvpd(arg0, arg1, arg2, arg3);
  }

  public static void plgvpw(double[] arg0, double[] arg1, double[] arg2, double[] arg3) {
    plplotjavacJNI.plgvpw(arg0, arg1, arg2, arg3);
  }

  public static void plgxax(int[] arg0, int[] arg1) {
    plplotjavacJNI.plgxax(arg0, arg1);
  }

  public static void plgyax(int[] arg0, int[] arg1) {
    plplotjavacJNI.plgyax(arg0, arg1);
  }

  public static void plgzax(int[] arg0, int[] arg1) {
    plplotjavacJNI.plgzax(arg0, arg1);
  }

  public static void plhist(double[] n, double datmin, double datmax, int nbin, int oldwin) {
    plplotjavacJNI.plhist(n, datmin, datmax, nbin, oldwin);
  }

  public static void plhls(double h, double l, double s) {
    plplotjavacJNI.plhls(h, l, s);
  }

  public static void plhlsrgb(double h, double l, double s, double[] arg3, double[] arg4, double[] arg5) {
    plplotjavacJNI.plhlsrgb(h, l, s, arg3, arg4, arg5);
  }

  public static void plinit() {
    plplotjavacJNI.plinit();
  }

  public static void pljoin(double x1, double y1, double x2, double y2) {
    plplotjavacJNI.pljoin(x1, y1, x2, y2);
  }

  public static void pllab(String xlabel, String ylabel, String tlabel) {
    plplotjavacJNI.pllab(xlabel, ylabel, tlabel);
  }

  public static void pllightsource(double x, double y, double z) {
    plplotjavacJNI.pllightsource(x, y, z);
  }

  public static void plline(double[] n, double[] ArrayCk) {
    plplotjavacJNI.plline(n, ArrayCk);
  }

  public static void plline3(double[] n, double[] arg1, double[] arg2) {
    plplotjavacJNI.plline3(n, arg1, arg2);
  }

  public static void pllsty(int lin) {
    plplotjavacJNI.pllsty(lin);
  }

  public static void plmesh(double[] ArrayX, double[] ArrayY, double[][] MatrixCk, int opt) {
    plplotjavacJNI.plmesh(ArrayX, ArrayY, MatrixCk, opt);
  }

  public static void plmeshc(double[] ArrayX, double[] ArrayY, double[][] MatrixCk, int opt, double[] Array) {
    plplotjavacJNI.plmeshc(ArrayX, ArrayY, MatrixCk, opt, Array);
  }

  public static void plmkstrm(int[] OUTPUT) {
    plplotjavacJNI.plmkstrm(OUTPUT);
  }

  public static void plmtex(String side, double disp, double pos, double just, String text) {
    plplotjavacJNI.plmtex(side, disp, pos, just, text);
  }

  public static void plot3d(double[] ArrayX, double[] ArrayY, double[][] MatrixCk, int opt, int side) {
    plplotjavacJNI.plot3d(ArrayX, ArrayY, MatrixCk, opt, side);
  }

  public static void plot3dc(double[] ArrayX, double[] ArrayY, double[][] MatrixCk, int opt, double[] Array) {
    plplotjavacJNI.plot3dc(ArrayX, ArrayY, MatrixCk, opt, Array);
  }

  public static void plot3dcl(double[] ArrayX, double[] ArrayY, double[][] MatrixCk, int opt, double[] arg4, int ixstart, int[] arg6, int[] ArrayCk) {
    plplotjavacJNI.plot3dcl(ArrayX, ArrayY, MatrixCk, opt, arg4, ixstart, arg6, ArrayCk);
  }

  public static void plsurf3d(double[] ArrayX, double[] ArrayY, double[][] MatrixCk, int opt, double[] Array) {
    plplotjavacJNI.plsurf3d(ArrayX, ArrayY, MatrixCk, opt, Array);
  }

  public static void plsurf3dl(double[] ArrayX, double[] ArrayY, double[][] MatrixCk, int opt, double[] arg4, int ixstart, int[] arg6, int[] ArrayCk) {
    plplotjavacJNI.plsurf3dl(ArrayX, ArrayY, MatrixCk, opt, arg4, ixstart, arg6, ArrayCk);
  }

  public static int plparseopts(String[] p_argc, int mode) {
    return plplotjavacJNI.plparseopts(p_argc, mode);
  }

  public static void plpat(int[] n, int[] ArrayCk) {
    plplotjavacJNI.plpat(n, ArrayCk);
  }

  public static void plpoin(double[] n, double[] ArrayCk, int code) {
    plplotjavacJNI.plpoin(n, ArrayCk, code);
  }

  public static void plpoin3(double[] n, double[] arg1, double[] arg2, int code) {
    plplotjavacJNI.plpoin3(n, arg1, arg2, code);
  }

  public static void plpoly3(double[] n, double[] arg1, double[] arg2, int[] ArrayCkMinus1, int flag) {
    plplotjavacJNI.plpoly3(n, arg1, arg2, ArrayCkMinus1, flag);
  }

  public static void plprec(int setp, int prec) {
    plplotjavacJNI.plprec(setp, prec);
  }

  public static void plpsty(int patt) {
    plplotjavacJNI.plpsty(patt);
  }

  public static void plptex(double x, double y, double dx, double dy, double just, String text) {
    plplotjavacJNI.plptex(x, y, dx, dy, just, text);
  }

  public static void plreplot() {
    plplotjavacJNI.plreplot();
  }

  public static void plrgbhls(double r, double g, double b, double[] arg3, double[] arg4, double[] arg5) {
    plplotjavacJNI.plrgbhls(r, g, b, arg3, arg4, arg5);
  }

  public static void plschr(double def, double scale) {
    plplotjavacJNI.plschr(def, scale);
  }

  public static void plscmap0(int[] Array, int[] arg1, int[] arg2) {
    plplotjavacJNI.plscmap0(Array, arg1, arg2);
  }

  public static void plscmap0n(int ncol0) {
    plplotjavacJNI.plscmap0n(ncol0);
  }

  public static void plscmap1(int[] Array, int[] arg1, int[] arg2) {
    plplotjavacJNI.plscmap1(Array, arg1, arg2);
  }

  public static void plscmap1l(int itype, double[] n, double[] arg2, double[] arg3, double[] arg4, int[] ArrayCkMinus1) {
    plplotjavacJNI.plscmap1l(itype, n, arg2, arg3, arg4, ArrayCkMinus1);
  }

  public static void plscmap1n(int ncol1) {
    plplotjavacJNI.plscmap1n(ncol1);
  }

  public static void plscol0(int icol0, int r, int g, int b) {
    plplotjavacJNI.plscol0(icol0, r, g, b);
  }

  public static void plscolbg(int r, int g, int b) {
    plplotjavacJNI.plscolbg(r, g, b);
  }

  public static void plscolor(int color) {
    plplotjavacJNI.plscolor(color);
  }

  public static void plscompression(int compression) {
    plplotjavacJNI.plscompression(compression);
  }

  public static void plsdev(String devname) {
    plplotjavacJNI.plsdev(devname);
  }

  public static void plsdidev(double mar, double aspect, double jx, double jy) {
    plplotjavacJNI.plsdidev(mar, aspect, jx, jy);
  }

  public static void plsdimap(int dimxmin, int dimxmax, int dimymin, int dimymax, double dimxpmm, double dimypmm) {
    plplotjavacJNI.plsdimap(dimxmin, dimxmax, dimymin, dimymax, dimxpmm, dimypmm);
  }

  public static void plsdiori(double rot) {
    plplotjavacJNI.plsdiori(rot);
  }

  public static void plsdiplt(double xmin, double ymin, double xmax, double ymax) {
    plplotjavacJNI.plsdiplt(xmin, ymin, xmax, ymax);
  }

  public static void plsdiplz(double xmin, double ymin, double xmax, double ymax) {
    plplotjavacJNI.plsdiplz(xmin, ymin, xmax, ymax);
  }

  public static void plsesc(char esc) {
    plplotjavacJNI.plsesc(esc);
  }

  public static int plsetopt(String opt, String optarg) {
    return plplotjavacJNI.plsetopt(opt, optarg);
  }

  public static void plsfam(int fam, int num, int bmax) {
    plplotjavacJNI.plsfam(fam, num, bmax);
  }

  public static void plsfci(long fci) {
    plplotjavacJNI.plsfci(fci);
  }

  public static void plsfnam(String fnam) {
    plplotjavacJNI.plsfnam(fnam);
  }

  public static void plshades(double[][] Matrix, double xmin, double xmax, double ymin, double ymax, double[] Array, int fill_width, int cont_color, int cont_width, int rectangular, double[][] pltr, double[][] OBJECT_DATA) {
    plplotjavacJNI.plshades(Matrix, xmin, xmax, ymin, ymax, Array, fill_width, cont_color, cont_width, rectangular, pltr, OBJECT_DATA);
  }

  public static void plshade(double[][] Matrix, double left, double right, double bottom, double top, double shade_min, double shade_max, int sh_cmap, double sh_color, int sh_width, int min_color, int min_width, int max_color, int max_width, int rectangular, double[][] pltr, double[][] OBJECT_DATA) {
    plplotjavacJNI.plshade(Matrix, left, right, bottom, top, shade_min, shade_max, sh_cmap, sh_color, sh_width, min_color, min_width, max_color, max_width, rectangular, pltr, OBJECT_DATA);
  }

  public static void plsmaj(double def, double scale) {
    plplotjavacJNI.plsmaj(def, scale);
  }

  public static void plsmin(double def, double scale) {
    plplotjavacJNI.plsmin(def, scale);
  }

  public static void plsori(int ori) {
    plplotjavacJNI.plsori(ori);
  }

  public static void plspage(double xp, double yp, int xleng, int yleng, int xoff, int yoff) {
    plplotjavacJNI.plspage(xp, yp, xleng, yleng, xoff, yoff);
  }

  public static void plspause(int pause) {
    plplotjavacJNI.plspause(pause);
  }

  public static void plsstrm(int strm) {
    plplotjavacJNI.plsstrm(strm);
  }

  public static void plssub(int nx, int ny) {
    plplotjavacJNI.plssub(nx, ny);
  }

  public static void plssym(double def, double scale) {
    plplotjavacJNI.plssym(def, scale);
  }

  public static void plstar(int nx, int ny) {
    plplotjavacJNI.plstar(nx, ny);
  }

  public static void plstart(String devname, int nx, int ny) {
    plplotjavacJNI.plstart(devname, nx, ny);
  }

  public static void plstripa(int id, int pen, double x, double y) {
    plplotjavacJNI.plstripa(id, pen, x, y);
  }

  public static void plstripc(int[] OUTPUT, String xspec, String yspec, double xmin, double xmax, double xjump, double ymin, double ymax, double xlpos, double ylpos, int y_ascl, int acc, int colbox, int collab, int[] Array, int[] ArrayCk, SWIGTYPE_p_p_char legline, String labx, String laby, String labtop) {
    plplotjavacJNI.plstripc(OUTPUT, xspec, yspec, xmin, xmax, xjump, ymin, ymax, xlpos, ylpos, y_ascl, acc, colbox, collab, Array, ArrayCk, SWIGTYPE_p_p_char.getCPtr(legline), labx, laby, labtop);
  }

  public static void plstripd(int id) {
    plplotjavacJNI.plstripd(id);
  }

  public static void plstyl(int[] n, int[] ArrayCk) {
    plplotjavacJNI.plstyl(n, ArrayCk);
  }

  public static void plsvect(double[] Array, double[] ArrayCk, int fill) {
    plplotjavacJNI.plsvect(Array, ArrayCk, fill);
  }

  public static void plsvpa(double xmin, double xmax, double ymin, double ymax) {
    plplotjavacJNI.plsvpa(xmin, xmax, ymin, ymax);
  }

  public static void plsxax(int digmax, int digits) {
    plplotjavacJNI.plsxax(digmax, digits);
  }

  public static void plsyax(int digmax, int digits) {
    plplotjavacJNI.plsyax(digmax, digits);
  }

  public static void plsym(double[] n, double[] ArrayCk, int code) {
    plplotjavacJNI.plsym(n, ArrayCk, code);
  }

  public static void plszax(int digmax, int digits) {
    plplotjavacJNI.plszax(digmax, digits);
  }

  public static void pltext() {
    plplotjavacJNI.pltext();
  }

  public static void plvasp(double aspect) {
    plplotjavacJNI.plvasp(aspect);
  }

  public static void plvect(double[][] Matrix, double[][] MatrixCk, double scale, double[][] pltr, double[][] OBJECT_DATA) {
    plplotjavacJNI.plvect(Matrix, MatrixCk, scale, pltr, OBJECT_DATA);
  }

  public static void plvpas(double xmin, double xmax, double ymin, double ymax, double aspect) {
    plplotjavacJNI.plvpas(xmin, xmax, ymin, ymax, aspect);
  }

  public static void plvpor(double xmin, double xmax, double ymin, double ymax) {
    plplotjavacJNI.plvpor(xmin, xmax, ymin, ymax);
  }

  public static void plvsta() {
    plplotjavacJNI.plvsta();
  }

  public static void plw3d(double basex, double basey, double height, double xmin0, double xmax0, double ymin0, double ymax0, double zmin0, double zmax0, double alt, double az) {
    plplotjavacJNI.plw3d(basex, basey, height, xmin0, xmax0, ymin0, ymax0, zmin0, zmax0, alt, az);
  }

  public static void plwid(int width) {
    plplotjavacJNI.plwid(width);
  }

  public static void plwind(double xmin, double xmax, double ymin, double ymax) {
    plplotjavacJNI.plwind(xmin, xmax, ymin, ymax);
  }

  public static void plxormod(int mode, int[] OUTPUT) {
    plplotjavacJNI.plxormod(mode, OUTPUT);
  }

  public static void plClearOpts() {
    plplotjavacJNI.plClearOpts();
  }

  public static void plResetOpts() {
    plplotjavacJNI.plResetOpts();
  }

  public static void plSetUsage(String program_string, String usage_string) {
    plplotjavacJNI.plSetUsage(program_string, usage_string);
  }

  public static void plOptUsage() {
    plplotjavacJNI.plOptUsage();
  }

}