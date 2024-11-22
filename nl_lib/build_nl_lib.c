#include "nl_lib.h"

// This version specifically defines what is built for which platform
// more copy paste, less awkward defines

#if defined(_WIN32)
#include "private/common/nl_audio_openal.c"
#include "private/common/nl_camera.c"
#include "private/common/nl_fileio.c"
#include "private/common/nl_input.c"
#include "private/common/nl_math.c"
#include "private/common/nl_memory.c"
#include "private/common/nl_random.c"

#include "third_party/stb_image.c"

#include "private/gl/nl_gl_win32.c"
#include "private/gl/nl_renderer_gl_common.c"
#include "private/gl/nl_renderer_gl_win32.c"
#include "private/gl/nl_shader.c"

#include "private/win32/nl_deltatime_win32.c"
#include "private/win32/nl_window_win32.c"


#elif defined(__EMSCRIPTEN__)
#include "private/common/nl_audio_openal.c"
#include "private/common/nl_camera.c"
#include "private/common/nl_fileio.c"
#include "private/common/nl_input.c"
#include "private/common/nl_math.c"
#include "private/common/nl_memory.c"
#include "private/common/nl_random.c"

#include "third_party/stb_image.c"

#include "private/gl/nl_gl_web.c"
#include "private/gl/nl_renderer_gl_common.c"
#include "private/gl/nl_renderer_gl_web.c"
#include "private/gl/nl_shader.c"

#include "private/web/nl_window_web.c"
#include "private/web/nl_deltatime_web.c"


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
#include "private/null/nl_mesh_null.c"
#include "private/null/nl_renderer_null.c"
#include "private/null/nl_shader_null.c"
#include "private/null/nl_vertex_attrib_null.c"
#include "private/null/nl_window_null.c"

#endif // Platform