#include "private/gl/nl_gl.h"
#include "private/nl_shader.h"

#include "string.h" //memcpy, memset


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
    // If I want indices for font rendering I need to add it
    // I'll decide when the time comes though 
};

void init_ui_renderer(ui_renderer* const ui_renderer);
void cleanup_ui_renderer(ui_renderer* const ui_renderer);
void update_ui_screen_size(ui_renderer* const ui_renderer, int width, int height);
void add_element_to_render_batch(ui_renderer* const batch, const ui_element *const elem);
void begin_ui_render_batch(ui_renderer* const ui_renderer);
void end_ui_render(ui_renderer* const ui_renderer);

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

void update_ui_screen_size(ui_renderer* const ui_renderer, int width, int height)
{
    mat4x4f mat = {0};
    create_identity_matrix(&mat);
    create_orthographic_projection(&mat, 0.f, (float)width, 0.f, (float)height, -0.1f, 100.f);

    use_shader_program(ui_renderer->shader_program);
    unsigned int viewMat = glGetUniformLocation(ui_renderer->shader_program, VIEW_MATRIX_UNIFORM_NAME);
    glUniformMatrix4fv(viewMat, 1, GL_FALSE, &mat.m11);
}

void init_ui_renderer(ui_renderer* const ui_renderer)
{
    ui_renderer->shader_program = create_shader_program(ui_vert_shader_code, ui_fragment_shader_code);
    use_shader_program(ui_renderer->shader_program);

    const unsigned int vertice_count = UI_MAX_BATCH_COUNT * 4;
    const unsigned int indice_count  = UI_MAX_BATCH_COUNT * 6;

    const size_t vertice_data = vertice_count * sizeof(ui_vertex_data);
    const size_t indice_data  = indice_count  * sizeof(unsigned int);

    glGenVertexArrays(1, &ui_renderer->vao);
    glBindVertexArray(ui_renderer->vao);
 
    glGenBuffers(1, &ui_renderer->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, ui_renderer->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertice_data, (void*)0, GL_DYNAMIC_DRAW);

    unsigned int *indices = (unsigned int*)memory_allocate(indice_data);
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

    glGenBuffers(1, &ui_renderer->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ui_renderer->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_data, indices, GL_STATIC_DRAW);

    memory_free(indices);
}

void begin_ui_render_batch(ui_renderer* const ui_renderer)
{
    use_shader_program(ui_renderer->shader_program);

    glBindVertexArray(ui_renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, ui_renderer->vbo);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ui_vertex_data), (void*)offsetof(ui_vertex_data, pos));
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ui_vertex_data), (void*)offsetof(ui_vertex_data, color));
    glEnableVertexAttribArray(1);
}

void render_batch(ui_renderer* const ui_renderer)
{
    glBindBuffer(GL_ARRAY_BUFFER, ui_renderer->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, ui_renderer->current_count*4*sizeof(ui_vertex_data), ui_renderer->vertices);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ui_renderer->ebo);
    glDrawElements(GL_TRIANGLES, ui_renderer->current_count*6, GL_UNSIGNED_INT, 0);

    ui_renderer->current_count = 0;

    memset(ui_renderer->vertices, 0, sizeof(ui_vertex_data)*4*UI_MAX_BATCH_COUNT);
}

void add_element_to_render_batch(ui_renderer* const batch, const ui_element *const elem)
{
    if (batch->current_count == UI_MAX_BATCH_COUNT)
    {
        render_batch(batch);
    }

    const unsigned int current_idx = batch->current_count * 4;
    
    v2f pos = elem->pos;
    v2i screen_size = get_screen_size();
    const float half_w = screen_size.x/2.0f;
    const float half_h = screen_size.y/2.0f;
    //pos.x += (half_w) + (elem->anchor.x * half_w);
    //pos.y += (half_h) + (elem->anchor.y * half_h);

    const colourf col = elem->color;
    const v2f size = elem->size;
    const ui_vertex_data square_verts[] =
    {
        {{pos.x + -size.x, pos.y + -size.y}, col},
        {{pos.x +  size.x, pos.y + -size.y}, col},
        {{pos.x +  size.x, pos.y +  size.y}, col},
        {{pos.x + -size.x, pos.y +  size.y}, col}
    };

    ui_vertex_data* dest = &batch->vertices[current_idx];
    memcpy(dest, &square_verts, sizeof(ui_vertex_data)*4);

    batch->current_count++;
}

void end_ui_render(ui_renderer* const ui_renderer)
{
    render_batch(ui_renderer);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void cleanup_ui_renderer(ui_renderer* const ui_renderer)
{
    NL_UNUSED(ui_renderer);
}