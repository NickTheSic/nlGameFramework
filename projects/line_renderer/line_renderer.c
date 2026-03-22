#include "nl_lib.h"
#include "nl_rr_linerenderer.h"

#include "private/gl/nl_gl.h"

nl_rr_linerenderer line_renderer = {0};

v3f positions[50] = {0};
int current_pos = 0;
int max_positions = 0;

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

        float half_w = (float)screen.x * 0.5f;
        float half_h = (float)screen.y * 0.5f;
        
        positions[current_pos].x = ((float)mouse.x-half_w)/half_w;
        positions[current_pos].y = ((float)mouse.y-half_h)/half_h;
        v3f storage = positions[current_pos];
        
        NL_LOG("Mouse X: %i Y: %i After X: %f, Y %f", mouse.x, mouse.y, storage.x, storage.y);

        current_pos++;
        if (current_pos >= 50)
        {
            current_pos -= 50;
        }

        max_positions++;
        if (max_positions>50) {max_positions = 50;}
    }
}

void app_specific_render(void)
{
    begin_linerender_draw(&line_renderer);
    add_linerender_line(&line_renderer, positions, max_positions);
    end_linerender_draw(&line_renderer);
}

void app_specific_cleanup(void)
{
    free_line_renderer(&line_renderer);
}

#include "nl_rr_linerenderer.c"