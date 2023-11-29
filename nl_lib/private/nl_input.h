#ifndef __NL_INPUT_H__
#define __NL_INPUT_H__

#include "nl_keys.h"

void update_input_frame_state();

void set_key_state_on(nl_key k);
void set_key_state_off(nl_key k);

void set_key_state(nl_key key, int state);

int is_key_held(nl_key k);
int was_key_pressed(nl_key k);
int was_key_released(nl_key k);

// Works if I don't reset to 0.  Use case was for rebinding a key originally
nl_key get_last_key_pressed();


#endif //__NL_INPUT_H__