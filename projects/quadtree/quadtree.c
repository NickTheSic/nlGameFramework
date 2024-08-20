#include "nl_lib.h"
#include "private/nl_gl.h"

typedef struct ball ball;
struct ball
{
    v2f position;
    float radius;
};

ball balls[100] = {0};

void app_specific_init(void)
{
    for (int i = 0; i < 100; ++i)
    {
        balls[i].position.x = random_float_in_range(0.f, 200.f);
        balls[i].position.y = random_float_in_range(0.f, 200.f);
        balls[i].radius     = random_float_in_range(0.f, 10.f);
    }
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{
    for (int i = 0; i < 100; ++i)
    {
        
    }
}

void app_specific_cleanup(void)
{
    
}