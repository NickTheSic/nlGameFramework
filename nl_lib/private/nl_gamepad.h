#ifndef __NL_GAMEPAD_H__
#define __NL_GAMEPAD_H__

// Based off gamecube and wii library 

int init_gamepad_system(void);
void udpate_gamepad(void);
int get_pressed_buttons(int);

int is_button_pressed(int button);

#endif//__NL_GAMEPAD_H__