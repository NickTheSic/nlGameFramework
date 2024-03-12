#include "nl_lib.h"

#include "nl_ui_renderer.c"

static ui_renderer ui_batch = {0};

void winsizecbk(int width, int height)
{
   update_ui_screen_size(&ui_batch, width, height);
}

void app_specific_init(void)
{
    init_ui_renderer(&ui_batch);
    
    pfn_window_size_callback = &winsizecbk;
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);
}

void app_specific_update(double dt)
{
    (void)dt;

    begin_ui_render_batch(&ui_batch);

    const ui_element elem1 = {
        {1.0f,0.5f,0.2f, 1.0f},
        {20.0f,80.0f},
        {30.0f, 20.0f},
        {0.0f,0.0f},
        {0.0f} 
    };

    v2i mouse_pos = get_mouse_position_from_system();

    const ui_element elem2 = {
        {0.0f,0.5f,0.2f, 1.0f},
        {(float)mouse_pos.x, (float)mouse_pos.y},
        {5.0f, 5.0f},
        {0.0f,0.0f},
        {0.0f} 
    };

    add_element_to_render_batch(&ui_batch, &elem1);
    add_element_to_render_batch(&ui_batch, &elem2);

    end_ui_render(&ui_batch);
}

void app_specific_cleanup()
{
    cleanup_ui_renderer(&ui_batch);
}