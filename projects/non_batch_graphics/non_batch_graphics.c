#include <nl_lib.h>

#include "nl_graphics.h"

#ifdef PSP
#include <pspctrl.h>
#define key_right PSP_CTRL_RIGHT
#define key_left PSP_CTRL_LEFT
#define key_down PSP_CTRL_DOWN
#define key_up PSP_CTRL_UP

#define key_is_held(b) is_button_pressed(0, b)

#endif

global_variable camera main_cam = {0};
global_variable float camera_pos_x = 0.f;
global_variable float camera_pos_y = 0.f;

global_variable v2f mouse_pos = {0};
global_variable v2i grid_coords = {0};

internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0, width, 0, height, -0.1f, 100.f);
    set_batch_proj_matrix(&main_cam.proj_matrix.m11);
}

void camera_controls(float dt)
{
    char bIsDirty = 0;

    if (key_is_held(key_right))
    {
        camera_pos_x -= 100.f * dt;
        bIsDirty = 1;
    }
    else if (key_is_held(key_left))
    {
        camera_pos_x += 100.f * dt;
        bIsDirty = 1;
    }

    if (key_is_held(key_up))
    {
        camera_pos_y -= 100.f * dt;
        bIsDirty = 1;
    }
    else if (key_is_held(key_down))
    {
        camera_pos_y += 100.f * dt;
        bIsDirty = 1;
    }

    if (bIsDirty > 0)
    {
        create_srt_matrix(&main_cam.view_matrix, (v3f){1.0f,1.0f,1.0f}, (v3f){0.0f,0.0f,0.0f}, (v3f){camera_pos_x,camera_pos_y,0.0f});
        set_batch_view_matrix(&main_cam.view_matrix.m11);
    }
}

void app_specific_init(void)
{   
    game_init_graphics();
    pfn_window_size_callback = &winsizecbk;
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);

    create_srt_matrix(&main_cam.view_matrix, (v3f){1.0f,1.0f,0.0f}, (v3f){0.0f,0.0f,0.0f}, (v3f){0.0f,0.0f,0.0f});
    set_batch_view_matrix(&main_cam.view_matrix.m11);
}

void app_specific_update(double dt)
{
    camera_controls(dt);

    const v2i mouse_posi = get_mouse_position_from_system();
    mouse_pos = (v2f){(float)mouse_posi.x, (float)mouse_posi.y};
    project_mouse_to_camera(&main_cam, &mouse_pos);
}

void app_specific_render()
{
    game_begin_render();

    add_square_to_render_batch(mouse_pos, COLOUR_BLUE, 5.0f);

    game_end_render();
}

void app_specific_cleanup()
{
    game_free_graphics();
}

#ifdef PSP
#include "platforms/nl_graphics_psp.c"
#else
#include "platforms/nl_graphics_gl.c"
#endif
