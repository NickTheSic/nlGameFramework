#include "../nl_input.h"

// Global array?
nl_key key_states[NL_KEY_COUNT];

void set_key_state_down(nl_key k)
{
    set_key_state(k,1);
}

void set_key_state_up(nl_key k)
{
    set_key_state(k,0);
}

void set_key_state(nl_key k, int state)
{
    key_states[k] = state;
}

int is_key_down(nl_key k)
{
    return (key_states[k] == 1);
}

int is_key_up(nl_key k)
{
    return (key_states[k] == 0);
}
