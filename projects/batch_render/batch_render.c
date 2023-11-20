#include "nl_lib.h"
#include "private/nl_gl.h"

#include <string.h>

const char* vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"out vec4 oColor;                                      \n"
"void main() {                                         \n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);   \n"
"   oColor = aColor;                                   \n"
"}                                                     \0";

const char* fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                   \n"
"in vec4 oColor;                                       \n"
"void main() {                                         \n"
"    FragColor = oColor;                               \n"
"}                                                     \0";

typedef struct batch_render3d batch_render;
struct batch_render3d
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    unsigned int max_vertices;
    unsigned int max_indices;

    unsigned int current_vertices;
    unsigned int current_indices;

    vertex_data* vertex_batch;
    
    // this could be wasted space and cycles in a 2D game where all indices are 0,1,2,2,3,0 for a sprite...
    // Rewrite it when I get to it I guess!
    unsigned int* indice_batch;
};

void init_batch_renderer(batch_render* const batch, unsigned int max_vertices, unsigned int max_indices)
{
    batch->max_vertices = max_vertices;
    batch->max_indices = max_indices;

    size_t vertex_data_size = max_vertices * sizeof(vertex_data);
    size_t indice_data_size = sizeof(unsigned int) * max_indices;

    batch->vertex_batch = (vertex_data*)memory_allocate(vertex_data_size);
    batch->indice_batch = (unsigned int*)memory_allocate(indice_data_size);

    glGenVertexArrays(1, &batch->VAO);
    glBindVertexArray(batch->VAO);

    glGenBuffers(1, &batch->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, batch->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_data_size, 0, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &batch->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_data_size, 0, GL_DYNAMIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)0);
    glEnableVertexAttribArray(0);  

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)12);
    glEnableVertexAttribArray(1);  

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void start_render_batch(batch_render* const batch)
{
    glBindVertexArray(batch->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, batch->VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->EBO);
}

void end_render_batch(batch_render* const batch)
{
    glBindVertexArray(batch->VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, batch->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_data) * batch->current_vertices, batch->vertex_batch);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * batch->current_indices, batch->indice_batch);

    glDrawElements(GL_TRIANGLES, batch->current_indices, GL_UNSIGNED_INT, 0);

    batch->current_indices = 0;
    batch->current_vertices = 0;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void add_mesh_to_batch(batch_render* const batch, const mesh* const mesh)
{
    unsigned int current_verts = batch->current_vertices;
    unsigned int current_index = batch->current_indices;

    if ((current_verts + mesh->vertice_count > batch->max_vertices) || (current_index + mesh->indice_count > batch->max_indices))
    {
        end_render_batch(batch);
    }

    vertex_data* vertex_buffer = &batch->vertex_batch[current_verts];
    memcpy(vertex_buffer, mesh->vertices, sizeof(vertex_data) * mesh->vertice_count);

    unsigned int* index_buffer = &batch->indice_batch[current_index];
    for (unsigned int i = 0; i < mesh->indice_count; i++)
    {
        index_buffer[i] = current_index + mesh->indices[i];
    }

    batch->current_indices += mesh->indice_count;
    batch->current_vertices += mesh->vertice_count;    
}

batch_render batch = {0};


mesh triangle;
mesh square;

vertex_data vertices[] = 
{
    {{-0.5f, -0.5f, 1.0f}, {1.0f, 0.5f, 0.8f, 1.0f}},
    {{ 0.5f, -0.5f, 1.0f}, {1.0f, 0.5f, 0.8f, 1.0f}},
    {{ 0.0f,  0.5f, 1.0f}, {1.0f, 0.5f, 0.8f, 1.0f}}
};

#define SPOS 0.4f
vertex_data square_verts[] =
{
    {{-SPOS, -SPOS, 0.0f}, {1.0f, 0.5f, 0.8f, 1.0f}},
    {{ SPOS, -SPOS, 0.0f}, {0.8f, 1.0f, 0.5f, 1.0f}},
    {{ SPOS,  SPOS, 0.0f}, {0.5f, 0.8f, 1.0f, 1.0f}},
    {{-SPOS,  SPOS, 0.0f}, {0.7f, 0.2f, 0.0f, 1.0f}}
};

unsigned int square_indices[] =
{
    0,1,2,
    2,3,0
};

unsigned int shader_program = {0};

void app_specific_init(void)
{
    init_batch_renderer(&batch, 30, 30);

    generate_mesh_using_vertices_and_indices(&triangle, vertices, 3, square_indices, 3);
    generate_mesh_using_vertices_and_indices(&square, square_verts, 4, square_indices, 6);
    
    shader_program = create_shader_program(vert_shader_code, fragment_shader_code);
    use_shader_program(shader_program);
}

void app_specific_update(double dt)
{
    (void)dt;
    
    use_shader_program(shader_program);

    add_mesh_to_batch(&batch, &triangle);
    add_mesh_to_batch(&batch, &square);
    end_render_batch(&batch);
}
