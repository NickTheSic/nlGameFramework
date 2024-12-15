#include "nl_lib.h"


#if defined(_WIN32)
#include "build_nl_lib/windows.c"


#elif defined(__EMSCRIPTEN__)
#include "build_nl_lib/emscripten.c"


#elif defined(__linux__)
#include "build_nl_lib/linux.c"


#elif defined(PSP)
#include "build_nl_lib/psp.c"


#else
#warning Incomplete Library for this platform. Using null platform

#include "private/common/nl_camera.c"
#include "private/common/nl_fileio.c"
#include "private/common/nl_input.c"
#include "private/common/nl_math.c"
#include "private/common/nl_memory.c"
#include "private/common/nl_random.c"
//#include "third_party/stb_image.c"
#include "private/null/nl_audio_null.c"
#include "private/null/nl_deltatime_null.c"
#include "private/null/nl_gamepad_null.c"
#include "private/null/nl_renderer_null.c"
#include "private/null/nl_shader_null.c"
#include "private/null/nl_vertex_attrib_null.c"
#include "private/null/nl_window_null.c"

#endif // Platform