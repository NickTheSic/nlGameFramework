#ifndef __NL_GRAPHICS_H__
#define __NL_GRAPHICS_H__

#include <private/nl_colour.h>

typedef struct batch2d batch2d;

batch2d* init_batch(unsigned int count);
void free_batch(batch2d** batch);

void begin_render_batch(batch2d* const batch);

void add_rectangle_to_render_batch(batch2d* const batch, v2f pos, colour col, v2f size);
void add_square_to_render_batch(batch2d* const batch, v2f pos, colour col, float size);
void add_sprite_to_render_batch(batch2d* const batch, v2f pos, colour col, v2f size, unsigned int texture_id);

void end_render_batch(batch2d* const batch);

void set_batch_view_matrix(float* m11);
void set_batch_proj_matrix(float* m11);

#endif//__NL_GRAPHICS_H__