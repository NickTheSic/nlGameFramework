#ifndef __NL_SPRITE_SHEET_H__
#define __NL_SPRITE_SHEET_H__

#include "private/nl_math.h"

typedef struct sprite sprite;
struct sprite
{
    v2f bl_coord;
    v2f tr_coord;
};

typedef struct sprite_vertex_data sprite_vertex_data;
struct sprite_vertex_data
{
    v3f pos;
    colourf colour;
    v2f uv_coord;
};

typedef struct spritesheet spritesheet;
struct spritesheet
{
    v2i atlas_size;

    unsigned int vao, vbo, ibo, shader_program, texture_id;

    unsigned int max_sprites, sprite_count;
    unsigned int max_vertices, vertex_count;
    unsigned int draw_count;

    sprite* sprites;
    sprite_vertex_data* vertices;
};

void init_sprite_sheet(spritesheet* const sheet, unsigned int batch_count, unsigned int sprite_count, v2i atlas_size);
void free_sprite_sheet(spritesheet* sheet);

int load_sprite(const char* const filename);

void begin_sprite_batch(spritesheet* const sheet);
void add_sprite_to_batch(int sprite_idx, v2f pos, colourf colour);
void end_sprite_batch(spritesheet* const sheet);

#endif//__NL_SPRITE_SHEET_H__