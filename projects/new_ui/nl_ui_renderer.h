#ifndef __NL_UI_RENDERER_H__
#define __NL_UI_RENDERER_H__

typedef struct ui_element ui_element;
struct ui_element
{
    colourf color;
    v2f pos;
    v2f size;
    v2f anchor;
    float rot;
};

void init_ui_renderer(void);
void cleanup_ui_renderer(void);

int ui_do_button(ui_element* elem, int x, int y, const char* label);
void  ui_do_text(ui_element* elem, int x, int y, const char* text);
void  ui_do_icon(ui_element* elem, int x, int y);

#endif//__NL_UI_RENDERER_H__