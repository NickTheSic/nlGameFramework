#include "../nl_graphics.h"

#include <pspgu.h>
#include <pspge.h>
#include <pspdisplay.h>

typedef struct 
{
    unsigned short u, v;
    float x, y, z;
} Vertex;

void game_init_graphics(void);
void game_begin_render(void);
void game_end_render(void);

void game_init_graphics(void){}
void game_free_graphics(void){}
void game_begin_render(void){}

void add_rectangle_to_render_batch(v2f pos, colour col, v2f size)
{
    Vertex* vertices = (Vertex*)sceGuGetMemory(2 * sizeof(Vertex));

    vertices[0].x = pos.x;
    vertices[0].y = pos.y;

    vertices[1].x = pos.x + size.x;
    vertices[1].y = pos.y + size.y;

    sceGuColor(col.unsigned_integer);
    //             int prim,   int vtype,            int count, const void* indices, const void* vertices
    sceGuDrawArray(GU_SPRITES, GU_TEXTURE_16BIT | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, vertices);
}

void add_square_to_render_batch(v2f pos, colour col, float size)
{
    Vertex* vertices = (Vertex*)sceGuGetMemory(2 * sizeof(Vertex));

    vertices[0].x = pos.x;
    vertices[0].y = pos.y;

    vertices[1].x = pos.x + size;
    vertices[1].y = pos.y + size;

    sceGuColor(col.unsigned_integer);
    //             int prim,   int vtype,            int count, const void* indices, const void* vertices
    sceGuDrawArray(GU_SPRITES, GU_TEXTURE_16BIT | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, vertices);
}

void add_sprite_to_render_batch(v2f pos, colour col, v2f size, unsigned int texture_id)
{
    // incomplete as I don't have a texture ID
    Vertex* vertices = (Vertex*)sceGuGetMemory(2 * sizeof(Vertex));

    vertices[0].x = pos.x;
    vertices[0].y = pos.y;

    vertices[1].x = pos.x + size.x;
    vertices[1].y = pos.y + size.y;

    sceGuColor(col.unsigned_integer);
    //             int prim,   int vtype,            int count, const void* indices, const void* vertices
    sceGuDrawArray(GU_SPRITES, GU_TEXTURE_16BIT | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, vertices);
}

void game_end_render(void){}
void set_batch_view_matrix(float* m11){NL_UNUSED(m11);}
void set_batch_proj_matrix(float* m11){NL_UNUSED(m11);}

