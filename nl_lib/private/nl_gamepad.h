#ifndef __NL_GAMEPAD_H__
#define __NL_GAMEPAD_H__

#include "nl_controller_buttons.h"

// Based off gamecube and wii library to start
// immediately not viable for psp nds etc with only one controller
#define MAX_PLAYERS 4

int init_gamepad_system(void);
void cleanup_gamepad_system(void);

void udpate_gamepad(void);
int get_pressed_buttons(unsigned char controller_id);
int is_button_pressed(unsigned char controller_index, int button);

#endif//__NL_GAMEPAD_H__