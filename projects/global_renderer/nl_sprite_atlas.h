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
    // Not sure if this needs to be a pointer
    // could just have a max array of like 50?
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
void get_atlas_frame(sprite_atlas *atlas, sprite_handle handle, atlas_frame *frame);

#endif//__NL_SPRITE_ATLAS_H__