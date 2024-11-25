#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <pspgu.h>

#define STBI_ONLY_PNG
#include <stb_image.h>

struct sprite_vertex_data
{    
    float u, v;
    uint32_t colour;
    float x, y, z;
};

typedef struct
{
    int width, height;
    uint32_t * data;
} Texture;

Texture textures[5] = {0};
unsigned int next_texture = {0};

v2f _MODEL_POS = {0};

void init_sprite_renderer(void)
{
    NL_UNIMPLEMENTED_FUNC
}

void render_single_simple_sprite(nl_sprite* const sprite)
{
    render_single_sprite_colour(sprite, COLOUR_WHITE);
}

void render_single_sprite_colour(nl_sprite* const sprite, colour col)
{
    Texture* texture = &textures[sprite->texture_id];
    static sprite_vertex_data vertices[2];

    vertices[0].u = 0.0f;
    vertices[0].v = 0.0f;
    vertices[0].colour = col.unsigned_integer;
    vertices[0].x = _MODEL_POS.x;
    vertices[0].y = get_screen_size().y - _MODEL_POS.y;
    vertices[0].z = 0.0f;

    vertices[1].u = texture->width;
    vertices[1].v = texture->height;
    vertices[1].colour = col.unsigned_integer;
    vertices[1].x = _MODEL_POS.x + 32.f;
    vertices[1].y = get_screen_size().y - _MODEL_POS.y + 32.f;
    vertices[1].z = 0.0f;

    sceGuTexMode(GU_PSM_8888, 0, 0, GU_FALSE);
    sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);
    sceGuTexImage(0, texture->width, texture->height, texture->width, texture->data);

    sceGuEnable(GU_TEXTURE_2D); 
    sceGuDrawArray(GU_SPRITES, GU_COLOR_8888 | GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, vertices);
    sceGuDisable(GU_TEXTURE_2D);
}

void generate_rectangle_simple_sprite(nl_sprite *const sprite, float width, float height)
{
    textures[sprite->texture_id].width = width;
    textures[sprite->texture_id].height = height;
}

void generate_square_simple_sprite(nl_sprite *const sprite, float width)
{
    generate_rectangle_simple_sprite(sprite, width, width);
}

void load_texture_for_sprite(nl_sprite* const sprite, const char* filename)
{
    textures[next_texture].data = (uint32_t *)stbi_load(filename, 
        &(textures[next_texture].width), &(textures[next_texture].height), NULL, STBI_rgb_alpha);

    // Make sure the texture cache is reloaded
    sceKernelDcacheWritebackInvalidateAll();

    sprite->texture_id = next_texture++;
}

void free_simple_sprite(nl_sprite *const sprite)
{
    NL_UNUSED(sprite);
    NL_UNIMPLEMENTED_FUNC;
}

void set_model_matrix(mat4x4f* mat)
{
    _MODEL_POS.x = mat->m41;
    _MODEL_POS.y = mat->m42;
}

void set_view_matrix(mat4x4f* mat)
{
    NL_UNUSED(mat);
    NL_UNIMPLEMENTED_FUNC;
}

void set_projection_matrix(mat4x4f* mat)
{
    NL_UNUSED(mat);
    NL_UNIMPLEMENTED_FUNC;
}
