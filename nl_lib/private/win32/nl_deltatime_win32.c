#include "../nl_deltatime.h"

#include "nl_win32_include.h"

global_variable double global_previous_time = 0.0;

internal_function double get_system_time()
{
    unsigned __int64 freq;
    unsigned __int64 time;

    QueryPerformanceFrequency( (LARGE_INTEGER*)&freq);
    QueryPerformanceCounter( (LARGE_INTEGER*)&time);

    double time_seconds = (double)time / freq;

    return time_seconds;
}

void init_delta_time()
{
    global_previous_time = get_system_time();
}

double get_frame_delta_time()
{
    double time_seconds = get_system_time();
    double dt = time_seconds - global_previous_time;
    global_previous_time = time_seconds;   

    return dt;
}
