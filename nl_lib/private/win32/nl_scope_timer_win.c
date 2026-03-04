#include "../nl_scope_timer.h"
#include "nl_win32_include.h"

#if NL_DEBUG_ENABLED

double debug_get_system_time()
{
    unsigned __int64 freq;
    unsigned __int64 time;

    //Note: Only need Frequency once, could be init.
    // Also this is copied from the delta time in this stage
    QueryPerformanceFrequency( (LARGE_INTEGER*)&freq); 
    QueryPerformanceCounter( (LARGE_INTEGER*)&time);

    double time_seconds = (double)time / freq;

    return time_seconds;
}

void debug_end_scope_timer(debug_scope_timer* const st)
{
    st->ms = debug_get_system_time() - st->ms;
    NL_LOG("%s: %f", st->name, st->ms);
}

#endif
