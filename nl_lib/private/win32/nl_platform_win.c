#include "../nl_platform.h"
#include <nl_lib.h>

int platform_init(void)
{
    if (!initialize_window(1280,800, "Sandbox Mode"))
    {
        NL_LOG("Failed to initialize window");
        return 0;
    }

    if (!init_gamepad_system())
    {
        NL_LOG("Failed to initialize gamepad system");
        return 0;
    }

    if (init_audio_system() == 0)
    {
        NL_LOG("Failed to initialize audio system");
        return 0;
    }

    if (!initialize_renderer_subsystem())
    {
        NL_LOG("Failed to initialize renderer subsystem");
        return 0;
    }

    //init_random_number_generator(time(NULL));
    init_random_number_generator(80); NL_LOG("Not using random number as Seed");
    init_delta_time();

    return 1;
}

void platform_cleanup(void)
{
    cleanup_audio_system();
    basic_memory_leak_check();
}
