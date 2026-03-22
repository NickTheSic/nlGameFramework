#ifndef __ENDLESS_GRID_H__
#define __ENDLESS_GRID_H__

#ifdef __cplusplus
extern "C" {
#endif


typedef struct endless_grid_data endless_grid_data;
struct endless_grid_data
{
    unsigned int shader_program;
    unsigned int view_mat_loc;
    unsigned int camera_pos_loc;
    unsigned int screen_size_loc;

    unsigned char reset_uniforms : 1;
};

void init_endless_grid(endless_grid_data *endless_grid);
void render_endless_grid(endless_grid_data *endless_grid);

// Utility for setting the screen size, can decide later which one I want to use
void set_endless_grid_screen_sizei(endless_grid_data *endless_grid, int width, int height);
void set_endless_grid_screen_sizef(endless_grid_data *endless_grid, float width, float height);
void set_endless_grid_screen_size_v2f(endless_grid_data *endless_grid, v2f size);

void set_endless_grid_camera_position(endless_grid_data *endless_grid, v3f pos);
void set_endless_grid_view_matrix(endless_grid_data *endless_grid, const mat4x4f* const mat);

#ifdef __cplusplus
}
#endif

#endif//__ENDLESS_GRID_H__