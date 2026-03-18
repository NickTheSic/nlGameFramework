#ifndef __NL_RR_SPRITE_H__
#define __NL_RR_SPRITE_H__

typedef struct nl_rr_sprite nl_rr_sprite;
struct nl_rr_sprite
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int TextureID;
};

void create_simple_rr_sprite(const char* filename, nl_rr_sprite* const sprite);
void render_simple_rr_sprite(nl_rr_sprite* const spr);
void free_simple_rr_sprite(nl_rr_sprite* const sprite);

#endif//__NL_RR_SPRITE_H__