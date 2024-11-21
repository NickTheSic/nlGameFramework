#include "nl_lib.h"

//TODO: A Generic way for controllers to work
// I like the idea of setting a callback, but how would rebinding work
// get it working first then worry about details

void app_specific_init(void)
{

}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{

}

void app_specific_cleanup(void)
{
    
}