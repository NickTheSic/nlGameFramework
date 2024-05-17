#ifndef __SPRITE_RENDERER_H__
#define __SPRITE_RENDERER_H__

#include "private/nl_math.h"

typedef int sprite_handle;

sprite_handle load_sprite(const char* filename);
void draw_sprite(sprite_handle sprite, v2f pos);

#endif//__SPRITE_RENDERER_H__