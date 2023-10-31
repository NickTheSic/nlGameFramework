#include "../nl_window.h"
#include "../nl_renderer.h"

#include <emscripten.h>
#include <emscripten/html5.h>

int initialize_window(int width, int height, const char* title)
{
    emscripten_set_window_title(title);
    emscripten_set_canvas_element_size("#canvas", width, height);

    return 0;
}

void poll_events(){/*intentionally empty*/}

// Web window is always active.  Can't use this in while loop and must run our update using callback
int window_active(){return 1;} 

void window_swap_buffers()
{
    // Unfortunately part of the window but the egl renderer I use will be the real swap.
    renderer_swap_buffers();
}