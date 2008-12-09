#----------------------------------------------------------------------------
# $Id: x19.tcl,v 1.2 2002/07/04 00:53:41 airwin Exp $
#----------------------------------------------------------------------------

proc x19 {{w loopback}} {
    set miny -70
    set maxy 80
    set minx 190
    set maxx 550
    $w cmd plcol0 1
    $w cmd plenv $minx $maxx $miny $maxy 1 -1
    $w cmd plcol0 2
    $w cmd plmap usaglobe 0 $minx $maxx $miny $maxy
    
    set minx 190
    set maxx 340
    $w cmd plcol0 1
    $w cmd plenv $minx $maxx $miny $maxy 1 -1
    $w cmd plcol0 2
    $w cmd plmap usaglobe 0 $minx $maxx $miny $maxy

    set minx 0
    set maxx 360
    $w cmd plcol0 2
    $w cmd plenv -75 75 -75 75 1 -1
    $w cmd plmap globe 1 $minx $maxx $miny $maxy
    $w cmd plcol0 1
    $w cmd pllsty 2
    $w cmd plmeridians 1 10.0 10.0 0.0 360.0 -10.0 80.0
    $w cmd pllsty 1
# No defaults to restore
}
