#include "nl_lib.h"
#include "sprite_batch.h"

render_batch_2d sprite_renderer = {0};

void app_specific_init(void)
{
    init_render_batch_2d(&sprite_renderer, 10);
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

#include "sprite_batch.c"
