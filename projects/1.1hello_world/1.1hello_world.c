#include "nl_lib.h"

global_variable float total_time = {0.0f};

void app_specific_init(void)
{
    NL_LOG("Hello, World!");
}

void app_specific_update(double dt)
{
    total_time+=dt;
    //NL_LOG("Frame: %f, total: %f", dt, total_time);

    // if (was_button_pressed(0, NL_GAMEPAD_A))
    // {
    //     static int count;
    //     NL_LOG("A Was Pressed! %d", count);
    // }

    // if (was_button_pressed(0, NL_GAMEPAD_B))
    // {
    //     static int count;
    //     NL_LOG("B Was Pressed! %d", count);
    // }

    // if (was_button_released(0, NL_GAMEPAD_Y))
    // {
    //     static int count;
    //     NL_LOG("Y Was Released! %d", count);
    // }

    // if (was_button_released(0, NL_GAMEPAD_DPAD_LEFT))
    // {
    //     static int count;
    //     NL_LOG("Left Was Released! %d", count);
    // }
}

void app_specific_render(void){}
void app_specific_cleanup(void){}
