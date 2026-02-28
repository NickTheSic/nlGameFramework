#ifndef __NL_GAMEPAD_H__
#define __NL_GAMEPAD_H__

#include "nl_controller_buttons.h"
#include "nl_math.h" 

#ifdef __cplusplus
extern "C" {
#endif

// Might as well define the variable here.  
// Maybe in the future the player can modify it
global_variable float default_stick_dead_zone = 0.01;

int init_gamepad_system(void);
void cleanup_gamepad_system(void);

void udpate_gamepad(void);
int get_pressed_buttons(void);

unsigned char button_is_held(button_value_type button);
unsigned char button_was_pressed(button_value_type button);
unsigned char button_was_released(button_value_type button);

float get_right_trigger(void);
float get_left_trigger(void);
v2f get_left_stick(void);
v2f get_right_stick(void);

// To print the current state of pressed and released
void debug_test_controller(void);

#ifdef __cplusplus
}
#endif

#endif//__NL_GAMEPAD_H__