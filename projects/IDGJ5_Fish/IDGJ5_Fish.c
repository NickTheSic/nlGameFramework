#include "nl_lib.h"
#include "nl_sprite_renderer.h"

void app_specific_init(void)
{
    set_background_colour_4f(0.3f,0.5f,1.0f,1.0f);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{

}

void app_specific_cleanup(void)
{
    
}

#include "nl_sprite_renderer_gl.c"