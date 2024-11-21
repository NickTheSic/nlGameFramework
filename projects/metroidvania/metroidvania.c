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
    player_init(&player);

    generate_square_simple_sprite(&mouse_follow.sprite, PLAYER_HALF_WIDTH);
    load_texture_for_sprite(&mouse_follow.sprite, "data/test_sprite.png");

    init_sprite_renderer();

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

    // Overlap Code
    {
        aabb player_box = {0};
        player_box.min.x = player.pos.x;
        player_box.min.y = player.pos.y;
        player_box.max.x = player.pos.x + player.width;
        player_box.max.y = player.pos.y + player.width;

        aabb mouse_box  = {0};
        mouse_box.min.x = mouse_follow.pos.x - PLAYER_QUARTER_WIDTH;
        mouse_box.min.y = mouse_follow.pos.y - PLAYER_QUARTER_WIDTH;
        mouse_box.max.x = mouse_follow.pos.x + PLAYER_QUARTER_WIDTH;
        mouse_box.max.y = mouse_follow.pos.y + PLAYER_QUARTER_WIDTH;

        if (aabb_box_overlap(player_box, mouse_box))
        {
            local_persist int count;
            NL_LOG("Overlap! %d", ++count);
        }
    }
}

void app_specific_render(void)
{   
    mat4x4f model = {0};
    create_identity_matrix(&model);
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
}

#include "camera_control.c"
#include "player.c"
#include "nl_sprite_renderer_gl.c"
