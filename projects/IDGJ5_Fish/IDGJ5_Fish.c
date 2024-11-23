#include "nl_lib.h"
#include "nl_sprite_renderer.h"

nl_sprite bait = {0};
nl_sprite fish = {0};

v2f player_pos = {0};
v2f hook_pos = {0};
v2f *bait_pos = {0};

internal_function load_sprites()
{
    load_texture_for_sprite(&fish, "data/fish.png");
    generate_rectangle_simple_sprite(&fish, 32, 64);

    load_texture_for_sprite(&bait, "data/bait.png");
    generate_rectangle_simple_sprite(&bait, 32, 32);
}

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