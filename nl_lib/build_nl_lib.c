#include "nl_lib.h"


/*-------Common Files--------------*/
#include "private/common/nl_fileio.c"
#include "private/common/nl_memory.c"
#include "private/common/nl_math.c"
#include "private/common/nl_audio_loading.c"
#include "private/common/nl_utility.c"
#include "private/common/nl_renderer_gl_common.c"
#include "private/common/nl_shader.c"
#include "private/common/nl_input.c"


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


#elif 
#error Incomplete Library for this platform


#endif // Platform