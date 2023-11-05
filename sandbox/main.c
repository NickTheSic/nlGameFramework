#include "nl_lib.h"
#include "nl_gl.h"

extern void app_specific_init(void);
extern void app_specific_update(double dt);

void run()
{
    poll_events();
    begin_render_frame();

    double dt = get_frame_delta_time();
    // NL_LOG("Delta Time: %f", dt);
    // NL_LOG("1/60: %f", 1.0/60.0);

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
    set_background_colour_4f(0.4f,0.6f,0.8f,1.0f);
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

    return 0;
}
