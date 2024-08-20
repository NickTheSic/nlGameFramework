#ifndef __METROIDVANIA_H__
#define __METROIDVANIA_H__

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

typedef struct game_object game_object;
struct game_object
{
    mesh mesh;
    v2f pos;
    float vertical_speed;
    float width;

    char is_grounded;
};

typedef struct player_controller player_controller; 
struct player_controller
{
    nl_key left;
    nl_key right;
    nl_key jump;
};

static const char* vertex_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                                   \n"
"layout (location = 1) in vec4 aColor;                                 \n"
"uniform mat4 uModelMat;                                               \n"
"uniform mat4 uViewMat;                                                \n"
"uniform mat4 uProjMat;                                                \n"
"out vec4 oColor;                                                      \n"
"void main() {                                                         \n"
"   gl_Position = uProjMat * uViewMat * uModelMat * vec4(aPos,1.0);    \n"
"   oColor = aColor;                                                   \n"
"}                                                                     \0";

static const char* fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                        \n"
"in vec4 oColor;                                            \n"
"void main() {                                              \n"
"    FragColor = oColor;                                    \n"
"}                                                          \0";


#endif//__METROIDVANIA_H__