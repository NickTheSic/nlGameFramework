#include "nl_sprite_atlas.h"

#include "private/gl/nl_gl.h"
#include "private/nl_shader.h"
#define STBI_ONLY_PNG
#include <third_party/main_stb_image.h>

#define SPRITE_ATLAS_WIDTH  32
#define SPRITE_ATLAS_HEIGHT 64

global_variable nl_sprite_atlas sprite_atlas;

void initialize_sprite_atlas(void)
{
    stbi_set_flip_vertically_on_load(1);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &sprite_atlas.texture_id);
    glBindTexture(GL_TEXTURE_2D, sprite_atlas.texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(
        GL_TEXTURE_2D,
        0, GL_RGBA,
        SPRITE_ATLAS_WIDTH, SPRITE_ATLAS_HEIGHT,
        0, GL_RGBA,
        GL_UNSIGNED_BYTE,
        0
    );
}

void cleanup_sprite_atlas(void)
{

}

sprite_handle load_sprite(const char* name)
{
    sprite_handle handle = -1;
    int x,y,channel;
    unsigned char* data = stbi_load(name, &x, &y, &channel, 4);

    if (stbi_failure_reason())
    {
        NL_LOG("%s while loading: %s", stbi_failure_reason(), name);
        return handle;
    }

    if (data == 0)
    {
        NL_LOG("Unable to load image %s.  stbi_load failed to load", name);
        return handle;
    }

    glTexSubImage2D(GL_TEXTURE_2D, 0,
                    sprite_atlas.current_texture_x, sprite_atlas.current_texture_y,
                    x, y,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    data);

    stbi_image_free(data);

    if ((sprite_atlas.current_texture_x + x) > SPRITE_ATLAS_WIDTH)
    {
        sprite_atlas.current_texture_x = 0; 
        sprite_atlas.current_texture_y = sprite_atlas.current_used_height;
    }

    if ((sprite_atlas.current_texture_y + y) > SPRITE_ATLAS_HEIGHT)
    {
        NL_LOG("Reached max height for this texture. Unable to allocate new sprite");
        return handle;
    }

    texture_data *const current_texture = &sprite_atlas.textures[sprite_atlas.next_texture_index];

    current_texture->coord_bl.x = (float)sprite_atlas.current_texture_x / (float)SPRITE_ATLAS_WIDTH;
    current_texture->coord_bl.y = (float)sprite_atlas.current_texture_y / (float)SPRITE_ATLAS_HEIGHT;
    current_texture->coord_tr.x = (float)(sprite_atlas.current_texture_x + x) / (float)SPRITE_ATLAS_WIDTH;
    current_texture->coord_tr.y = (float)(sprite_atlas.current_texture_y + y) / (float)SPRITE_ATLAS_HEIGHT;
    
    sprite_atlas.current_texture_x += x;
    if ((sprite_atlas.current_used_height - sprite_atlas.current_texture_y) < y)
    {
        sprite_atlas.current_used_height = y + sprite_atlas.current_texture_y;
    }
    else
    {
        sprite_atlas.current_used_height = sprite_atlas.current_texture_y;
    }

    handle = sprite_atlas.next_texture_index++;
    
    return handle;
}

void bind_sprite_atlas_texture(void)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sprite_atlas.texture_id);
}

const texture_data get_texture_for_handle(sprite_handle handle)
{
    return sprite_atlas.textures[handle];
}
