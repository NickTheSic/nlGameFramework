#ifndef __NL_GAMEPAD_H__
#define __NL_GAMEPAD_H__

// Based off gamecube and wii library to start

#define MAX_PLAYERS 4

int init_gamepad_system(void);
void cleanup_gamepad_system(void);

void udpate_gamepad(void);
int get_pressed_buttons(int);
int is_button_pressed(unsigned char controller_index, int button);

#endif//__NL_GAMEPAD_H__