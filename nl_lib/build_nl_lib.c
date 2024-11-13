#include "nl_lib.h"


/*-------Common Files--------------*/
#include "private/common/nl_audio_openal.c"
#include "private/common/nl_fileio.c"
#include "private/common/nl_memory.c"
#include "private/common/nl_math.c"
#include "private/common/nl_camera.c"
#include "private/common/nl_random.c"

#if !defined(GEKKO)
#include "private/common/nl_renderer_gl_common.c"
#include "private/common/nl_shader.c"
#endif

#include "private/common/nl_input.c"


/*--------Third Party-------------*/
#ifndef GEKKO
#include "third_party/stb_image.c"
#endif

#if defined(_WIN32)
#include "private/win32/nl_window_win32.c"
#include "private/win32/nl_renderer_gl_win32.c"
#include "private/win32/nl_gl_win32.c"
#include "private/win32/nl_deltatime_win32.c"

#elif defined(__EMSCRIPTEN__)
#include "private/web/nl_window_web.c"
#include "private/web/nl_renderer_gl_web.c"
#include "private/web/nl_gl_web.c"
#include "private/web/nl_deltatime_web.c"

#elif defined(__linux__)
#include "private/linux/nl_window_linux.c"
#include "private/linux/nl_renderer_gl_linux.c"
#include "private/linux/nl_gl_linux.c"
#include "private/linux/nl_deltatime_linux.c"

#elif defined(GEKKO)
#include "private/gcn/nl_window_gcn.c"

#else
#warning Incomplete Library for this platform


#endif // Platform