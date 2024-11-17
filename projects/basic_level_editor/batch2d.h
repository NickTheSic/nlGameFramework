#ifndef __NL_BATCH2D_H__
#define __NL_BATCH2D_H__

#include <private/nl_colour.h>

static const char* batch_vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                   \n"
"layout (location = 1) in vec4 aCol;                   \n"
"uniform mat4 uViewMat;                                \n"
"uniform mat4 uProjMat;                                \n"
"out vec4 oColour;                                     \n"
"void main() {                                         \n"
"   vec4 viewPos = vec4(aPos, 1.0);                    \n"
"   gl_Position = uProjMat * uViewMat * viewPos;       \n"
"   oColour = aCol;                                    \n"
"}                                                     \0";

static const char* sprite_frag_shader_code = 
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                     \n"
"in vec4 oColour;                        \n"
"uniform sampler2D text;                 \n"
"void main(){                            \n"
"FragColor = oColour;                    \n"
"}                                       \0";

typedef struct batch_vertex_data batch_vertex_data;
struct batch_vertex_data
{
    v3f pos;
    colour col;
};

typedef struct batch2d batch2d;
struct batch2d
{
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    unsigned int max_count;
    unsigned int current_count;

    batch_vertex_data*  vertices;
};

void init_batch(batch2d* const batch, unsigned int count);
void free_batch(batch2d* const batch);

void begin_render_batch(batch2d* const batch);
void add_to_render_batch(batch2d* const batch, v2f pos, colour col, float size);
void render_grid(batch2d* const batch, struct grid* const grid);
void end_render_batch(batch2d* const batch);

#endif//__NL_BATCH2D_H__