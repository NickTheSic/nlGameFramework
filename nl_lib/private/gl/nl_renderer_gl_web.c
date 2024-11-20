#include "../nl_renderer.h"
#include "nl_gl_web.h"

void renderer_swap_buffers()
{
    eglSwapBuffers(g_EGLRenderer.display, g_EGLRenderer.surface);
}

void set_wireframe_rendering(void)
{
    //TODO Learn how to do this here (if needed)
}

void set_fill_rendering(void)
{
    //TODO Learn how to do this here (if needed)
}
