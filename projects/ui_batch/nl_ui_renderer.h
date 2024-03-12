#ifndef __NL_UI_RENDERER_H__
#define __NL_UI_RENDERER_H__

#define UI_MAX_BATCH_COUNT 10

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
};

void init_ui_renderer(ui_renderer* const ui_renderer);
void cleanup_ui_renderer(ui_renderer* const ui_renderer);
void update_ui_screen_size(ui_renderer* const ui_renderer, int width, int height);
void add_element_to_render_batch(ui_renderer* const batch, const ui_element *const elem);
void begin_ui_render_batch(ui_renderer* const ui_renderer);
void end_ui_render(ui_renderer* const ui_renderer);

#endif//__NL_UI_RENDERER_H__