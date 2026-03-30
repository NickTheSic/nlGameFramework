#include "sprite_renderer.h"
#include "private/nl_memory.h"
#include "private/gl/nl_gl.h"

#define MAX_SPRITES_FOR_BATCHING 20

void init_sprite_renderer(sprite_renderer *const renderer)
{
    const size_t vertice_memory_size = sizeof(sprite_vertex_data)*4*MAX_SPRITES_FOR_BATCHING;
    const size_t indice_memory_size = sizeof(unsigned int)*6*MAX_SPRITES_FOR_BATCHING;
    
    renderer->vertices = (sprite_vertex_data*)bump_alloc(get_transient_bump_allocator(), vertice_memory_size);
    
    //initialize sprite renderer
    glGenVertexArrays(1, &renderer->vao);
    glGenBuffers(1, &renderer->vbo);
    glGenBuffers(1, &renderer->ebo);

    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertice_memory_size, renderer->vertices, GL_DYNAMIC_DRAW);

    unsigned int* indices = (unsigned int*)bump_alloc(get_temporary_bump_allocator(), indice_memory_size);

    int indice_offset = 0;
    for (int i = 0; i < MAX_SPRITES_FOR_BATCHING*6; i +=6)
    {
        indices[i]   = 0+indice_offset;
        indices[i+1] = 1+indice_offset;
        indices[i+2] = 3+indice_offset;
        indices[i+3] = 1+indice_offset;
        indices[i+4] = 2+indice_offset;
        indices[i+5] = 3+indice_offset;

        indice_offset += 4;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_memory_size, indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(v2f), (void*)offsetof(sprite_vertex_data, pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(v2f), (void*)offsetof(sprite_vertex_data, uv));
    glEnableVertexAttribArray(1);
    
    flush_bump_allocator(get_temporary_bump_allocator());
}

void free_sprite_renderer(sprite_renderer *const renderer)
{
    //free the sprite stuff
}

internal_function void flush_sprite_batch(sprite_renderer *const renderer)
{
    // bind and call glDrawElements
}

void begin_sprite_batch(sprite_renderer *const renderer)
{
    // set shader 
}

void end_sprite_batch(sprite_renderer *const renderer)
{
    flush_sprite_batch(renderer);
}

void add_sprite_to_batch(sprite_renderer *const renderer, sprite_data* const sprite)
{
    if (0)
    {
        flush_sprite_batch(renderer);
    }
}
