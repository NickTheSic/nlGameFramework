#include "nl_lib.h"

extern void app_specific_init(void);
extern void app_specific_update(double dt);
extern void app_specific_render(void);
extern void app_specific_cleanup(void);

int main(int count, char** args)
{
    NL_UNUSED(count);NL_UNUSED(args);

    if (platform_init() == 0)
    {
        NL_LOG("Failed to initialize platform layer");
    }

    set_background_colour_4f(0.5f,0.5f,0.5f,1.0f);
    app_specific_init();

    while (window_active())
    {
        poll_events();
        update_input_frame_state();
        udpate_gamepad();

        double dt = get_frame_delta_time();

        app_specific_update(dt);

        begin_render_frame();
        app_specific_render();
        end_render_frame();
    }

    app_specific_cleanup();
    platform_cleanup();

    return 0;
}
