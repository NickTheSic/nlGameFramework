#include "../nl_renderer.h"
#include "../nl_debug.h"
#include "nl_gl.h"

int initialize_renderer_subsystem()
{
    if (!initialize_gl())
    {
        return 0;
    }

    // Required for sprite rendering
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

    return 1;
}

void begin_render_frame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void set_depth_test_enabled(int enabled)
{
    if (enabled == 1)
    {
        glEnable(GL_DEPTH_TEST); 
    } 
    else
    {
        glDisable(GL_DEPTH_TEST); 
    }
}

void set_cull_face_enabled(int enabled)
{
    if (enabled == 0)
    {
        glDisable(GL_CULL_FACE);
    }
    else 
    {
        glEnable(GL_CULL_FACE);
    }
}

void set_cull_face_side(int front)
{
    if (front == 0)
    {
        glCullFace(GL_BACK);
    }
    else
    {
        glCullFace(GL_FRONT);
    }
}

void set_cull_front_face(int clockwise)
{
    if (clockwise)
    {
        glFrontFace(GL_CW);
    }  
    else
    {
        glFrontFace(GL_CCW);
    }
}

