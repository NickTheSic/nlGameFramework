#ifndef __NL_WINDOW_H__
#define __NL_WINDOW_H__

int initialize_window(int width, int height, const char* title);
void poll_events();
int window_active();
void window_swap_buffers();

v2i get_screen_size();

#endif // __NL_WINDOW_H__