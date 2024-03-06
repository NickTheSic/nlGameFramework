// included in more_ui_stuff after the normal includes to keep this file separate for clarity

#include <string.h> // memcpy

#define SQUARE_HALF_SIZE 100.0f


static const char* ui_vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"uniform mat4 uWorldMat;                               \n"
"uniform mat4 uViewMat;                                \n"
"out vec4 oColor;                                      \n"
"void main() {                                         \n"
"   vec4 worldPos = uWorldMat * vec4(aPos, 1.0);       \n"
"   gl_Position = uViewMat * worldPos;                 \n"
"   oColor = aColor;                                   \n"
"}                                                     \0";

static const char* ui_fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                   \n"
"in vec4 oColor;                                       \n"
"void main() {                                         \n"
"    FragColor = oColor;                               \n"
"}                                                     \0";


typedef struct ui_element ui_element;
struct ui_element
{
    transform2d trans;
    colourf color;
    v2f anchor;
};

typedef struct ui_batch_renderer ui_batch_renderer;
struct ui_batch_renderer
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    
    unsigned int batch_count;
    unsigned int current_count;

    vertex_data* vertices;
};

void free_ui_batch_renderer(ui_batch_renderer* const ui_renderer)
{
    memory_free(ui_renderer->vertices);
    ui_renderer->batch_count = 0;
}

void draw_ui_batch(ui_batch_renderer* const ui_renderer)
{
    glBindVertexArray(ui_renderer->VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ui_renderer->EBO);

    glDrawElements(GL_TRIANGLES, ui_renderer->current_count, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void add_element_to_ui_renderer(ui_batch_renderer* const ui_renderer, ui_element* const elem)
{
    if (ui_renderer->batch_count == ui_renderer->current_count)
    {
        draw_ui_batch(ui_renderer);
        ui_renderer->current_count = 0;
    }

    const unsigned int idx = (ui_renderer->current_count++) * 4;
    const v3f pos = elem->trans.position;
    const colourf col = elem->color;

    const vertex_data square_verts[] =
    {
        {{pos.x, pos.y, 0.0f}, col},
        {{pos.x, pos.y, 0.0f}, col},
        {{pos.x, pos.y, 0.0f}, col},
        {{pos.x, pos.y, 0.0f}, col}
    };

    vertex_data* const dest = &ui_renderer->vertices[idx];
    memcpy(dest, &square_verts, sizeof(vertex_data));
}

void initialize_ui_renderer(ui_batch_renderer* const ui_renderer, unsigned int batch_count)
{
    const unsigned int max_vertices = batch_count * 4;
    const unsigned int max_indices  = batch_count * 6;

    const size_t vertex_data_size = sizeof(vertex_data) * max_vertices;
    const size_t indice_data_size = sizeof(unsigned int) * max_indices;

    ui_renderer->batch_count = batch_count;
    ui_renderer->vertices = (vertex_data*)memory_allocate(vertex_data_size);

    glGenVertexArrays(1, &ui_renderer->VAO);
    glBindVertexArray(ui_renderer->VAO);

    glGenBuffers(1, &ui_renderer->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, ui_renderer->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_data_size, NULL, GL_DYNAMIC_DRAW);

    unsigned int *indices = (unsigned int*)memory_allocate(indice_data_size);
    unsigned int offset = 0;
    for (unsigned int i = 0; i < max_indices; i+=6)
    {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;
        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;
        offset += 4;
    }

    glGenBuffers(1, &ui_renderer->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ui_renderer->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_data_size, indices, GL_STATIC_DRAW);

    memory_free(indices);
}
