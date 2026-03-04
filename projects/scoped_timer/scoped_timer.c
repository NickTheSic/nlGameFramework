#include "nl_lib.h"

#include "private/win32/nl_win32_include.h"

typedef struct scope_timer scope_timer;
struct scope_timer
{
    const char* name;
    double ms;
};

internal_function double temp_get_system_time()
{
    unsigned __int64 freq;
    unsigned __int64 time;

    QueryPerformanceFrequency( (LARGE_INTEGER*)&freq); //Note: Only need this once, could be init?
    QueryPerformanceCounter( (LARGE_INTEGER*)&time);

    double time_seconds = (double)time / freq;

    return time_seconds;
}

void end_scope_timer(scope_timer* const st)
{
    st->ms = temp_get_system_time() - st->ms;
    NL_LOG("%s: %f", st->name, st->ms);
}

#define SCOPED_TIMER(label) \
scope_timer scope_##__LINE__ __attribute__((cleanup(end_scope_timer))) = {label};\
scope_##__LINE__.ms = temp_get_system_time();


void app_specific_init(void)
{
    SCOPED_TIMER("Called Begin");

    {
        SCOPED_TIMER("Nest 1");
        {
            SCOPED_TIMER("Nest 2");
        }
    }
    
    {
        SCOPED_TIMER("Nest 3");
    }
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

}