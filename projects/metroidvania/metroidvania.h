#ifndef __METROIDVANIA_H__
#define __METROIDVANIA_H__

#include "player.h"
#include "simple_sprite.h"

/*
TODO:
    - Make a grid for the level
    - Make character controller
        - Rebindable Controls 
    - Jump Physics
        - Gravity
    - Collision Physics
    - Collectable Items
        - Abilities
*/

static const char* vertex_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                                   \n"
"uniform mat4 uModelMat;                                               \n"
"uniform mat4 uViewMat;                                                \n"
"uniform mat4 uProjMat;                                                \n"
"void main() {                                                         \n"
"   gl_Position = uProjMat * uViewMat * uModelMat * vec4(aPos,1.0);    \n"
"}                                                                     \0";

static const char* fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                        \n"
"void main() {                                              \n"
"    FragColor = vec4(1.0,1.0,1.0,1.0);                     \n"
"}                                                          \0";

global_variable player_controller controller = {key_a, key_d, key_space};
global_variable game_object player = {0};

global_variable game_object mouse_follow = {0};

global_variable unsigned int shader_program = 0;
global_variable unsigned int u_model_loc = 0;
global_variable unsigned int u_view_mat = 0;
global_variable camera main_cam = {0};

#endif//__METROIDVANIA_H__