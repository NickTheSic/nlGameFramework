#include "nl_lib.h"

global_variable float total_time = {0.0f};

void app_specific_init(void)
{
    NL_LOG("Hello, World!");
}

void app_specific_update(double dt)
{
    total_time += (float)dt;
    NL_LOG("Frame: %f, total: %f", dt, total_time);

    debug_test_controller();
}

void app_specific_render(void){}
void app_specific_cleanup(void){}
