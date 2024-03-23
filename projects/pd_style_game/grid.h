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
    Block_Wall = 0,

    Block_Floor,

    Block_Stairs,

    BLOCK_COUNT
};

void init_grid(Grid* const grid, int width, int height, int* data);
void free_grid(Grid* const grid);
int get_value_at_coords(const Grid* const grid, int x, int y);
int get_value_at_index(const Grid* const grid, int idx);

v2f grid_to_world_position(const Grid* const grid, int cel_idx);
v2i world_to_grid_coords(const Grid* const grid, v2f world_pos);

#endif//__GRID_H__