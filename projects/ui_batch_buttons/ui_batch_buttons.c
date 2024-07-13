#include "nl_lib.h"
#include "private/nl_gl.h"

// Opting out of classic 'button' for just selectable UI using an arrow or highlight effect
// May be easier to mix controller and mouse input this way and just use text instead of a rectangle

static const char* ui_vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec2 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"uniform mat4 uViewMat;                                \n"
"out vec4 oColor;                                      \n"
"void main() {                                         \n"
"   vec4 viewPos = uViewMat * vec4(aPos, 0.0, 1.0);    \n"
"   gl_Position = viewPos;                             \n"
"   oColor = aColor;                                   \n"
"}                                                     \0";

static const char* ui_fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                   \n"
"in vec4 oColor;                                       \n"
"void main() {                                         \n"
"    FragColor = oColor;                               \n"
"}                                                     \n";

typedef struct ui_element ui_element;
struct ui_element
{
    colourf color;
    v2f pos;
    v2f size;
    v2f anchor;
    float rot;

    int hot;
    int active;
};

typedef struct myvd myvd;
struct myvd 
{
    v2f pos;
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

global_variable unsigned int sp = {0};

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

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(myvd), (void*)offsetof(myvd, pos));
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

void add_element_to_render_batch(my_batch* const batch, const ui_element *const elem)
{
    if (batch->current_count == batch->max_count)
    {
        render_batch(batch);
    }

    const unsigned int current_idx = batch->current_count * 4;

    const v2i screen_size = get_screen_size();
    const colourf col = elem->color;
    const v2f size = elem->size;
    const v2f anchor = elem->anchor;
    v2f pos = elem->pos;

    const float half_w = (float)screen_size.x/2.0f;
    const float half_h = (float)screen_size.y/2.0f;
    pos.x += half_w - (anchor.x * half_w);
    pos.y += half_h - (anchor.y * half_h);

    const myvd square_verts[] =
    {
        {{pos.x + -size.x, pos.y + -size.y}, col},
        {{pos.x +  size.x, pos.y + -size.y}, col},
        {{pos.x +  size.x, pos.y +  size.y}, col},
        {{pos.x + -size.x, pos.y +  size.y}, col}
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

void winsizecbk(int width, int height)
{
    mat4x4f mat = {0};
    create_identity_matrix(&mat);

    use_shader_program(sp);

    int hwidth = width;
    int hheight= height;

    create_orthographic_projection(&mat, -hwidth, hwidth, -hheight, hheight, -0.1f, 100.f);
    unsigned int viewMat = glGetUniformLocation(sp, "uViewMat");
    glUniformMatrix4fv(viewMat, 1, GL_FALSE, &mat.m11);
}

void app_specific_init(void)
{
    sp = create_shader_program(ui_vert_shader_code, ui_fragment_shader_code);
    use_shader_program(sp);

    pfn_window_size_callback = &winsizecbk;
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);
    
    init_batch(&batch, 3);
}

int ui_element_contains_point(const ui_element* const elem, v2f point)
{
    const v2f pos  = elem->pos;
    const v2f size = elem->size;

    return point.x < pos.x + size.x 
        && point.x > pos.x - size.x 
        && point.y < pos.y + size.y
        && point.y > pos.y - size.y;
}

int is_element_highlighted(ui_element* const elem)
{
    const v2i mouse_pos = get_mouse_position_from_system();

    if (ui_element_contains_point(elem, (v2f){(float)mouse_pos.x, (float)mouse_pos.y}))
    {
        elem->color = (colourf){0.0f, 0.0f, 0.0f,1.0f};
        return 1;
    }

    elem->color = (colourf){0.4f, 0.0f, 0.3f,1.0f};
    return 0;
}

static ui_element elem1 = {
        {1.0f,0.5f,0.2f, 1.0f},
        {20.0f,80.0f},
        {30.0f, 20.0f},
        {0.0f,0.0f},
        {0.0f} 
    };

void app_specific_update(double dt)
{
    (void)dt;
}

void app_specific_render()
{
    use_shader_program(sp);
    begin_render_batch(&batch);

    if (is_element_highlighted(&elem1) && mouse_button_is_held(NL_MOUSE_BUTTON_LEFT))
    {
        const v2i mouse_pos = get_mouse_position_from_system();
        elem1.pos = (v2f){(float)mouse_pos.x, (float)mouse_pos.y};
    }

    v2i mouse_pos = get_mouse_position_from_system();

    const ui_element elem2 = {
        {0.0f,0.5f,0.2f, 1.0f},
        {(float)mouse_pos.x, (float)mouse_pos.y},
        {5.0f, 5.0f},
        {0.0f,0.0f},
        {0.0f} 
    };

    add_element_to_render_batch(&batch, &elem1);
    add_element_to_render_batch(&batch, &elem2);

    end_render_batch(&batch);
}

void app_specific_cleanup()
{
    free_batch(&batch);
}