#include "../nl_gamepad.h"
#include "../nl_controller_state_defines.h"
#include <pspctrl.h>

global_variable SceCtrlData controller = {0};

// I do believe that the implementation of psp sdk provides a way to get a Make or Break state which is what this is supposed to calculate
typedef union gamepad_button_state gamepad_button_state;
union gamepad_button_state
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
        
        // explicit padding
        unsigned char pad : 4;
    };
    unsigned long long int bytes;
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
}

int get_pressed_buttons(void)
{
    return controller.Buttons;
}

unsigned char button_is_held(button_value_type button)
{
    return (controller_state.bytes & ((unsigned long long)0x01 << (button*5))) != 0;
}

unsigned char button_was_pressed(button_value_type button)
{
    return (controller_state.bytes & ((unsigned long long)0x02 << (button*5))) != 0;
}

unsigned char button_was_released(button_value_type button)
{
    return (controller_state.bytes & ((unsigned long long)0x04 << (button*5))) != 0;
}


#define PRINT_BUTTON_PRESS_RELEASE(button)\
{if (button_was_pressed(button)){NL_LOG(#button" pressed");}\
else if (button_was_released(button)){NL_LOG(#button" pressed");}}

void debug_test_controller(void)
{
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_DPAD_UP     );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_DPAD_DOWN   );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_DPAD_LEFT   );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_DPAD_RIGHT  );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_START       );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_SELECT      );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_L           );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_R           );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_A           );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_B           );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_X           );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_Y           );
}
