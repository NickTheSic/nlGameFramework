#include "nl_lib.h"
#include "nl_gl.h"

#if defined __EMSCRIPTEN__
#define SHADER_VERSION_HEADER "#version 300 es \n precision mediump float; \n"
#else
#define SHADER_VERSION_HEADER  "#version 330 core\n"
#endif

const char* vert_shader_code =
SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"out vec4 oColor;                                      \n"
"void main() {                                         \n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);   \n"
"   oColor = aColor;                                   \n"
"}                                                     \0";

const char* fragment_shader_code =
SHADER_VERSION_HEADER
"out vec4 FragColor;                                   \n"
"in vec4 oColor;                                       \n"
"void main() {                                         \n"
"    FragColor = oColor;                               \n"
"}                                                     \0";

mesh triangle;
mesh square;

vertex_data vertices[] = 
{
    {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.5f, 0.8f, 1.0f}},
    {{ 0.5f, -0.5f, 0.0f}, {1.0f, 0.5f, 0.8f, 1.0f}},
    {{ 0.0f,  0.5f, 0.0f}, {1.0f, 0.5f, 0.8f, 1.0f}}
};

vertex_data square_verts[] =
{
    {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.5f, 0.8f, 1.0f}},
    {{ 0.5f, -0.5f, 0.0f}, {0.8f, 1.0f, 0.5f, 1.0f}},
    {{ 0.5f,  0.5f, 0.0f}, {0.5f, 0.8f, 1.0f, 1.0f}},
    {{-0.5f,  0.5f, 0.0f}, {0.7f, 0.2f, 0.0f, 1.0f}}
};

unsigned int square_indices[] =
{
    0,1,2,
    2,3,0
};

// Required - Could be renderer or material
unsigned int shader_program;

void app_specific_init(void)
{
    generate_mesh_using_vertices_and_indices(&triangle, vertices, 3, square_indices, 3);
    generate_mesh_using_vertices_and_indices(&square, square_verts, 4, square_indices, 6);
    
    shader_program = create_shader_program(vert_shader_code, fragment_shader_code);
    use_shader_program(shader_program);
}

void app_specific_update(double dt)
{
    use_shader_program(shader_program);

    render_single_mesh(&square);
    render_single_mesh(&triangle);
}
