#include "nl_lib.h"
#include "private/nl_gl.h"

#if defined GEKKO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;
void *Initialise();
void app_specific_init(void)
{
    xfb = Initialise();
    NL_LOG("Hello, World!");
}
void app_specific_update(double dt)
{
    VIDEO_WaitVSync();
	PAD_ScanPads();

	int buttonsDown = PAD_ButtonsDown(0);
		
	if( buttonsDown & PAD_BUTTON_A ) 
    {
		NL_LOG("Button A pressed.");
	}
}
void * Initialise() 
{
	void *framebuffer;

	VIDEO_Init();
	PAD_Init();
	
	rmode = VIDEO_GetPreferredMode(NULL);

	framebuffer = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	console_init(framebuffer,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);
	
	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(framebuffer);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();

	return framebuffer;
}
void app_specific_render(void){}
void app_specific_cleanup(void){}

#else

void app_specific_init(void)
{
    NL_LOG("Hello, World!");
}
void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}
void app_specific_render(void){}
void app_specific_cleanup(void){}

#endif