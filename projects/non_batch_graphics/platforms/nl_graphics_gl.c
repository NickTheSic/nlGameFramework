#include "../nl_graphics.h"
#include "private/gl/nl_gl.h"

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
    unsigned int shader_program;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    unsigned int max_count;
    unsigned int current_count;

    batch_vertex_data*  vertices;
};

global_variable batch2d batch;

global_variable unsigned int loc_view_mat = {0};
global_variable unsigned int loc_proj_mat = {0};

#define BATCH_COUNT 10

void game_init_graphics(void)
{   
    batch.shader_program = create_shader_program(batch_vert_shader_code, sprite_frag_shader_code);
    use_shader_program(batch.shader_program);

    loc_view_mat = get_uniform_loc(batch.shader_program, "uViewMat");
    loc_proj_mat = get_uniform_loc(batch.shader_program, "uProjMat");

    const unsigned int vertice_count = BATCH_COUNT * 4;
    const unsigned int indice_count  = BATCH_COUNT * 6;

    const size_t vertice_data = vertice_count * sizeof(batch_vertex_data);
    const size_t indice_data  = indice_count  * sizeof(unsigned int);

    batch.max_count = BATCH_COUNT;
    batch.vertices = (batch_vertex_data*)memory_allocate(vertice_data);

    glGenVertexArrays(1, &batch.vao);
    glBindVertexArray(batch.vao);

    glGenBuffers(1, &batch.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, batch.vbo);
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

    glGenBuffers(1, &batch.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_data, indices, GL_STATIC_DRAW);

    memory_free(indices);
}

void game_begin_render(void)
{
    use_shader_program(batch.shader_program);

    glBindVertexArray(batch.vao);
    glBindBuffer(GL_ARRAY_BUFFER, batch.vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(batch_vertex_data), (void*)offsetof(batch_vertex_data, pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(batch_vertex_data), (void*)offsetof(batch_vertex_data, col));
    glEnableVertexAttribArray(1);
}

internal_function void render_batch(void)
{
    glBindBuffer(GL_ARRAY_BUFFER, batch.vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, batch.current_count*4*sizeof(batch_vertex_data), batch.vertices);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch.ebo);
    glDrawElements(GL_TRIANGLES, batch.current_count*6, GL_UNSIGNED_INT, 0);

    batch.current_count = 0;
}

void draw_rectangle(v2f pos, colour col, v2f size)
{
    if (batch.current_count == batch.max_count)
    {
        render_batch();
    }

    const unsigned int current_idx = batch.current_count * 4;

    batch_vertex_data square_verts[4];
    square_verts[0] = (batch_vertex_data){{pos.x, pos.y, 0.0f}, col};
    square_verts[1] = (batch_vertex_data){{pos.x +  size.x, pos.y, 0.0f}, col};
    square_verts[2] = (batch_vertex_data){{pos.x +  size.x, pos.y +  size.y, 0.0f}, col};
    square_verts[3] = (batch_vertex_data){{pos.x, pos.y +  size.y, 0.0f}, col};

    batch_vertex_data* const dest = &batch.vertices[current_idx];
    memcpy(dest, &square_verts, sizeof(batch_vertex_data)*4);

    batch.current_count++;
}

void draw_square(v2f pos, colour col, float size)
{
    if (batch.current_count == batch.max_count)
    {
        render_batch();
    }

    const unsigned int current_idx = batch.current_count * 4;

    batch_vertex_data square_verts[4];
    square_verts[0] = (batch_vertex_data){{pos.x, pos.y, 0.0f}, col};
    square_verts[1] = (batch_vertex_data){{pos.x +  size, pos.y, 0.0f}, col};
    square_verts[2] = (batch_vertex_data){{pos.x +  size, pos.y +  size, 0.0f}, col};
    square_verts[3] = (batch_vertex_data){{pos.x, pos.y +  size, 0.0f}, col};

    batch_vertex_data* const dest = &batch.vertices[current_idx];
    memcpy(dest, &square_verts, sizeof(batch_vertex_data)*4);

    batch.current_count++;
}

void draw_sprite(v2f pos, colour col, v2f size, unsigned int texture_id)
{
    NL_UNUSED(pos);
    NL_UNUSED(col);
    NL_UNUSED(size);
    NL_UNUSED(texture_id);
    NL_UNIMPLEMENTED_FUNC;
}

void game_end_render(void)
{
    render_batch();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void game_free_graphics()
{
    memory_free(batch.vertices);
}

void set_batch_view_matrix(float* m11)
{
    set_uniform_mat4x4f(loc_view_mat, m11);
}

void set_batch_proj_matrix(float* m11)
{
    set_uniform_mat4x4f(loc_proj_mat, m11);
}
