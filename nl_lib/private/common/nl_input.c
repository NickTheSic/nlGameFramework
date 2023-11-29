#include "../nl_input.h"
#include "../nl_debug.h"

typedef struct  input_key_state input_key_state;
struct input_key_state
{
    unsigned char held : 1;
    unsigned char pressed : 1;
    unsigned char released : 1;

    unsigned char down_state : 1;
    unsigned char prev_state : 1;

    // explicit padding
    unsigned char pad : 3;
};

global_variable input_key_state key_states[NL_KEY_COUNT];
global_variable int last_key_pressed = 0;

void update_input_frame_state()
{
    for (int i = 0; i < NL_KEY_COUNT; ++i)
    {
        key_states[i].pressed = 0;
		key_states[i].released = 0;
		if (key_states[i].down_state != key_states[i].prev_state)
		{
			if (key_states[i].down_state)
			{
				key_states[i].pressed = (key_states[i].held == 0);
                last_key_pressed = i;
				key_states[i].held = 1;
			}
			else
			{
				key_states[i].released = 1;
				key_states[i].held = 0;
			}
		}

		key_states[i].prev_state = key_states[i].down_state;
    }
}

void set_key_state_down(nl_key k)
{
    set_key_state(k,1);
    last_key_pressed = k;
}

void set_key_state_up(nl_key k)
{
    set_key_state(k,0);
}

void set_key_state(nl_key k, int state)
{
    key_states[k].down_state = state;
}

int is_key_held(nl_key k)
{
    return (key_states[k].held == 1);
}

int was_key_pressed(nl_key k)
{
    return (key_states[k].pressed == 1);
}

int was_key_released(nl_key k)
{
    return (key_states[k].released == 1);
}

int get_last_key_pressed()
{
    return last_key_pressed;
}
