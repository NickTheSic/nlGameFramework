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

int is_button_down(button_value_type button);
int was_button_pressed(button_value_type button);
int was_button_released(button_value_type button);


#ifdef __cplusplus
}
#endif

#endif//__NL_GAMEPAD_H__