#ifndef __NL_UI_STUFF_H__
#define __NL_UI_STUFF_H__
#include "private/nl_shader.h"

static const char* ui_vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"uniform mat4 uWorldMat;                               \n"
"uniform mat4 uViewMat;                                \n"
"out vec4 oColor;                                      \n"
"void main() {                                         \n"
"   vec4 worldPos = uWorldMat * vec4(aPos, 1.0);       \n"
"   gl_Position = uViewMat * worldPos;                 \n"
"   oColor = aColor;                                   \n"
"}                                                     \0";

static const char* ui_fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                   \n"
"in vec4 oColor;                                       \n"
"void main() {                                         \n"
"    FragColor = oColor;                               \n"
"}                                                     \0";


#define SQUARE_HALF_SIZE 100.0f

static vertex_data square_verts[] =
{
    {{-SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
    {{ SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
    {{ SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
    {{-SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
};

static unsigned int square_indices[] =
{
    0,1,2,
    2,3,0
};

typedef struct ui_element ui_element;
struct ui_element
{
    transform2d trans;
    v2f anchor;
    mesh m;
};

#endif//__NL_UI_STUFF_H__