#include "ft_nl.h"

#include <ft2build.h>
#include FT_FREETYPE_H

float  DivAtlasWidth = 0;
float DivAtlasHeight = 0;

int ft_load_font(const char* font_name)
{
    FT_Library ft = {0};
    if (FT_Init_FreeType(&ft))
    {
        NL_LOG("Freetype: Failed to init FT Library");
        return 0;
    }

    FT_Face face = {0};
    if (FT_New_Face(ft, font_name))
    {
        NL_LOG("Freetype: Failed to load font");
        return 0;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);
    

    // The following makes a long texture 
    // using the max height and adding each width together

    int atlas_width = 0; // To store the width of all characters
    int atlas_height = 0; // To store the max height of a single character
    for (unsigned char c = 33; c < 127; ++c)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            NL_LOG("Freeytpe: Failed to load glyph %c", c);
            continue;
        }

        atlas_width += face->glyph->bitmap.width;
        atlas_height = (face->glyph->bitmap.rows > atlas_height) 
                     ? face->glyph->bitmap.rows
                     : atlas_height;
    }

    float div_atlas_width  = 1.f / (float)atlas_width;

}
