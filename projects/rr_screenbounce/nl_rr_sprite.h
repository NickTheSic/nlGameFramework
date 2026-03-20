#ifndef __NL_RR_SPRITE_H__
#define __NL_RR_SPRITE_H__

typedef struct nl_rr_vertex_data nl_rr_vertex_data;
struct nl_rr_vertex_data
{
    v3f position;
    v3f colour;
    v2f uv;
};

typedef struct nl_rr_sprite nl_rr_sprite;
struct nl_rr_sprite
{
    mat4x4f transform;

    v3f position;
    v3f scale;
    v3f rotation;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int TextureID;

    unsigned char transform_dirty : 1;
};

void create_simple_rr_sprite(const char* filename, nl_rr_sprite* const sprite);
void render_simple_rr_sprite(nl_rr_sprite* const spr);
void free_simple_rr_sprite(nl_rr_sprite* const sprite);

#endif//__NL_RR_SPRITE_H__