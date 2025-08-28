#include "nl_lib.h"

#include "nl_sprite_renderer.h"

global_variable nl_sprite peanut_one = {0};
global_variable nl_sprite peanut_two = {0};

void app_specific_init(void)
{
    //init_sprite_renderer();

    load_texture_for_sprite(&peanut_one, "data/peanut_1.png");
    generate_rectangle_simple_sprite(&peanut_one, 32, 64);
    load_texture_for_sprite(&peanut_two, "data/peanut_2.png");
    generate_rectangle_simple_sprite(&peanut_two, 32, 64);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{
    render_single_simple_sprite(&peanut_one);

    render_single_simple_sprite(&peanut_two);
}

void app_specific_cleanup(void)
{
    
}

#include "nl_sprite_renderer_gl.c"
