#include "nl_lib.h"

// TODO: Add an actual timer to the scope timer and thn

typedef struct scope_timer scope_timer;
struct scope_timer
{
    const char* name;
};

void end_scope_timer(scope_timer* const st)
{
    NL_LOG("%s", st->name);
}

#define SCOPED_TIMER(label) \
scope_timer scope_##__LINE__ __attribute__((cleanup(end_scope_timer))) = {label};

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