#include "endless_grid_2d.h"
#include "private/gl/nl_gl.h"

void init_endless_grid(endless_grid_data* endless_grid)
{
    endless_grid->shader_program  = load_shader_from_files("endless_grid_2d.vs", "endless_grid_2d.fs");

    endless_grid->view_mat_loc    = get_uniform_loc(endless_grid->shader_program, "uViewMat");
    endless_grid->screen_size_loc = get_uniform_loc(endless_grid->shader_program, "uScreenSize");
    endless_grid->camera_pos_loc  = get_uniform_loc(endless_grid->shader_program, "uCameraPosition");
}

void render_endless_grid(endless_grid_data *endless_grid)
{
    use_shader_program(endless_grid->shader_program);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}


void set_endless_grid_screen_sizei(endless_grid_data *endless_grid, int width, int height)
{
    set_uniform_2f(endless_grid->shader_program, endless_grid->screen_size_loc, (float)width, (float)height);
}

void set_endless_grid_screen_sizef(endless_grid_data *endless_grid, float width, float height)
{
    set_uniform_2f(endless_grid->shader_program, endless_grid->screen_size_loc, width, height);
}

void set_endless_grid_screen_size_v2f(endless_grid_data *endless_grid, v2f size)
{
    set_uniform_2f(endless_grid->shader_program, endless_grid->screen_size_loc, size.x, size.y);
}

void set_endless_grid_camera_position(endless_grid_data *endless_grid, v3f pos)
{
    set_uniform_v3f(endless_grid->shader_program, endless_grid->camera_pos_loc, &pos.x);
}

void set_endless_grid_view_matrix(endless_grid_data *endless_grid, const mat4x4f* const mat)
{
    set_uniform_mat4x4f(endless_grid->shader_program, endless_grid->view_mat_loc, &mat->m11);
}
