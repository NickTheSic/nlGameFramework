#include "nl_gl.h"
#include "nl_gl_web.h"
#include "nl_egl.h"

int initialize_gl(void)
{
    EmscriptenWebGLContextAttributes attr = {};
    emscripten_webgl_init_context_attributes(&attr);

    return initialize_egl(0);
}

// a silly hack to be able to include and compile this
#define NL_EGL_API  EGL_OPENGL_ES_API //SWITCH VERSIO: EGL_OPENGL_API

#include "nl_egl.c"
