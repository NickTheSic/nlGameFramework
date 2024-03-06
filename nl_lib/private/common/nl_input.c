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

global_variable input_key_state mouse_button_states[NL_MOUSE_BUTTON_COUNT];
global_variable int input_mouse_scroll_delta = 0;
global_variable int input_mouse_scroll = 0;

global_variable v2i input_mouse_position = {0};

void update_input_frame_state(void)
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

    for (int i = 0; i < NL_MOUSE_BUTTON_COUNT; ++i)
    {
        mouse_button_states[i].pressed = 0;
		mouse_button_states[i].released = 0;
		if (mouse_button_states[i].down_state != mouse_button_states[i].prev_state)
		{
			if (mouse_button_states[i].down_state)
			{
				mouse_button_states[i].pressed = (mouse_button_states[i].held == 0);
				mouse_button_states[i].held = 1;
			}
			else
			{
				mouse_button_states[i].released = 1;
				mouse_button_states[i].held = 0;
			}
		}

		mouse_button_states[i].prev_state = mouse_button_states[i].down_state;
    }

    input_mouse_scroll = input_mouse_scroll_delta;
    input_mouse_scroll_delta = 0;
}


internal_function void set_key_state(nl_key k, int state)
{
    key_states[k].down_state = state;
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


internal_function void set_mouse_button_state(int mb, int state)
{
    mouse_button_states[mb].down_state = state;
}

void set_mouse_button_down(int mb)
{
    set_mouse_button_state(mb, 1);
}

void set_mouse_button_up(int mb)
{
    set_mouse_button_state(mb, 0);
}

int is_mouse_button_held(int mb)
{
    return (mouse_button_states[mb].held == 1);
}

int was_mouse_button_pressed(int mb)
{
    return (mouse_button_states[mb].pressed == 1);
}

int was_mouse_button_released(int mb)
{
    return (mouse_button_states[mb].released == 1);
}

void add_mouse_scroll(int val)
{
    input_mouse_scroll_delta = val;
}

int get_mouse_scroll_this_frame(void)
{
    return input_mouse_scroll;
}

void set_mouse_position_from_system(int x, int y)
{
    input_mouse_position.x = x;
    input_mouse_position.y = y;
}

v2i get_mouse_position_from_system(void)
{
    return input_mouse_position;
}
