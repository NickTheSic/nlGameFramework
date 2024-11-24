#ifndef __NL_SHADER_H__
#define __NL_SHADER_H__

#if defined __EMSCRIPTEN__
#define NL_SHADER_VERSION_HEADER "#version 300 es \n precision mediump float; \n"

#elif defined _WIN32
#define NL_SHADER_VERSION_HEADER  "#version 330 core\n"

#elif defined (__linux__)
#define NL_SHADER_VERSION_HEADER  "#version 330 core\n"

#elif defined (__SWITCH__)
#define NL_SHADER_VERSION_HEADER  "#version 330 core\n"

#elif defined (NOT_YET_IMPLEMENTED)
#define NL_SHADER_VERSION_HEADER //define it as nothing to compile

#else
#warning Shader is not defined for this platform
#define NL_SHADER_VERSION_HEADER //define it as nothing to compile

#endif


//create_shader_program(common_vert_shader_code , common_fragment_shader_code);
unsigned int create_shader_program(const char* vertex_shader_code, const char* fragment_shader_code);
void use_shader_program(unsigned int shader_program);
void free_shader_program(unsigned int shader_program);

unsigned int create_common_shader_program(void);

unsigned int get_uniform_loc(unsigned int program, const char* name);
void set_uniform_mat4x4f(unsigned int loc, const float* mat);

const char* get_common_vertex_shader_code(void);
const char* get_common_fragment_shader_code(void);

#endif //__NL_SHADER_H__