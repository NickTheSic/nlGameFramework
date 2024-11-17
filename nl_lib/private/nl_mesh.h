#ifndef __NL_MESH_H__
#define __NL_MESH_H__

#include "nl_colour.h"
#include "nl_vertex_data.h"

// not batch able?
// creates own VAO, VBO, EBO which could be avoided in some cases
typedef struct mesh mesh;
struct mesh
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    unsigned int indice_count;
    unsigned int vertice_count;

    unsigned int* indices;
    vertex_data* vertices;
};

/////////////////////////////////////////////////////////////////
//                        Mesh Functions                       //
/////////////////////////////////////////////////////////////////
// Does not yet take into account batching
void generate_mesh_using_vertices_and_indices(mesh* const mesh, const vertex_data* const vertice, int vertice_count, const unsigned int* const indices, unsigned int indice_count);
void render_single_mesh(mesh* const mesh);
void move_mesh(mesh* const mesh, const v2f difference);

void generate_rectangle_mesh(mesh* const mesh, float width, float height, colourf col);
void generate_square_mesh(mesh* const mesh, float width, colourf col);

void free_mesh(mesh* const mesh);


#endif//__NL_MESH_H__