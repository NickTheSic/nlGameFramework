#include "../nl_gamepad.h"
#include <ogc/pad.h>

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

typedef struct gamepad_input gamepad_input;
struct gamepad_input
{
        unsigned char held       : 1;
        unsigned char pressed    : 1;
        unsigned char released   : 1;
        unsigned char down_state : 1;
        unsigned char prev_state : 1;
        // explicit padding
        unsigned char pad : 3;
}; 
global_variable gamepad_input controller_states[MAX_PLAYERS][12] = {0}; 

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

        GENERATE_UPDATE_STATE(controller_states[i][0],  buttons_down_this_frame[i], 0x0001);
        GENERATE_UPDATE_STATE(controller_states[i][1],  buttons_down_this_frame[i], 0x0002);
        GENERATE_UPDATE_STATE(controller_states[i][2],  buttons_down_this_frame[i], 0x0004);
        GENERATE_UPDATE_STATE(controller_states[i][3],  buttons_down_this_frame[i], 0x0008);
        GENERATE_UPDATE_STATE(controller_states[i][4],  buttons_down_this_frame[i], 0x0010);
        GENERATE_UPDATE_STATE(controller_states[i][5],  buttons_down_this_frame[i], 0x0020);
        GENERATE_UPDATE_STATE(controller_states[i][6],  buttons_down_this_frame[i], 0x0040);
        GENERATE_UPDATE_STATE(controller_states[i][7],  buttons_down_this_frame[i], 0x0100);
        GENERATE_UPDATE_STATE(controller_states[i][8],  buttons_down_this_frame[i], 0x0200);
        GENERATE_UPDATE_STATE(controller_states[i][9],  buttons_down_this_frame[i], 0x0400);
        GENERATE_UPDATE_STATE(controller_states[i][10], buttons_down_this_frame[i], 0x0800);
        GENERATE_UPDATE_STATE(controller_states[i][11], buttons_down_this_frame[i], 0x1000);
    }
}

int get_pressed_buttons(unsigned char controller)
{
    return PAD_ButtonsDown(controller);
}

int was_button_pressed(unsigned char controller, unsigned char button)
{
    return controller_states[controller][button].pressed;
}

int was_button_released(unsigned char controller, unsigned char button)
{
    return controller_states[controller][button].released;
}