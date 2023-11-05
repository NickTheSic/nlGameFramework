#include "../nl_deltatime.h"

#include <emscripten.h>

double dt1 = 0;
double dt2 = 0;

void init_delta_time()
{
    dt1 = emscripten_date_now();
    dt2 = dt1;
}

double get_frame_delta_time()
{
    dt2 = emscripten_date_now();

    double time = (dt2 - dt1)*0.001;
    dt1 = dt2;

    return time;
}

