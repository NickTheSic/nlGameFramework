#include "nl_lib.h"

//*      Could add SDL for a blanket just works implementation?  Maybe Raylib?

#if defined(_WIN32)
#include "build_nl_lib/windows.c"

#elif defined(__EMSCRIPTEN__)
#include "build_nl_lib/emscripten.c"

#else
#warning Incomplete Library for this platform. Using null platform

#include "main/nullmain.c"

#include "private/common/nl_camera.c"
#include "private/common/nl_fileio.c"
#include "private/common/nl_input.c"
#include "private/common/nl_math.c"
#include "private/common/nl_memory.c"
#include "private/common/nl_random.c"

#include "third_party/stb/stb_image.c"
#include "third_party/stb/stb_truetype.c"

#include "private/null/nl_null.c"

#endif // Platform
