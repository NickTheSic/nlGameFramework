#ifndef __NL_GRID_H__
#define __NL_GRID_H__

typedef struct world_grid world_grid;
struct  world_grid
{
    unsigned int width, height;

    unsigned int tile_size;

    unsigned int *tiles;
};

v2i convert_index_to_grid_coords(world_grid *const grid, unsigned int index);
int get_value_at_coords(world_grid* grid, unsigned int x, unsigned int y);
void init_world_grid(world_grid* grid, int width, int height, int tile_size);
void free_world_grid(world_grid* const grid);

#endif//__NL_GRID_H__