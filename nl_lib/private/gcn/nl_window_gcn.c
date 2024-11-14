#include "../nl_window.h"

#include <ogc/consol.h>
#include <ogc/system.h>
#include <ogc/video.h>

global_variable void *framebuffer = 0;
global_variable GXRModeObj *screenmode = NULL;

int initialize_window(int width, int height, const char* title)
{
    NL_UNUSED(width); NL_UNUSED(height); NL_UNUSED(title);

    VIDEO_Init();
    screenmode = VIDEO_GetPreferredMode(NULL);

    framebuffer = MEM_K0_TO_K1(SYS_AllocateFramebuffer(screenmode));

	console_init(
        framebuffer, 
        20, 20, 
        screenmode->fbWidth, screenmode->xfbHeight, 
        screenmode->fbWidth*VI_DISPLAY_PIX_SZ);
	
	VIDEO_Configure(screenmode);
	VIDEO_SetNextFramebuffer(framebuffer);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if(screenmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
    
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
    // Good enough I think
    // fbWidth width of external framebuffer
    // efbHeight height of embedded framebuffer
    // xfbHeight height of external framebuffer
    return (v2i){screenmode->fbWidth,screenmode->efbHeight};
}

void set_window_title(const char* title)
{
    NL_UNUSED(title);
}
