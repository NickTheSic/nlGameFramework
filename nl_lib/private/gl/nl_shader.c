#include "../nl_shader.h"
#include "../nl_debug.h"
#include "nl_gl.h"

const char* VIEW_MATRIX_UNIFORM_NAME = "uViewMat";
const char* WORLD_MATRIX_UNIFORM_NAME = "uWorldMat";

const char* common_vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"uniform mat4 uWorldMat;                               \n"
"uniform mat4 uViewMat;                                \n"
"uniform mat4 uProjMat;                                \n"
"out vec4 oColor;                                      \n"
"void main() {                                         \n"
"   vec4 worldPos = uWorldMat * vec4(aPos, 1.0);       \n"
"   vec4 viewPos = uViewMat * worldPos;                \n"
"   gl_Position = uProjMat * viewPos;                  \n"
"   oColor = aColor;                                   \n"
"}                                                     \0";

const char* common_fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                   \n"
"in vec4 oColor;                                       \n"
"void main() {                                         \n"
"    FragColor = oColor;                               \n"
"}                                                     \0";

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

unsigned int create_shader_program(const char* const vertex_shader_code, const char* const fragment_shader_code)
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

unsigned int load_shader_from_files(const char* vertex_shader_filename, const char* fragment_shader_filename)
{
    unsigned int shader_program_result = 0;

    file_contents vs_content = {0};
    file_contents fs_content = {0};

    load_shader_from_data(vertex_shader_filename, &vs_content);
    load_shader_from_data(fragment_shader_filename, &fs_content);

    shader_program_result = create_shader_program((char*)vs_content.content, (char*)fs_content.content);

    clear_file_read(&vs_content);
    clear_file_read(&fs_content);

    return shader_program_result;
}

void use_shader_program(unsigned int shader_program)
{
    glUseProgram(shader_program);
}

void free_shader_program(unsigned int shader_program)
{
    glDeleteProgram(shader_program);
}

unsigned int create_common_shader_program()
{
    return create_shader_program(common_vert_shader_code, common_fragment_shader_code);
}

unsigned int get_uniform_loc(unsigned int program, const char* name)
{
    return glGetUniformLocation(program, name);
}

void set_uniform_mat4x4f(unsigned int loc, const float* const mat)
{
    glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
}

const char* get_common_vertex_shader_code(void)
{
    return common_vert_shader_code;
}

const char* get_common_fragment_shader_code(void)
{
    return common_fragment_shader_code;
}
