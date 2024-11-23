#ifndef __NL_SPRITE_RENDERER_H__
#define __NL_SPRITE_RENDERER_H__

typedef struct sprite_vertex_data sprite_vertex_data;
typedef struct nl_sprite nl_sprite;
struct nl_sprite
{
    unsigned int texture_id;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    unsigned int indice_count;
    unsigned int vertice_count;

    unsigned int* indices;
    sprite_vertex_data* vertices;
};

void init_sprite_renderer(void);

void render_single_simple_sprite(nl_sprite* const sprite);
void render_single_sprite_colour(nl_sprite* const sprite, colour col);

void generate_rectangle_simple_sprite(nl_sprite *const sprite, float width, float height);
void generate_square_simple_sprite(nl_sprite *const sprite, float width);

void load_texture_for_sprite(nl_sprite* const sprite, const char* filename);

void free_simple_sprite(nl_sprite *const sprite);


void set_model_matrix(float* m11);
void set_view_matrix(float* m11);
void set_projection_matrix(float* m11);


#endif//__NL_SPRITE_H__