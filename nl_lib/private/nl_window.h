#ifndef __NL_WINDOW_H__
#define __NL_WINDOW_H__

typedef void (*PFNWINDOWSIZECALLBACK)(int width, int height);

int initialize_window(int width, int height, const char* title);
void poll_events(void);
int window_active(void);
void window_request_close(void);
void window_swap_buffers(void);

v2i get_screen_size(void);

void set_window_title(const char* title);

void set_window_size_callback(PFNWINDOWSIZECALLBACK callback);

#endif // __NL_WINDOW_H__