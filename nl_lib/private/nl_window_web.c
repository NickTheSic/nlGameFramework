#include "../nl_window.h"
#include "../nl_renderer.h"

int initialize_window(int width, int height, const char* title)
{
    emscripten_set_window_title(title);
    emscripten_set_canvas_element_size("#canvas", width, height);

    //todo: Only plan to use webgl/egl on web so I think this is safe here
    EmscriptenWebGLContextAttributes attr = {};
    emscripten_webgl_init_context_attributes(&attr);
}

void poll_events(){/*intentionally empty*/}
int window_active(){/*intentionally empty*/}

void window_swap_buffers()
{
    // Unfortunately part of the window but the egl renderer I use will be the real swap.
    renderer_swap_buffers();
}