#ifndef __ENDLESS_GRID_H__
#define __ENDLESS_GRID_H__

#ifdef __cplusplus
extern "C" {
#endif


typedef struct endless_grid_2d endless_grid_2d;
struct endless_grid_2d
{
    unsigned int shader_program;
    unsigned int view_mat_loc;
    unsigned int camera_pos_loc;
    unsigned int screen_size_loc;

    /* 
    Possible Members
    bTransformDirty
    Size, Position, Ortho?
    Be able to compare the size position and projection before setting?
    */
};

void init_endless_grid(endless_grid_2d *endless_grid);
void render_endless_grid(endless_grid_2d *endless_grid);
void render_endless_grid_as(endless_grid_2d *endless_grid, v2f size, v3f pos, const mat4x4f* const mat);

// Utility for setting the screen size, can decide later which one I want to use
void set_endless_grid_screen_sizei(endless_grid_2d *endless_grid, int width, int height);
void set_endless_grid_screen_sizef(endless_grid_2d *endless_grid, float width, float height);
void set_endless_grid_screen_size_v2f(endless_grid_2d *endless_grid, v2f size);

void set_endless_grid_camera_position(endless_grid_2d *endless_grid, v3f pos);
void set_endless_grid_view_matrix(endless_grid_2d *endless_grid, const mat4x4f* const mat);

#ifdef __cplusplus
}
#endif

#endif//__ENDLESS_GRID_H__