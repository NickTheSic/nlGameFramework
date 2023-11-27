#ifndef __NL_INPUT_H__
#define __NL_INPUT_H__

#include "nl_keys.h"

void set_key_state_on(nl_key k);
void set_key_state_off(nl_key k);

void set_key_state(nl_key key, int state);

int is_key_down(nl_key k);
int is_key_up(nl_key k);

#endif //__NL_INPUT_H__