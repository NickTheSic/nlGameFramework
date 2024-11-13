#include "nl_lib.h"
#include "private/nl_gl.h"

#if defined GEKKO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>

void *Initialise();
void app_specific_init(void)
{
    NL_LOG("Library Version");
	PAD_Init();
}
void app_specific_update(double dt)
{
	NL_UNUSED(dt);
	
	PAD_ScanPads();

	int buttonsDown = PAD_ButtonsDown(0);
		
	if( buttonsDown & PAD_BUTTON_A ) 
    {
		NL_LOG("Button A pressed.");
	}
}
void app_specific_render(void)
{
    VIDEO_WaitVSync();
}
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