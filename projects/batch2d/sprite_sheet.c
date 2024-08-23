#include "sprite_sheet.h"

#define STBI_ONLY_PNG
#include "third_party/stb_image.h"

global_variable sprite_sheet sheet = {0};

unsigned int load_image(const char* const filename)
{
    // only needs to be set once on init
    {
    stbi_set_flip_vertically_on_load(1);

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
                 128, 128,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
#if !defined __EMSCRIPTEN__ || !defined PLATFORM_WEB
                0
#else
                memory_allocate(sizeof(unsigned char)*sheet->atlas_size.x*sheet->atlas_size.y);
#endif
                 );
    }
    
    int x, y, channel;
    unsigned char* png_data = stbi_load(filename, &x, &y, &channel, 4);

    glTexSubImage2D(GL_TEXTURE_2D, 0,
                0, 0,
                x, y, 
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                png_data);

    stbi_image_free(png_data);

//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SpriteVertexData), (void*)(offsetof(SpriteVertexData, position)));
//    glEnableVertexAttribArray(0);
//    
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertexData), (void*)(offsetof(SpriteVertexData, uv)));
//    glEnableVertexAttribArray(1);

    return 1;
}