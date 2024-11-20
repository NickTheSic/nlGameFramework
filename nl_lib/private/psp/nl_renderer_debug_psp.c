#include "../nl_renderer.h"
#include <pspdebug.h>
#include <pspdisplay.h>

int initialize_renderer_subsystem()
{
    return 1;
}

void begin_render_frame()
{
    pspDebugScreenSetXY(0, 0);
}

void end_render_frame()
{
    sceDisplayWaitVblankStart();
}

void renderer_swap_buffers()
{
    NL_UNIMPLEMENTED_FUNC;
}

/////////////////////////////////////////////////////////////////
//              Wrappers around GL specific calls              //
/////////////////////////////////////////////////////////////////
void set_background_colour_4f(float r, float g, float b, float a)
{
    NL_UNUSED(r);NL_UNUSED(g);NL_UNUSED(b);NL_UNUSED(a);
    NL_UNIMPLEMENTED_FUNC;
}

void set_viewport_size(int width, int height)
{
    NL_UNUSED(width);NL_UNUSED(height);
    NL_UNIMPLEMENTED_FUNC;
}

void set_wireframe_rendering()
{
    NL_UNIMPLEMENTED_FUNC;
}

void set_fill_rendering()
{
    NL_UNIMPLEMENTED_FUNC;
}

void set_depth_test_enabled(int enabled)
{
    NL_UNUSED(enabled);
    NL_UNIMPLEMENTED_FUNC;
}

void set_cull_face_enabled(int enabled)
{
    NL_UNUSED(enabled);
    NL_UNIMPLEMENTED_FUNC;
}
void set_cull_face_side(int front)
{
    NL_UNUSED(front);
    NL_UNIMPLEMENTED_FUNC;
}

void set_cull_front_face(int clockwise)
{    
    NL_UNUSED(clockwise);
    NL_UNIMPLEMENTED_FUNC;
}