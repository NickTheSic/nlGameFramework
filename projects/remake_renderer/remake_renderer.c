#include "nl_lib.h"
#include "private/gl/nl_gl.h"


float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

unsigned int VBO = 0;

const char* rr_vertex_shader_code = 
"#version 330 core\n" 
"layout (location = 0) in vec3 Pos;\n"
"void main() {\n"
"  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

unsigned int rr_vertex_shader_program = 0;


void app_specific_init(void)
{
    NL_LOG("Application Initializing...");
printf("stdout handle: %p\n", GetStdHandle(STD_OUTPUT_HANDLE));
    fprintf(stdout, "TEST\n");
    printf("TEst1");

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    rr_vertex_shader_program = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(rr_vertex_shader_program, 1, &rr_vertex_shader_code, NULL);
    glCompileShader(rr_vertex_shader_program);
    
    int success = 0;
    char info[512];
    glGetShaderiv(rr_vertex_shader_program, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(rr_vertex_shader_program, 512, NULL, info);
        NL_LOG("Vertex Shader Compilation failed: %s", info);
    }
    
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{
    glClearColor(0.2f,0.3f,0.8f,1.0f);
}

void app_specific_cleanup(void)
{

}