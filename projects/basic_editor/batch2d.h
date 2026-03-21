#ifndef __NL_BATCH2D_H__
#define __NL_BATCH2D_H__

#include <private/nl_colour.h>

typedef struct batch_vertex_data batch_vertex_data;
struct batch_vertex_data
{
    v3f pos;
    colour col;
};

typedef struct batch2d batch2d;
struct batch2d
{
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    unsigned int max_count;
    unsigned int current_count;

    batch_vertex_data*  vertices;
};

void init_batch(batch2d* const batch, unsigned int count);
void free_batch(batch2d* const batch);

void begin_render_batch(batch2d* const batch);
void add_to_render_batch(batch2d* const batch, v2f pos, colour col, float size);
void end_render_batch(batch2d* const batch);

#endif//__NL_BATCH2D_H__