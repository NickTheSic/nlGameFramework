#include "sprite_renderer.h"
#include "private/nl_memory.h"
#include "private/gl/nl_gl.h"

// should be variable I pass in or something instead of global
#define MAX_SPRITES_FOR_BATCHING 1

void init_sprite_renderer(sprite_renderer *const renderer)
{
    renderer->shader = load_shader_from_files("sprite_2d_00.vs", "sprite_2d_00.fs");
    glUseProgram(renderer->shader); 

    const size_t vertice_memory_size = sizeof(sprite_vertex_data)*4*MAX_SPRITES_FOR_BATCHING;
    const size_t indice_memory_size = sizeof(unsigned int)*6*MAX_SPRITES_FOR_BATCHING;
    
    renderer->vertices = (sprite_vertex_data*)bump_alloc(get_transient_bump_allocator(), vertice_memory_size);
    renderer->max_batch_count = MAX_SPRITES_FOR_BATCHING;

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
    glDeleteBuffers(1, &renderer->ebo);
    glDeleteBuffers(1, &renderer->vbo);
    glDeleteVertexArrays(1, &renderer->vao);
    glDeleteTextures(1, &renderer->texture_id);
}

void create_sprite_data(sprite_data* const sprite, const char* asset)
{
    
}

internal_function void flush_sprite_batch(sprite_renderer *const renderer)
{
    glBufferSubData(GL_ARRAY_BUFFER, 0, renderer->current_batch_count*sizeof(sprite_vertex_data)*4, renderer->vertices);
    glDrawElements(GL_TRIANGLES, renderer->current_batch_count*6, GL_UNSIGNED_INT, 0);
    renderer->current_batch_count = 0;
}

void begin_sprite_batch(sprite_renderer *const renderer)
{
    glUseProgram(renderer->shader);

    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->ebo);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderer->texture_id);
}

void end_sprite_batch(sprite_renderer *const renderer)
{
    flush_sprite_batch(renderer);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void add_sprite_to_batch(sprite_renderer *const renderer, sprite_data* const sprite)
{
    if (renderer->current_batch_count+1 > renderer->max_batch_count)
    {
        NL_LOG("Adding more sprites to batch than allowed, flushing early");
        flush_sprite_batch(renderer);
    }

    const int starting_index = renderer->current_batch_count * 4;

    // setup vertex 1
    {
        sprite_vertex_data* vd0 = &renderer->vertices[starting_index];
        vd0->pos.x = sprite->pos.x;
        vd0->pos.y = sprite->pos.y;
        vd0->uv.x  = sprite->texture_uv_bl.x;
        vd0->uv.y  = sprite->texture_uv_bl.y;
    }

    // setup vertex 2
    {
        sprite_vertex_data* vd1 = &renderer->vertices[starting_index+1];
        vd1->pos.x = sprite->pos.x + sprite->size.x;
        vd1->pos.y = sprite->pos.y;
        vd1->uv.x  = sprite->texture_uv_tr.x;
        vd1->uv.y  = sprite->texture_uv_bl.y;
    }

    // setup vertex 3
    {
        sprite_vertex_data* vd2 = &renderer->vertices[starting_index+2];
        vd2->pos.x = sprite->pos.x + sprite->size.x;
        vd2->pos.y = sprite->pos.y + sprite->size.y;
        vd2->uv.x  = sprite->texture_uv_tr.x;
        vd2->uv.y  = sprite->texture_uv_tr.y;
    }

    // setup vertex 4
    {
        sprite_vertex_data* vd3 = &renderer->vertices[starting_index+3];
        vd3->pos.x = sprite->pos.x;
        vd3->pos.y = sprite->pos.y + sprite->size.y;
        vd3->uv.x  = sprite->texture_uv_bl.x;
        vd3->uv.y  = sprite->texture_uv_tr.y;
    }

    renderer->current_batch_count+=1;
}
