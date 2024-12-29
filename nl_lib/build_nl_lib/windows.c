
#include "main/winmain.c"

#if 0
#include "private/common/nl_audio_openal.c"
#else
#include "private/win32/nl_audio_xaudio.c"
#endif

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
#include "private/gl/nl_vertex_attrib_gl.c"

#include "private/win32/nl_deltatime_win32.c"
#include "private/win32/nl_gamepad_xinput.c"
#include "private/win32/nl_platform_win.c"
#include "private/win32/nl_window_win32.c"