#include "../batch2d.h"

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
}

void add_to_render_batch(batch2d* const batch, v2f pos, colour col, float size)
{
    NL_UNUSED(batch);NL_UNUSED(pos);NL_UNUSED(col);NL_UNUSED(size);
}

void end_render_batch(batch2d* const batch)
{
    NL_UNUSED(batch);
}

void set_batch_view_matrix(float* m11)
{
    NL_UNIMPLEMENTED_FUNC;
}

void set_batch_proj_matrix(float* m11)
{
    NL_UNIMPLEMENTED_FUNC;
}

