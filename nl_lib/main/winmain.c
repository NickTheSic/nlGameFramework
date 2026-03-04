#include "nl_lib.h"
#include <private/win32/nl_win32_include.h>
#include "private/nl_deltatime.h" // Only needed by main UNLESS we stop passing DT around and do it more like unity
#include "private/nl_platform.h" // Only main will use it, and it is just a simple function to initialize the platform

typedef struct win_fps_stats win_fps_stats
{
    float highest_fps = -1.0f;
    float lowest_fps = 54028234663.000000f; // a really big number higher than the average fps I have ever seen
};
global_variable win_fps_stats fps_stats;

extern void app_specific_init(void);
extern void app_specific_update(double dt);
extern void app_specific_render(void);
extern void app_specific_cleanup(void);


int WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nShowCmd
)
{
    NL_UNUSED(hInstance);NL_UNUSED(hPrevInstance);
    NL_UNUSED(lpCmdLine);NL_UNUSED(nShowCmd);

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

        // debug FPS
        {
            local_persist float TimedLoop;
        	local_persist int frameCount;
        	local_persist float fps;

        	TimedLoop += (float)(dt);
        	if (TimedLoop >= 1.f)
        	{
        		fps = (float)(frameCount) / TimedLoop;
        		TimedLoop -= 1.f;
        		frameCount = 0;

                fps_stats.highest_fps = fps_stats.highest_fps > fps ? fps_stats.highest_fps : fps;
                fps_stats.lowest_fps = fps_stats.lowest_fps < fps ? fps_stats.lowest_fps : fps;

                char c[50];
                sprintf_s(c, 50, "FPS: %f\n", fps);
                set_window_title(c);
        	}
        	frameCount++;
        }

        app_specific_update(dt);

        begin_render_frame();
        app_specific_render();
        end_render_frame();

        if (key_is_held(key_control) && key_was_pressed(key_c))
        {
            window_request_close();
        }
    
    }

    app_specific_cleanup();
    platform_cleanup();

    NL_LOG("Highest FPS Reached: %f", fps_stats.highest_fps);
    NL_LOG("Lowest FPS Reached: %f" , fps_stats.lowest_fps );

    return 0;
}
