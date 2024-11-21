#include "simple_sprite.h"
#include "private/gl/nl_gl.h"
#include <math.h>

internal_function void generate_simple_sprite_using_vertices_and_indices(simple_sprite* const simple_sprite, const sprite_vertices* const vertices, int vertice_count, const unsigned int* const indices, unsigned int indice_count)
{
    const size_t vertices_data_size = sizeof(sprite_vertices) * vertice_count;
    const size_t indice_data_size = indice_count * sizeof(unsigned int);

    simple_sprite->vertices = (sprite_vertices*)memory_allocate(vertices_data_size);
    memcpy(simple_sprite->vertices, vertices, vertices_data_size);

    simple_sprite->indices = (unsigned int*)memory_allocate(indice_data_size);
    memcpy(simple_sprite->indices, indices, indice_data_size);

    simple_sprite->vertice_count = vertice_count;
    simple_sprite->indice_count = indice_count;

    glGenVertexArrays(1, &simple_sprite->VAO);
    glBindVertexArray(simple_sprite->VAO);

    glGenBuffers(1, &simple_sprite->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, simple_sprite->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_data_size, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &simple_sprite->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, simple_sprite->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_data_size, indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(sprite_vertices), (void*)offsetof(sprite_vertices, pos));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void render_single_simple_sprite(simple_sprite* simple_sprite)
{
    glBindVertexArray(simple_sprite->VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, simple_sprite->EBO);

    glDrawElements(GL_TRIANGLES, simple_sprite->indice_count, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void free_simple_sprite(simple_sprite* const simple_sprite)
{
    memory_free(simple_sprite->vertices);
    memory_free(simple_sprite->indices);

    // gl free buffers here
    glDeleteBuffers(1, &simple_sprite->EBO);
    glDeleteBuffers(1, &simple_sprite->VBO);
    glDeleteBuffers(1, &simple_sprite->VAO);
}

void generate_rectangle_simple_sprite(simple_sprite* const simple_sprite, float width, float height)
{
    sprite_vertices square_vertices[] =
    {
        {{0.0f,  0.0f,   0.0f}},
        {{width, 0.0f,   0.0f}},
        {{width, height, 0.0f}},
        {{0.0f,  height, 0.0f}},
    };

    static const unsigned int indices[] = {0,1,2,0,2,3};

    generate_simple_sprite_using_vertices_and_indices(simple_sprite, square_vertices, 4, indices, 6);
}

void generate_square_simple_sprite(simple_sprite* const simple_sprite, float width)
{
    generate_rectangle_simple_sprite(simple_sprite, width, width);
}

void load_texture_for_sprite(simple_sprite* const sprite, const char* filename)
{

}
