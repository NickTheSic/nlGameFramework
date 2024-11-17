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

v2i world_to_grid_coords(const grid* const grid, v2f world_pos)
{
    v2i result = {0};
    result.x = (world_pos.x) / grid->cell_size;
    result.y = (world_pos.y) / grid->cell_size;
    return (result);
}
