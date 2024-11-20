#include "../nl_window.h"
#include <pspdebug.h>

int initialize_window(int width, int height, const char* title)
{
    NL_UNUSED(width); NL_UNUSED(height); NL_UNUSED(title);

    // Not necessisarily debug screen though...
    pspDebugScreenInit();

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
    return (v2i){SCREEN_WIDTH,SCREEN_HEIGHT};
}

void set_window_title(const char* title)
{
    NL_UNUSED(title);
    NL_UNIMPLEMENTED_FUNC;
}
