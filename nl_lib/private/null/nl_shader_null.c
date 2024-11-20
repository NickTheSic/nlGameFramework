#include "../nl_shader.h"

unsigned int create_shader_program(const char* vertex_shader_code, const char* fragment_shader_code)
{
    NL_UNUSED(vertex_shader_code);
    NL_UNUSED(fragment_shader_code);
    NL_UNIMPLEMENTED_FUNC;
    return 0;
}

void use_shader_program(unsigned int shader_program)
{
    NL_UNUSED(shader_program);
    NL_UNIMPLEMENTED_FUNC;
}

void free_shader_program(unsigned int shader_program)
{
    NL_UNUSED(shader_program);
    NL_UNIMPLEMENTED_FUNC;
}

unsigned int create_common_shader_program()
{
    NL_UNIMPLEMENTED_FUNC;
    return 0;
}

unsigned int get_uniform_loc(unsigned int program, const char* name)
{
    NL_UNUSED(program); NL_UNUSED(name);
    NL_UNIMPLEMENTED_FUNC;
    return 0;
}

void set_uniform_mat4x4f(unsigned int loc, const float* mat)
{
    NL_UNUSED(loc); NL_UNUSED(mat);
    NL_UNIMPLEMENTED_FUNC;
}