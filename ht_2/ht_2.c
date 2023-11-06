#include "nl_lib.h"
#include "nl_gl.h"

#if defined __EMSCRIPTEN__
#define SHADER_VERSION_HEADER "#version 300 es \n precision mediump float; \n"
#else
#define SHADER_VERSION_HEADER  "#version 330 core\n"
#endif

const char* vert_shader_code =
SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"out vec4 oColor;                                      \n"
"void main() {                                         \n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);   \n"
"   oColor = aColor;                                   \n"
"}                                                     \0";

const char* fragment_shader_code =
SHADER_VERSION_HEADER
"out vec4 FragColor;                                   \n"
"in vec4 oColor;                                       \n"
"void main() {                                         \n"
"    FragColor = oColor;                               \n"
"}                                                     \0";

typedef struct vertex_data vertex_data;
struct vertex_data
{
    v3f pos;
    colourf color;
};

typedef struct mesh mesh;
struct mesh
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    vertex_data* vertices;
};

void generate_mesh_from_vertices_count(mesh* mesh, vertex_data* vertices, int vertice_count)
{
    glGenVertexArrays(1, &mesh->VAO);
    glBindVertexArray(mesh->VAO);

    size_t vertices_data_size = sizeof(vertex_data) * vertice_count;

    glGenBuffers(1, &mesh->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_data_size, vertices, GL_STATIC_DRAW);

    mesh->vertices = (vertex_data*)memory_allocate(vertices_data_size);
    for (int i = 0; i < vertice_count; ++i)
    {
        mesh->vertices[i].pos.x = vertices[i].pos.x;
        mesh->vertices[i].pos.y = vertices[i].pos.y;
        mesh->vertices[i].pos.z = vertices[i].pos.z;
    }
}

void generate_mesh_from_vertices_indices_count(mesh* mesh, vertex_data* vertices, int vertice_count, unsigned int* indices, int indice_count)
{
    glGenVertexArrays(1, &mesh->VAO);
    glBindVertexArray(mesh->VAO);

    size_t vertices_data_size = sizeof(vertex_data) * vertice_count;

    glGenBuffers(1, &mesh->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_data_size, vertices, GL_STATIC_DRAW);

    mesh->vertices = (vertex_data*)memory_allocate(vertices_data_size);
    for (int i = 0; i < vertice_count; ++i)
    {
        mesh->vertices[i].pos.x = vertices[i].pos.x;
        mesh->vertices[i].pos.y = vertices[i].pos.y;
        mesh->vertices[i].pos.z = vertices[i].pos.z;
    }

    glGenBuffers(1, &mesh->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indice_count, indices, GL_STATIC_DRAW); 
}

mesh triangle;
mesh square;

vertex_data vertices[] = 
{
    {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.5f, 0.8f, 1.0f}},
    {{ 0.5f, -0.5f, 0.0f}, {0.8f, 1.0f, 0.5f, 1.0f}},
    {{ 0.0f,  0.5f, 0.0f}, {0.5f, 0.8f, 1.0f, 1.0f}}
};

vertex_data square_verts[] =
{
    {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.5f, 0.8f, 1.0f}},
    {{ 0.5f, -0.5f, 0.0f}, {0.8f, 1.0f, 0.5f, 1.0f}},
    {{ 0.5f,  0.5f, 0.0f}, {0.5f, 0.8f, 1.0f, 1.0f}},
    {{-0.5f,  0.5f, 0.0f}, {0.7f, 0.2f, 0.0f, 1.0f}}
};

unsigned int square_indices[] =
{
    0,1,2,
    2,3,0
};

// Required - Could be renderer or material
unsigned int shader_program;

void app_specific_init(void)
{
    //generate_mesh_from_vertices_count(&triangle, vertices, 3);
    generate_mesh_from_vertices_indices_count(&square, square_verts, 4, square_indices, 6);
    
    shader_program = create_shader_program(vert_shader_code, fragment_shader_code);
    glUseProgram(shader_program);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)0);
    glEnableVertexAttribArray(0);  

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)12);
    glEnableVertexAttribArray(1);  
}

void app_specific_update(double dt)
{
    glUseProgram(shader_program);

    //glBindVertexArray(triangle.VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, square.EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
