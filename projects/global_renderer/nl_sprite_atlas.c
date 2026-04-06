#include "nl_sprite_atlas.h"
#include "private/gl/nl_gl.h"
#include "third_party/stb/stb_image.h"

void init_sprite_atlas(sprite_atlas *atlas)
{
    atlas->max_frames = 5;   // Parameterize!
    atlas->max_height = 512; // Parameterize!
    atlas->max_width = 512;  // Parameterize!

    //atlas -> frames = bump_alloc(max_frames);

    atlas->allocated_frames=0;
    atlas->current_width = 0;
    atlas->current_height = 0;

    glGenTextures(1, &atlas->texture_id);
    glBindTexture(GL_TEXTURE_2D, atlas->texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(1);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        atlas->max_width, atlas->max_height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        0 // Should be data / nullptr
    );

    glBindTexture(GL_TEXTURE_2D, 0);
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
        NL_LOG("NL_SPRITE_ATLAS: Unable to add sprite since we have reached the max frames...");
        return INVALID_SPRITE_HANDLE;
    }

    char path[64] = "data/images/";
    strcat(path, name);
    int width, height, channels;
    unsigned char* data = stbi_load(path, &width, &height, &channels, 0);

    // add to buffer
    if (data)
    {
        stbi_image_free(data);
    }
    else
    {
        NL_LOG("NL_SPRITE_ATLAS: Unable to add sprite to atlas, could not load image");
        return INVALID_SPRITE_HANDLE;
    }

    const int handle = atlas->allocated_frames;
    atlas->allocated_frames++;

    // TODO: Get bottom left, should be the old handle?
    atlas->frames[handle].bottom_left = (v2f){0.f, 0.f};
    // TODO: Top right should be width and height + bottom left?
    atlas->frames[handle].top_right = (v2f){1.f,1.f};

    return handle;
}

void get_atlas_frame(sprite_atlas *atlas, sprite_handle handle, atlas_frame *frame)
{
    if (handle > atlas->max_frames || handle > atlas->allocated_frames)
    {
        NL_LOG("Unable to get the atlas frame: %u, it is outside the bounds: max %u, made %u", handle, atlas->max_frames, atlas->allocated_frames);
        frame->top_right = (v2f){1.f,1.f};
        return;
    }

    *(frame) = atlas->frames[handle];
}
