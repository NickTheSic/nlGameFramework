#include "../nl_gamepad.h"
#include <pspctrl.h>

global_variable SceCtrlData controller;

int init_gamepad_system(void)
{
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    return 1;
}

void udpate_gamepad()
{
    sceCtrlReadBufferPositive(&controller, 1);
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
