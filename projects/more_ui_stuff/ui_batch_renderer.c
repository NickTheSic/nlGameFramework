// included in more_ui_stuff after the normal includes to keep this file separate for clarity


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

void add_element_to_ui_renderer(ui_batch_renderer* const ui_renderers)
{

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
