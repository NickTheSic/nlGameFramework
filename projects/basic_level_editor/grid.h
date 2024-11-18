#ifndef __GRID_H__
#define __GRID_H__

typedef unsigned char GRID_DATA_TYPE;

typedef struct grid grid;
struct grid
{
    GRID_DATA_TYPE *data;
    GRID_DATA_TYPE w, h;
    GRID_DATA_TYPE cell_size;
};

void init_grid(grid* grid, GRID_DATA_TYPE w, GRID_DATA_TYPE h);
void free_grid(grid* grid);

GRID_DATA_TYPE get_value_at_coords(const grid* const grid, int x, int y);
void set_value_at_coord(const grid* const grid, int x, int y, GRID_DATA_TYPE val);
v2i world_to_grid_coords(const grid* const grid, v2f world_pos);

unsigned char are_valid_grid_coords(const grid* const grid, int x, int y);

#endif//__GRID_H__