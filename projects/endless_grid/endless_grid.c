#include "nl_lib.h"

#include "private/gl/nl_gl.h"

//https://www.youtube.com/watch?v=RqrkVmj-ntM

unsigned int endless_grid_shader_program;
unsigned int endless_grid_vao;

void app_specific_init(void)
{
    endless_grid_shader_program = load_shader_from_files("endless_grid_2d.vs", "endless_grid_2d.fs");
    use_shader_program(endless_grid_shader_program);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{
    use_shader_program(endless_grid_shader_program);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void app_specific_cleanup(void)
{
    glDeleteVertexArrays(1, &endless_grid_vao);
}