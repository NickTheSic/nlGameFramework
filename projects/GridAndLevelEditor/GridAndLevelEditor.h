#ifndef __GRIDANDLEVELEDITOR__
#define __GRIDANDLEVELEDITOR__

#include "Grid.h"

global_variable world_grid grid = {0};
global_variable mesh tile_0 = {0};
global_variable unsigned int shader_program = {0};

#define col_white (colourf){1.f,1.f,1.f,1.f}

unsigned int u_model_loc = 0;
unsigned int u_view_mat = 0;
unsigned int u_object_colour = {0};
camera main_cam = {0};


static const char* vertex_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                                   \n"
"layout (location = 1) in vec4 aColor;                                 \n"
"uniform mat4 uModelMat;                                               \n"
"uniform mat4 uViewMat;                                                \n"
"uniform mat4 uProjMat;                                                \n"
"uniform vec4 uObjCol;                                                 \n"
"out vec4 oColor;                                                      \n"
"void main() {                                                         \n"
"   gl_Position = uProjMat * uViewMat * uModelMat * vec4(aPos,1.0);    \n"
"   oColor = aColor * uObjCol;                                         \n"
"}                                                                     \0";

static const char* fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                        \n"
"in vec4 oColor;                                            \n"
"void main() {                                              \n"
"    FragColor = oColor;                                    \n"
"}                                                          \0";

#endif//__GRIDANDLEVELEDITOR__