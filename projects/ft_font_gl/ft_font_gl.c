#include "nl_lib.h"

#include "private/gl/nl_gl.h"
#include <stddef.h>

#include "nl_sprite_renderer.h"

unsigned int FontTexture = 0;

global_variable nl_sprite full = {0};

global_variable camera main_cam = {0};

internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0.f, (float)width, 0.f, (float)height, -0.1f, 100.f);
    set_projection_matrix(&main_cam.proj_matrix);
}


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

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        atlasw,
        atlash,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        0
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


    generate_square_mesh(&full, 400, COLOURF_WHITE);

    set_window_size_callback(&winsizecbk);
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);

    create_srt_matrix(&main_cam.view_matrix, (v3f){1.0f,1.0f,0.0f}, (v3f){0.0f,0.0f,0.0f}, (v3f){0.0f,0.0f,0.0f});
    set_view_matrix(&main_cam.view_matrix.m11);

}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{
    render_single_mesh(&full);
}

void app_specific_cleanup(void)
{

}

#include "nl_sprite_renderer_gl.c"
