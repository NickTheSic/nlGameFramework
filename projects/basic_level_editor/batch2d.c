#include "batch2d.h"
#include "private/gl/nl_gl.h"

#include "grid.h"

void init_batch(batch2d* const _batch, unsigned int count)
{   
    const unsigned int vertice_count = count * 4;
    const unsigned int indice_count  = count * 6;

    const size_t vertice_data = vertice_count * sizeof(batch_vertex_data);
    const size_t indice_data  = indice_count  * sizeof(unsigned int);

    _batch->max_count = count;
    _batch->vertices = (batch_vertex_data*)memory_allocate(vertice_data);

    glGenVertexArrays(1, &_batch->vao);
    glBindVertexArray(_batch->vao);

    glGenBuffers(1, &_batch->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _batch->vbo);
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

    glGenBuffers(1, &_batch->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _batch->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_data, indices, GL_STATIC_DRAW);

    memory_free(indices);
}

void begin_render_batch(batch2d* const _batch)
{
    glBindVertexArray(_batch->vao);
    glBindBuffer(GL_ARRAY_BUFFER, _batch->vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(batch_vertex_data), (void*)offsetof(batch_vertex_data, pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(batch_vertex_data), (void*)offsetof(batch_vertex_data, col));
    glEnableVertexAttribArray(1);
}

internal_function void render_batch(batch2d* const _batch)
{
    glBindBuffer(GL_ARRAY_BUFFER, _batch->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, _batch->current_count*4*sizeof(batch_vertex_data), _batch->vertices);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _batch->ebo);
    glDrawElements(GL_TRIANGLES, _batch->current_count*6, GL_UNSIGNED_INT, 0);

    _batch->current_count = 0;
}

void add_to_render_batch(batch2d* const _batch, v2f pos, colour col, float size)
{
    if (_batch->current_count == _batch->max_count)
    {
        render_batch(_batch);
    }

    const unsigned int current_idx = _batch->current_count * 4;

    batch_vertex_data square_verts[4];
    square_verts[0] = (batch_vertex_data){{pos.x, pos.y, 0.0f}, col};
    square_verts[1] = (batch_vertex_data){{pos.x +  size, pos.y, 0.0f}, col};
    square_verts[2] = (batch_vertex_data){{pos.x +  size, pos.y +  size, 0.0f}, col};
    square_verts[3] = (batch_vertex_data){{pos.x, pos.y +  size, 0.0f}, col};

    batch_vertex_data* const dest = &_batch->vertices[current_idx];
    memcpy(dest, &square_verts, sizeof(batch_vertex_data)*4);

    _batch->current_count++;
}

void end_render_batch(batch2d* const _batch)
{
    render_batch(_batch);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void free_batch(batch2d* const _batch)
{
    memory_free(_batch->vertices);
}
