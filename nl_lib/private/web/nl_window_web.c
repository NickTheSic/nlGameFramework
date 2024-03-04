#include "../nl_window.h"
#include "../nl_renderer.h"
#include "../nl_input.h"
#include "../nl_debug.h"

#include <emscripten.h>
#include <emscripten/dom_pk_codes.h>
#include <emscripten/html5.h>

PFNWINDOWSIZECALLBACK pfn_window_size_callback = {0};

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

	NL_LOG("Key Code: %s, domPk code: %d", e->code, emscripten_compute_dom_pk_code(e->code));

	return EM_TRUE;
}

internal_function EM_BOOL mouse_callback(int event_type, const EmscriptenMouseEvent* e, void* user_data)
{
    NL_UNUSED(user_data);

	switch(e->button)
	{
		case 0:
		{
			if (event_type == EMSCRIPTEN_EVENT_MOUSEDOWN)
			{
				set_mouse_button_down(NL_MOUSE_BUTTON_LEFT);
			}
			else if (event_type == EMSCRIPTEN_EVENT_MOUSEUP)
			{
				set_mouse_button_up(NL_MOUSE_BUTTON_LEFT);
			}
		} break;

		case 2:
		{
			if (event_type == EMSCRIPTEN_EVENT_MOUSEDOWN)
			{
				set_mouse_button_down(NL_MOUSE_BUTTON_RIGHT);
			}
			else if (event_type == EMSCRIPTEN_EVENT_MOUSEUP)
			{
				set_mouse_button_up(NL_MOUSE_BUTTON_RIGHT);
			}
		} break;
	}

	return EM_FALSE;
}

internal_function EM_BOOL mouse_move_callback(int event_type, const EmscriptenMouseEvent* e, void* user_data)
{
	set_mouse_position_from_system(e->targetX, get_screen_size().y - e->targetY);
	return EM_FALSE;
}

v2i get_screen_size()
{
	v2i result = {0};
	emscripten_get_canvas_element_size("#canvas", &result.x, &result.y);
	return (result);
}

int initialize_window(int width, int height, const char* title)
{
    emscripten_set_window_title(title);
    emscripten_set_canvas_element_size("#canvas", width, height);

    emscripten_set_keydown_callback("#canvas", 0, 1, keyboard_callback);
	emscripten_set_keyup_callback("#canvas", 0, 1, keyboard_callback);
	
	emscripten_set_mouseup_callback("#canvas", 0, 1, mouse_callback);
	emscripten_set_mousedown_callback("#canvas", 0, 1, mouse_callback);

	emscripten_set_mousemove_callback("#canvas", 0, 1, mouse_move_callback);

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