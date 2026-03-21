#ifndef __NL_RR_LINERENDERER_H__
#define __NL_RR_LINERENDERER_H__

#include "private/nl_math.h" //so I can include v3f.  Maybe I make a types header?

typedef struct nl_linerenderer_vertexdata nl_linerenderer_vertexdata;
struct nl_linerenderer_vertexdata
{
    v3f pos;
    //colour col;
};

typedef struct nl_rr_linerenderer nl_rr_linerenderer;
struct nl_rr_linerenderer
{
    nl_linerenderer_vertexdata* vertices;
    int max_vertices;
    int num_vertices;

    unsigned int vao;
    unsigned int vbo;
    unsigned int shader;
};

void init_line_renderer(nl_rr_linerenderer* const renderer);
void free_line_renderer(nl_rr_linerenderer* const renderer);

void begin_linerender_draw(nl_rr_linerenderer* const renderer);
void add_linerender_line(nl_rr_linerenderer* const renderer, v3f* points, int num_points);
void end_linerender_draw(nl_rr_linerenderer* const renderer);

#endif//__NL_RR_LINERENDERER_H__