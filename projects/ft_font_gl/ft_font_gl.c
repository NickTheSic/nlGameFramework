#include "nl_lib.h"

#include "private/gl/nl_gl.h"
#include <stddef.h>

#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct GlyphData GlyphData;

struct GlyphData
{
        v2i size;
        v2i bearing;
        float xoffset;        // works for ascii characters
        unsigned int advance; // works for ascii characters
};

GlyphData Glyphs[128-33] = {0};

float  DivAtlasWidth = 0;
float DivAtlasHeight = 0;
int FontTexture = 0;

void app_specific_init(void)
{
    FT_Library ft_library = {0};
    if (FT_Init_FreeType(&ft_library))
    {
        NL_LOG("Failed to init FT Library");
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft_library, "data/fonts/promptfont-all/promptfont.ttf", 0, &face))
    {
        NL_LOG("ERROR::FREETYPE: Failed to load font");
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 64);

    int atlasw = 0;
    int atlash = 0;
    for (unsigned char c = 33; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            NL_LOG("ERROR::FREETYTPE: Failed to load Glyph");
            continue;
        }
    
        atlasw += face->glyph->bitmap.width*4;
        atlash = (face->glyph->bitmap.rows*4 > atlash)
            ? face->glyph->bitmap.rows*4
            : atlash;
    }

    DivAtlasWidth = 1.0f / (float)atlasw;
    DivAtlasHeight = 1.0f / (float)atlash;

    glGenTextures(1, &FontTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, FontTexture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    // set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    NL_LOG("Allocating gl buffer");

    void* gl_buffer = malloc(atlasw*atlash*sizeof(unsigned char));

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            atlasw,
            atlash,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            gl_buffer
        );
        

        NL_LOG("For loop to set gl tex dub image");
        
        int xoffset = 0;
        for (unsigned char c = 33; c < 128; c++)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                NL_LOG("ERROR::FREETYTPE: Failed to load Glyph");
                continue;
            }

            unsigned int* Buffer = (unsigned int*)malloc(sizeof(unsigned int) * face->glyph->bitmap.width * face->glyph->bitmap.rows);

            for (int i = 0; i < face->glyph->bitmap.width * face->glyph->bitmap.rows; i++)
            {
                Buffer[i] = 0x00ffffff | (face->glyph->bitmap.buffer[i] << 24);
            }
        
            glTexSubImage2D(GL_TEXTURE_2D, 0,
                xoffset, 0,
                face->glyph->bitmap.width, face->glyph->bitmap.rows,
                GL_RGBA,
                GL_UNSIGNED_BYTE, 
                Buffer);//face->glyph->bitmap.buffer);
        
            float tx = (float)xoffset * DivAtlasWidth;
            // now store character for later use
            GlyphData glyph = {
                (v2i){face->glyph->bitmap.width, face->glyph->bitmap.rows},
                (v2i){face->glyph->bitmap_left,  face->glyph->bitmap_top },
                tx,
                (unsigned int)(face->glyph->advance.x >> 6)
            };

            Glyphs[c-33] = glyph;

            free(Buffer);
        
            xoffset += face->glyph->bitmap.width*4;
        }
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    FT_Done_Face(face);
    FT_Done_FreeType(ft_library);
}





void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{

}

void app_specific_cleanup(void)
{

}
