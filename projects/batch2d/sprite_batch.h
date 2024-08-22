#ifndef __NL_BATCH2D_H__
#define __NL_BATCH2D_H__

static const char* batch_vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"out vec4 oColor;                                      \n"
"void main() {                                         \n"
"   vec4 viewPos = vec4(aPos, 1.0);                    \n"
"   gl_Position = viewPos;                             \n"
"   oColor = aColor;                                   \n"
"}                                                     \0";

typedef struct sprite_batch_vertex_data sprite_batch_vertex_data;
struct sprite_batch_vertex_data
{
    v3f pos;
    colourf color;
};

typedef struct sprite_batch sprite_batch;
struct sprite_batch
{
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    unsigned int max_count;
    unsigned int current_count;

    sprite_batch_vertex_data*  vertices;
};

void init_batch(sprite_batch* const batch, unsigned int count);
void free_batch(sprite_batch* const batch);

void begin_render_batch(sprite_batch* const batch);
void add_to_render_batch(sprite_batch* const batch, v2f pos);
void end_render_batch(sprite_batch* const batch);

#endif//__NL_BATCH2D_H__