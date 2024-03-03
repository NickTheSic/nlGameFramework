#ifndef __NL_SHADER_H__
#define __NL_SHADER_H__


#if defined __EMSCRIPTEN__
#define NL_SHADER_VERSION_HEADER "#version 300 es \n precision mediump float; \n"
#else
#define NL_SHADER_VERSION_HEADER  "#version 330 core\n"
#endif

unsigned int create_shader_program(const char* vertex_shader_code, const char* fragment_shader_code);
void use_shader_program(unsigned int shader_program);


#endif //__NL_SHADER_H__