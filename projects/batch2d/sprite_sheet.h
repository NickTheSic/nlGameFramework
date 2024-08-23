#ifndef __NL_SPRITE_SHEET_H__
#define __NL_SPRITE_SHEET_H__

typedef struct sprite_sheet sprite_sheet;
struct sprite_sheet
{
    unsigned int texture_id;
};

unsigned int load_image(const char* const filename);

#endif//__NL_SPRITE_SHEET_H__