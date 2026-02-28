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

int get_pressed_buttons(void)
{
    NL_UNIMPLEMENTED_FUNC;
    return 0;
}

unsigned char button_is_held(button_value_type button)
{
    NL_UNUSED(button);
    NL_UNIMPLEMENTED_FUNC
    return 0;
}

unsigned char button_was_pressed(button_value_type button)
{
    NL_UNUSED(button);
    NL_UNIMPLEMENTED_FUNC
    return 0;
}

unsigned char button_was_released(button_value_type button)
{
    NL_UNUSED(button);
    NL_UNIMPLEMENTED_FUNC
    return 0;
}

void debug_test_controller(void)
{
    NL_UNIMPLEMENTED_FUNC;
}

float get_right_trigger(void)
{
    NL_UNIMPLEMENTED_FUNC
    return 0;
}

float get_left_trigger(void)
{
    NL_UNIMPLEMENTED_FUNC
    return 0;
}

v2f get_left_stick(void)
{
    NL_UNIMPLEMENTED_FUNC
    return (v2f){0,0};
}

v2f get_right_stick(void)
{
    NL_UNIMPLEMENTED_FUNC
    return (v2f){0,0};
}

