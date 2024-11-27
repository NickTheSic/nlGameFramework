#include "nl_ui_renderer.h"

#include <private/gl/nl_gl.h>
#include <private/nl_shader.h>

#define UI_MAX_BATCH_COUNT 10

typedef struct ui_vertex_data ui_vertex_data;
struct ui_vertex_data
{
    colourf color;
    transform2d trans;
    v2f anchor;
};

static const char* ui_vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec2 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"uniform mat4 uViewMat;                                \n"
"out vec4 oColor;                                      \n"
"void main() {                                         \n"
"   vec4 viewPos = uViewMat * vec4(aPos, 0.0, 1.0);    \n"
"   gl_Position = viewPos;                             \n"
"   oColor = aColor;                                   \n"
"}                                                     \0";

static const char* ui_fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                   \n"
"in vec4 oColor;                                       \n"
"void main() {                                         \n"
"    FragColor = oColor;                               \n"
"}                                                     \n";


typedef struct ui_batch_renderer ui_batch_renderer;
struct ui_batch_renderer
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
global_variable ui_batch_renderer ui_renderer = {0};

void init_ui_renderer(void)
{
    ui_renderer.shader_program = create_shader_program(ui_vert_shader_code, ui_fragment_shader_code);
    use_shader_program(ui_renderer.shader_program);

    const unsigned int vertice_count = UI_MAX_BATCH_COUNT * 4;
    const unsigned int indice_count  = UI_MAX_BATCH_COUNT * 6;

    const size_t vertice_data = vertice_count * sizeof(ui_vertex_data);
    const size_t indice_data  = indice_count  * sizeof(unsigned int);
}

void cleanup_ui_renderer(void)
{

}

int ui_do_button(ui_element* elem, int x, int y, const char* label)
{
    return 0;
}

void  ui_do_text(ui_element* elem, int x, int y, const char* text)
{

}

void  ui_do_icon(ui_element* elem, int x, int y)
{

}
