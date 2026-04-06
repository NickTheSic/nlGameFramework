#ifndef __NL_SPRITE_ATLAS_H__
#define __NL_SPRITE_ATLAS_H__

#include "private/nl_math.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned short sprite_handle;
#define INVALID_SPRITE_HANDLE ((sprite_handle)65534)

typedef struct atlas_frame atlas_frame;
struct atlas_frame
{
    v2f bottom_left;
    v2f top_right;
};

typedef struct sprite_atlas sprite_atlas;
struct sprite_atlas
{
    atlas_frame frames[5];
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



// TODO: I could handle loading a premade sprite atlas/sprite sheet
//       Where I would need to load the texture and then chop it up as it is loaded?
//       This is where a return value doesn't work exactly...
//       Unless I pass in an array to fill


#ifdef __cplusplus
}
#endif

#endif//__NL_SPRITE_ATLAS_H__