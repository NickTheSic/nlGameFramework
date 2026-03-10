
//base components 
#define FT2_BUILD_LIBRARY
#include <ft2build.h>
#include FT_FREETYPE_H

#include "src/base/ftbase.c"
#include "src/base/ftsystem.c"
#include "src/base/ftinit.c"
#include "src/base/ftdebug.c"
#include "src/base/ftbbox.c"      // recommended, see <ftbbox.h>
#include "src/base/ftglyph.c"     // recommended, see <ftglyph.h>

//#include "src/base/ftbdf.c"        // optional, see <ftbdf.h>
#include "src/base/ftbitmap.c"     // optional, see <ftbitmap.h>
//#include "src/base/ftcid.c"        // optional, see <ftcid.h>
//#include "src/base/ftfstype.c"     // optional
//#include "src/base/ftgasp.c"       // optional, see <ftgasp.h>
//#include "src/base/ftgxval.c"      // optional, see <ftgxval.h>
#include "src/base/ftmm.c"         // optional, see <ftmm.h>
//#include "src/base/ftotval.c"      // optional, see <ftotval.h>
//#include "src/base/ftpatent.c"     // optional
//#include "src/base/ftpfr.c"        // optional, see <ftpfr.h>
//#include "src/base/ftstroke.c"     // optional, see <ftstroke.h>
//#include "src/base/ftsynth.c"      // optional, see <ftsynth.h>
//#include "src/base/fttype1.c"      // optional, see <t1tables.h>
//#include "src/base/ftwinfnt.c"     // optional, see <ftwinfnt.h>

// font drivers (optional; at least one is needed)

// #include "src/bdf/bdf.c"           // BDF font driver
// #include "src/cff/cff.c"           // CFF/OpenType font driver
// #include "src/cid/type1cid.c"      // Type 1 CID-keyed font driver
// #include "src/pcf/pcf.c"           // PCF font driver
// #include "src/pfr/pfr.c"           // PFR/TrueDoc font driver
#include "src/sfnt/sfnt.c"         // SFNT files support
//                                  // (TrueType & OpenType)
#include "src/truetype/truetype.c" // TrueType font driver
// #include "src/type1/type1.c"       // Type 1 font driver
// #include "src/type42/type42.c"     // Type 42 font driver
// #include "src/winfonts/winfnt.c"   // Windows FONT / FNT font driver
// 
// //rasterizers (optional; at least one is needed for vectorformats)
// 
#include "src/smooth/smooth.c"     // anti-aliasing rasterizer
// #include "src/raster/raster.c"     // monochrome rasterizer
// #include "src/sdf/sdf.c"           // Signed Distance Field driver
// 
// // auxiliary modules (optional)
// 
#include "src/autofit/autofit.c"   // auto hinting module
// #include "src/cache/ftcache.c"     // cache sub-system (in beta)
#include "src/gzip/ftgzip.c"       // support for compressed fonts (.gz)
// #include "src/lzw/ftlzw.c"         // support for compressed fonts (.Z)
// #include "src/bzip2/ftbzip2.c"     // support for compressed fonts (.bz2)
// #include "src/gxvalid/gxvalid.c"   // TrueTypeGX/AAT table validation
// #include "src/otvalid/otvalid.c"   // OpenType table validation
// #include "src/psaux/psaux.c"       // PostScript Type 1 parsing
// #include "src/pshinter/pshinter.c" // PS hinting module
#include "src/psnames/psnames.c"   // PostScript glyph names support


/* Notes:

`ftcache.c'  needs `ftglyph.c'
`ftfstype.c' needs `fttype1.c'
`ftglyph.c'  needs `ftbitmap.c'
`ftstroke.c' needs `ftglyph.c'
`ftsynth.c'  needs `ftbitmap.c'

`cff.c'      needs `sfnt.c', `pshinter.c', and `psnames.c'
`truetype.c' needs `sfnt.c' and `psnames.c'
`type1.c'    needs `psaux.c' `pshinter.c', and `psnames.c'
`type1cid.c' needs `psaux.c', `pshinter.c', and `psnames.c'
`type42.c'   needs `truetype.c'
*/
