from Numeric import *
from plplot import *

# main
#
# Displays Greek letters and mathematically interesting Unicode ranges

Greek = (
"#gA","#gB","#gG","#gD","#gE","#gZ","#gY","#gH","#gI","#gK","#gL","#gM",
"#gN","#gC","#gO","#gP","#gR","#gS","#gT","#gU","#gF","#gX","#gQ","#gW",
"#ga","#gb","#gg","#gd","#ge","#gz","#gy","#gh","#gi","#gk","#gl","#gm",
"#gn","#gc","#go","#gp","#gr","#gs","#gt","#gu","#gf","#gx","#gq","#gw",
)

Type1 = (
"0x0020","0x0021","0x0023","0x0025","0x0026",
"0x0028","0x0029","0x002b","0x002c","0x002e",
"0x002f","0x0030","0x0031","0x0032","0x0033",
"0x0034","0x0035","0x0036","0x0037","0x0038",
"0x0039","0x003a","0x003b","0x003c","0x003d",
"0x003e","0x003f","0x005b","0x005d","0x005f",
"0x007b","0x007c","0x007d","0x00a9","0x00ac",
"0x00ae","0x00b0","0x00b1","0x00d7","0x00f7",
"0x0192","0x0391","0x0392","0x0393","0x0394",
"0x0395","0x0396","0x0397","0x0398","0x0399",
"0x039a","0x039b","0x039c","0x039d","0x039e",
"0x039f","0x03a0","0x03a1","0x03a3","0x03a4",
"0x03a5","0x03a6","0x03a7","0x03a8","0x03a9",
"0x03b1","0x03b2","0x03b3","0x03b4","0x03b5",
"0x03b6","0x03b7","0x03b8","0x03b9","0x03ba",
"0x03bb","0x03bc","0x03bd","0x03be","0x03bf",
"0x03c0","0x03c1","0x03c2","0x03c3","0x03c4",
"0x03c5","0x03c6","0x03c7","0x03c8","0x03c9",
"0x03d1","0x03d2","0x03d5","0x03d6","0x2022",
"0x2026","0x2032","0x2033","0x203e","0x2044",
"0x2111","0x2118","0x211c","0x2122","0x2126",
"0x2135","0x2190","0x2191","0x2192","0x2193",
"0x2194","0x21b5","0x21d0","0x21d1","0x21d2",
"0x21d3","0x21d4","0x2200","0x2202","0x2203",
"0x2205","0x2206","0x2207","0x2208","0x2209",
"0x220b","0x220f","0x2211","0x2212","0x2215",
"0x2217","0x221a","0x221d","0x221e","0x2220",
"0x2227","0x2228","0x2229","0x222a","0x222b",
"0x2234","0x223c","0x2245","0x2248","0x2260",
"0x2261","0x2264","0x2265","0x2282","0x2283",
"0x2284","0x2286","0x2287","0x2295","0x2297",
"0x22a5","0x22c5","0x2320","0x2321","0x2329",
"0x232a","0x25ca","0x2660","0x2663","0x2665",
"0x2666",
)

title = (
"#<0x10>PLplot Example 23 - Greek Letters",
"#<0x10>PLplot Example 23 - Type 1 Symbol Font Glyphs by Unicode (a)",
"#<0x10>PLplot Example 23 - Type 1 Symbol Font Glyphs by Unicode (b)",
"#<0x10>PLplot Example 23 - Type 1 Symbol Font Glyphs by Unicode (c)",
"#<0x10>PLplot Example 23 - Number Forms Unicode Block",
"#<0x10>PLplot Example 23 - Arrows Unicode Block (a)",
"#<0x10>PLplot Example 23 - Arrows Unicode Block (b)",
"#<0x10>PLplot Example 23 - Mathematical Operators Unicode Block (a)",
"#<0x10>PLplot Example 23 - Mathematical Operators Unicode Block (b)",
"#<0x10>PLplot Example 23 - Mathematical Operators Unicode Block (c)",
"#<0x10>PLplot Example 23 - Mathematical Operators Unicode Block (d)",
)

lo = (
"0x0",
"0x0",
"0x0",
"0x0",
"0x2153",
"0x2190",
"0x21d0",
"0x2200",
"0x2240",
"0x2280",
"0x22c0",
)

hi = (
"0x0",
"0x0",
"0x0",
"0x0",
"0x2184",
"0x21d0",
"0x2200",
"0x2240",
"0x2280",
"0x22c0",
"0x2300",
)
nxcells = (
12,
8,
8,
8,
8,
8,
8,
8,
8,
8,
8,
)

nycells = (
8,
8,
8,
8,
8,
8,
8,
8,
8,
8,
8,
)

# non-zero values Must be consistent with nxcells and nycells.
offset = (
0,
0,
64,
128,
0,
0,
0,
0,
0,
0,
0,
)

def main():
    
    for page in range(11):
	pladv(0)

	# Set up viewport and window

	plvpor(0.02, 0.98, 0.02, 0.90)
	plwind(0.0, 1.0, 0.0, 1.0)
	mm = plgspa()
	plschr(0., 0.8)
	ycharacter_scale = (1.0 - 0.0)/(mm[3]-mm[2])
	# Factor should be 0.5, but heuristically it turns out to be larger.
	yoffset = 1.0*plgchr()[1]*ycharacter_scale

	# Draw the grid using plbox

	plcol0(2)
	deltax = 1./float(nxcells[page])
	deltay = 1./float(nycells[page])
	plbox("bcg", deltax, 0, "bcg", deltay, 0)
	plcol0(15)
	if page == 0:
	    # Greek letters.
	    CommandString = Greek
	elif 1 <= page and page <= 3:
	    # Unicode for Type 1 Symbol Glyphs.
	    # Work around Numeric bug which only allows you to add one-character
	    # strings to arrays of Pyobjects.
	    CommandString = "#" + ("[" + array(Type1,PyObject)\
	    [offset[page]:offset[page]+(nxcells[page]*nycells[page])] + "]")
	elif page >= 4:
	    numarray = arange(int(lo[page],16),int(hi[page],16))
	    symbolarray = []
	    for number in numarray:
		symbolarray.append(hex(number))
	    CommandString = "#" + ("[" + array(symbolarray,PyObject) + "]")
	length = len(CommandString)
	slice = 0
	for y in (0.5+arange(nycells[page]-1,-1,-1))*deltay:
	    for x in (0.5+arange(nxcells[page]))*deltax:
		if slice < length:
		    plptex(x,y+yoffset,1.,0.,0.5, CommandString[slice])
		    plptex(x,y-yoffset,1.,0.,0.5, "#" +CommandString[slice])
		slice += 1

	plschr(0., 1.0)
	# Page title
	plmtex("t", 1.5, 0.5, 0.5, title[page])

    # Restore defaults
    plcol0(1)

main()
