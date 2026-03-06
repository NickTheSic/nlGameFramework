#include "nl_lib.h"

#include "third_party/stb_truetype.h"
#include "private/gl/nl_gl.h"


void app_specific_init(void)
{
    NL_LOG("Loading font!")
    file_contents font = {0};
    read_entire_file("data/fonts/promptfont-all/promptfont.ttf", &font);

    stbtt_fontinfo info;
    if (!stbtt_InitFont(&info, font.content, 0))
    {
        NL_LOG("Font loading failed");
        clear_file_read(&font);
        return;
    }

    int width, height, line;

    clear_file_read(&font);
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