#ifndef __METROIDVANIA_H__
#define __METROIDVANIA_H__

#include "player.h"

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

global_variable player_controller controller = {key_a, key_d, key_space};
global_variable game_object player = {0};
global_variable game_object ground = {0};
global_variable game_object mouse_follow = {0};

global_variable camera main_cam = {0};

#endif//__METROIDVANIA_H__