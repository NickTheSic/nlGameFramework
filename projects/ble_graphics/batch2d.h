#ifndef __NL_BATCH2D_H__
#define __NL_BATCH2D_H__

#include <private/nl_colour.h>

typedef struct batch2d batch2d;

batch2d* init_batch(unsigned int count);
void free_batch(batch2d** batch);

void begin_render_batch(batch2d* const batch);
void add_to_render_batch(batch2d* const batch, v2f pos, colour col, float size);
void end_render_batch(batch2d* const batch);

void set_batch_view_matrix(float* m11);
void set_batch_proj_matrix(float* m11);

#endif//__NL_BATCH2D_H__