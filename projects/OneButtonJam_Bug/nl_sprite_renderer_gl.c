#include "nl_sprite_renderer.h"
#include "private/gl/nl_gl.h"
#include "private/nl_shader.h"
#include <third_party/stb_image.h>
#include <math.h>

struct sprite_vertex_data
{
    v3f pos;
    v2f uv;
};

global_variable const char* vertex_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                                   \n"
"layout (location = 1) in vec2 aUV_coord;                              \n"
"uniform mat4 uModelMat;                                               \n"
"uniform mat4 uViewMat;                                                \n"
"uniform mat4 uProjMat;                                                \n"
"out vec2 uv_coords;                                                   \n"
"void main() {                                                         \n"
"   gl_Position = uProjMat * uViewMat * uModelMat * vec4(aPos,1.0);    \n"
"   uv_coords = aUV_coord;                                             \n"
"}                                                                     \0";

global_variable const char* fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                        \n"
"in vec2 uv_coords;                                         \n"
"uniform sampler2D sprite_texture;                          \n"
"void main() {                                              \n"
"    FragColor = texture(sprite_texture,uv_coords);         \n"
"}                                                          \0";

global_variable unsigned int shader_program = {0};
global_variable unsigned int u_model_loc = {0};
global_variable unsigned int u_view_mat = {0};
global_variable unsigned int u_proj_mat = {0};

void set_model_matrix(float* m11)
{
    set_uniform_mat4x4f(u_model_loc, m11);
}

void set_view_matrix(float* m11)
{
    set_uniform_mat4x4f(u_view_mat, m11);
}

void set_projection_matrix(float* m11)
{
    set_uniform_mat4x4f(u_proj_mat, m11);
}

void init_sprite_renderer(void)
{
    shader_program = create_shader_program(vertex_shader_code, fragment_shader_code);
    use_shader_program(shader_program);

    u_model_loc = get_uniform_loc(shader_program, "uModelMat");
    u_view_mat = get_uniform_loc(shader_program, "uViewMat");
    u_proj_mat = get_uniform_loc(shader_program, "uProjMat");
}

internal_function void generate_simple_sprite_using_vertices_and_indices(nl_sprite* const simple_sprite, const sprite_vertex_data* const vertices, int vertice_count, const unsigned int* const indices, unsigned int indice_count)
{
    const size_t vertices_data_size = sizeof(sprite_vertex_data) * vertice_count;
    const size_t indice_data_size = indice_count * sizeof(unsigned int);

    simple_sprite->vertices = (sprite_vertex_data*)memory_allocate(vertices_data_size);
    memcpy(simple_sprite->vertices, vertices, vertices_data_size);

    simple_sprite->indices = (unsigned int*)memory_allocate(indice_data_size);
    memcpy(simple_sprite->indices, indices, indice_data_size);

    simple_sprite->vertice_count = vertice_count;
    simple_sprite->indice_count = indice_count;

    glGenVertexArrays(1, &simple_sprite->VAO);
    glBindVertexArray(simple_sprite->VAO);

    glGenBuffers(1, &simple_sprite->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, simple_sprite->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_data_size, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &simple_sprite->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, simple_sprite->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_data_size, indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex_data), (void*)offsetof(sprite_vertex_data, pos));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex_data), (void*)offsetof(sprite_vertex_data, uv));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void render_single_simple_sprite(nl_sprite* simple_sprite)
{
    glBindVertexArray(simple_sprite->VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, simple_sprite->EBO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, simple_sprite->texture_id);

    glDrawElements(GL_TRIANGLES, simple_sprite->indice_count, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
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

void generate_rectangle_simple_sprite(nl_sprite* const simple_sprite, float width, float height)
{
    sprite_vertex_data square_vertices[] =
    {
        {{0.0f,  0.0f,   0.0f}, {0.0f,0.0f}},
        {{width, 0.0f,   0.0f}, {1.0f,0.0f}},
        {{width, height, 0.0f}, {1.0f,1.0f}},
        {{0.0f,  height, 0.0f}, {0.0f,1.0f}},
    };

    static const unsigned int indices[] = {0,1,2,0,2,3};

    generate_simple_sprite_using_vertices_and_indices(simple_sprite, square_vertices, 4, indices, 6);
}

void generate_square_simple_sprite(nl_sprite* const simple_sprite, float width)
{
    generate_rectangle_simple_sprite(simple_sprite, width, width);
}

void load_texture_for_sprite(nl_sprite* const sprite, const char* filename)
{
    stbi_set_flip_vertically_on_load(1);

    int x, y, channel;
    unsigned char * data = stbi_load(filename, &x, &y, &channel, 4);

    //glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &sprite->texture_id);
    glBindTexture(GL_TEXTURE_2D, sprite->texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D,
             0,
             GL_RGBA,
             x, y,
             0,
             GL_RGBA,
             GL_UNSIGNED_BYTE,
             data
             );

    stbi_image_free(data);
}
