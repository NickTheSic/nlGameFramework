#include "nl_rr_linerenderer.h"
#include "private/nl_memory.h"
#include "private/gl/nl_gl.h"

void init_line_renderer(nl_rr_linerenderer* const renderer)
{
    renderer->max_vertices = 30;
    renderer->num_vertices = 0;

    const size_t vertices_memory = renderer->max_vertices*sizeof(nl_linerenderer_vertexdata);
    
    renderer->vertices = memory_allocate(vertices_memory);

    renderer->shader = load_shader_from_files("lines_shader.vs", "lines_shader.fs");
    use_shader_program(renderer->shader);

    glGenVertexArrays(1, &renderer->vao);
    glBindVertexArray(renderer->vao);

    glGenBuffers(1, &renderer->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_memory, renderer->vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(nl_linerenderer_vertexdata), (void*)0);
    glEnableVertexAttribArray(0);
}

void free_line_renderer(nl_rr_linerenderer* const renderer)
{
    memory_free(renderer->vertices);

    glDeleteVertexArrays(1, &renderer->vao);
    glDeleteBuffers(1, &renderer->vbo);
    glDeleteProgram(renderer->shader);
}

internal_function void flush_line_renderer(nl_rr_linerenderer* const renderer)
{
    glBufferSubData(GL_ARRAY_BUFFER, 0, renderer->num_vertices*sizeof(v3f), renderer->vertices);
    glDrawArrays(GL_LINES, 0, renderer->num_vertices);

    renderer->num_vertices = 0;
}

void begin_linerender_draw(nl_rr_linerenderer* const renderer)
{
    use_shader_program(renderer->shader);
    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
}

void add_linerender_line(nl_rr_linerenderer* const renderer, v3f* points, int num_points)
{
    if (renderer->num_vertices + num_points >= renderer->max_vertices)
    {
        flush_line_renderer(renderer);
    }

    const int current_index = renderer->num_vertices;
    
    for (int i = 0; i < num_points; ++i)
    {
        renderer->vertices[current_index+i].pos = points[i];
    }
    
    renderer->num_vertices += num_points;
}

void end_linerender_draw(nl_rr_linerenderer* const renderer)
{
    flush_line_renderer(renderer);
}
