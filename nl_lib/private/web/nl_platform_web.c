#include "../nl_platform.h"
#include <nl_lib.h>
#include <time.h>

int platform_init(void)
{
    if (!initialize_window(1280,800, "Sandbox Mode"))
    {
        NL_LOG("Failed to initialize window");
        return 0;
    }

    if (init_audio_system() == 0)
    {
        NL_LOG("Unable to intialize the audio system");
        return 0;
    }

    if (!initialize_renderer_subsystem())
    {
        NL_LOG("Unable to intialize renderer subsystem");
        return 0;
    }

    init_random_number_generator(time(NULL));
    init_delta_time();

    return 1;
}

void platform_cleanup(void)
{
    cleanup_audio_system();
    basic_memory_leak_check();
}
