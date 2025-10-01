#include "nl_lib.h"

#include "nl_mesh.h"
#include "nl_sprite_atlas.h"
#include "nl_ui.h"

#include <private/gl/nl_gl.h>

// Goal of this project is to consolodate the UI projects into 1 project
// The UI should be batched; have its own GL texture sheet for all icons and fonts
// Maybe it has it's own camera too

//This is probably where one of the scenarios becomes the new 4th project instead of consolodating the other 3


global_variable ui_element center_square = {0};
global_variable ui_element square_ur = {0};
global_variable ui_element square_bl = {0};
global_variable ui_element mouse_pointer = {0};

void winsizecbk(int width, int height)
{
    ui_set_window_size(width, height);
}

void app_specific_init(void)
{
    ui_init();

    initialize_object(&square_ur, (v2f){-1.0f,1.0f});
    square_ur.transform.position.x = SQUARE_HALF_SIZE;
    square_ur.transform.position.y = -SQUARE_HALF_SIZE;
    initialize_object(&square_bl, (v2f){1.0f,-1.0f});
    square_bl.transform.position.x = -SQUARE_HALF_SIZE;
    square_bl.transform.position.y = SQUARE_HALF_SIZE;
    initialize_object(&center_square, (v2f){0.0f,0.0f});
    initialize_object(&mouse_pointer, (v2f){0.0f,0.0f});

    set_window_size_callback(&winsizecbk);
    
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}


void ui_anchored_matrix(mat4x4f* const mat, ui_element* const o)
{
    create_identity_matrix(mat);

    v2i screen_size = get_screen_size();
    transform2d trans = o->transform;
    const float half_w = screen_size.x/2.0f;
    const float half_h = screen_size.y/2.0f;
    trans.position.x += (half_w) + (o->anchor.x * half_w);
    trans.position.y += (half_h) + (o->anchor.y * half_h);
    create_srt_matrix_from_transform2d(mat, trans);
}

void matrix_for_ui(ui_element* const o)
{
    mat4x4f mat = {0};
    ui_anchored_matrix(&mat, o);

    ui_set_world_matrix(&mat.m11);

    render_single_mesh(&o->m);
}

void app_specific_render()
{
    ui_render();
    matrix_for_ui(&square_ur);
    matrix_for_ui(&square_bl);
    matrix_for_ui(&center_square);
    
    const v2i cur_mouse_pos = get_mouse_position_from_system();
    const v3f scale = {0.1f,0.1f,0.1f};
    const v3f rot = {0.f, 0.f, 0.f};
    const v3f trans = {(float)cur_mouse_pos.x, (float)cur_mouse_pos.y, 0.f};
    mat4x4f mat = {0};
    create_identity_matrix(&mat);
    create_srt_matrix(&mat, scale, rot, trans);

    ui_set_world_matrix(&mat.m11);

    render_single_mesh(&mouse_pointer.m);
}

void app_specific_cleanup(void)
{
    ui_cleanup();

    free_mesh(&center_square.m);
    free_mesh(&square_ur.m);
    free_mesh(&square_bl.m);
    free_mesh(&mouse_pointer.m);
}

#include "nl_ui.c"
#include "nl_mesh_gl.c"
