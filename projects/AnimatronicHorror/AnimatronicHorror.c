#include "nl_lib.h"

#include "nl_sprite_renderer.h"

global_variable nl_sprite peanut_one = {0};
global_variable nl_sprite peanut_two = {0};

global_variable camera main_cam = {0};

internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0, (float)width, 0, (float)height, -0.1f, 100.f);
    set_projection_matrix(&main_cam.proj_matrix);
}

void app_specific_init(void)
{
    init_sprite_renderer();

    load_texture_for_sprite(&peanut_one, "data/peanut_1.png");
    generate_rectangle_simple_sprite(&peanut_one, 32, 64);
    load_texture_for_sprite(&peanut_two, "data/peanut_2.png");
    generate_rectangle_simple_sprite(&peanut_two, 32, 64);

    set_window_size_callback(&winsizecbk);
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);

    create_srt_matrix(&main_cam.view_matrix, (v3f){1.0f,1.0f,0.0f}, (v3f){0.0f,0.0f,0.0f}, (v3f){0.0f,0.0f,0.0f});
    set_view_matrix(&main_cam.view_matrix);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{
    mat4x4f model = {0};
    create_identity_matrix(&model);

    model.m41 = 10.0f;
    model.m42 = 10.0f;
    set_model_matrix(&model);
    render_single_simple_sprite(&peanut_one);

    model.m41 = 300.0f;
    model.m42 = 300.0f;
    set_model_matrix(&model);
    render_single_simple_sprite(&peanut_two);
}

void app_specific_cleanup(void)
{
    free_simple_sprite(&peanut_two);
    free_simple_sprite(&peanut_one);
}

#include "nl_sprite_renderer_gl.c"
