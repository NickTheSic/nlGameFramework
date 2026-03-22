#include "nl_rr_linerenderer.h"
#include "private/nl_memory.h"
#include "private/gl/nl_gl.h"

void init_line_renderer(nl_rr_linerenderer* const renderer)
{
    renderer->max_vertices = 30;
    renderer->num_vertices = 0;

    const size_t vertices_memory = renderer->max_vertices*sizeof(nl_linerenderer_vertexdata);
    
    renderer->vertices = (nl_linerenderer_vertexdata*)bump_alloc(get_transient_bump_allocator(), vertices_memory);

    renderer->shader = load_shader_from_files("lines_shader.vs", "lines_shader.fs");
    use_shader_program(renderer->shader);

    glGenVertexArrays(1, &renderer->vao);
    glBindVertexArray(renderer->vao);

    glGenBuffers(1, &renderer->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_memory, renderer->vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(nl_linerenderer_vertexdata), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(nl_linerenderer_vertexdata), offsetof(nl_linerenderer_vertexdata, pos));
    glEnableVertexAttribArray(1);
}

void free_line_renderer(nl_rr_linerenderer* const renderer)
{
    glDeleteVertexArrays(1, &renderer->vao);
    glDeleteBuffers(1, &renderer->vbo);
    glDeleteProgram(renderer->shader);
}

internal_function void flush_line_renderer(nl_rr_linerenderer* const renderer)
{
    glBufferSubData(GL_ARRAY_BUFFER, 0, renderer->num_vertices*sizeof(v3f), renderer->vertices);
    //glDrawArrays(GL_LINE_STRIP, 0, renderer->num_vertices); //Strips are pretty cool
    //glDrawArrays(GL_LINE_LOOP, 0, renderer->num_vertices);
    
    glDrawArrays(GL_LINES, 0, renderer->num_vertices);

    renderer->num_vertices = 0;
}

void begin_linerender_draw(nl_rr_linerenderer* const renderer)
{
    use_shader_program(renderer->shader);
    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
}

void add_linerender_points_coloured(nl_rr_linerenderer* const renderer, v3f* points, int num_points, colour col)
{
    if (renderer->max_vertices < num_points)
    {
        DO_ONCE(NL_LOG("NL_LINERENDERER: Number of points is greater than our max vertices! Splitting the draw"));

        add_linerender_points_coloured(renderer, points, renderer->max_vertices, col);
        points = points + renderer->max_vertices;
        num_points -= renderer->max_vertices;
    }

    if (renderer->num_vertices + num_points >= renderer->max_vertices)
    {
        flush_line_renderer(renderer);
    }

    const int current_index = renderer->num_vertices;
    
    for (int i = 0; i < num_points; ++i)
    {
        renderer->vertices[current_index+i].pos = points[i];
        renderer->vertices[current_index+i].col = col;
    }
    
    renderer->num_vertices += num_points;
}

void add_linerender_points(nl_rr_linerenderer* const renderer, v3f* points, int num_points)
{
    add_linerender_points_coloured(renderer, points, num_points, COLOUR_BLACK);
}

void end_linerender_draw(nl_rr_linerenderer* const renderer)
{
    flush_line_renderer(renderer);
}
