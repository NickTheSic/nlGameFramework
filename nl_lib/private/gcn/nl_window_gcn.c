#include "../nl_window.h"

#include <ogc/consol.h>
#include <ogc/system.h>
#include <ogc/video.h>

global_variable void *xfb = 0;
global_variable GXRModeObj *rmode = NULL;

int initialize_window(int width, int height, const char* title)
{
    NL_UNUSED(width); NL_UNUSED(height); NL_UNUSED(title);

    VIDEO_Init();
    rmode = VIDEO_GetPreferredMode(NULL);

    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

	console_init(
        xfb, 
        20, 20, 
        rmode->fbWidth, rmode->xfbHeight, 
        rmode->fbWidth*VI_DISPLAY_PIX_SZ);
	
	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(xfb);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
    
    return 1;
}

void poll_events()
{
    VIDEO_WaitVSync();
}

int window_active()
{
    return 1;
}

void window_request_close()
{

}

void window_swap_buffers()
{

}

v2i get_screen_size()
{
    NL_UNIMPLEMENTED_FUNC
    return (v2i){0,0};
}

void set_window_title(const char* title)
{
    NL_UNUSED(title);
}
