#ifndef __NL_INPUT_H__
#define __NL_INPUT_H__

#include "nl_keys.h"
#include "nl_math.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NL_MOUSE_BUTTON_LEFT 0
#define NL_MOUSE_BUTTON_RIGHT 1
#define NL_MOUSE_BUTTON_MIDDLE 2
#define NL_MOUSE_BUTTON_COUNT 3

void update_input_frame_state(void);

void set_key_state_down(nl_key k);
void set_key_state_up(nl_key k);

int is_key_held(nl_key k);
int was_key_pressed(nl_key k);
int was_key_released(nl_key k);

// Works if I don't reset to 0.  Use case was for rebinding a key
int get_last_key_pressed(void);


void set_mouse_button_down(int mb);
void set_mouse_button_up(int mb);

int is_mouse_button_held(int mb);
int was_mouse_button_pressed(int mb);
int was_mouse_button_released(int mb);

void add_mouse_scroll(int val);
int get_mouse_scroll_this_frame(void);

void set_mouse_position_from_system(int x, int y);
v2i get_mouse_position_from_system(void);

#ifdef __cplusplus
}
#endif
#endif //__NL_INPUT_H__