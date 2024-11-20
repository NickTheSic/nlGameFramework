#include "../nl_renderer.h"
#include "nl_psp_include.h"
#include <pspgu.h>
#include <pspdisplay.h>

char list[0x20000] __attribute__((aligned(64)));

int initialize_renderer_subsystem(void)
{
    sceGuInit();

    //Set up buffers
    sceGuStart(GU_DIRECT, list);
    sceGuDrawBuffer(GU_PSM_8888,(void*)0,BUFFER_WIDTH);
    sceGuDispBuffer(SCREEN_WIDTH,SCREEN_HEIGHT,(void*)0x88000,BUFFER_WIDTH);
    sceGuDepthBuffer((void*)0x110000,BUFFER_WIDTH);

    //Set up viewport
    sceGuOffset(2048 - (SCREEN_WIDTH / 2), 2048 - (SCREEN_HEIGHT / 2));
    sceGuViewport(2048, 2048, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    //Set some stuff
    sceGuDepthRange(65535, 0); //Use the full buffer for depth testing - buffer is reversed order

    sceGuDepthFunc(GU_GEQUAL); //Depth buffer is reversed, so GEQUAL instead of LEQUAL
    sceGuEnable(GU_DEPTH_TEST); //Enable depth testing

    sceGuFinish();
    sceGuDisplay(GU_TRUE);

    return 1;
}

void begin_render_frame(void)
{
    sceGuStart(GU_DIRECT, list);
    //sceGuClearColor(0xFFFFFFFF); // White background
    sceGuClearColor(0xff777777); // White background
    sceGuClear(GU_COLOR_BUFFER_BIT);
}

void end_render_frame(void)
{
    sceGuFinish();
    sceGuSync(0, 0);
    sceDisplayWaitVblankStart();

    sceGuSwapBuffers();
}

void renderer_swap_buffers(void)
{
    sceGuSwapBuffers();
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

void set_wireframe_rendering(void)
{
    NL_UNIMPLEMENTED_FUNC;
}

void set_fill_rendering(void)
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