#include "nl_lib.h"

#ifdef __EMSCRIPTEN__  
#include <emscripten.h>
#endif

extern void app_specific_init(void);
extern void app_specific_update(double dt);
extern void app_specific_cleanup(void);

void run()
{
    poll_events();
    update_input_frame_state();
    
    begin_render_frame();

    double dt = get_frame_delta_time();

    app_specific_update(dt);
    
    end_render_frame();
}

int main(int count, char** args)
{
    (void)count;(void)args;
    
    if (!initialize_window(800,800, "Sandbox Mode"))
    {
        return -1;
    }

    if (!initialize_renderer_subsystem())
    {
        return -1;
    }
    set_background_colour_4f(0.85f,0.85f,0.85f,1.0f);
    init_delta_time();

    app_specific_init();

#ifdef _WIN32
    while (window_active())
    {
        run();
    }
#elif defined(__EMSCRIPTEN__)
    emscripten_set_main_loop(run, 0, 1);
#endif

    app_specific_cleanup();

    basic_memory_leak_check();

    return 0;
}
