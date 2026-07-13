#include <private/nl_window.h>

int initialize_window(int width, int height, const char* title);

void poll_events(void);

int window_active(void);

void window_request_close(void);

void window_swap_buffers(void);

v2i get_screen_size(void);

void set_screen_size(int width, int height);

void set_screen_size_v2i(v2i new_size);

void set_window_title(const char* title);

void set_window_size_callback(PFNWINDOWSIZECALLBACK callback);

