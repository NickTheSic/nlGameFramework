#include "nl_lib.h"
#include "private/nl_gl.h"

#if defined GEKKO
#include <ogcsys.h>

void app_specific_init(void)
{
    NL_LOG("nl gamepad");
}
void app_specific_update(double dt)
{
	NL_UNUSED(dt);
		
	if(is_button_pressed(0x0100)) // A button but hidden 
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