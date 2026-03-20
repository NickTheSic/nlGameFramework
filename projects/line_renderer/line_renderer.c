#include "nl_lib.h"
#include "nl_rr_linerenderer.h"

#include "private/gl/nl_gl.h"

nl_rr_linerenderer line_renderer = {0};

v3f positions[50];
int current_pos = 0;

void app_specific_init(void)
{
    init_line_renderer(&line_renderer);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);

    if (mouse_button_was_pressed(NL_MOUSE_BUTTON_LEFT))
    {
        v2i mouse = get_mouse_position_from_system();
        v2i screen = get_screen_size();

        NL_LOG("Mouse X: %i Y: %i Screen X: %i, Y %i", mouse.x, mouse.y, screen.x, screen.y);

        positions[current_pos].x = (float)mouse.x / (float)screen.x;
        positions[current_pos].y = (float)mouse.y / (float)screen.y;

        current_pos++;
    }
}

void app_specific_render(void)
{
    begin_linerender_draw(&line_renderer);


    add_linerender_line(&line_renderer, positions, current_pos);


    end_linerender_draw(&line_renderer);
}

void app_specific_cleanup(void)
{
    free_line_renderer(&line_renderer);
}

#include "nl_rr_linerenderer.c"