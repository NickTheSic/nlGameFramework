#ifndef __GRID_H__
#define __GRID_H__

#include "nl_lib.h" // for colourf

#define GRID_MAX_WIDTH 10
#define GRID_MAX_HEIGHT 10
typedef struct Grid Grid;
struct Grid
{
    unsigned int Width;
    unsigned int Height;
    float cell_size;
    float cell_half_size;

    unsigned int Data[GRID_MAX_WIDTH*GRID_MAX_HEIGHT];
};

enum GridBlockTypes
{
    Block_Empty = 0,
    Block_Wall = 1,
    Block_Stairs = 2
};

void init_grid(Grid* const grid, int width, int height, int* data);
void free_grid(Grid* const grid);
int get_value_at_coords(const Grid* const grid, int x, int y);
int get_value_at_index(const Grid* const grid, int idx);
void render_grid(const Grid* const grid);
v2f grid_to_world_position(const Grid* const grid, int cel_idx);

#endif//__GRID_H__