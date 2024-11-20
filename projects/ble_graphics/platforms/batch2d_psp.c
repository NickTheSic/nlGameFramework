#include "../batch2d.h"

typedef struct 
{
    unsigned short u, v;
    float x, y, z;
} Vertex;

struct batch2d
{
    int unused;
};

batch2d* init_batch(unsigned int count)
{
    NL_UNUSED(count);
    return 0;
}

void free_batch(batch2d** batch)
{
    NL_UNUSED(batch);
}

void begin_render_batch(batch2d* const batch)
{
    NL_UNUSED(batch);
    NL_UNIMPLEMENTED_FUNC;
}

void add_to_render_batch(batch2d* const batch, v2f pos, colour col, float size)
{
    NL_UNUSED(batch);NL_UNUSED(col);
    NL_UNIMPLEMENTED_FUNC;

    Vertex* vertices = (Vertex*)sceGuGetMemory(2 * sizeof(Vertex));

    vertices[0].x = pos.x;
    vertices[0].y = pos.y;

    vertices[1].x = pos.x + size.x;
    vertices[1].y = pos.y + size.y;

    sceGuColor(0xFF0000FF); // Red, colors are ABGR
    sceGuDrawArray(GU_SPRITES, GU_TEXTURE_16BIT | GU_VERTEX_16BIT | GU_TRANSFORM_2D, 2, 0, vertices);

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

