#include "nl_lib.h"

#include "batch2d.h"
#include "grid.h"

global_variable unsigned int sp    = {0};
global_variable batch2d batch = {0};

global_variable unsigned int loc_view_mat = {0};
global_variable unsigned int loc_proj_mat = {0};

global_variable camera main_cam = {0};
global_variable float camera_pos_x = 0.f;
global_variable float camera_pos_y = 0.f;

global_variable v2f mouse_pos = {0};
global_variable v2i grid_coords = {0};

global_variable grid grid_ = {0};

internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0, width, 0, height, -0.1f, 100.f);
    set_uniform_mat4x4f(loc_proj_mat, &main_cam.proj_matrix.m11);
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
        set_uniform_mat4x4f(loc_view_mat, &main_cam.view_matrix.m11);
    }
}

void app_specific_init(void)
{
    sp = create_shader_program(batch_vert_shader_code, sprite_frag_shader_code);
    use_shader_program(sp);
    loc_view_mat = get_uniform_loc(sp, "uViewMat");
    loc_proj_mat = get_uniform_loc(sp, "uProjMat");
    
    pfn_window_size_callback = &winsizecbk;
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);

    create_srt_matrix(&main_cam.view_matrix, (v3f){1.0f,1.0f,0.0f}, (v3f){0.0f,0.0f,0.0f}, (v3f){0.0f,0.0f,0.0f});
    set_uniform_mat4x4f(loc_view_mat, &main_cam.view_matrix.m11);

    init_batch(&batch, 3);
    init_grid(&grid_, 10, 10);
    grid_.cell_size = 50;

    for (int i = 0; i < grid_.h * grid_.w; ++i)
    {
        grid_.data[i] = (i%grid_.h)%4;
    }
}

void app_specific_update(double dt)
{
    camera_controls(dt);

    const v2i mouse_posi = get_mouse_position_from_system();
    mouse_pos = (v2f){(float)mouse_posi.x, (float)mouse_posi.y};
    project_mouse_to_camera(&main_cam, &mouse_pos);

    grid_coords = world_to_grid_coords(&grid_, mouse_pos);

    if (mouse_button_was_pressed(NL_MOUSE_BUTTON_LEFT))
    {
        GRID_DATA_TYPE value = get_value_at_coords(&grid_, grid_coords.x, grid_coords.y);
        value = ++value%4;
        set_value_at_coord(&grid_, grid_coords.x, grid_coords.y, value);
    }
}

void app_specific_render()
{
    use_shader_program(sp);
    begin_render_batch(&batch);

    const colour COLOURS[] =
    {   
        COLOUR_RED, COLOUR_GREEN, COLOUR_BLUE, COLOUR_WHITE
    };

    for (GRID_DATA_TYPE y = 0; y < grid_.h; ++y)
    {
        for (GRID_DATA_TYPE x = 0; x < grid_.w; ++x)
        {
            float px = (float)(x * grid_.cell_size);
            float py = (float)(y * grid_.cell_size);

            if (grid_coords.x == x && grid_coords.y == y)
            {
                add_to_render_batch(&batch, (v2f){px,py}, (colour){0,0,0,255}, grid_.cell_size);
            }
            else
            {
                add_to_render_batch(&batch, (v2f){px,py}, COLOURS[get_value_at_coords(&grid_, x, y)], grid_.cell_size);
            }
        }
    }

    add_to_render_batch(&batch, mouse_pos, COLOUR_BLUE, 5.0f);

    end_render_batch(&batch);
}

void app_specific_cleanup()
{
    free_grid(&grid_);
    free_batch(&batch);
}

#include "batch2d.c"
#include "grid.c"