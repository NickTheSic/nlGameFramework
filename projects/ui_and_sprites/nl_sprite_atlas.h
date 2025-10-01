#ifndef __NL_SPRITE_ATLAS_H__
#define __NL_SPRITE_ATLAS_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef int sprite_handle;

typedef struct texture_data texture_data;
struct texture_data
{
    v2f coord_bl;
    v2f coord_tr;
};

typedef struct sprite_atlas sprite_atlas;
struct sprite_atlas
{
    unsigned int texture_id;

    unsigned int next_texture_index;  //The sprite index to return and where the newly loaded sprite goes
    unsigned int current_texture_x;   // Current value along the width of the loaded texutre
    unsigned int current_texture_y;   // Current value along the height of the loaded texutre
    unsigned int current_used_height; // how tall the tallest loaded image this row was

    unsigned int max_textures;
    unsigned int current_textures;
    texture_data* textures;
};

int initialize_sprite_atlas(sprite_atlas* atlas);
void cleanup_sprite_atlas(sprite_atlas* atlas);

sprite_handle load_sprite_in_atlas(sprite_atlas* atlas, const char* name);

void bind_sprite_atlas_texture(sprite_atlas* atlas);
const texture_data get_texture_for_handle(sprite_atlas* atlas, sprite_handle handle);

#ifdef __cplusplus
}
#endif

#endif//___NL_SPRITE_ATLAS_H__