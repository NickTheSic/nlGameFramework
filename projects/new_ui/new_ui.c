#include "nl_lib.h"

#include "nl_ui_renderer.h"

void app_specific_init(void)
{
    init_ui_renderer();
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
    cleanup_ui_renderer();
}

#include "nl_ui_renderer_gl.c"
