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

typedef struct ui_vertex_data ui_vertex_data;
struct ui_vertex_data
{
    v2f pos;
    colourf color;
};

typedef struct ui_renderer ui_renderer;
struct ui_renderer
{
    unsigned int shader_program;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    unsigned int current_count;

    ui_vertex_data vertices[UI_MAX_BATCH_COUNT];
    // If I want indices for font rendering I need to add it
    // I'll decide when the time comes though 
};

void init_ui_renderer(void);
void cleanup_ui_renderer(void);

int ui_do_button(ui_element* elem, int x, int y, const char* label);
void  ui_do_text(ui_element* elem, int x, int y, const char* text);
void  ui_do_icon(ui_element* elem, int x, int y)

#endif//__NL_UI_RENDERER_H__