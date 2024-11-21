#ifndef __SIMPLE_SPRITE_H__
#define __SIMPLE_SPRITE_H__

typedef struct sprite_vertices sprite_vertices;
struct sprite_vertices
{
    v3f pos;
    v2f uv;
};

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
    sprite_vertices* vertices;
};

void render_single_simple_sprite(simple_sprite* const sprite);

void generate_rectangle_simple_sprite(simple_sprite *const sprite, float width, float height);
void generate_square_simple_sprite(simple_sprite *const sprite, float width);

void load_texture_for_sprite(simple_sprite* const sprite, const char* filename);

void free_simple_sprite(simple_sprite *const sprite);


#endif//__SIMPLE_SPRITE_H__