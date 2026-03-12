#ifndef __FT_NL_H__
#define __FT_NL_H__

typedef struct GlyphData GlyphData;
struct GlyphData
{
        v2i size;
        v2i bearing;
        float xoffset;        // works for ascii characters
        unsigned int advance; // works for ascii characters
};
// Use characters 33 to 127
GlyphData Glyphs[95] = {0};

int ft_load_font(const char* font_name);

#endif//__FT_NL_H__