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
    begin_ui_render();

    ui_element e = {0};
    e.color = COLOURF_RED;
    e.pos = (v2f){0.1f, 0.1f};
    e.size = (v2f){0.1f, 0.1f};

    DEBUG_add_elem(&e);

    end_ui_render();
}

void app_specific_cleanup(void)
{
    cleanup_ui_renderer();
}

#include "nl_ui_renderer_gl.c"
