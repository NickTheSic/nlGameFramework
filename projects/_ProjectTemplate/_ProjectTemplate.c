#include "nl_lib.h"

int *test_ptr = 0;

void app_specific_init(void)
{
    test_ptr = memory_allocate(sizeof(int));
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
    memory_free(test_ptr);
}