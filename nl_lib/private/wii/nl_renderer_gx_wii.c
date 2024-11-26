#include "../nl_renderer.h"
#include "../nl_window.h"
#include "nl_window_helpers_wii.h"
#include <ogc/gx.h>
#include <ogc/system.h>
#include <malloc.h>

#define	FIFO_SIZE (256*1024)
global_variable void *fifo_buffer = 0;


int initialize_renderer_subsystem()
{
    fifo_buffer= MEM_K0_TO_K1(memalign(32, FIFO_SIZE));
    memset(fifo_buffer, 0, FIFO_SIZE);

    GX_Init(fifo_buffer, FIFO_SIZE);
    GX_SetCopyClear((GXColor){0,0,0,255}, 0x00ffffff);

    GXRModeObj* const mode = get_gxr_object();
    GX_SetViewport(0,0,mode->fbWidth,mode->efbHeight,0,1);
    GX_SetDispCopyYScale((float)mode->xfbHeight/(float)mode->efbHeight);
    GX_SetScissor(0,0,mode->fbWidth,mode->efbHeight);
	GX_SetDispCopySrc(0,0,mode->fbWidth,mode->efbHeight);
	GX_SetDispCopyDst(mode->fbWidth,mode->xfbHeight);
	GX_SetCopyFilter(mode->aa,mode->sample_pattern,
					 GX_TRUE,mode->vfilter);
	GX_SetFieldMode(mode->field_rendering,
					((mode->viHeight==2*mode->xfbHeight)?GX_ENABLE:GX_DISABLE));

	GX_SetCullMode(GX_CULL_NONE);
	GX_CopyDisp(get_wii_framebuffer(),GX_TRUE);
	GX_SetDispCopyGamma(GX_GM_1_0);

    return 1;
}

void begin_render_frame()
{

}

void end_render_frame()
{
    GX_End();
    GX_DrawDone();
}


void set_background_colour_4f(float r, float g, float b, float a)
{
    NL_UNIMPLEMENTED_FUNC;
    NL_UNUSED(r);
    NL_UNUSED(g);
    NL_UNUSED(b);
    NL_UNUSED(a);
}

void renderer_swap_buffers()
{
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
