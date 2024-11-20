#include "../nl_mesh.h"

void generate_mesh_using_vertices_and_indices(mesh* const mesh, const vertex_data* const vertice, int vertice_count, const unsigned int* const indices, unsigned int indice_count)
{
    NL_UNUSED(mesh);NL_UNUSED(vertice);NL_UNUSED(vertice_count);NL_UNUSED(indices);NL_UNUSED(indice_count);
}

void render_single_mesh(mesh* const mesh)
{
    NL_UNUSED(mesh);
}

void move_mesh(mesh* const mesh, const v2f difference)
{
    NL_UNUSED(mesh);NL_UNUSED(difference);
}

void generate_rectangle_mesh(mesh* const mesh, float width, float height, colourf col)
{
    NL_UNUSED(mesh);NL_UNUSED(width);NL_UNUSED(height);NL_UNUSED(col);
}

void generate_square_mesh(mesh* const mesh, float width, colourf col)
{
    generate_rectangle_mesh(mesh, width, width, col);
}

void generate_circle_mesh(mesh* const mesh, float radius, int segments)
{
    NL_UNUSED(mesh);NL_UNUSED(radius);NL_UNUSED(segments);
}

void free_mesh(mesh* const mesh)
{
    NL_UNUSED(mesh);
}

