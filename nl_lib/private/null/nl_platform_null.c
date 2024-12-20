#include "private/nl_platform.h"

int platform_init(void)
{
    // We can compile with 0 and run but it shouldn't do much
    return 0;
}

void platform_cleanup(void)
{
    NL_UNIMPLEMENTED_FUNC
}
