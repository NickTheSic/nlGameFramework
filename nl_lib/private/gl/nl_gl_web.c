#include "nl_gl.h"
#include "nl_gl_web.h"
#include "nl_gles.h"

int initialize_gl(void)
{
    EmscriptenWebGLContextAttributes attr = {};
    emscripten_webgl_init_context_attributes(&attr);

	initialize_gles();

    return 1;
}

#include "nl_gles.c"
