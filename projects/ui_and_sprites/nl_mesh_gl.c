#include "nl_mesh.h"
#include "private/gl/nl_gl.h"

#include "math.h"   // cos/sin
#include "string.h" // memcpy

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
    glDeleteBuffers(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);
    glDeleteBuffers(1, &mesh->EBO);
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

void generate_circle_mesh(mesh* const mesh, float radius, int segments)
{
    colourf col = COLOURF_RED;
    unsigned int vertice_count = segments + 1;
    unsigned int indice_count = segments * 3 - 3;

    vertex_data* data = memory_allocate(sizeof(vertex_data) * vertice_count);
    unsigned int* indices = memory_allocate(sizeof(unsigned int) * indice_count);

    if (data == 0 || indices == 0)
    {
        NL_LOG("Unable to allocate memory for a circle mesh. Mesh not being created");
        return;
    }

    data[0].pos = (v3f){0.0f,0.0f,0.0f};
    data[0].color = col;
    float angle_diff = 2 * 3.1415f / (float)segments;
    for (unsigned int i = 0; i < vertice_count-1; ++i)
    {
        const float x = cosf( angle_diff * i ) * radius;
        const float y = sinf( angle_diff * i ) * radius;
        const int idx = i+1;
        data[idx].pos.x = x;
        data[idx].pos.y = y;
        data[idx].pos.z = 0.0f;
        data[idx].color = col;
    }
    
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    unsigned int start = 3;
    for (unsigned int i = 3; i < indice_count; i+=3)
    {
        indices[i] = 0;
        indices[i+1] = start-1;
        indices[i+2] = start;
        ++start;
    }
    indices[indice_count-1] = 1;

    generate_mesh_using_vertices_and_indices(mesh, data, segments, indices, indice_count);

    memory_free(indices);
    memory_free(data);
}

