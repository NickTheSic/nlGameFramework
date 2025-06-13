#include "nl_lib.h"
#include "private/nl_deltatime.h" // Game does use this, just uses DT we pass it
#include "private/nl_platform.h"  // Contains platform agnostic calls.
#include <emscripten.h>

EM_JS(bool, verify_site, (), {
    if (document.location.host == 'html-classic.itch.zone' || document.location.host == 'localhost:6931'){
        return true;
    }
        
    alert('This game can only be played at: https://nickthesic.itch.io');
    throw 'Please Visit https://nickthesic.itch.io';
    return false;
});

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

    // Debug
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
            
            char c[50];
            sprintf(c, "FPS: %f\n", fps);
            set_window_title(c);
    	}
    	frameCount++;
    }

    app_specific_update(dt);

    begin_render_frame();
    app_specific_render();
    end_render_frame();
}

int main(int count, char** args)
{
    NL_UNUSED(count);NL_UNUSED(args);

    if (!verify_site())
    {
        NL_LOG("Failed to verify the correct website!");
        return 1;
    }

    if (platform_init() == 0)
    {
        NL_LOG("Failed to initialize platform layer");
    }

    set_background_colour_4f(0.5f,0.5f,0.5f,1.0f);
    app_specific_init();

    emscripten_set_main_loop(run, 0, 1);
    // I don't believe that functions after this are called
    // According to the documentation we should not be closing 

    app_specific_cleanup();
    platform_cleanup();

    return 0;
}
