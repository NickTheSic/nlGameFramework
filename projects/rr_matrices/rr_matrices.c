#include "nl_lib.h"
#include "nl_rr_sprite.h"

nl_rr_sprite SPRITE = {0};
nl_rr_sprite TWO = {0};

camera main_camera = {0};

unsigned int rr_shader_program = 0;

void app_specific_init(void)
{
    create_simple_rr_sprite("fish.png", &SPRITE);
    create_simple_rr_sprite("thing.png", &TWO);

    //translate_matrix2f(&SPRITE.transform, (v2f){430.0f,100.0f});
    //translate_matrix2f(&TWO.transform, (v2f){230.0f,600.0f});

    rr_shader_program = load_shader_from_files("rr_shader_matrices.vs", "rr_shader.fs");
    use_shader_program(rr_shader_program);

    initialize_camera_to_identity(&main_camera);

    v2i screen_size = get_screen_size();
    unsigned int projection_loc = get_uniform_loc(rr_shader_program, "uProjection");
    //create_orthographic_projection(&main_camera.proj_matrix, 0.f, (float)screen_size.x, 0.f, (float)screen_size.y, -1.1f, 10.f);
    create_perspective_projection(&main_camera.proj_matrix, 45.f, (float)screen_size.x / (float)screen_size.y, -1.f, 100.f);
    set_uniform_mat4x4f(projection_loc, &main_camera.proj_matrix.m11);
}

void app_specific_update(double dt)
{
    rotate_matrix(&TWO.transform, 75.f * dt, 0.8f, 0.5f, 1.f);
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
