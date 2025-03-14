#include "nl_sprite_renderer.h"
#include "private/gl/nl_gl.h"
#include "private/nl_shader.h"
#include <math.h>

#include "nl_sprite_atlas.h"

struct sprite_vertex_data
{
    v3f pos;
    v2f uv;
    colour col;
};

global_variable const char* vertex_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                                   \n"
"layout (location = 1) in vec2 aUV_coord;                              \n"
"layout (location = 2) in vec4 aCol;                                   \n"
"uniform mat4 uModelMat;                                               \n"
"uniform mat4 uViewMat;                                                \n"
"uniform mat4 uProjMat;                                                \n"
"out vec2 uv_coords;                                                   \n"
"out vec4 oCol;                                                        \n"
"void main() {                                                         \n"
"   gl_Position = uProjMat * uViewMat * uModelMat * vec4(aPos,1.0);    \n"
"   uv_coords = aUV_coord;                                             \n"
"   oCol = aCol;                                                       \n"
"}                                                                     \0";

global_variable const char* fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                        \n"
"in vec2 uv_coords;                                         \n"
"in vec4 oCol;                                              \n"
"uniform sampler2D sprite_texture;                          \n"
"void main() {                                              \n"
"    FragColor = texture(sprite_texture,uv_coords) * oCol;  \n"
"}                                                          \0";

global_variable unsigned int shader_program = {0};
global_variable unsigned int u_model_loc = {0};
global_variable unsigned int u_view_mat = {0};
global_variable unsigned int u_proj_mat = {0};

void set_model_matrix(mat4x4f*const mat)
{
    use_shader_program(shader_program);
    set_uniform_mat4x4f(u_model_loc, &mat->m11);
}

void set_view_matrix(mat4x4f*const mat)
{
    use_shader_program(shader_program);
    set_uniform_mat4x4f(u_view_mat, &mat->m11);
}

void set_projection_matrix(mat4x4f*const mat)
{
    use_shader_program(shader_program);
    set_uniform_mat4x4f(u_proj_mat, &mat->m11);
}

void init_sprite_renderer(void)
{
    shader_program = create_shader_program(vertex_shader_code, fragment_shader_code);
    use_shader_program(shader_program);

    u_model_loc = get_uniform_loc(shader_program, "uModelMat");
    u_view_mat = get_uniform_loc(shader_program, "uViewMat");
    u_proj_mat = get_uniform_loc(shader_program, "uProjMat");
}

internal_function void generate_simple_sprite_using_vertices_and_indices(nl_sprite* const simple_sprite, const sprite_vertex_data* const vertices, int vertice_count)
{
    static const unsigned int indices[] = {0,1,2,0,2,3};
    static const unsigned int indice_count = 6;

    const size_t vertices_data_size = sizeof(sprite_vertex_data) * vertice_count;
    const size_t indice_data_size = indice_count * sizeof(unsigned int);

    simple_sprite->vertices = (sprite_vertex_data*)memory_allocate(vertices_data_size);
    if (simple_sprite->vertices == 0)
    {
        NL_LOG("Unable to allocate memory for simple sprite vertices.  Returning early");
        return;
    }
    memcpy(simple_sprite->vertices, vertices, vertices_data_size);

    simple_sprite->indices = (unsigned int*)memory_allocate(indice_data_size);
    if (simple_sprite->indices == 0)
    {
        NL_LOG("Unable to allocate memory for simple sprite indices. Returning early");
        return;
    }
    memcpy(simple_sprite->indices, indices, indice_data_size);

    simple_sprite->vertice_count = vertice_count;
    simple_sprite->indice_count = indice_count;

    glGenVertexArrays(1, &simple_sprite->VAO);
    glBindVertexArray(simple_sprite->VAO);

    glGenBuffers(1, &simple_sprite->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, simple_sprite->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_data_size, vertices, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &simple_sprite->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, simple_sprite->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_data_size, indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex_data), (void*)offsetof(sprite_vertex_data, pos));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex_data), (void*)offsetof(sprite_vertex_data, uv));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(sprite_vertex_data), (void*)offsetof(sprite_vertex_data, col));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void begin_sprite_render(void)
{
    use_shader_program(shader_program);
    
    // Cannot call vertex attrivs without binding a VAO on web

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex_data), (void*)offsetof(sprite_vertex_data, pos));
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex_data), (void*)offsetof(sprite_vertex_data, uv));
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(sprite_vertex_data), (void*)offsetof(sprite_vertex_data, col));
    //glEnableVertexAttribArray(2);
}

void end_sprite_render(void)
{

}

void render_single_simple_sprite(nl_sprite* simple_sprite)
{
    use_shader_program(shader_program);

    glBindVertexArray(simple_sprite->VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, simple_sprite->EBO);

    bind_sprite_atlas_texture();

    // Cannot set vertex atrib pointers here, wish I knew where I could learn more about why

    glDrawElements(GL_TRIANGLES, simple_sprite->indice_count, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void render_single_sprite_colour(nl_sprite* const sprite, colour col)
{
    glBindVertexArray(sprite->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, sprite->VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite->EBO);

    bind_sprite_atlas_texture();

    size_t offset_inc = sizeof(sprite_vertex_data);

    glBufferSubData(GL_ARRAY_BUFFER, offsetof(sprite_vertex_data, col), sizeof(colour), &col);
    glBufferSubData(GL_ARRAY_BUFFER, offsetof(sprite_vertex_data, col)+offset_inc, sizeof(colour), &col);
    glBufferSubData(GL_ARRAY_BUFFER, offsetof(sprite_vertex_data, col)+(offset_inc*2), sizeof(colour), &col);
    glBufferSubData(GL_ARRAY_BUFFER, offsetof(sprite_vertex_data, col)+(offset_inc*3), sizeof(colour), &col);

    glDrawElements(GL_TRIANGLES, sprite->indice_count, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void free_simple_sprite(nl_sprite* const simple_sprite)
{
    memory_free(simple_sprite->vertices);
    memory_free(simple_sprite->indices);

    // gl free buffers here
    glDeleteBuffers(1, &simple_sprite->EBO);
    glDeleteBuffers(1, &simple_sprite->VBO);
    glDeleteBuffers(1, &simple_sprite->VAO);
}

void generate_rectangle_simple_sprite(nl_sprite* const sprite, float width, float height)
{
    texture_data td = get_texture_for_handle(sprite->texture_id);

    const colour white = COLOUR_WHITE;
    sprite_vertex_data square_vertices[] =
    {
        {{0.0f,  0.0f,   0.0f},  td.coord_bl,                   white},
        {{width, 0.0f,   0.0f}, {td.coord_tr.x, td.coord_bl.y}, white},
        {{width, height, 0.0f},  td.coord_tr,                   white},
        {{0.0f,  height, 0.0f}, {td.coord_bl.x, td.coord_tr.y}, white},
    };

    generate_simple_sprite_using_vertices_and_indices(sprite, square_vertices, 4);
}

void generate_square_simple_sprite(nl_sprite* const simple_sprite, float width)
{
    generate_rectangle_simple_sprite(simple_sprite, width, width);
}

