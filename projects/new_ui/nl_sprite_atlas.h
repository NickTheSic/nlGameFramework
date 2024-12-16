#ifndef __NL_SPRITE_ATLAS_H__
#define __NL_SPRITE_ATLAS_H__

typedef int sprite_handle;

typedef struct texture_data texture_data;
struct texture_data
{
    v2f coord_bl;
    v2f coord_tr;
};

typedef struct nl_sprite_atlas nl_sprite_atlas;
struct nl_sprite_atlas
{
    unsigned int texture_id;
    unsigned int next_texture_index;  //The sprite index to return and where the newly loaded sprite goes
    unsigned int current_texture_x;   // Current value along the width of the loaded texutre
    unsigned int current_texture_y;   // Current value along the height of the loaded texutre
    unsigned int current_used_height; // how tall the tallest loaded image this row was

    texture_data textures[5];         // hardcoded set number for easy testing
};

void initialize_sprite_atlas(void);
void cleanup_sprite_atlas(void);

sprite_handle load_sprite(const char* name);

void bind_sprite_atlas_texture(void);
const texture_data get_texture_for_handle(sprite_handle handle);

#endif//__NL_SPRITE_ATLAS_H__