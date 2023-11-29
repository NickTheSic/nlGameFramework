#include "../nl_window.h"
#include "../nl_renderer.h"
#include "../nl_input.h"
#include "../nl_debug.h"

#include <emscripten.h>
#include <emscripten/html5.h>

internal_function EM_BOOL keyboard_callback(int eventType, const EmscriptenKeyboardEvent* e, void* user_data)
{
    NL_UNUSED(user_data);

    if (eventType == EMSCRIPTEN_EVENT_KEYDOWN)
	{
		set_key_state_down((nl_key)emscripten_compute_dom_pk_code(e->code));
	}

	if (eventType == EMSCRIPTEN_EVENT_KEYUP)
	{
        set_key_state_up((nl_key)emscripten_compute_dom_pk_code(e->code));
	}

	return EM_TRUE;
}

internal_function EM_BOOL mouse_callback(int event_type, const EmscriptenMouseEvent* e, void* user_data)
{
    NL_UNUSED(user_data);

	if (e->button == 0) // left click
	{
		if (event_type == EMSCRIPTEN_EVENT_MOUSEDOWN)
		{
			
		}
		else if (event_type == EMSCRIPTEN_EVENT_MOUSEUP)
		{
			
		}
	}

	if (e->button == 2) // right click
	{
		if (event_type == EMSCRIPTEN_EVENT_MOUSEDOWN)
		{
			
		}
		else if (event_type == EMSCRIPTEN_EVENT_MOUSEUP)
		{
			
		}
	}

	return EM_FALSE;
}

int initialize_window(int width, int height, const char* title)
{
    emscripten_set_window_title(title);
    emscripten_set_canvas_element_size("#canvas", width, height);

    emscripten_set_keydown_callback("#canvas", 0, 1, keyboard_callback);
	emscripten_set_keyup_callback("#canvas", 0, 1, keyboard_callback);

    return 1;
}

void poll_events(){/*intentionally empty*/}

// Web window is always active.  Can't use this in while loop and must run our update using callback
int window_active(){return 1;} 

void window_swap_buffers()
{
    // Unfortunately part of the window but the egl renderer I use will be the real swap.
    renderer_swap_buffers();
}