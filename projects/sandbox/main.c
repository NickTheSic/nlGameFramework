#include "nl_lib.h"

#ifdef __EMSCRIPTEN__  
#include <emscripten.h>
#include <time.h>

EM_JS(bool, verify_site, (), {
    if (document.location.host == 'html-classic.itch.zone' || document.location.host == 'localhost:6931'){
        return true;
    }
        
    alert('This game can only be played at: https://nickthesic.itch.io');
    throw 'Please Visit https://nickthesic.itch.io';
    return false;
});

#endif

extern void app_specific_init(void);
extern void app_specific_update(double dt);
extern void app_specific_render(void);
extern void app_specific_cleanup(void);

void run()
{
    poll_events();
    update_input_frame_state();
    
    double dt = get_frame_delta_time();
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

    init_random_number_generator(time(NULL));

    if (!initialize_window(500,300, "Sandbox Mode"))
    {
        NL_LOG("Failed to initialize window");
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
    set_background_colour_4f(0.5f,0.5f,0.5f,1.0f);
    init_delta_time();

    app_specific_init();

#if defined(__EMSCRIPTEN__)
    if (verify_site()) 
    {
        emscripten_set_main_loop(run, 0, 1);
    }
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
