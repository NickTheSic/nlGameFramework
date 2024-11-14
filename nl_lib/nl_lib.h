#ifndef __NL_LIB_H__
#define __NL_LIB_H__

#include "private/nl_audio.h"
#include "private/nl_camera.h"
#include "private/nl_debug.h"
#include "private/nl_deltatime.h"
#include "private/nl_fileio.h"
#include "private/nl_gamepad.h"
#include "private/nl_input.h"
#include "private/nl_math.h"
#include "private/nl_memory.h"
#include "private/nl_random.h"
#include "private/nl_renderer.h"
#ifndef GEKKO
#include "private/nl_shader.h"
#endif
#include "private/nl_window.h"


#ifdef  __EMSCRIPTEN__
#include "private/web/nl_web_glue.h"
#endif//__EMSCRIPTEN__

#define CANNOT_EXIT_MAIN_LOOP (__EMSCRIPTEN__ || GEKKO)

#endif //__NL_LIB_H__