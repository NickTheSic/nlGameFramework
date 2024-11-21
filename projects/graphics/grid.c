#include "grid.h"

void init_grid(grid* grid, GRID_DATA_TYPE w, GRID_DATA_TYPE h)
{
    grid->w = w;
    grid->h = h;

    grid->data = (GRID_DATA_TYPE*)memory_allocate(sizeof(GRID_DATA_TYPE)*w*h);
    if (grid->data == 0)
    {
        NL_LOG("Error allocating space for grid data");
    }
}

void free_grid(grid* grid)
{
    memory_free(grid->data);
}

GRID_DATA_TYPE get_value_at_coords(const grid* const grid, int x, int y)
{
    if (x < 0 || y < 0 || x > grid->w || y>grid->h)
    {
        NL_LOG("Invalid values were passed into %s", __FUNCTION__);
        return 0;
    }

    return grid->data[y*grid->w+x];
}

void set_value_at_coord(const grid* const grid, int x, int y, GRID_DATA_TYPE val)
{
    if (x < 0 || y < 0 || x >= grid->w || y >= grid->h)
    {
        NL_LOG("Invalid coords were passed into %s. Cannot set value", __FUNCTION__);
        return;
    }

    grid->data[y*grid->w+x] = val;
}

v2i world_to_grid_coords(const grid* const grid, v2f world_pos)
{
    // Issue - a negative world pos still starts at 0 but does not take into a account that the mouse is in -1 
    // A negative world pos around the origin after division results in a 0,0 coord when we should be in negative
    v2i result = {0};
    result.x = (world_pos.x) / (float)grid->cell_size;
    result.y = (world_pos.y) / (float)grid->cell_size;
    return (result);
}

unsigned char are_valid_grid_coords(const grid* const grid, int x, int y)
{
    return (x>=0 && y>=0 && x<grid->w && y<grid->h);
}
