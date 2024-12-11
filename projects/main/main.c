#include "nl_lib.h"

#ifdef __EMSCRIPTEN__  
#include <emscripten.h>
#include <time.h>
#endif

global_variable float highest_fps = -1.0f;
global_variable float lowest_fps = 54028234663.000000f; // a really big number higher than the average fps I have ever seen

extern void app_specific_init(void);
extern void app_specific_update(double dt);
extern void app_specific_render(void);
extern void app_specific_cleanup(void);

internal_function void run()
{
    poll_events();
    update_input_frame_state();
    udpate_gamepad();
    
    double dt = get_frame_delta_time();

#if !NOT_YET_IMPLEMENTED
    // debug FPS
    {
        static float TimedLoop;
    	static int frameCount;
    	static float fps;

    	TimedLoop += (float)(dt);
    	if (TimedLoop >= 1.f)
    	{
    		fps = (float)(frameCount) / TimedLoop;
    		TimedLoop -= 1.f;
    		frameCount = 0;

            highest_fps = highest_fps > fps ? highest_fps : fps;
            lowest_fps = lowest_fps < fps ? lowest_fps : fps;
            
            char c[50];
            #ifdef __WIN32
            sprintf_s(c, 50, "FPS: %f\n", fps);
            #else
            sprintf(c, "FPS: %f\n", fps);
            #endif
            set_window_title(c);
    	}
    	frameCount++;
    }
#endif

    app_specific_update(dt);

    begin_render_frame();
    app_specific_render();
    end_render_frame();

#if !defined CANNOT_EXIT_MAIN_LOOP
    if (key_is_held(key_control) && key_was_pressed(key_c))
    {
        window_request_close();
    }
#endif
}

int main(int count, char** args)
{
    NL_UNUSED(count);NL_UNUSED(args);

    if (platform_init() == 0)
    {
        NL_LOG("Failed to initialize platform layer");
    }

    set_background_colour_4f(0.5f,0.5f,0.5f,1.0f);
    app_specific_init();

#if defined(__EMSCRIPTEN__)
    emscripten_set_main_loop(run, 0, 1);
#else
    while (window_active())
    {
        run();   
    }
#endif

    app_specific_cleanup();
    platform_cleanup();

    NL_LOG("Highest FPS Reached: %f", highest_fps);
    NL_LOG("Lowest FPS Reached: %f", lowest_fps);

    return 0;
}
