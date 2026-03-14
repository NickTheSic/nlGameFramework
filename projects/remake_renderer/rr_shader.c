#include "private/gl/nl_gl.h"

unsigned int rr_vertex_shader_program = 0;
unsigned int rr_fragment_shader_program = 0;

unsigned int rr_create_shader_program(void)
{
    {
        file_contents vs_shader = {0};
        load_shader_from_data("rr_shader.vs", &vs_shader);
        
        rr_vertex_shader_program = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(rr_vertex_shader_program, 1, (const char**)&vs_shader.content, NULL);
        glCompileShader(rr_vertex_shader_program);
        
        int success = 0;
        char info[512];
        glGetShaderiv(rr_vertex_shader_program, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(rr_vertex_shader_program, 512, NULL, info);
            NL_LOG("Vertex Shader Compilation failed: %s", info);
        }
        
        clear_file_read(&vs_shader);
    }
    
    {
        file_contents fs_shader = {0};
        load_shader_from_data("rr_shader.fs", &fs_shader);

        rr_fragment_shader_program = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(rr_fragment_shader_program, 1, (const char**)&fs_shader.content, NULL);
        glCompileShader(rr_fragment_shader_program);
    
        int success = 0;
        char info[512];
        glGetShaderiv(rr_fragment_shader_program, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(rr_fragment_shader_program, 512, NULL, info);
            NL_LOG("Fragment Shader Compilation failed: %s", info);
        }

        clear_file_read(&fs_shader);
    }

    unsigned int local_shader_program = glCreateProgram();
    glAttachShader(local_shader_program, rr_vertex_shader_program);
    glAttachShader(local_shader_program, rr_fragment_shader_program);
    glLinkProgram(local_shader_program);
    {
        int success = 0;
        char info[512];
        glGetProgramiv(local_shader_program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(local_shader_program, 512, NULL, info);
            NL_LOG("Shader Programfailed to link: %s", info);
        }
    }

    glDeleteShader(rr_vertex_shader_program);
    glDeleteShader(rr_fragment_shader_program);

    return local_shader_program;
}
