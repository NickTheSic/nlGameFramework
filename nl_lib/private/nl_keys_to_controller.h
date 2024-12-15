#ifndef __NL_KEYS_TO_CONTROLLER_H__
#define __NL_KEYS_TO_CONTROLLER_H__

#include "nl_controller_buttons.h"

// TODO: Create better input handling that specifically handles KB/M and Controller support for specific platforms
// Probably requires the game controlls to be setup in a way that I can call the required function from the input

// This is some basic glue so I can have homebrew controls froms the keyboard/mouse input controls
// TODO: Decide if this should be a platform console only header first

#define nl_key unsigned int

#define key_up NL_GAMEPAD_D_UP
#define key_left NL_GAMEPAD_D_LEFT
#define key_right NL_GAMEPAD_D_RIGHT
#define key_down NL_GAMEPAD_D_DOWN

#define key_w NL_GAMEPAD_D_UP
#define key_a NL_GAMEPAD_D_LEFT
#define key_d NL_GAMEPAD_D_RIGHT
#define key_s NL_GAMEPAD_D_DOWN

#define key_space NL_GAMEPAD_A

#define key_was_pressed(k) was_button_pressed(0, k)

#endif//__NL_KEYS_TO_CONTROLLER_H__