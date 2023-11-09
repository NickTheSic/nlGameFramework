#include "../nl_renderer.h"
#include "../nl_window.h"

void renderer_swap_buffers()
{
    window_swap_buffers();
}

void set_wireframe_rendering(void)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void set_fill_rendering(void)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
