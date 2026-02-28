#include "nl_lib.h"

// A Project for getting back into things and testing what I already have written.


int *test_ptr = 0;

void app_specific_init(void)
{
    test_ptr = memory_allocate(sizeof(int));
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);

    debug_test_controller();
}

void app_specific_render(void)
{

}

void app_specific_cleanup(void)
{
    memory_free(test_ptr);
}