#include "nl_lib.h"
#include "nl_sprite_renderer.h"
#include <private/nl_physics2d.h>

// Goal = You play as a spider that swings back and forth. 
// You can only press space
// You jump form place to place, hopefully catching bugs

global_variable camera main_cam = {0};

internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0, width, 0, height, -0.1f, 100.f);
    set_projection_matrix(&main_cam.proj_matrix.m11);
}

internal_function void load_game_sfx(void)
{}

internal_function void generate_game_sprites(void)
{}

internal_function void restart_game(void)
{}   

internal_function void collision_test(void)
{}

void app_specific_init(void)
{
    init_sprite_renderer();

    generate_game_sprites();
    load_game_sfx();

    pfn_window_size_callback = &winsizecbk;
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);

    create_srt_matrix(&main_cam.view_matrix, (v3f){1.0f,1.0f,0.0f}, (v3f){0.0f,0.0f,0.0f}, (v3f){0.0f,0.0f,0.0f});
    set_view_matrix(&main_cam.view_matrix.m11);

    restart_game();
}

void app_specific_update(double dt)
{}

void app_specific_render(void)
{}

void app_specific_cleanup(void)
{}

#include "nl_sprite_renderer_gl.c"
