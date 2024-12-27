#ifndef __NL_GAMEPAD_H__
#define __NL_GAMEPAD_H__

#include "nl_controller_buttons.h"

#ifdef __cplusplus
extern "C" {
#endif


int init_gamepad_system(void);
void cleanup_gamepad_system(void);

void udpate_gamepad(void);
int get_pressed_buttons(void);

unsigned char button_is_held(button_value_type button);
unsigned char button_was_pressed(button_value_type button);
unsigned char button_was_released(button_value_type button);


// To print the current state of pressed and released
void debug_test_controller(void);


#ifdef __cplusplus
}
#endif

#endif//__NL_GAMEPAD_H__