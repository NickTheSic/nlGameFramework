#include "nl_lib.h"
#include "nl_rr_sprite.h"

nl_rr_sprite SPRITE = {0};
nl_rr_sprite TWO = {0};

camera main_camera = {0};

unsigned int rr_shader_program = 0;

char bCameraUse = 0;

internal_function void winsizecbk(int width, int height)
{
    float aspect = (float)width / (float)height;

    unsigned int projection_loc = get_uniform_loc(rr_shader_program, "uProjection");

    if (bCameraUse)
    {
        NL_LOG("Orthographic projection");
        create_orthographic_projection(&main_camera.proj_matrix, -aspect, aspect, -1, 1, 0.f, 10.f);
    } else {
        NL_LOG("PerspectiveProjection");
        create_perspective_projection(&main_camera.proj_matrix, 90.f, (float)width / (float)height, -1.f, 100.f);
    }

    set_uniform_mat4x4f(projection_loc, &main_camera.proj_matrix.m11);
}

void app_specific_init(void)
{
    create_simple_rr_sprite("fish.png", &SPRITE);
    translate_matrix2f(&SPRITE.transform, (v2f){-0.2f,0.3f});
    
    create_simple_rr_sprite("thing.png", &TWO);
    scale_matrix_2f(&TWO.transform, (v2f){0.5f,0.5f});

    //translate_matrix2f(&TWO.transform, (v2f){230.0f,600.0f});

    rr_shader_program = load_shader_from_files("rr_shader_matrices.vs", "rr_shader.fs");
    use_shader_program(rr_shader_program);

    initialize_camera_to_identity(&main_camera);

    set_window_size_callback(&winsizecbk);

    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);
}

void app_specific_update(double dt)
{
    rotate_matrix(&TWO.transform, 75.f * dt, 0.8f, 0.5f, 1.f);

    if (mouse_button_was_pressed(NL_MOUSE_BUTTON_LEFT))
    {
        bCameraUse = !bCameraUse;
        v2i screen_size = get_screen_size();
        winsizecbk(screen_size.x, screen_size.y);
    }
}

void app_specific_render(void)
{
    use_shader_program(rr_shader_program);
    
    render_simple_rr_sprite(&SPRITE);
    render_simple_rr_sprite(&TWO);
}

void app_specific_cleanup(void)
{
    free_simple_rr_sprite(&SPRITE);
    free_simple_rr_sprite(&TWO);

    free_shader_program(rr_shader_program);
}


#include "nl_rr_sprite.c"
