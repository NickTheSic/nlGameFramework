#include "../nl_gamepad.h"
#include <wiiuse/wpad.h>

#define GENERATE_UPDATE_STATE(var, sys_buttons, controller_button)\
    var.down_state = (sys_buttons & controller_button) != 0;\
    var.pressed = 0;\
    var.released = 0;\
    if (var.down_state != var.prev_state)\
    {\
        if(var.down_state)\
        {\
            var.pressed = (var.held == 0);\
            var.held = 1;\
        }\
        else\
        {\
            var.released = 1;\
            var.held = 0;\
        }\
    }\
    var.prev_state = var.down_state;

global_variable int buttons_down_this_frame[MAX_PLAYERS] = {0};

// The following is all but home button
// 0x0001      
// 0x0002      
// 0x0004      
// 0x0008      
// 0x0010      
// 0x0100      
// 0x0200      
// 0x0400      
// 0x0800      
// 0x1000      
// (0x0001<<16)
// (0x0002<<16)


int init_gamepad_system(void)
{
    WPAD_Init();
    return 1;
}

void udpate_gamepad(void)
{
    WPAD_ScanPads();
    
    for (unsigned char i = 0; i < MAX_PLAYERS; ++i)
    {
        buttons_down_this_frame[i] = WPAD_ButtonsDown(i);

        

    }
}

int get_pressed_buttons(unsigned char controller)
{
    return WPAD_ButtonsDown(controller);
}

int is_button_pressed(unsigned char controller_index, int button)
{
    return buttons_down_this_frame[controller_index] & button;
}
