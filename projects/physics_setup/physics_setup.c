#include "nl_lib.h"
#include "private/nl_gl.h"

mesh square = {0};

void app_specific_init(void)
{
    generate_square_mesh(&square, 0.1f);
}

void app_specific_update(double dt)
{
    (void)dt;
}

void app_specific_render(void)
{
    render_single_mesh(&square);
}

void app_specific_cleanup(void)
{
    free_mesh(&square);
}