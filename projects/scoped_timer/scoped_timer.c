#include "nl_lib.h"

typedef struct scope_end scope_end;
struct scope_end
{
    const char* name;
    
};

void on_end_scope(scope_end* const se)
{
    NL_LOG("%s", se->name);
}

#define SCOPED_TEST(label) \
scope_end scope_##__LINE__ __attribute__((cleanup(on_end_scope))) = {label};

void app_specific_init(void)
{
    SCOPED_TEST("Called Begin");

    {
        SCOPED_TEST("Nest 1");
        {
            SCOPED_TEST("Nest 2");
        }
    }
    
    {
        SCOPED_TEST("Nest 3");
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