#include "nl_lib.h"
#include "nl_sprite_renderer.h"

global_variable camera main_cam = {0};

#define LASER_BOTTOM_Y 80.f
#define LASER_DISTANCE 170.f
#define LASER_TOP_Y LASER_BOTTOM_Y + LASER_DISTANCE
#define LASER_START_X 120.f

nl_sprite laser_base = {0};
nl_sprite laser_beam = {0};
nl_sprite laser_top = {0};
nl_sprite man = {0};
nl_sprite money = {0};

internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0, width, 0, height, -0.1f, 100.f);
    set_projection_matrix(&main_cam.proj_matrix.m11);
}

void app_specific_init(void)
{
    init_sprite_renderer();

    generate_rectangle_simple_sprite(&laser_base, 32, 16);
    load_texture_for_sprite(&laser_base, "data/laser_stop.png");

    generate_rectangle_simple_sprite(&laser_top, 32, 16);
    load_texture_for_sprite(&laser_top, "data/laser_top.png");

    generate_rectangle_simple_sprite(&laser_beam, 32, LASER_DISTANCE);
    load_texture_for_sprite(&laser_beam, "data/single_red_pixel.png");

    generate_rectangle_simple_sprite(&man, 32, 64);
    load_texture_for_sprite(&man, "data/man.png");

    generate_rectangle_simple_sprite(&money, 32, 32);
    load_texture_for_sprite(&money, "data/money.png");

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
    //model.m41
    create_identity_matrix(&model);
    {
        model.m41 = LASER_START_X;
        for (int i = 0; i < 3; ++i)
        {
            model.m42 = LASER_BOTTOM_Y;
            set_model_matrix(&model.m11);
            render_single_simple_sprite(&laser_beam);
            render_single_simple_sprite(&laser_base);
            model.m42 = LASER_TOP_Y;
            set_model_matrix(&model.m11);
            render_single_simple_sprite(&laser_top);
            model.m41 += 50;
        }
        model.m42 = LASER_BOTTOM_Y + 32;
        set_model_matrix(&model.m11);
        render_single_simple_sprite(&money);
    }

    create_identity_matrix(&model);
    {
        model.m41 = LASER_START_X - 40.f;
        model.m42 = LASER_BOTTOM_Y + 32.f;
        set_model_matrix(&model.m11);
        render_single_simple_sprite(&man);
    }

}

void app_specific_cleanup(void)
{
    free_simple_sprite(&laser_base);
    free_simple_sprite(&laser_beam);
    free_simple_sprite(&laser_top);
    free_simple_sprite(&man);
    free_simple_sprite(&money);
}

#include "nl_sprite_renderer_gl.c"
