#ifndef __SIMPLE_SPRITE__
#define __SIMPLE_SPRITE__

#include "private/nl_colour.h"

typedef struct simple_sprite simple_sprite;
struct simple_sprite
{
    unsigned int texture_id;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    unsigned int indice_count;
    unsigned int vertice_count;

    unsigned int* indices;
    struct sprite_vertices* vertices;
};

void render_single_simple_sprite(simple_sprite* const sprite);

void generate_rectangle_simple_sprite(simple_sprite *const sprite, float width, float height);
void generate_square_simple_sprite(simple_sprite *const sprite, float width);

void free_simple_sprite(simple_sprite *const sprite);


#endif//__SIMPLE_SPRITE__