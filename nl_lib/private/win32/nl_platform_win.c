#include "../nl_platform.h"
#include <nl_lib.h>

int platform_init(void)
{
    initialize_global_bump_allocators(MB(10), MB(1));

    if (!initialize_window(1280,800, "Sandbox Mode"))
    {
        NL_LOG("NL_PLATFORM: Failed to initialize window");
        return 0;
    }

    if (!init_gamepad_system())
    {
        NL_LOG("NL_PLATFORM: Failed to initialize gamepad system");
        return 0;
    }

    if (init_audio_system() == 0)
    {
        NL_LOG("NL_PLATFORM: Failed to initialize audio system");
        return 0;
    }

    if (!initialize_renderer_subsystem())
    {
        NL_LOG("NL_PLATFORM: Failed to initialize renderer subsystem");
        return 0;
    }

#if NL_DEBUG_ENABLED
    init_random_number_generator(80); NL_LOG("NL_PLATFORM: Using 80 as debug random seed");
#else
    const time_t random_seed = time(NULL);
    init_random_number_generator(random_seed); NL_LOG("NL_PLATFORM: Random Seed: %ld", random_seed);
#endif
    
    init_delta_time();

    return 1;
}

void platform_cleanup(void)
{
    cleanup_audio_system();
    free_global_bump_allocators();
}
