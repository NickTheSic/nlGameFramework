#ifndef __SPRITE_RENDERER_H__
#define __SPRITE_RENDERER_H__

typedef struct sprite_vertex_data sprite_vertex_data;
struct sprite_vertex_data
{
    v2f pos;
    v2f uv;
};

typedef struct sprite_renderer sprite_renderer;
struct sprite_renderer
{
    // NOTE: No indices as all sprites are square, 0,1,3, 1,2,3
    //       Maybe I could use indices for polygonal sprites
    //       But that can be a future thing

    sprite_vertex_data *vertices;
    unsigned int max_vertices;
    unsigned int num_vertices;

    unsigned int vao, vbo, ebo;
    unsigned int shader;
    unsigned int texture_id;
};

typedef struct sprite_data sprite_data;
struct sprite_data
{  
    v2f texutre_uv_bl;
    v2f texture_uv_tr;

    v2f size;
    v2f position;
};

void init_sprite_renderer(sprite_renderer *const renderer);
void free_sprite_renderer(sprite_renderer *const renderer);

void begin_sprite_batch(sprite_renderer *const renderer);
void end_sprite_batch(sprite_renderer *const renderer);

void add_sprite_to_batch(sprite_renderer *const renderer, sprite_data* const sprite);
void load_sprite_image(const char* name);

#endif//__SPRITE_RENDERER_H__