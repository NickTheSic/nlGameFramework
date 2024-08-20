#include "../nl_shader.h"
#include "../nl_debug.h"
#include "../nl_gl.h"

internal_function unsigned int compile_shader_source(int type, const char* code)
{
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, 0);
    glCompileShader(shader);

    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    
    if (!success)
    {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        NL_LOG("Error Compiling shader: %d\n\t%s\n", type, info_log);
        return 0;
    }

    return shader;
}

unsigned int create_shader_program(const char* vertex_shader_code, const char* fragment_shader_code)
{
    unsigned int vertex_shader = compile_shader_source(GL_VERTEX_SHADER, vertex_shader_code);
    if (vertex_shader == 0)
    {
        NL_LOG("Failed to make Vertex Shader"); 
        return 0;
    }

    unsigned int fragment_shader = compile_shader_source(GL_FRAGMENT_SHADER, fragment_shader_code);
    if (fragment_shader == 0)
    {
        NL_LOG("Failed to make Fragment Shader"); 
        glDeleteShader(vertex_shader);
        return 0;
    }

    unsigned int local_shader_program = glCreateProgram();
    glAttachShader(local_shader_program, vertex_shader);
    glAttachShader(local_shader_program, fragment_shader);
    glLinkProgram(local_shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader); 

    return local_shader_program; 
}

void use_shader_program(unsigned int shader_program)
{
    glUseProgram(shader_program);
}

void free_shader_program(unsigned int shader_program)
{
    glDeleteProgram(shader_program);
}

void use_shader(unsigned int shader_program)
{
    glUseProgram(shader_program);
}

unsigned int create_common_shader_program()
{
    return create_shader_program(common_vert_shader_code, common_fragment_shader_code);
}
