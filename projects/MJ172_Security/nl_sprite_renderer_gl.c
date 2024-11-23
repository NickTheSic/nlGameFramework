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

typedef struct texture_data texture_data;
struct texture_data
{
    v2f coord_bl;
    v2f coord_tr;
};
// temporary game specific value of 5
texture_data textures[5] = {0};
unsigned int next_texture_to_load = {0};
unsigned int atlas_texture_id = {0};
unsigned int current_texture_x_loaded = {0};
float texture_height;
float texture_width;

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

internal_function void init_sprite_atlas()
{
    glGenTextures(1, &atlas_texture_id);
    glBindTexture(GL_TEXTURE_2D, atlas_texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unsigned int x_size = 32*5;
    unsigned int y_size = 64;
    unsigned char* null_data = (unsigned char* )memory_allocate(sizeof(unsigned char) * x_size * y_size)

    glTexImage2D(GL_TEXTURE_2D,
             0,
             GL_RGBA,
             x_size, y_size,
             0,
             GL_RGBA,
             GL_UNSIGNED_BYTE,
             null_data
             );

    texture_height = (float)y_size;
    texture_width  = (float)x_size;

    memory_free(null_data);
}

void init_sprite_renderer(void)
{
    shader_program = create_shader_program(vertex_shader_code, fragment_shader_code);
    use_shader_program(shader_program);

    u_model_loc = get_uniform_loc(shader_program, "uModelMat");
    u_view_mat = get_uniform_loc(shader_program, "uViewMat");
    u_proj_mat = get_uniform_loc(shader_program, "uProjMat");

    init_sprite_atlas();
}

internal_function void generate_simple_sprite_using_vertices_and_indices(nl_sprite* const simple_sprite, const sprite_vertex_data* const vertices, int vertice_count)
{
    static const unsigned int indices[] = {0,1,2,0,2,3};
    static const unsigned int indice_count = 6;

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
    glBindTexture(GL_TEXTURE_2D, atlas_texture_id);

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

void generate_rectangle_simple_sprite(nl_sprite* const sprite, float width, float height)
{
    texture_data td = textures[sprite->texture_id];
    sprite_vertex_data square_vertices[] =
    {
        {{0.0f,  0.0f,   0.0f},  td.coord_bl},
        {{width, 0.0f,   0.0f}, {td.coord_tr.x, td.coord_bl.y}},
        {{width, height, 0.0f},  td.coord_tr},
        {{0.0f,  height, 0.0f}, {td.coord_bl.x, td.coord_tr.y}},
    };

    generate_simple_sprite_using_vertices_and_indices(sprite, square_vertices, 4);
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

    glTexSubImage2D(GL_TEXTURE_2D, 0,
                    current_texture_x_loaded, 0,
                    x, y, 
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    data);

    stbi_image_free(data);

    textures[next_texture_to_load].coord_bl.x = (float)current_texture_x_loaded / texture_width;
    textures[next_texture_to_load].coord_bl.y = 0;

    current_texture_x_loaded += x;

    textures[next_texture_to_load].coord_tr.x = current_texture_x_loaded / texture_width;
    textures[next_texture_to_load].coord_tr.y = y / texture_height;

    sprite->texture_id = next_texture_to_load++;
}
