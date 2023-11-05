#include "../nl_renderer.h"
#include "../nl_gl.h"

int initialize_renderer_subsystem()
{
    if (!initialize_gl())
    {
        return 0;
    }

    return 1;
}

void begin_render_frame()
{
    glClear(GL_COLOR_BUFFER_BIT); 
    glClear(GL_DEPTH_BUFFER_BIT);
}

void end_render_frame()
{
    renderer_swap_buffers();
}

void set_background_colour_4f(float r, float g, float b, float a)
{
    glClearColor(r,g,b,a);
}

void set_viewport_size(int width, int height)
{
    glViewport(0, 0, width, height);
}
