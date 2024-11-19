#ifndef __NL_SPRITE_BATCH_H__
#define __NL_SPRITE_BATCH_H__

typedef int sprite_handle;

typedef struct sprite_vertex_data sprite_vertex_data;
struct sprite_vertex_data
{
    v3f game_pos;
    v2f uv_coords;
    colourf colour;
};

typedef struct sprite sprite;
struct sprite
{
    v2f loaded_size;
    v2f uv_coords;
};

/* The texture data on the GPU - Separate from the Batch Renderer */
typedef struct sprite_sheet sprite_sheet;
struct sprite_sheet
{
    v2i atlas_size;
    v2i atlas_used;
    int atlas_height_loc;

    unsigned int sprite_count;

    sprite* sprites;
};

typedef struct render_batch_2d render_batch_2d;
struct render_batch_2d
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    unsigned int max_count;
    unsigned int draw_count;

    sprite_vertex_data* sprite_data; // render_data? Alternate name.  Names not important.  Not sure how to keep generic
};

void init_render_batch_2d(render_batch_2d* const batch, const unsigned int batch_count);
void start_render_batch(render_batch_2d* const batch);
void end_render_batch(render_batch_2d* const batch);

#endif//__NL_SPRITE_BATCH_H__