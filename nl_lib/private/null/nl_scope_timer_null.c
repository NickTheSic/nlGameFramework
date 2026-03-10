#include "../nl_scope_timer.h"

#if NL_DEBUG_ENABLED

// Don't exactly need this but sure I can add it.
// This won't be working correct as DT is multiplied by 0.001

double debug_get_system_time()
{
    return 0;
}

void debug_end_scope_timer(debug_scope_timer* const st)
{
}

#endif