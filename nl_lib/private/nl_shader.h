#ifndef __NL_SHADER_H__
#define __NL_SHADER_H__

#ifdef __cplusplus
extern "C" {
#endif

unsigned int create_shader_program(const char* const vertex_shader_code, const char* const fragment_shader_code);
void use_shader_program(unsigned int shader_program);
void free_shader_program(unsigned int shader_program);

unsigned int load_shader_from_files(const char* vertex_shader_filename, const char* fragment_shader_filename);

unsigned int get_uniform_loc(unsigned int program, const char* name);

//NOTE: Should use the shader program instead of assuming it is bound already
void set_uniform_mat4x4f(unsigned int loc, const float* const mat); 
void set_uniform_v3f(unsigned int loc, const float* const vec);

#ifdef __cplusplus
}
#endif

#endif //__NL_SHADER_H__