#include "../nl_gamepad.h"
#include <ogc/pad.h>

global_variable int buttons_down_this_frame = 0;

int init_gamepad_system(void)
{
    PAD_Init();
    return 1;
}

void udpate_gamepad(void)
{
    PAD_ScanPads();
    // TODO: Do stuff involving was button pressed this frame or up this frame
    buttons_down_this_frame = PAD_ButtonsDown(0);
}

int get_pressed_buttons(int controller)
{
    return PAD_ButtonsDown(controller);
}

int is_button_pressed(int button)
{
    return buttons_down_this_frame & button;
}
