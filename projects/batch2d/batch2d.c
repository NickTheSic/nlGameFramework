#include "nl_lib.h"
#include "private/nl_gl.h"

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

typedef struct myvd myvd;
struct myvd 
{
    v3f pos;
    colourf color;
};

typedef struct my_batch my_batch;
struct my_batch
{
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    unsigned int max_count;
    unsigned int current_count;

    myvd*  vertices;
};

static unsigned int sp = {0};

void init_batch(my_batch* const batch, unsigned int count)
{   
    const unsigned int vertice_count = count * 4;
    const unsigned int indice_count  = count * 6;

    const size_t vertice_data = vertice_count * sizeof(myvd);
    const size_t indice_data  = indice_count  * sizeof(unsigned int);

    batch->max_count = count;
    batch->vertices = (myvd*)memory_allocate(vertice_data);

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

void begin_render_batch(my_batch* const batch)
{
    glBindVertexArray(batch->vao);
    glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(myvd), (void*)offsetof(myvd, pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(myvd), (void*)offsetof(myvd, color));
    glEnableVertexAttribArray(1);
}

void render_batch(my_batch* const batch)
{
    glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, batch->current_count*4*sizeof(myvd), batch->vertices);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->ebo);
    glDrawElements(GL_TRIANGLES, batch->current_count*6, GL_UNSIGNED_INT, 0);

    batch->current_count = 0;
}

void add_to_render_batch(my_batch* const batch, v2f pos)
{
    if (batch->current_count == batch->max_count)
    {
        render_batch(batch);
    }

    const unsigned int current_idx = batch->current_count * 4;

    const float SQUARE_HALF_SIZE = 0.1f;
    colourf col = (colourf){0.8f, 0.0f, 0.1f, 1.0f};
    const myvd square_verts[] =
    {
        {{pos.x + -SQUARE_HALF_SIZE, pos.y + -SQUARE_HALF_SIZE, 0.0f}, col},
        {{pos.x +  SQUARE_HALF_SIZE, pos.y + -SQUARE_HALF_SIZE, 0.0f}, col},
        {{pos.x +  SQUARE_HALF_SIZE, pos.y +  SQUARE_HALF_SIZE, 0.0f}, col},
        {{pos.x + -SQUARE_HALF_SIZE, pos.y +  SQUARE_HALF_SIZE, 0.0f}, col}
    };

    myvd* dest = &batch->vertices[current_idx];
    memcpy(dest, &square_verts, sizeof(myvd)*4);

    batch->current_count++;
}

void end_render_batch(my_batch* const batch)
{
    render_batch(batch);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void free_batch(my_batch* const batch)
{
    memory_free(batch->vertices);
}

static my_batch batch = {0};

void app_specific_init(void)
{
    sp = create_shader_program(batch_vert_shader_code, common_fragment_shader_code);
    use_shader_program(sp);
    init_batch(&batch, 3);
}

void app_specific_update(double dt)
{
    (void)dt;
}

void app_specific_render()
{
    use_shader_program(sp);
    begin_render_batch(&batch);
    add_to_render_batch(&batch, (v2f){0.5f,0.3f});
    add_to_render_batch(&batch, (v2f){0.1f,-0.2f});
    end_render_batch(&batch);
}

void app_specific_cleanup()
{
    free_batch(&batch);
}