#include "../nl_mesh.h"
#include "../nl_gl.h"


void generate_mesh_using_vertices_and_indices(mesh* const mesh, const vertex_data* const vertices, int vertice_count, const unsigned int* const indices, unsigned int indice_count)
{
    const size_t vertices_data_size = sizeof(vertex_data) * vertice_count;
    const size_t indice_data_size = indice_count * sizeof(unsigned int);

    mesh->vertices = (vertex_data*)memory_allocate(vertices_data_size);
    memcpy(mesh->vertices, vertices, vertices_data_size);

    mesh->indices = (unsigned int*)memory_allocate(indice_data_size);
    memcpy(mesh->indices, indices, indice_data_size);

    mesh->vertice_count = vertice_count;
    mesh->indice_count = indice_count;

    glGenVertexArrays(1, &mesh->VAO);
    glBindVertexArray(mesh->VAO);

    glGenBuffers(1, &mesh->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_data_size, vertices, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &mesh->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_data_size, indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, pos));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, color));
    glEnableVertexAttribArray(1);  

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void render_single_mesh(mesh* mesh)
{
    glBindVertexArray(mesh->VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);

    glDrawElements(GL_TRIANGLES, mesh->indice_count, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void free_mesh(mesh* const mesh)
{
    memory_free(mesh->vertices);
    memory_free(mesh->indices);

    // gl free buffers here
}

void generate_rectangle_mesh(mesh* const mesh, float width, float height, colourf col)
{
    vertex_data square_vertices[] =
    {
        {{0.0f,  0.0f,   0.0f}, col},
        {{width, 0.0f,   0.0f}, col},
        {{width, height, 0.0f}, col},
        {{0.0f,  height, 0.0f}, col},
    };

    static const unsigned int indices[] = {0,1,2,0,2,3};

    generate_mesh_using_vertices_and_indices(mesh, square_vertices, 4, indices, 6);
}

void generate_square_mesh(mesh* const mesh, float width, colourf col)
{
    generate_rectangle_mesh(mesh, width, width, col);
}

