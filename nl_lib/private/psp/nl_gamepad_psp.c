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

int get_pressed_buttons(int controller)
{
    NL_UNUSED(controller)
    return controller.Buttons;
}

int is_button_pressed(int button)
{
    return controller.Buttons & button;
}
