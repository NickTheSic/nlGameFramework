#ifndef __ENDLESS_GRID_H__
#define __ENDLESS_GRID_H__

typedef struct endless_grid_data endless_grid_data;
struct endless_grid_data
{
    unsigned int shader_program;
    unsigned int view_mat_loc;
    unsigned int camera_pos_loc;
    unsigned int screen_size_loc;
};

void render_endless_grid(endless_grid_data *endless_grid);


// source file impl
//include this
#include "private/gl/nl_gl.h"

void render_endless_grid(endless_grid_data *endless_grid)
{
    use_shader_program(endless_grid->shader_program);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

#endif//__ENDLESS_GRID_H__