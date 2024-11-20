#include "batch2d.h"
#include "private/gl/nl_gl.h"

#include "grid.h"

void init_batch(batch2d* const batch, unsigned int count)
{   
    const unsigned int vertice_count = count * 4;
    const unsigned int indice_count  = count * 6;

    const size_t vertice_data = vertice_count * sizeof(batch_vertex_data);
    const size_t indice_data  = indice_count  * sizeof(unsigned int);

    batch->max_count = count;
    batch->vertices = (batch_vertex_data*)memory_allocate(vertice_data);

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

void begin_render_batch(batch2d* const batch)
{
    glBindVertexArray(batch->vao);
    glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(batch_vertex_data), (void*)offsetof(batch_vertex_data, pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(batch_vertex_data), (void*)offsetof(batch_vertex_data, col));
    glEnableVertexAttribArray(1);
}

internal_function void render_batch(batch2d* const batch)
{
    glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, batch->current_count*4*sizeof(batch_vertex_data), batch->vertices);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->ebo);
    glDrawElements(GL_TRIANGLES, batch->current_count*6, GL_UNSIGNED_INT, 0);

    batch->current_count = 0;
}

void add_to_render_batch(batch2d* const batch, v2f pos, colour col, float size)
{
    if (batch->current_count == batch->max_count)
    {
        render_batch(batch);
    }

    const unsigned int current_idx = batch->current_count * 4;

    batch_vertex_data square_verts[4];
    square_verts[0] = (batch_vertex_data){{pos.x, pos.y, 0.0f}, col};
    square_verts[1] = (batch_vertex_data){{pos.x +  size, pos.y, 0.0f}, col};
    square_verts[2] = (batch_vertex_data){{pos.x +  size, pos.y +  size, 0.0f}, col};
    square_verts[3] = (batch_vertex_data){{pos.x, pos.y +  size, 0.0f}, col};

    batch_vertex_data* const dest = &batch->vertices[current_idx];
    memcpy(dest, &square_verts, sizeof(batch_vertex_data)*4);

    batch->current_count++;
}

void end_render_batch(batch2d* const batch)
{
    render_batch(batch);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void free_batch(batch2d* const batch)
{
    memory_free(batch->vertices);
}
