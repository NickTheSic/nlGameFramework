#include "nl_lib.h"

int main(int count, char** args)
{
    if (initialize_window(800,800, "Now a Horror Game") != 0)
    {
        return -1;
    }

    if (initialize_renderer_subsystem() != 0)
    {
        return -1;
    }
    set_background_colour_4f(0.7f,0.5f,0.9f,1.0f);

    while (window_active())
    {
        poll_events();

        // game_update?

        begin_render_frame();
        // game_render?
        end_render_frame();
    }

    return 0;
}
