#include "../nl_renderer.h"
#include "nl_gl_web.h"

void renderer_swap_buffers()
{
    eglSwapBuffers(g_EGLRenderer.display, g_EGLRenderer.surface);
}
