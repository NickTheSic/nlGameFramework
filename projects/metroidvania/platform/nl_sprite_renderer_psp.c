#include "../nl_sprite_renderer.h"

struct sprite_vertex_data
{
    unsigned unused;
};

void init_sprite_renderer(void)
{

}

void render_single_simple_sprite(nl_sprite* const sprite)
{
    NL_UNUSED(sprite);
}

void generate_rectangle_simple_sprite(nl_sprite *const sprite, float width, float height)
{
    NL_UNUSED(sprite);NL_UNUSED(width);NL_UNUSED(height);
}

void generate_square_simple_sprite(nl_sprite *const sprite, float width)
{
    NL_UNUSED(sprite);NL_UNUSED(width);
}

void load_texture_for_sprite(nl_sprite* const sprite, const char* filename)
{
    NL_UNUSED(sprite);NL_UNUSED(filename);
}

void free_simple_sprite(nl_sprite *const sprite)
{
    NL_UNUSED(sprite);
}

void set_model_matrix(float* m11)
{
    NL_UNUSED(m11);
}

void set_view_matrix(float* m11)
{
    NL_UNUSED(m11);
}

void set_projection_matrix(float* m11)
{
    NL_UNUSED(m11);
}
