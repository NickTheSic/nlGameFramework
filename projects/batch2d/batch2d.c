#include "nl_lib.h"
#include "sprite_batch.h"
#include "sprite_sheet.h"

global_variable unsigned int sp    = {0};
global_variable sprite_batch g_batch = {0};
global_variable unsigned int img   = {0};

global_variable unsigned int loc_view_mat = {0};
global_variable unsigned int loc_proj_mat = {0};

global_variable camera main_cam = {0};

internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0.0f, (float)width, 0.0f, (float)height, -0.1f, 100.f);
    set_uniform_mat4x4f(loc_proj_mat, &main_cam.proj_matrix.m11);
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

    init_batch(&g_batch, 3);
    //init_sprite_sheet();
    //img = load_image("data/test_sprite.png");
}

void app_specific_update(double dt)
{
    (void)dt;
}

void app_specific_render()
{
    use_shader_program(sp);
    begin_render_batch(&g_batch);
    add_to_render_batch(&g_batch, (v2f){200.f, 30.f});
    add_to_render_batch(&g_batch, (v2f){600.f, 120.f});

    const v2i mouse_posi = get_mouse_position_from_system();
    v2f mouse_pos = (v2f){(float)mouse_posi.x, (float)mouse_posi.y};
    project_mouse_to_camera(&main_cam, &mouse_pos);

    add_to_render_batch(&g_batch, mouse_pos);

    end_render_batch(&g_batch);
}

void app_specific_cleanup()
{
    free_batch(&g_batch);
    //free_sprite_sheet();
}

#include "sprite_batch.c"
#include "sprite_sheet.c"