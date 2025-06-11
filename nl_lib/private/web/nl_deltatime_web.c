#include "../nl_deltatime.h"
#include <emscripten.h>

global_variable double global_deltatime_1 = 0;
global_variable double global_deltatime_2 = 0;

void init_delta_time()
{
    global_deltatime_1 = emscripten_performance_now();
    global_deltatime_2 = global_deltatime_1;
}

double get_frame_delta_time()
{
    global_deltatime_2 = emscripten_performance_now();

    double time = (global_deltatime_2 - global_deltatime_1) * 0.001; 
    global_deltatime_1 = global_deltatime_2;

    return time;
}

