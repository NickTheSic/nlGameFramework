#include "nl_lib.h"
#include "private/nl_gl.h"

mesh player = {0};
unsigned int shader_program = 0;
camera main_cam = {0};

void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.view_matrix, 0, width, 0, height, -0.1f, 100.f);
    unsigned int viewMat = glGetUniformLocation(shader_program, "uViewMat");
    glUniformMatrix4fv(viewMat, 1, GL_FALSE, &main_cam.view_matrix.m11);
}

void app_specific_init(void)
{
    generate_square_mesh(&player, 100, (colourf){1.0f,0.5f,0.2f,1.0f});

    shader_program = create_common_shader_program();
    use_shader_program(shader_program);

    pfn_window_size_callback = &winsizecbk;
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);
}

void app_specific_update(double dt)
{
    (void)dt;
}

void app_specific_render(void)
{
    render_single_mesh(&player);
}

void app_specific_cleanup(void)
{
    free_mesh(&player);
}