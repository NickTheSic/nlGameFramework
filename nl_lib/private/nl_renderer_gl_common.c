#include "../nl_renderer.h"
#include "../nl_debug.h"
#include "../nl_gl.h"

int initialize_renderer_subsystem()
{
    if (!initialize_gl())
    {
        return 0;
    }

    return 1;
}

void begin_render_frame()
{
    glClear(GL_COLOR_BUFFER_BIT); 
    glClear(GL_DEPTH_BUFFER_BIT);
}

void end_render_frame()
{
    renderer_swap_buffers();
}

void set_background_colour_4f(float r, float g, float b, float a)
{
    glClearColor(r,g,b,a);
}

void set_viewport_size(int width, int height)
{
    glViewport(0, 0, width, height);
}

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

