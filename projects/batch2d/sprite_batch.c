#include "sprite_batch.h"
#include "private/gl/nl_gl.h"

void init_batch(sprite_batch* const batch, unsigned int count)
{   
    const unsigned int vertice_count = count * 4;
    const unsigned int indice_count  = count * 6;

    const size_t vertice_data = vertice_count * sizeof(sprite_batch_vertex_data);
    const size_t indice_data  = indice_count  * sizeof(unsigned int);

    batch->max_count = count;
    batch->vertices = (sprite_batch_vertex_data*)memory_allocate(vertice_data);

    glGenVertexArrays(1, &batch->vao);
    glBindVertexArray(batch->vao);

    glGenBuffers(1, &batch->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertice_data, (void*)0, GL_DYNAMIC_DRAW);

    unsigned int *indices = (unsigned int*)memory_allocate(indice_data);
    unsigned int offset = 0;
    for (unsigned int i = 0; i < indice_count; i+=6)
    {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;
        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;
        offset += 4;
    }

    glGenBuffers(1, &batch->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_data, indices, GL_STATIC_DRAW);

    memory_free(indices);
}

void begin_render_batch(sprite_batch* const batch)
{
    glBindVertexArray(batch->vao);
    glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(sprite_batch_vertex_data), (void*)offsetof(sprite_batch_vertex_data, pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(sprite_batch_vertex_data), (void*)offsetof(sprite_batch_vertex_data, uv_coord));
    glEnableVertexAttribArray(1);
}

internal_function void render_batch(sprite_batch* const batch)
{
    glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, batch->current_count*4*sizeof(sprite_batch_vertex_data), batch->vertices);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->ebo);
    glDrawElements(GL_TRIANGLES, batch->current_count*6, GL_UNSIGNED_INT, 0);

    batch->current_count = 0;
}

void add_to_render_batch(sprite_batch* const batch, v2f pos)
{
    if (batch->current_count == batch->max_count)
    {
        render_batch(batch);
    }

    const unsigned int current_idx = batch->current_count * 4;

    const float SQUARE_HALF_SIZE = 50.f;
    const sprite* const sp = get_sprite(0);
    sprite_batch_vertex_data square_verts[4];

    if (sp != 0)
    {
        square_verts[0] = (sprite_batch_vertex_data){{pos.x + -SQUARE_HALF_SIZE, pos.y + -SQUARE_HALF_SIZE, 0.0f}, (v2f){sp->bl_coord.x, sp->bl_coord.y}};
        square_verts[1] = (sprite_batch_vertex_data){{pos.x +  SQUARE_HALF_SIZE, pos.y + -SQUARE_HALF_SIZE, 0.0f}, (v2f){sp->tr_coord.x, sp->bl_coord.y}};
        square_verts[2] = (sprite_batch_vertex_data){{pos.x +  SQUARE_HALF_SIZE, pos.y +  SQUARE_HALF_SIZE, 0.0f}, (v2f){sp->tr_coord.x, sp->tr_coord.y}};
        square_verts[3] = (sprite_batch_vertex_data){{pos.x + -SQUARE_HALF_SIZE, pos.y +  SQUARE_HALF_SIZE, 0.0f}, (v2f){sp->bl_coord.x, sp->tr_coord.y}};
    }
    else
    {
        square_verts[0] = (sprite_batch_vertex_data){{pos.x + -SQUARE_HALF_SIZE, pos.y + -SQUARE_HALF_SIZE, 0.0f}, (v2f){0.f,0.f}};
        square_verts[1] = (sprite_batch_vertex_data){{pos.x +  SQUARE_HALF_SIZE, pos.y + -SQUARE_HALF_SIZE, 0.0f}, (v2f){0.f,1.f}};
        square_verts[2] = (sprite_batch_vertex_data){{pos.x +  SQUARE_HALF_SIZE, pos.y +  SQUARE_HALF_SIZE, 0.0f}, (v2f){1.f,1.f}};
        square_verts[3] = (sprite_batch_vertex_data){{pos.x + -SQUARE_HALF_SIZE, pos.y +  SQUARE_HALF_SIZE, 0.0f}, (v2f){1.f,0.f}};
    }

    sprite_batch_vertex_data* const dest = &batch->vertices[current_idx];
    memcpy(dest, &square_verts, sizeof(sprite_batch_vertex_data)*4);

    batch->current_count++;
}

void end_render_batch(sprite_batch* const batch)
{
    render_batch(batch);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void free_batch(sprite_batch* const batch)
{
    memory_free(batch->vertices);
}
