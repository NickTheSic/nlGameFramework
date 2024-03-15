#ifndef __NL_SHADER_H__
#define __NL_SHADER_H__


#if defined __EMSCRIPTEN__
#define NL_SHADER_VERSION_HEADER "#version 300 es \n precision mediump float; \n"
#else
#define NL_SHADER_VERSION_HEADER  "#version 330 core\n"
#endif


static const char* common_vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"uniform mat4 uWorldMat;                               \n"
"uniform mat4 uViewMat;                                \n"
//"uniform mat4 uProjMat;                                \n"
"out vec4 oColor;                                      \n"
"void main() {                                         \n"
"   vec4 worldPos = uWorldMat * vec4(aPos, 1.0);       \n"
"   vec4 viewPos = uViewMat * worldPos;                \n"
"   gl_Position = viewPos;                             \n"
//"   gl_Position = uProjMat * viewPos;                  \n"
"   oColor = aColor;                                   \n"
"}                                                     \0";

static const char* common_fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                   \n"
"in vec4 oColor;                                       \n"
"void main() {                                         \n"
"    FragColor = oColor;                               \n"
"}                                                     \0";

//create_shader_program(common_vert_shader_code , common_fragment_shader_code);
unsigned int create_shader_program(const char* vertex_shader_code, const char* fragment_shader_code);
void use_shader_program(unsigned int shader_program);


#endif //__NL_SHADER_H__