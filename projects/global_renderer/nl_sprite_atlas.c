#include "nl_sprite_atlas.h"
#include "private/gl/nl_gl.h"
#include "third_party/stb/stb_image.h"

void init_sprite_atlas(sprite_atlas *atlas)
{
    // Max frames a parameter
    // atlas width and height also a parameter
    atlas->max_frames = 5; // Allocate with the bump allocator!
    atlas->current_frames=0;
    atlas->max_width = 1024;
    atlas->max_height = 1024;
    atlas->current_width = 0;
    atlas->current_height = 0;

    glGenTextures(1, &atlas->texture_id);
    glBindTexture(GL_TEXTURE_2D, atlas->texture_id);
}

void free_sprite_atlas(sprite_atlas *atlas)
{
    glDeleteTextures(1, &atlas->texture_id);
}

sprite_handle add_sprite_to_atlas(sprite_atlas *atlas, const char* name)
{
    if (atlas->allocated_frames + 1 > atlas->max_frames)
    {
        // TODO: Could realloc the array?
        NL_LOG("Unable to add sprite since we have reached the max frames...");
        return 0;
    }

    // stb load image
    // add to buffer
    // note: Could load all images at once in their own batch?
    // Note: I plan to load each image separate but I could save this info out and make a custom spritesheet class

    atlas->allocated_frames++;
}

void get_atlas_frame(sprite_atlas *atlas, sprite_handle handle, atlas_frame *frame)
{
    if (handle > atlas->max_frames || handle > atlas->allocated_frames)
    {
        NL_LOG("Unable to get the atlas frame: %u, it is outside the bounds: max %u, made %u", handle, atlas->max_frames, atlas->allocated_frames);
    }
}
