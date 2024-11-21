#include "nl_lib.h"

void app_specific_init(void)
{
    NL_LOG("Hello, World!");
}
void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void){}
void app_specific_cleanup(void){}
