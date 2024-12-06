#include "nl_ui_renderer.h"

#include <private/gl/nl_gl.h>
#include <private/nl_shader.h>

#include <string.h>

#define UI_MAX_BATCH_COUNT 10

typedef struct ui_vertex_data ui_vertex_data;
struct ui_vertex_data
{
    v2f pos;
    colourf color;
};

static const char* ui_vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec2 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"uniform mat4 uProjMat;                                \n"
"out vec4 oColor;                                      \n"
"void main() {                                         \n"
"   vec4 viewPos = uProjMat * vec4(aPos, 0.0, 1.0);    \n"
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

    ui_vertex_data vertices[4*UI_MAX_BATCH_COUNT];
};
global_variable ui_batch_renderer ui_renderer = {0};

global_variable unsigned int loc_projection_matrix = {0};

void set_screen_dimensions(int x, int y)
{
    mat4x4f viewport = {0};
    create_orthographic_projection(&viewport, 0, x, 0, y, -0.1f, 100.f);

    use_shader_program(ui_renderer.shader_program);
    set_uniform_mat4x4f(loc_projection_matrix, &viewport.m11);
}

void init_ui_renderer(void)
{
    ui_renderer.shader_program = create_shader_program(ui_vert_shader_code, ui_fragment_shader_code);
    use_shader_program(ui_renderer.shader_program);

    loc_projection_matrix = get_uniform_loc(ui_renderer.shader_program, "uProjMat");
    v2i screen =  get_screen_size();
    set_screen_dimensions(screen.x, screen.y);

    const unsigned int vertice_count = UI_MAX_BATCH_COUNT * 4;
    const unsigned int indice_count  = UI_MAX_BATCH_COUNT * 6;

    const size_t vertice_data = vertice_count * sizeof(ui_vertex_data);
    const size_t indice_data  = indice_count  * sizeof(unsigned int);

    glGenVertexArrays(1, &ui_renderer.vao);
    glBindVertexArray(ui_renderer.vao);

    glGenBuffers(1, &ui_renderer.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, ui_renderer.vbo);
    glBufferData(GL_ARRAY_BUFFER, vertice_data, (void*)0, GL_DYNAMIC_DRAW);

    unsigned int *indices = (unsigned int*)memory_allocate(indice_data);
    if (indices == 0)
    {
        NL_LOG("Failed to allocate memory for ui renderer indices!  Doing an early return");
        return;
    }

    unsigned int offset = 0;
    for (unsigned int i = 0; i < indice_count; i+=6)
    {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;
        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;
        offset += 4;
    }

    glGenBuffers(1, &ui_renderer.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ui_renderer.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_data, indices, GL_STATIC_DRAW);

    memory_free(indices);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void cleanup_ui_renderer(void)
{

}

void begin_ui_render(void)
{
    use_shader_program(ui_renderer.shader_program);

    glBindVertexArray(ui_renderer.vao);
    glBindBuffer(GL_ARRAY_BUFFER, ui_renderer.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ui_renderer.ebo);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ui_vertex_data), (void*)offsetof(ui_vertex_data, pos));
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ui_vertex_data), (void*)offsetof(ui_vertex_data, color));
    glEnableVertexAttribArray(1);
}

internal_function void render_batch(void)
{
    glBindBuffer(GL_ARRAY_BUFFER, ui_renderer.vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, ui_renderer.current_count*4*sizeof(ui_vertex_data), ui_renderer.vertices);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ui_renderer.ebo);
    glDrawElements(GL_TRIANGLES, ui_renderer.current_count*6, GL_UNSIGNED_INT, 0);

    ui_renderer.current_count = 0;
    
    memset(ui_renderer.vertices, 0, sizeof(ui_vertex_data)*4*(UI_MAX_BATCH_COUNT - 1));
}

void end_ui_render(void)
{
    render_batch();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

internal_function void add_element_to_render_batch(const ui_element* const element)
{
    if (ui_renderer.current_count == UI_MAX_BATCH_COUNT)
    {
        render_batch();
    }

    const unsigned int current_idx = ui_renderer.current_count * 4;

    const v2f pos = element->pos;
    const colourf col = element->color;
    const v2f size = element->size;
    const ui_vertex_data square_verts[] =
    {
        {{pos.x + -size.x, pos.y + -size.y}, col},
        {{pos.x +  size.x, pos.y + -size.y}, col},
        {{pos.x +  size.x, pos.y +  size.y}, col},
        {{pos.x + -size.x, pos.y +  size.y}, col}
    };

    ui_vertex_data* dest = &ui_renderer.vertices[current_idx];
    memcpy(dest, &square_verts, sizeof(ui_vertex_data)*4);

    ui_renderer.current_count++;
}

int ui_do_text_button(ui_element* elem, int x, int y, const char* label)
{
    NL_UNUSED(elem); 
    NL_UNUSED(x);
    NL_UNUSED(y); 
    NL_UNUSED(label);
    return 0;
}

int ui_do_icon_button(ui_element* elem, int x, int y, unsigned int texture)
{
    NL_UNUSED(elem); 
    NL_UNUSED(x);
    NL_UNUSED(y); 
    NL_UNUSED(texture);
    return 0;
}

void  ui_do_text(ui_element* elem, int x, int y, const char* text)
{
    NL_UNUSED(elem); 
    NL_UNUSED(x);
    NL_UNUSED(y); 
    NL_UNUSED(text);
}

void  ui_do_icon(ui_element* elem, int x, int y, unsigned int texture_id)
{
    NL_UNUSED(elem); 
    NL_UNUSED(x);
    NL_UNUSED(y); 
    NL_UNUSED(texture_id);
}

void DEBUG_add_elem(ui_element* const elem)
{
    add_element_to_render_batch(elem);
}
