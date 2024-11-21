#include "nl_lib.h"

#include "metroidvania.h"
#include "camera_control.h"
#include "private/nl_physics2d.h"

internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0, width, 0, height, -0.1f, 100.f);
    set_projection_matrix(&main_cam.proj_matrix.m11);
}

void app_specific_init(void)
{
    init_sprite_renderer();

    player_init(&player);
    init_gameobject(&ground, 100, 20, (v2f){0.f,0.f}, "data/thing.png");
    init_gameobject(&mouse_follow, PLAYER_HALF_WIDTH, PLAYER_HALF_WIDTH, (v2f){0.f,0.f}, "data/test_sprite.png");

    pfn_window_size_callback = &winsizecbk;
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);

    create_srt_matrix(&main_cam.view_matrix, (v3f){1.0f,1.0f,0.0f}, (v3f){0.0f,0.0f,0.0f}, (v3f){0.0f,0.0f,0.0f});
    set_view_matrix(&main_cam.view_matrix.m11);
}

void app_specific_update(double dt)
{
    player_update(dt, &player, &controller);
    camera_controls(dt, &main_cam);

    const v2i mouse_posi = get_mouse_position_from_system();
    mouse_follow.pos = (v2f){(float)mouse_posi.x, (float)mouse_posi.y};
    project_mouse_to_camera(&main_cam, &mouse_follow.pos);
}

void app_specific_render(void)
{   
    mat4x4f model = {0};
    create_identity_matrix(&model);
    {
        set_model_matrix(&model.m11);
        render_single_simple_sprite(&ground.sprite);
    }

    {
        model.m41 = player.pos.x;
        model.m42 = player.pos.y;
        set_model_matrix(&model.m11);
        render_single_simple_sprite(&player.sprite);
    }

    {
        model.m41 = (mouse_follow.pos.x-PLAYER_QUARTER_WIDTH);
        model.m42 = (mouse_follow.pos.y-PLAYER_QUARTER_WIDTH);

        set_model_matrix(&model.m11);
        render_single_simple_sprite(&mouse_follow.sprite);
    }
}

void app_specific_cleanup(void)
{
    free_simple_sprite(&player.sprite);
    free_simple_sprite(&mouse_follow.sprite);
    free_simple_sprite(&ground.sprite);
}

#include "camera_control.c"
#include "player.c"
#include "nl_sprite_renderer_gl.c"
