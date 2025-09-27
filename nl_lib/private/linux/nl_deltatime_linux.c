#include "../nl_deltatime.h"
#include <time.h>
#include <sys/time.h>

global_variable struct timeval start ={0};
global_variable unsigned int prev_ticks = 0;

void init_delta_time()
{
    gettimeofday(&start, NULL);
}

double get_frame_delta_time()
{
    struct timeval now;
    gettimeofday(&now, NULL);

    unsigned int ticks = (now.tv_sec-start.tv_sec)*1000+(now.tv_usec-start.tv_usec)/1000;
    double dt = (double)(ticks - prev_ticks) / 1000.0f;
    prev_ticks = ticks;
    return dt;
}