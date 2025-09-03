#include "nl_lib.h"
#include "nl_sprite_renderer.h"
#include <private/nl_physics2d.h>

#if PLATFORM_CONSOLE
#include <private/nl_keys_to_controller.h>
#endif

global_variable camera main_cam = {0};

nl_sprite man = {0};
nl_sprite money = {0};

v2f man_pos = {0};
v2f money_pos = {0};

internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0, (float)width, 0, (float)height, -0.1f, 100.f);
    set_projection_matrix(&main_cam.proj_matrix);
}

internal_function void generate_game_sprites(void)
{
    load_texture_for_sprite(&man, "data/man.png");
    generate_rectangle_simple_sprite(&man, 32, 64);

    load_texture_for_sprite(&money, "data/money.png");
    generate_rectangle_simple_sprite(&money, 32, 32);
}

void app_specific_init(void)
{
    init_sprite_renderer();

    generate_game_sprites();

    set_screen_size(200, 240);

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
    {
        model.m41 = money_pos.x;
        model.m42 = money_pos.y;
        set_model_matrix(&model);
        render_single_simple_sprite(&money);
    }

    create_identity_matrix(&model);
    {
        model.m41 = man_pos.x;
        model.m42 = man_pos.y;
        set_model_matrix(&model);
        render_single_sprite_colour(&man, COLOUR_GREEN);
    }
}

void app_specific_cleanup(void)
{
    free_simple_sprite(&man);
    free_simple_sprite(&money);
}

#include "nl_sprite_renderer_gl.c"
