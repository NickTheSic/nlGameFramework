#include "../nl_window.h"

// Avoid link errors for null platforms
PFNWINDOWSIZECALLBACK pfn_window_size_callback;

int initialize_window(int width, int height, const char* title)
{
    NL_UNUSED(width); NL_UNUSED(height); NL_UNUSED(title);
    NL_UNIMPLEMENTED_FUNC;
    return 1;
}

void poll_events(void)
{
    NL_UNIMPLEMENTED_FUNC;
}

int window_active(void)
{
    NL_UNIMPLEMENTED_FUNC;
    return 1;
}

void window_request_close(void)
{
    NL_UNIMPLEMENTED_FUNC;
}

void window_swap_buffers(void)
{
    NL_UNIMPLEMENTED_FUNC;
}

v2i get_screen_size(void)
{
    NL_UNIMPLEMENTED_FUNC;
    return (v2i){0,0};
}

void set_window_title(const char* title)
{
    NL_UNUSED(title);
    NL_UNIMPLEMENTED_FUNC;
}
