#include "nl_lib.h"

#ifdef __EMSCRIPTEN__  
#include <emscripten.h>
#endif

extern void app_specific_init(void);
extern void app_specific_update(double dt);
extern void app_specific_render(void);
extern void app_specific_cleanup(void);

void run()
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

    	TimedLoop += dt;
    	if (TimedLoop > 1.f)
    	{
    		fps = (double)frameCount / TimedLoop;
    		TimedLoop -= 1.f;
    		frameCount = 0;
            
            char c[50];
            sprintf(c, "FPS: %f\n", fps);
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

    // Consistent seed for testing
    init_random_number_generator(80);
    //init_random_number_generator(time(NULL));

    if (!initialize_window(800,600, "Sandbox Mode"))
    {
        NL_LOG("Failed to initialize window");
        return -1;
    }

    if (!init_gamepad_system())
    {
        NL_LOG("Failed to initialize gamepad system");
        return -1;
    }

    if (init_audio_system() == 0)
    {
        return -1;
    }

    if (!initialize_renderer_subsystem())
    {
        return -1;
    }
    set_background_colour_4f(0.5f,0.5f,0.85f,1.0f);
    init_delta_time();

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
#ifndef GEKKO
    cleanup_audio_system();
#endif
    basic_memory_leak_check();

    return 0;
}
