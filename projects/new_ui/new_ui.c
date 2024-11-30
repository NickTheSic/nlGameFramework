#include "nl_lib.h"

#include "nl_ui_renderer.h"
#include "nl_sprite_renderer.h"

global_variable camera main_cam = {0};
global_variable nl_sprite man = {0};

internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0, width, 0, height, -0.1f, 100.f);
    set_projection_matrix(&main_cam.proj_matrix);

    set_screen_dimensions(width, height);
}

void app_specific_init(void)
{
    init_ui_renderer();
    init_sprite_renderer();

    load_texture_for_sprite(&man, "data/man.png");
    generate_rectangle_simple_sprite(&man, 32, 64);
    
    set_window_size_callback(&winsizecbk);
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);
    create_srt_matrix(&main_cam.view_matrix, (v3f){1.0f,1.0f,0.0f}, (v3f){0.0f,0.0f,0.0f}, (v3f){0.0f,0.0f,0.0f});
    set_view_matrix(&main_cam.view_matrix);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{
    begin_sprite_render();

    mat4x4f model = {0};
    create_identity_matrix(&model);
    set_model_matrix(&model);
    render_single_simple_sprite(&man);
    //render_single_sprite_colour(&man, COLOUR_GREEN);

    end_sprite_render();


    begin_ui_render();
    ui_element e = {0};
    e.color = COLOURF_RED;
    e.pos = (v2f){100.1f, 100.1f};
    e.size = (v2f){10.1f, 10.1f};
    DEBUG_add_elem(&e);
    end_ui_render();
}

void app_specific_cleanup(void)
{
    free_simple_sprite(&man);
    cleanup_ui_renderer();
}

#include "nl_ui_renderer_gl.c"
#include "nl_sprite_renderer_gl.c"
