#include "grid.h"
#include "string.h" //memcpy

#define GRID_CELL_SIZE 64
#define GRID_CELL_HALF_SIZE GRID_CELL_SIZE/2.0f

int get_value_at_coords(const Grid* const grid, int x, int y)
{
    if (x < 0 || y < 0 || x > grid->Width || y>grid->Height)
    {
        NL_LOG("Invalid values were passed into %s", __FUNCTION__);
        return 0;
    }

    return grid->Data[y*grid->Width+x];
}

mesh grid_meshes[3] = {0};

internal_function void make_grid_meshes(Grid* const grid)
{
    const colourf gcols[] = 
    {
        {0.0f,0.0f,0.0f,0.0f},
        {0.8f,0.8f,0.8f,1.0f},
        {0.2f,0.7f,0.3f,1.0f}
    };

    const int SQUARE_HALF_SIZE = GRID_CELL_HALF_SIZE;
    unsigned int indices[]={0,1,2,2,3,0};
    {
        vertex_data square_verts[] =
        {
            {{-SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, gcols[0]},
            {{ SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, gcols[0]},
            {{ SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, gcols[0]},
            {{-SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, gcols[0]}
        };
        generate_mesh_using_vertices_and_indices(&grid_meshes[0], square_verts, 4, indices,6);
    }
        {
        vertex_data square_verts[] =
        {
            {{-SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, gcols[1]},
            {{ SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, gcols[1]},
            {{ SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, gcols[1]},
            {{-SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, gcols[1]}
        };
        generate_mesh_using_vertices_and_indices(&grid_meshes[1], square_verts, 4, indices,6);
    }
        {
        vertex_data square_verts[] =
        {
            {{-SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, gcols[2]},
            {{ SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, gcols[2]},
            {{ SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, gcols[2]},
            {{-SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, gcols[2]}
        };
        generate_mesh_using_vertices_and_indices(&grid_meshes[2], square_verts, 4, indices,6);
    }
}

v2f grid_to_world_position(const Grid* const grid, int cell_idx)
{
    v2f result = {0};

    result.x = grid->cell_half_size + grid->cell_size*(cell_idx%grid->Width);
    result.y = grid->cell_half_size + grid->cell_size*(cell_idx/grid->Width);

    return (result);
}

v2i world_to_grid_coords(const Grid* const grid, v2f world_pos)
{
    v2i result = {0};
    result.x = (world_pos.x) / grid->cell_size;
    result.y = (world_pos.y) / grid->cell_size;
    return (result);
}

int get_value_at_index(const Grid* const grid, int idx)
{
    return grid->Data[idx];
}

void init_grid(Grid* const grid, int width, int height, int* data)
{
    grid->Width = width;
    grid->Height = height;
    grid->cell_size = GRID_CELL_SIZE;
    grid->cell_half_size = grid->cell_size*0.5f;

    memcpy(grid->Data, data, width*height*sizeof(int));

    make_grid_meshes(grid);
}

void free_grid(Grid* const grid)
{
    free_mesh(&grid_meshes[0]);
    free_mesh(&grid_meshes[1]);
    free_mesh(&grid_meshes[2]);
}

void render_grid(const Grid* const grid)
{
    NL_UNUSED(grid);
}
