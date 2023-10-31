#include "nl_lib.h"

#if defined(_WIN32)
#include "private/nl_window_win32.c"
#include "private/nl_renderer_gl_win32.c"
#include "private/nl_renderer_gl_common.c"
#include "private/nl_gl_win32.c"


#elif defined(__EMSCRIPTEN__)
#include "private/nl_window_web.c"
#include "private/nl_renderer_gl_web.c"
#include "private/nl_renderer_gl_common.c"
#include "private/nl_gl_web.c"


#elif 
#error Incomplete Library for this platform

#endif
