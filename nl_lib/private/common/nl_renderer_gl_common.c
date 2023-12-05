#include "../nl_renderer.h"
#include "../nl_debug.h"
#include "../nl_gl.h"

int initialize_renderer_subsystem()
{
    if (!initialize_gl())
    {
        return 0;
    }

    return 1;
}

void begin_render_frame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void end_render_frame()
{
    renderer_swap_buffers();
}

void set_background_colour_4f(float r, float g, float b, float a)
{
    glClearColor(r,g,b,a);
}

void set_viewport_size(int width, int height)
{
    glViewport(0, 0, width, height);
}

void set_depth_test_enabled(int enabled)
{
    if (enabled == 1)
    {
        glEnable(GL_DEPTH_TEST); 
    } 
    else
    {
        glDisable(GL_DEPTH_TEST); 
    }
}

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
    glBufferData(GL_ARRAY_BUFFER, vertices_data_size, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &mesh->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indice_count, indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)0);
    glEnableVertexAttribArray(0);  

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)12);
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

void setup_vertex_atrributes(size_t data_size, vertex_atrribute_info* const attrib_info, const int attrib_count)
{
    for (int i = 0; i < attrib_count - 1; ++i)
    {

        glVertexAttribPointer(
            i, 
            attrib_info[i].value_count, 
            attrib_info[i].type, 
            attrib_info[i].normalized, 
            data_size, 
            (const void*)attrib_info[i].offset // hate this but might be needed and hopefully doesn't cause problems
        );
        
        glEnableVertexAttribArray(i);  
    }
}
