#include "../nl_window.h"

int initialize_window(int width, int height, const char* title)
{
    return 1;
}

void poll_events()
{
    NL_UNIMPLEMENTED_FUNC
}

int window_active()
{
    return 1;
}

void window_request_close()
{
    NL_UNIMPLEMENTED_FUNC
}

void window_swap_buffers()
{
    NL_UNIMPLEMENTED_FUNC
}

v2i get_screen_size()
{
    return (v2i){0.0f,0.0f};
}

void set_window_title(const char* title)
{
    NL_UNIMPLEMENTED_FUNC
}
