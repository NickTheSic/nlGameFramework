#include "nl_lib.h"
#include "nl_gl.h"

extern void app_specific_init();
extern void app_specific_update();

void run()
{
    poll_events();
    begin_render_frame();

    app_specific_update();
    
    end_render_frame();
}

int main(int count, char** args)
{
    if (!initialize_window(800,800, "Sandbox Mode"))
    {
        return -1;
    }

    if (!initialize_renderer_subsystem())
    {
        return -1;
    }
    set_background_colour_4f(0.4f,0.6f,0.8f,1.0f);

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
