#include "endless_grid_2d.h"
#include "private/gl/nl_gl.h"

// NOTE: I could have removed glDrawArrays to hide implementation details
// Otherwise I am inlining the code instead

void init_endless_grid(endless_grid_2d* endless_grid)
{
    endless_grid->shader_program  = load_shader_from_files("endless_grid_2d.vs", "endless_grid_2d.fs");

    endless_grid->view_mat_loc    = get_uniform_loc(endless_grid->shader_program, "uViewMat");
    endless_grid->screen_size_loc = get_uniform_loc(endless_grid->shader_program, "uScreenSize");
    endless_grid->camera_pos_loc  = get_uniform_loc(endless_grid->shader_program, "uCameraPosition");
}

void render_endless_grid(endless_grid_2d *endless_grid)
{
    glUseProgram(endless_grid->shader_program);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void render_endless_grid_as(endless_grid_2d *endless_grid, v2f size, v3f pos, const mat4x4f* const mat)
{
    glUseProgram(endless_grid->shader_program);

    glUniform2fv(endless_grid->screen_size_loc, 1, &size.x);
    glUniform3fv(endless_grid->camera_pos_loc, 1, &pos.x);
    glUniformMatrix4fv(endless_grid->view_mat_loc, 1, GL_FALSE, &mat->m11);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void set_endless_grid_screen_sizei(endless_grid_2d *endless_grid, int width, int height)
{
    glUseProgram(endless_grid->shader_program);
    v2f size = {(float)width, (float)height};
    glUniform2fv(endless_grid->screen_size_loc, 1, &size.x);
}

void set_endless_grid_screen_sizef(endless_grid_2d *endless_grid, float width, float height)
{
    glUseProgram(endless_grid->shader_program);
    v2f size = {width, height};
    glUniform2fv(endless_grid->screen_size_loc, 1, &size.x);
}

void set_endless_grid_screen_size_v2f(endless_grid_2d *endless_grid, v2f size)
{
    glUseProgram(endless_grid->shader_program);
    glUniform2fv(endless_grid->screen_size_loc, 1, &size.x);
}

void set_endless_grid_camera_position(endless_grid_2d *endless_grid, v3f pos)
{
    glUseProgram(endless_grid->shader_program);
    glUniform3fv(endless_grid->camera_pos_loc, 1, &pos.x);
}

void set_endless_grid_view_matrix(endless_grid_2d *endless_grid, const mat4x4f* const mat)
{
    glUseProgram(endless_grid->shader_program);
    glUniformMatrix4fv(endless_grid->view_mat_loc, 1, GL_FALSE, &mat->m11);
}
