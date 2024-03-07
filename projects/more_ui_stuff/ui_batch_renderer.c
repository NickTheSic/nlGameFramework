// included in more_ui_stuff after the normal includes to keep this file separate for clarity

#include <string.h> // memcpy

#define SQUARE_HALF_SIZE 100.0f

static unsigned int shader_program = {0};

static const char* ui_vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec2 aVertexPos;                  \n"
"layout (location = 1) in vec4 aColor;                      \n"
"layout (location = 2) in mat4 aWorldMat;                   \n"
"uniform mat4 uViewMat;                                     \n"
"out vec4 oColor;                                           \n"
"void main() {                                              \n"
"   vec4 worldPos = aWorldMat * vec4(aVertexPos, 0.0, 1.0); \n"
"   gl_Position = uViewMat * worldPos;                      \n"
"   oColor = aColor;                                        \n"
"}                                                          \0";

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

typedef struct ui_vertex_data ui_vertex_data;
struct ui_vertex_data
{
    v3f pos;
    colourf color;
    mat4x4f world_mat;
};

typedef struct ui_batch_renderer ui_batch_renderer;
struct ui_batch_renderer
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    
    unsigned int batch_count;
    unsigned int current_count;

    ui_vertex_data* vertices;
};

void ui_anchored_matrix(mat4x4f* const mat, ui_element* const o)
{
    create_identity_matrix(mat);

    const v2i screen_size = get_screen_size();
    transform2d trans = o->trans;
    float half_w = screen_size.x/2.0f;
    float half_h = screen_size.y/2.0f;
    trans.position.x += (half_w) + (o->anchor.x * half_w);
    trans.position.y += (half_h) + (o->anchor.y * half_h);
    create_srt_matrix_from_transform2d(mat, trans);
}

void free_ui_batch_renderer(ui_batch_renderer* const ui_renderer)
{
    memory_free(ui_renderer->vertices);
    ui_renderer->batch_count = 0;
}

void draw_ui_batch(ui_batch_renderer* const ui_renderer)
{
    glBindVertexArray(ui_renderer->VAO);
    use_shader_program(shader_program);

    const vertex_atrribute_info attribs[] = 
    {
        {3,  GL_FLOAT, GL_FALSE,  0},
        {4,  GL_FLOAT, GL_FALSE, 12},
        {16, GL_FLOAT, GL_FALSE, 28},
    };
    setup_vertex_atrributes(sizeof(ui_vertex_data), attribs, 3);

    const size_t ui_data_size = ui_renderer->current_count*4*sizeof(ui_vertex_data);
    glBindBuffer(GL_ARRAY_BUFFER, ui_renderer->VBO);
    glBufferSubData(GL_ARRAY_BUFFER,
                    0,
                    ui_data_size,
                    ui_renderer->vertices);

    ui_vertex_data* uivd = (ui_vertex_data*)memory_allocate(ui_data_size);
    glGetBufferSubData(GL_ARRAY_BUFFER, 0, ui_data_size, uivd);
    memory_free(uivd);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ui_renderer->EBO);
    glDrawElements(GL_TRIANGLES, ui_renderer->current_count*6, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    ui_renderer->current_count = 0;
}

void add_element_to_ui_renderer(ui_batch_renderer* const ui_renderer, ui_element* const elem, mat4x4f* const mat)
{
    if (ui_renderer->batch_count == ui_renderer->current_count)
    {
        draw_ui_batch(ui_renderer);
        ui_renderer->current_count = 0;
    }

    const unsigned int idx = ui_renderer->current_count * 4;
    ++ui_renderer->current_count;
    const colourf col = elem->color;

    const ui_vertex_data square_verts[] =
    {
        {{-SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, col, *mat},
        {{ SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, col, *mat},
        {{ SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, col, *mat},
        {{-SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, col, *mat}
    };

    ui_vertex_data* const dest = &ui_renderer->vertices[idx];
    memcpy(dest, &square_verts, sizeof(ui_vertex_data)*4);
}

void initialize_ui_renderer(ui_batch_renderer* const ui_renderer, unsigned int batch_count)
{
    shader_program = create_shader_program(ui_vert_shader_code, ui_fragment_shader_code);
    use_shader_program(shader_program);
    
    const unsigned int max_vertices = batch_count * 4;
    const unsigned int max_indices  = batch_count * 6;

    const size_t vertex_data_size = sizeof(ui_vertex_data) * max_vertices;
    const size_t indice_data_size = sizeof(unsigned int) * max_indices;

    ui_renderer->batch_count = batch_count;
    ui_renderer->vertices = (ui_vertex_data*)memory_allocate(vertex_data_size);

    glGenVertexArrays(1, &ui_renderer->VAO);
    glGenBuffers(1, &ui_renderer->VBO);
    glGenBuffers(1, &ui_renderer->EBO);

    glBindVertexArray(ui_renderer->VAO);
    const vertex_atrribute_info attribs[] = 
    {
        {3,  GL_FLOAT, GL_FALSE,  0},
        {4,  GL_FLOAT, GL_FALSE, 12},
        {16, GL_FLOAT, GL_FALSE, 28},
    };
    setup_vertex_atrributes(sizeof(ui_vertex_data), attribs, 3);

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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ui_renderer->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_data_size, indices, GL_STATIC_DRAW);

    memory_free(indices);
}
