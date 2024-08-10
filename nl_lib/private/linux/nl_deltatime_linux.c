#include "../nl_deltatime.h"

global_variable double dt1 = 0;
global_variable double dt2 = 0;

void init_delta_time()
{
    dt1 = 1;
    dt2 = dt1;
}

double get_frame_delta_time()
{
    dt2 = dt1+1;

    double time = (dt2 - dt1) * 0.001; 
    dt1 = dt2;

    return time;
}
