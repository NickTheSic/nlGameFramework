#include "nl_lib.h"
#include "nl_sprite_renderer.h"

global_variable nl_sprite bait = {0};
global_variable nl_sprite fish = {0};

global_variable v2f player_pos = {0};
global_variable v2f hook_pos = {0};
global_variable v2f *bait_pos = {0};

global_variable camera main_cam = {0};

internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0, width, 0, height, -0.1f, 100.f);
    set_projection_matrix(&main_cam.proj_matrix.m11);
}

internal_function load_sprites()
{
    init_sprite_renderer();

    load_texture_for_sprite(&fish, "data/fish.png");
    generate_rectangle_simple_sprite(&fish, 64, 32);

    load_texture_for_sprite(&bait, "data/bait.png");
    generate_rectangle_simple_sprite(&bait, 32, 32);
}

void app_specific_init(void)
{
    set_background_colour_4f(0.3f,0.5f,1.0f,1.0f);
    load_sprites();

    pfn_window_size_callback = &winsizecbk;
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);

    create_srt_matrix(&main_cam.view_matrix, (v3f){1.0f,1.0f,0.0f}, (v3f){0.0f,0.0f,0.0f}, (v3f){0.0f,0.0f,0.0f});
    set_view_matrix(&main_cam.view_matrix.m11);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{
    mat4x4f model = {0};
    create_identity_matrix(&model);
    set_model_matrix(&model.m11);
    //render_single_sprite_colour(&fish, COLOUR_BLUE);
    render_single_simple_sprite(&fish);
}

void app_specific_cleanup(void)
{
    free_simple_sprite(&fish);
    free_simple_sprite(&bait);
}

#include "nl_sprite_renderer_gl.c"