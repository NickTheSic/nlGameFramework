
#include "main/pspmain.c"

#include "private/common/nl_camera.c"
#include "private/common/nl_fileio.c"
#include "private/common/nl_input.c"
#include "private/common/nl_math.c"
#include "private/common/nl_memory.c"
#include "private/common/nl_random.c"

#include "private/null/nl_shader_null.c"
#include "private/null/nl_vertex_attrib_null.c"

#if 0
#   include "private/common/nl_audio_openal.c"
#elif 0
#   include "private/psp/nl_audio_sdlmixer.c"
#else
#include "private/psp/nl_audio_psp.c"
#endif
#include "private/psp/nl_deltatime_psp.c"
#include "private/psp/nl_gamepad_psp.c"
#include "private/psp/nl_platform_psp.c"

#ifdef PSP_DEBUG_RENDERER
#   include "private/psp/nl_renderer_debug_psp.c"
#else 
#   include "private/psp/nl_renderer_psp.c"
#endif

#include "private/psp/nl_window_psp.c"
#include "third_party/stb_image.c"
