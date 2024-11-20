#include "../nl_window.h"
#include "../nl_debug.h"
#include "nl_psp_include.h"
#include <pspdebug.h>
#include <pspkernel.h>

// Unused... 
// Guess I should have set function that does nothing so I don't have extern variables
PFNWINDOWSIZECALLBACK pfn_window_size_callback;

int running = {1};

internal_function int exit_callback(int arg1, int arg2, void *common) 
{
    NL_UNUSED(arg1); NL_UNUSED(arg2); NL_UNUSED(common);
    running = 0;
    return 0;
}

internal_function int callback_thread(SceSize args, void *argp) 
{
    NL_UNUSED(args); NL_UNUSED(argp);

    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

internal_function int setup_callbacks(void) 
{
    int thid = sceKernelCreateThread("update_thread", callback_thread, 0x11, 0xFA0, 0, 0);
    if(thid >= 0)
        sceKernelStartThread(thid, 0, 0);
    
    return thid;
}

int initialize_window(int width, int height, const char* title)
{
    NL_UNUSED(width); NL_UNUSED(height); NL_UNUSED(title);

    setup_callbacks();

    return 1;
}

void poll_events(void)
{
    NL_UNIMPLEMENTED_FUNC;
}

int window_active(void)
{
    return running;
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
