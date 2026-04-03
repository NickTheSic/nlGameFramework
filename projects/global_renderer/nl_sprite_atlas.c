#include "nl_sprite_atlas.h"

void init_sprite_atlas(sprite_atlas *atlas)
{
    
}

void free_sprite_atlas(sprite_atlas *atlas)
{

}

sprite_handle add_sprite_to_atlas(sprite_atlas *atlas, const char* name)
{
    if (atlas->allocated_frames + 1 > atlas->max_frames)
    {
        // TODO: Could realloc the array
        NL_LOG("Unable to add sprite since we have reached the max frames...");
        return 0;
    }
}

void get_atlas_frame(sprite_atlas *atlas, sprite_handle handle, atlas_frame *frame)
{
    if (handle > atlas->max_frames || handle > atlas->allocated_frames)
    {
        NL_LOG("Unable to get the atlas frame: %u, it is outside the bounds: max %u, made %u", handle, atlas->max_frames, atlas->allocated_frames);
    }
}
