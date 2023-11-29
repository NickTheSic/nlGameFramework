#ifndef __NL_INPUT_H__
#define __NL_INPUT_H__

#include "nl_keys.h"

#ifdef __cplusplus
extern "C" {
#endif


void update_input_frame_state();

void set_key_state_down(nl_key k);
void set_key_state_up(nl_key k);

void set_key_state(nl_key key, int state);

int is_key_held(nl_key k);
int was_key_pressed(nl_key k);
int was_key_released(nl_key k);

// Works if I don't reset to 0.  Use case was for rebinding a key
int get_last_key_pressed();

#ifdef __cplusplus
}
#endif
#endif //__NL_INPUT_H__