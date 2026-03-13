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
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* rr_fragment_shader_code =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

unsigned int rr_vertex_shader_program = 0;
unsigned int rr_fragment_shader_program = 0;
unsigned int rr_shader_program = 0;


void app_specific_init(void)
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    rr_vertex_shader_program = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(rr_vertex_shader_program, 1, &rr_vertex_shader_code, NULL);
    glCompileShader(rr_vertex_shader_program);
    {
        int success = 0;
        char info[512];
        glGetShaderiv(rr_vertex_shader_program, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(rr_vertex_shader_program, 512, NULL, info);
            NL_LOG("Vertex Shader Compilation failed: %s", info);
        }
    }
    
    rr_fragment_shader_program = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(rr_fragment_shader_program, 1, &rr_fragment_shader_code, NULL);
    glCompileShader(rr_fragment_shader_program);
    {
        int success = 0;
        char info[512];
        glGetShaderiv(rr_fragment_shader_program, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(rr_fragment_shader_program, 512, NULL, info);
            NL_LOG("Fragment Shader Compilation failed: %s", info);
        }
    }

    rr_shader_program = glCreateProgram();
    glAttachShader(rr_shader_program, rr_vertex_shader_program);
    glAttachShader(rr_shader_program, rr_fragment_shader_program);
    glLinkProgram(rr_shader_program);
    {
        int success = 0;
        char info[512];
        glGetProgramiv(rr_shader_program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(rr_shader_program, 512, NULL, info);
            NL_LOG("Shader Programfailed to link: %s", info);
        }
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
    glDeleteShader(rr_vertex_shader_program);
    glDeleteShader(rr_fragment_shader_program);
}