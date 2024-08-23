#include "sprite_sheet.h"

#define STBI_ONLY_PNG
#include "third_party/stb_image.h"

global_variable sprite_sheet sheet = {0};

void init_sprite_sheet()
{
    stbi_set_flip_vertically_on_load(1);

    sheet.sprites = memory_allocate(sizeof(sprite) * 1);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &sheet.texture_id);
    glBindTexture(GL_TEXTURE_2D, sheet.texture_id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 16, 16,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 0
                 );
}

void free_sprite_sheet()
{
    memory_free(sheet.sprites);
}

unsigned int load_image(const char* const filename)
{
    sprite sprite = {0};
    
    int x, y, channel;
    unsigned char* png_data = stbi_load(filename, &x, &y, &channel, 4);

    sprite.bl_coord.x = 0.f;
    sprite.bl_coord.y = 0.f;
    sprite.tr_coord.x = 1.f;
    sprite.tr_coord.y = 1.f;

    glTexSubImage2D(GL_TEXTURE_2D, 
                    0,
                    0, 
                    0,
                    x, 
                    y, 
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    png_data);

    stbi_image_free(png_data);

    unsigned int handle = sheet.active_handle++;
    sheet.sprites[handle] = sprite;

    return handle;
}

sprite* const get_sprite(unsigned int sprite)
{
    return &sheet.sprites[0];
}
