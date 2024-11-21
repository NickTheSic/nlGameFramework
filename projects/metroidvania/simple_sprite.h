#ifndef __SIMPLE_SPRITE__
#define __SIMPLE_SPRITE__

#include "private/nl_colour.h"
#include "private/nl_vertex_data.h"

// not batch able?
// creates own VAO, VBO, EBO which could be avoided in some cases
typedef struct simple_sprite simple_sprite;
struct simple_sprite
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    unsigned int indice_count;
    unsigned int vertice_count;

    unsigned int* indices;
    vertex_data* vertices;
};

void generate_simple_sprite_using_vertices_and_indices(simple_sprite* const mesh, const vertex_data* const vertice, int vertice_count, const unsigned int* const indices, unsigned int indice_count);
void render_single_simple_sprite(simple_sprite* const mesh);
void move_simple_sprite(simple_sprite* const mesh, const v2f difference);

void generate_rectangle_simple_sprite(simple_sprite* const mesh, float width, float height, colourf col);
void generate_square_simple_sprite(simple_sprite* const mesh, float width, colourf col);
void generate_circle_simple_sprite(simple_sprite* const mesh, float radius, int segments);

void free_simple_sprite(simple_sprite* const mesh);


#endif//__SIMPLE_SPRITE__