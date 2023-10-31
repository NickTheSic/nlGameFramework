#include "nl_lib.h"
#include "nl_gl.h"

int main(int count, char** args)
{
    if (initialize_window(800,800, "Sandbox Mode") != 0)
    {
        return -1;
    }

    if (initialize_renderer_subsystem() != 0)
    {
        return -1;
    }
    set_background_colour_4f(0.4f,0.6f,0.8f,1.0f);

    while (window_active())
    {
        poll_events();
        begin_render_frame();
        
        

        end_render_frame();
    }

    return 0;
}
