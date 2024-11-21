#include "../nl_graphics.h"

#include <pspgu.h>
#include <pspge.h>
#include <pspdisplay.h>

typedef struct 
{
    unsigned short u, v;
    float x, y, z;
} Vertex;

struct batch2d
{
    int primitive_type;
    int batch_count;
    int current_vertices;
    Vertex* vertices;
};

batch2d* init_batch(unsigned int count)
{
    batch2d *batch = memory_allocate(sizeof(batch2d));
    batch->primitive_type = GU_SPRITES;

    // First issue: A sprite needs 2 points per item. a triangle needs 3. 
    // lines need 2, a line strip or triangle strip start normal then only need 1 new one after
    // assumption: these will be sprites so count * 2
    batch->batch_count = count*2; // 2 vertices per sprite

    batch->current_vertices = 0;

    return batch;
}

void free_batch(batch2d** batch)
{
    NL_UNUSED(batch);
}

void begin_render_batch(batch2d* const batch)
{
    batch->vertices = (Vertex*)sceGuGetMemory(sizeof(Vertex) * batch->batch_count);
}

internal_function void render_batch(batch2d* const batch)
{
    
}

void add_rectangle_to_render_batch(batch2d* const batch, v2f pos, colour col, v2f size)
{
    NL_UNUSED(batch);

    vertices[0].x = pos.x;
    vertices[0].y = pos.y;

    vertices[1].x = pos.x + size.x;
    vertices[1].y = pos.y + size.y;

    sceGuColor(col.unsigned_integer);
    //             int prim,   int vtype,            int count, const void* indices, const void* vertices
    sceGuDrawArray(batch->primitive_type, GU_TEXTURE_16BIT | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, vertices);
}

void add_square_to_render_batch(batch2d* const batch, v2f pos, colour col, float size)
{
    NL_UNUSED(batch);

    Vertex* vertices = (Vertex*)sceGuGetMemory(2 * sizeof(Vertex));

    vertices[0].x = pos.x;
    vertices[0].y = pos.y;

    vertices[1].x = pos.x + size;
    vertices[1].y = pos.y + size;

    sceGuColor(col.unsigned_integer);
    //             int prim,   int vtype,            int count, const void* indices, const void* vertices
    sceGuDrawArray(GU_SPRITES, GU_TEXTURE_16BIT | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, vertices);
}

void add_sprite_to_render_batch(batch2d* const batch, v2f pos, colour col, v2f size, unsigned int texture_id)
{
    NL_UNUSED(batch);
    NL_UNIMPLEMENTED_FUNC;

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

void end_render_batch(batch2d* const batch)
{
    NL_UNUSED(batch);
    NL_UNIMPLEMENTED_FUNC;
}

void set_batch_view_matrix(float* m11)
{
    NL_UNUSED(m11);
    NL_UNIMPLEMENTED_FUNC;
}

void set_batch_proj_matrix(float* m11)
{
    NL_UNUSED(m11);
    NL_UNIMPLEMENTED_FUNC;
}

