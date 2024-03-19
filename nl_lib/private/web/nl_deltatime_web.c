#include "../nl_deltatime.h"

#include <emscripten.h>

global_variable double dt1 = 0;
global_variable double dt2 = 0;

void init_delta_time()
{
    dt1 = emscripten_performance_now();
    dt2 = dt1;
}

double get_frame_delta_time()
{
    dt2 = emscripten_performance_now();

    double time = (dt2 - dt1);
    dt1 = dt2;

    return time;
}

