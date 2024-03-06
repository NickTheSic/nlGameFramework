#ifndef __NL_SPRITESHEET_H__
#define __NL_SPRITESHEET_H__

#include "nl_math.h"

typedef unsigned int sprite_handle;

typedef struct sprite_data sprite_data;
struct sprite_data
{
    v2f ur_coord;
    v2f bl_coord;

    v2i loaded_size;
};

typedef struct spritesheet spritesheet;
struct spritesheet
{
    v2i atlas_size;
    v2i atlas_used;

    unsigned int texture_id;

    sprite_handle error_sprite;

    int max_sprites;
    int sprite_count;

    sprite_data* sprites;
};

void initialize_spritesheet(spritesheet* const sheet, int sx, int sy);
void cleanup_spritesheet(spritesheet* const sheet);

sprite_handle load_sprite(spritesheet* const sheet, const char* filepath);

#endif //__NL_SPRITESHEET_H__