#include "../nl_gamepad.h"
#include <ogc/pad.h>

global_variable int buttons_down_this_frame[MAX_PLAYERS] = {0};

int init_gamepad_system(void)
{
    PAD_Init();
    return 1;
}

void udpate_gamepad(void)
{
    PAD_ScanPads();
    
    for (unsigned char i = 0; i < MAX_PLAYERS; ++i)
    {
        buttons_down_this_frame[i] = PAD_ButtonsDown(i);
    }
}

int get_pressed_buttons(unsigned char controller)
{
    return PAD_ButtonsDown(controller);
}

int is_button_pressed(unsigned char controller_index, int button)
{
    return buttons_down_this_frame[controller_index] & button;
}
