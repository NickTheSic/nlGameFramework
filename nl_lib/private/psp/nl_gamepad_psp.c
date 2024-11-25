#include "../nl_gamepad.h"
#include "../nl_controller_state_defines.h"
#include <pspctrl.h>

global_variable SceCtrlData controller;

// I do believe that the implementation of psp sdk provides a way to get a Make or Break state which is what this is supposed to calculate
typedef struct gamepad_button_state gamepad_button_state;
struct gamepad_button_state
{
    union
    {
        struct
        {
            GENERATE_BUTTON_STATE_VARIABLES(select);
            GENERATE_BUTTON_STATE_VARIABLES(start);
            GENERATE_BUTTON_STATE_VARIABLES(dpad_up);
            GENERATE_BUTTON_STATE_VARIABLES(dpad_right);
            GENERATE_BUTTON_STATE_VARIABLES(dpad_down);
            GENERATE_BUTTON_STATE_VARIABLES(dpad_left);
            GENERATE_BUTTON_STATE_VARIABLES(ltrigger);
            GENERATE_BUTTON_STATE_VARIABLES(rtrigger);
            GENERATE_BUTTON_STATE_VARIABLES(triangle);
            GENERATE_BUTTON_STATE_VARIABLES(circle);
            GENERATE_BUTTON_STATE_VARIABLES(cross);
            GENERATE_BUTTON_STATE_VARIABLES(square);

            unsigned char stick_x, stick_y;
            // explicit padding
            unsigned char pad : 2;
        };
        unsigned long long int bytes;
    };  
};

global_variable gamepad_button_state controller_state = {0}; 

int init_gamepad_system(void)
{
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    return 1;
}

void udpate_gamepad()
{
    sceCtrlReadBufferPositive(&controller, 1);

    GENERATE_UPDATE_STATE(controller_state, controller.Buttons, PSP_CTRL_SELECT, select);
    GENERATE_UPDATE_STATE(controller_state, controller.Buttons, PSP_CTRL_START, start);
    GENERATE_UPDATE_STATE(controller_state, controller.Buttons, PSP_CTRL_UP, dpad_up);
    GENERATE_UPDATE_STATE(controller_state, controller.Buttons, PSP_CTRL_RIGHT, dpad_right);
    GENERATE_UPDATE_STATE(controller_state, controller.Buttons, PSP_CTRL_DOWN, dpad_down);
    GENERATE_UPDATE_STATE(controller_state, controller.Buttons, PSP_CTRL_LEFT, dpad_left);
    GENERATE_UPDATE_STATE(controller_state, controller.Buttons, PSP_CTRL_LTRIGGER, ltrigger);
    GENERATE_UPDATE_STATE(controller_state, controller.Buttons, PSP_CTRL_RTRIGGER, rtrigger);
    GENERATE_UPDATE_STATE(controller_state, controller.Buttons, PSP_CTRL_TRIANGLE, triangle);
    GENERATE_UPDATE_STATE(controller_state, controller.Buttons, PSP_CTRL_CIRCLE, circle);
    GENERATE_UPDATE_STATE(controller_state, controller.Buttons, PSP_CTRL_CROSS, cross);
    GENERATE_UPDATE_STATE(controller_state, controller.Buttons, PSP_CTRL_SQUARE, square);

    controller_state.stick_x = controller.Lx;
    controller_state.stick_y = controller.Ly;
}

int get_pressed_buttons(unsigned char controller_id)
{
    NL_UNUSED(controller_id)
    return controller.Buttons;
}

int is_button_pressed(unsigned char controller_index, int button)
{
    NL_UNUSED(controller_index);
    return controller.Buttons & button;
}

int was_button_pressed(unsigned char controller, unsigned char button)
{
    NL_UNUSED(controller);
    return (controller_state.bytes & ((unsigned long long)0x02 << (button*5))) != 0;
}

int was_button_released(unsigned char controller, unsigned char button)
{
    NL_UNUSED(controller);
    return (controller_state.bytes & ((unsigned long long)0x04 << (button*5))) != 0;
}
