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
"void main() {                                         \n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);   \n"
"}                                                     \0";

const char* fragment_shader_code =
SHADER_VERSION_HEADER
"out vec4 FragColor;                                   \n"
"void main() {                                         \n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);         \n"
"}                                                     \0";

typedef struct vertex_data vertex_data;
struct vertex_data
{
    v3f pos;
};

typedef struct mesh mesh;
struct mesh
{
    unsigned int VAO;
    unsigned int VBO;
    vertex_data* vertices;
};

// Mesh
float vertices[] = 
{
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

unsigned int VBO;
unsigned int VAO;

// Required
unsigned int shader_program;

extern void app_specific_init(void)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    shader_program = create_shader_program(vert_shader_code, fragment_shader_code);
    glUseProgram(shader_program);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
}

extern void app_specific_update(double dt)
{
    glUseProgram(shader_program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
