#ifndef __NL_SPRITE_SHEET_H__
#define __NL_SPRITE_SHEET_H__

typedef struct sprite sprite;
struct sprite
{
    v2f bl_coord; //Bottom Left
    v2f tr_coord; //Top Right
};

typedef struct sprite_sheet sprite_sheet;
struct sprite_sheet
{
    unsigned int texture_id;
    unsigned int active_handle;
    sprite* sprites;
};

void init_sprite_sheet();
void free_sprite_sheet();

unsigned int load_image(const char* const filename);

sprite* const get_sprite(unsigned int sprite);

#endif//__NL_SPRITE_SHEET_H__