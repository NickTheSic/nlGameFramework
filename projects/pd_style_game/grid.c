#include "grid.h"

int get_value_at_coords(const Grid* const grid, int x, int y)
{
    if (x < 0 || y < 0)
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

    const int SQUARE_HALF_SIZE = 30;
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

void init_grid(Grid* const grid)
{
    NL_UNUSED(grid);
    make_grid_meshes(grid);
}

void free_grid(Grid* const grid)
{
    NL_UNUSED(grid);
    free_mesh(&grid_meshes[0]);
    free_mesh(&grid_meshes[1]);
    free_mesh(&grid_meshes[2]);
}

void render_grid(const Grid* const grid)
{
    NL_UNUSED(grid);
    
    mat4x4f mat = {0};
    transform2d transform = {0};
    transform.size = (v2f){1.0f,1.0f};
    transform.position  = (v2f){400.0f,100.0f};
    transform.rotation = 1.f;
    create_identity_matrix(&mat);
    create_srt_matrix_from_transform2d(&mat, transform);
    //glUniformMatrix4fv(worldMat, 1, GL_FALSE, &mat.m11);
    render_single_mesh(&grid_meshes[0]);
}
