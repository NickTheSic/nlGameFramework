#include "nl_lib.h"

#include "batch2d.h"

global_variable unsigned int sp    = {0};
global_variable batch2d batch = {0};

global_variable unsigned int loc_view_mat = {0};
global_variable unsigned int loc_proj_mat = {0};

global_variable camera main_cam = {0};
global_variable float camera_pos_x = 0.f;
global_variable float camera_pos_y = 0.f;

global_variable v2f mouse_pos = {0};
global_variable v2i grid_coords = {0};

typedef struct basic_square basic_square;
struct basic_square
{
    v2f pos;
    float size;
};

global_variable float square_size = 50.0f;
#define square_grid_length 5
#define grid_size square_grid_length*square_grid_length
basic_square squares[grid_size] = {0};
basic_square *selected_square = 0;

void init_square_grid(void)
{
    for (int y = 0; y < square_grid_length; ++y)
    {
        for (int x = 0; x < square_grid_length; ++x)
        {
            const int idx = y * square_grid_length + x;
            basic_square* const local_square = &squares[idx];
            local_square->pos.x = (float)(x * square_size);
            local_square->pos.y = (float)(y * square_size);
            local_square->size = square_size;
        }
    }
}

internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0.f, (float)width, 0.f, (float)height, -0.1f, 100.f);
    set_uniform_mat4x4f(loc_proj_mat, &main_cam.proj_matrix.m11);
}

void camera_controls(float dt)
{
    unsigned char bIsDirty = 0;

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

    if (mouse_button_is_held(NL_MOUSE_BUTTON_RIGHT))
    {
        v2i movement = get_mouse_movement_this_frame();
        camera_pos_x += movement.x;
        camera_pos_y += movement.y;

        bIsDirty = 1;
    }

    if (0 < bIsDirty)
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
    
    set_window_size_callback(&winsizecbk);
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);

    create_srt_matrix(&main_cam.view_matrix, (v3f){1.0f,1.0f,0.0f}, (v3f){0.0f,0.0f,0.0f}, (v3f){0.0f,0.0f,0.0f});
    set_uniform_mat4x4f(loc_view_mat, &main_cam.view_matrix.m11);

    init_square_grid();
    init_batch(&batch, 3);
}

static inline int is_mouse_in_square_bounds(v2f point, v2f pos, float sz)
{
    if (point.x < pos.x || point.x > pos.x+sz) return 0;
    if (point.y < pos.y || point.y > pos.y+sz) return 0;

    return 1;
}

void app_specific_update(double dt)
{
    camera_controls((float)(dt));

    const v2i mouse_posi = get_mouse_position_from_system();
    mouse_pos = (v2f){(float)mouse_posi.x, (float)mouse_posi.y};
    project_mouse_to_camera(&main_cam, &mouse_pos);

    if (mouse_button_was_pressed(NL_MOUSE_BUTTON_LEFT))
    {
        for (int i = 0; i < grid_size; ++i)
        {
            if (is_mouse_in_square_bounds(mouse_pos, squares[i].pos, square_size))
            {
                selected_square = &squares[i];
                break;
            }
        }
    }

    if (mouse_button_was_released(NL_MOUSE_BUTTON_LEFT))
    {
        selected_square = 0;
    }

    if (0 != selected_square)
    {
        v2i movement = get_mouse_movement_this_frame();
        selected_square->pos.x += (float)movement.x;
        selected_square->pos.y += (float)movement.y;
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

    for (int i = 0; i < grid_size; ++i)
    {
        add_to_render_batch(&batch, squares[i].pos, COLOURS[i%4], squares[i].size);
    }

    add_to_render_batch(&batch, mouse_pos, COLOUR_BLUE, 5.0f);

    end_render_batch(&batch);
}

void app_specific_cleanup()
{
    free_batch(&batch);
}

#include "batch2d.c"
