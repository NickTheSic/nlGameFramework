#include "nl_lib.h"
#include "nl_rr_sprite.h"
#include "nl_rr_camera.h"

nl_rr_sprite SPRITE = {0};
nl_rr_sprite TWO = {0};

nl_rr_camera main_camera = {0};

unsigned int rr_shader_program = 0;

internal_function void winsizecbk(int width, int height)
{
    const float aspect = (float)width / (float)height;
    main_camera.aspect_ratio = aspect;
    main_camera.transform_dirty = 1;
}

void app_specific_init(void)
{
    create_simple_rr_sprite("fish.png", &SPRITE);
    translate_matrix2f(&SPRITE.transform, (v2f){-0.2f,0.3f});
    
    create_simple_rr_sprite("thing.png", &TWO);
    scale_matrix_2f(&TWO.transform, (v2f){0.5f,0.5f});

    rr_shader_program = load_shader_from_files("rr_shader_matrices.vs", "rr_shader.fs");
    use_shader_program(rr_shader_program);

    initialize_rr_camera_to_default(&main_camera);
    main_camera.position.z = 100.f;

    set_window_size_callback(&winsizecbk);
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);

    setup_camera_matrices(&main_camera);
}

void app_specific_update(double dt)
{
    rotate_matrix(&TWO.transform, 75.f * dt, 0.8f, 0.5f, 1.f);

    update_camera(&main_camera, dt);
}

void app_specific_render(void)
{
    use_shader_program(rr_shader_program);
    setup_camera_matrices(&main_camera);
    
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
#include "nl_rr_camera.c"
