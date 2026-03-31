#ifndef __NL_SPRITE_ATLAS_H__
#define __NL_SPRITE_ATLAS_H__

#include "private/nl_math.h"

typedef unsigned int sprite_handle;

typedef struct atlas_frame atlas_frame;
struct atlas_frame
{
    v2f bottom_left;
    v2f top_right;
};

typedef struct sprite_atlas sprite_atlas;
struct sprite_atlas
{
    atlas_frame *frames;
    unsigned int max_frames;
    unsigned int allocated_frames;

    unsigned int max_width;
    unsigned int max_height;
    unsigned int current_width;
    unsigned int current_height;
    
    unsigned int texture_id;
};

void init_sprite_atlas(sprite_atlas *atlas);
void free_sprite_atlas(sprite_atlas *atlas);

sprite_handle add_sprite_to_atlas(sprite_atlas *atlas, const char* name);

#endif//__NL_SPRITE_ATLAS_H__