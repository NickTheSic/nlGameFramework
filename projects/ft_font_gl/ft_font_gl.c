#include "nl_lib.h"

#include "private/gl/nl_gl.h"

#include <ft2build.h>
#include FT_FREETYPE_H


float  DivAtlasWidth = 0;
float DivAtlasHeight = 0;

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
    
        atlasw += face->glyph->bitmap.width;
        atlash = (face->glyph->bitmap.rows > atlash)
            ? face->glyph->bitmap.rows
            : atlash;
    }
    DivAtlasWidth = 1.0f / (float)atlasw;
    DivAtlasHeight = 1.0f / (float)atlash;

    FT_Done_Face(face);
    FT_Done_FreeType(ft_library);

    NL_LOG("Ended Init!");
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
