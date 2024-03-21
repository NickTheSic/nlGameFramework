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

    unsigned int Data[GRID_MAX_WIDTH*GRID_MAX_HEIGHT];
};

enum GridBlockTypes
{
    Block_Empty = 0,
    Block_Wall = 1,
    Block_Stairs = 2
};

void init_grid(Grid* const grid);
void free_grid(Grid* const grid);
int get_value_at_coords(const Grid* const grid, int x, int y);
void render_grid(const Grid* const grid);

#endif//__GRID_H__