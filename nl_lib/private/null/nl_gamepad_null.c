#include "../nl_gamepad.h"

int init_gamepad_system(void)
{
    NL_UNIMPLEMENTED_FUNC;
    return 1;
}

void udpate_gamepad(void)
{
    NL_UNIMPLEMENTED_FUNC;
}

int get_pressed_buttons(unsigned char controller)
{
    NL_UNUSED(controller);
    NL_UNIMPLEMENTED_FUNC;
    return 0;
}

int is_button_pressed(unsigned char controller, int button)
{
    NL_UNUSED(controller);NL_UNUSED(button);
    NL_UNIMPLEMENTED_FUNC
    return 0;
}

int was_button_pressed(unsigned char controller, unsigned char button)
{
    NL_UNUSED(controller);NL_UNUSED(button);
    NL_UNIMPLEMENTED_FUNC
    return 0;
}

int was_button_released(unsigned char controller, unsigned char button)
{
    NL_UNUSED(controller);NL_UNUSED(button);
    NL_UNIMPLEMENTED_FUNC
    return 0;
}
